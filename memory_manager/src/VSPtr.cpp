
#include <VSPtr.hpp>
#include <control.hpp>
#include <fstream>
#include <client.hpp>

using namespace std;


static unordered_map<int, Bucket*> ptr_map; /*HashMap that saves the data of the pointers.*/
static int server = 0;
static int id_num = 0;


g_collector *g_collector::getInstance(){
    if(gc_instance == nullptr){
        gc_instance = new g_collector();
    }
    return gc_instance;
}

int g_collector::generate_id(){
    id_num++;
    return id_num;
}

void g_collector::run_inspection(){
    for (pair<int, Bucket*> element : ptr_map){
	    if(element.second->getCount()->get() == 0){
            ptr_map.erase(element.first);
        }
    }
}

void g_collector::add_ptr(int id, Bucket* b){
    ptr_map[id] = b;
}

string getData(Bucket* b){
    if(dynamic_cast<BucketT<int>*>(b) != nullptr){   
        BucketT<int>* temp = dynamic_cast<BucketT<int>*>(b);
        return to_string(*temp->getPtr());
    }
    else if(dynamic_cast<BucketT<float>*>(b) != nullptr){   
        BucketT<float>* temp = dynamic_cast<BucketT<float>*>(b);
        return to_string(*temp->getPtr());
    }
    else if(dynamic_cast<BucketT<double>*>(b) != nullptr){   
        BucketT<double>* temp = dynamic_cast<BucketT<double>*>(b);
        return to_string(*temp->getPtr());
    }
    else if(dynamic_cast<BucketT<bool>*>(b) != nullptr){   
        BucketT<bool>* temp = dynamic_cast<BucketT<bool>*>(b);
        return *temp->getPtr() ? "true" : "false";
    }
    else if(dynamic_cast<BucketT<char>*>(b) != nullptr){   
        BucketT<char>* temp = dynamic_cast<BucketT<char>*>(b);
        string s = "";
        return s += *temp->getPtr();
    }
    else if(dynamic_cast<BucketT<string>*>(b) != nullptr){   
        BucketT<string>* temp = dynamic_cast<BucketT<string>*>(b);
        return *temp->getPtr();
    }
    else{
        return "Unknown";
    }
}

void g_collector::generate_data(){
    if(server == 0){
        ofstream myJson;
        myJson.open ("/home/simon/Cpp/VScode-memory-manager/memory_manager/src/ptr_data.json");

        string line = "[\n";
        for (pair<int, Bucket*> element : ptr_map){
            line += "    {\n";
            line += "         \"ID\" : \"" + to_string(element.first) + "\",\n";
            line += "         \"Tipo\" : \"" + element.second->getType() + "\",\n";
            line += "         \"Valor\" : \"" + getData(element.second) + "\",\n";
            line += "         \"Ubicacion\" : \"" + element.second->getDir() + "\",\n";
            line += "         \"Referencias\" : \"" + to_string(element.second->getCount()->get()) + "\"\n";
            line += "    },\n";
        }
        line.pop_back();
        line.pop_back();
        line = line + "\n]";
        myJson << line;
        myJson.close();
    }
    else{
        string line = "[\n";
        for (pair<int, Bucket*> element : ptr_map){
            line += "    {\n";
            line += "         \"ID\" : \"" + to_string(element.first) + "\",\n";
            line += "         \"Tipo\" : \"" + element.second->getType() + "\",\n";
            line += "         \"Valor\" : \"" + getData(element.second) + "\",\n";
            line += "         \"Ubicacion\" : \"" + element.second->getDir() + "\",\n";
            line += "         \"Referencias\" : \"" + to_string(element.second->getCount()->get()) + "\"\n";
            line += "    },\n";
        }
        line.pop_back();
        line.pop_back();
        line = line + "\n]";
        string resp = send_msg(line);
        if(resp == "User saved." || resp =="Valid user." || resp =="Incorrect user/password"){
            ofstream txt;
            txt.open ("/home/simon/Cpp/VScode-memory-manager/memory_manager/build/resp.txt");
            txt << line;
            txt.close();
        }else{
            ofstream myJson;
            myJson.open ("/home/simon/Cpp/VScode-memory-manager/memory_manager/build/srv_response.json");
            myJson << line;
            myJson.close();
        }
    }

}


void make_json(){
    g_collector::getInstance()->generate_data();
}


void gc_loop(){
    while(key){
        usleep(100000);
        g_collector::getInstance()->run_inspection();
    }
}

void g_collector_run(){
    string srv;
    ifstream myJson("/home/simon/Cpp/VScode-memory-manager/memory_manager/src/server.txt");
        srv.assign( (istreambuf_iterator<char>(myJson) ),
                (istreambuf_iterator<char>()    ) );
    myJson.close();
    if(srv.at(0) == '1'){
        string test = run_client();
        if(test == "error"){
            cout << "Server down, going back to local. " << endl;
        }else{
            cout << "Connected to server. " << endl;
            server = 1;
        }
    }
    key = true;
    th = thread(gc_loop);
}

void g_collector_close(){
    g_collector::getInstance()->generate_data();
    key = false;
    th.join();
}


//CLIENT///

int sock;

string run_client(){
    /**
     * @note Crea el socket
     */
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        return "error";
    }
    /**
     * @note Struct con la informacion del server
     */
    int port = 54000;
    string ipAddress = "127.0.0.1";

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    /**
     * @note Intenta conectar con el servidor
     */
    int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if(connectRes == -1){
        return "error";
    }

    char buf[4096];
    string server_s;
    /**
     * @note Espera por respuesta
     */
    memset(buf, 0, 4096);
    int bytesReceived = recv(sock, buf, 4096, 0);
    if (bytesReceived == -1){
        server_s = "error";
    }else{
        server_s = string(buf, bytesReceived);
    }

    return server_s;
}


string send_msg(string msg){
    char buf[4096];
    string userInput = msg;
    /**
     * @note Se envia al server
     */
    int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
    if(sendRes == -1){
        return "No se pudo enviar el mensaje\n";
    }
    /**
     * @note Espera por respuesta
     */
    memset(buf, 0, 4096);
    int bytesReceived = recv(sock, buf, 4096, 0);
    if (bytesReceived == -1){
        return "error";
    }else{
        /**
         * @note Retorna la respuesta
         */
        return string(buf, bytesReceived);
    }
}


void close_sock(){
    close(sock);
}

void save_user(){
    string msg = "user,";

    string iterator = "";
    string srv;
    ifstream myJson("/home/simon/Cpp/VScode-memory-manager/memory_manager/src/server.txt");
        srv.assign( (istreambuf_iterator<char>(myJson) ),
                (istreambuf_iterator<char>()    ) );
    myJson.close();
    int i = 2;
    while(srv[i] != '\n'){
        iterator = iterator + srv[i];
        i++;
    }
    i++;
    msg = msg + iterator + ",";
    iterator = "";
    while(srv[i] != '\n'){
        iterator = iterator + srv[i];
        i++;
    }
    msg = msg + iterator + ",";

    send_msg(msg);
}