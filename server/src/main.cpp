
#include <VSPtr.hpp>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <server.hpp>
#include "md5.h"
#include <VSPtr.hpp>

#include <control.hpp>
#include <fstream>
using namespace std;

int main(){

    run_server();
    return 0;
}

int run_server(){
    /**
     * @note Creates the socket.
     */
    
    int listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_socket == -1){
        cerr<<"Unable to create socket, closing..."<<endl;
        return -1;
    }

    /**
     * @note Links an IP and a port number to the socket.
     */
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
 
    bind(listen_socket, (sockaddr*)&hint, sizeof(hint));
    
    /**
     * @note Tells Winsock the socket is for listening.
     */
    listen(listen_socket, SOMAXCONN);
 
    /**
     * @note Waits a connection.
     */
    cout<<"Waiting client..."<<endl;
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
 
    int clientSocket = accept(listen_socket, (sockaddr*)&client, &clientSize);
 
    char host[NI_MAXHOST]; //Name of the client.
    char service[NI_MAXSERV]; //Where the clients connects to.
 
    memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);
 
    if(getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) ==0){
        cout<<host<<" conecting to port "<<service<<endl;
    }else{
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout<<host<<" conecting to port " <<ntohs(client.sin_port)<<endl;
    }
    
    /**
     * @note Close the socket for listening.
     */
    close(listen_socket);

    char buf[4096];

    /**
     * @note Information that will send back to the client.
     */
    string message = "";

    send(clientSocket, message.c_str(), message.size() + 1, 0);
    
    /**
     * @note Waits for client request.
     */
    while(true){
        memset(buf, 0, 4096);
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == -1){
            cerr<<"Error receiving the message"<<endl;
            break;
        }
 
        if (bytesReceived == 0){
            cout<<"Client desconected"<<endl;
            break;
        }
        /**
         * @note Data received.
         */
        string temp_s;
        temp_s = string(buf, 0, bytesReceived);

        string response = process(temp_s);
        
        send(clientSocket, response.c_str(), response.size() + 1, 0);
    }
    
    /**
     * @note Close the socket.
     */
    close(clientSocket);
    
    return 0;
}

string add_info(string ID, string type, string value, string key){
    string response;
    if(key=="add"){
        if(type == "int"){
            VSPtr<int> ptr = VSPtr<int>::New();
        }
        else if(type == "float"){
            VSPtr<float> ptr = VSPtr<float>::New();
        }
        else if(type == "double"){
            VSPtr<double> ptr = VSPtr<double>::New();
        }
        else if(type == "bool"){
            VSPtr<bool> ptr = VSPtr<bool>::New();
        }
        else if(type == "char"){
            VSPtr<char> ptr = VSPtr<char>::New();
        }
        else if(type == "string"){
            VSPtr<int> ptr = VSPtr<int>::New();
        }
        response = "added";
    }
    if(key=="copy"){
        find_ptr(stoi(ID));
    }
    if(key=="*"){
        if(type == "int"){
            response = get_ptr_int(stoi(ID));
        }
        else if(type == "float"){
            response = get_ptr_float(stoi(ID));        
        }
        else if(type == "double"){
            response = get_ptr_double(stoi(ID));        
        }
        else if(type == "bool"){
            response = get_ptr_bool(stoi(ID));        
        }
        else if(type == "char"){
            response = get_ptr_char(stoi(ID));
        }
        else if(type == "string"){
            response = get_ptr_string(stoi(ID));
        }
        else{
            response = "void";
        }
    }
    if(key=="set"){
        if(type == "int"){
            get_ptr_int(stoi(ID)) = stoi(value);
        }
        else if(type == "float"){
            get_ptr_float(stoi(ID)) = stoi(value);       
        }
        else if(type == "double"){
            get_ptr_double(stoi(ID)) = stoi(value);
        }
        else if(type == "char"){
            response = get_ptr_char(stoi(ID));
        }
        else if(type == "string"){
            response = get_ptr_string(stoi(ID));
        }
        else{
            response = "void";
        }
    }
}

string process(string temp_s){
    string ID, type, value, response;
    string iterator = "";
    int i = 0;
    while(temp_s[i] != ','){
        iterator = iterator + temp_s[i];
        i++;
    }
    i++;
    string key = iterator;
    iterator = "";
    
    if(key=="add" || key=="copy" || key=="*" || key == "set"){
        while(temp_s[i] != ','){
            iterator = iterator + temp_s[i];
            i++;
        }
        i++;
        ID = iterator;
        iterator = "";

        while(temp_s[i] != ','){
            iterator = iterator + temp_s[i];
            i++;
        }
        i++;
        type = iterator;
        iterator = "";

        while(temp_s[i] != ','){
            iterator = iterator + temp_s[i];
            i++;
        }
        i++;
        ID = iterator;
        iterator = "";
        response = add_info(ID, type, value, key);
    }
    else if(key == "user"){
        while(temp_s[i] != ','){
            iterator = iterator + temp_s[i];
            i++;
        }
        i++;
        string user = iterator;
        iterator = "";
        while(temp_s[i] != ','){
            iterator = iterator + temp_s[i];
            i++;
        }
        i++;
        string pass = iterator;
        iterator = "";
        save_user(user, pass);
        response = "User saved.";
    }
    else if(key == "check"){
        while(temp_s[i] != ','){
            iterator = iterator + temp_s[i];
            i++;
        }
        i++;
        string user = iterator;
        iterator = "";
        while(temp_s[i] != ','){
            iterator = iterator + temp_s[i];
            i++;
        }
        i++;
        string pass = iterator;
        iterator = "";
        response = check_user(user, pass);
    }
    else{
        ofstream myJson;
        myJson.open ("/home/simon/Cpp/VScode-memory-manager/server/src/ptr_data.json");
        myJson << temp_s;
        myJson.close();

        string saved;
        ifstream myJ("/home/simon/Cpp/VScode-memory-manager/server/src/ptr_data.json");
        saved.assign( (istreambuf_iterator<char>(myJ) ),
                (istreambuf_iterator<char>()    ) );
        response = saved;
        myJ.close();
    }
    
    return response;
}

void save_user(string user_name, string user_pass){
    string password = md5(user_pass);
    ofstream myJson;
    myJson.open("/home/simon/Cpp/VScode-memory-manager/server/src/user_data.json");

    string line = "[\n";
    line += "    {\n";
    line += "         \"Usuario\" : \"" + user_name + "\",\n";
    line += "         \"Password\" : \"" + password + "\"\n";
    line += "    }\n";
    line.pop_back();
    line.pop_back();
    line = line + "\n]";
    myJson << line;
    myJson.close();

}

string check_user(string user_name, string user_pass){
    string saved;
    string password = md5(user_pass);

    string line = "[\n";
    line += "    {\n";
    line += "         \"Usuario\" : \"" + user_name + "\",\n";
    line += "         \"Password\" : \"" + password + "\"\n";
    line += "    }\n";
    line.pop_back();
    line.pop_back();
    line = line + "\n]";

    
    ifstream myJson("/home/simon/Cpp/VScode-memory-manager/server/src/user_data.json");
    saved.assign( (istreambuf_iterator<char>(myJson) ),
                (istreambuf_iterator<char>()    ) );
    myJson.close();
    if(saved == line){
        return "Valid user.";
    }else{
        return "Incorrect user/password";
    }
}



static unordered_map<int, Bucket*> ptr_map; /*HashMap that saves the data of the pointers.*/
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
    ofstream myJson;
    myJson.open ("/home/simon/Cpp/VScode-memory-manager/server/src/ptr_data.json");

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
    key = true;
    th = thread(gc_loop);
}

void g_collector_close(){
    key = false;
    th.join();
}


void find_ptr(int ID){
    for (pair<int, Bucket*> element : ptr_map){
	    if(element.first == ID){
            element.second->getCount()->plus(1);
        }
    }
}

string get_ptr_int(int ID){
    for (pair<int, Bucket*> element : ptr_map){
	    if(element.first == ID){
            BucketT<int>* temp = dynamic_cast<BucketT<int>*>(element.second);
            return to_string(*temp->getPtr());
        }
    }
}
string get_ptr_float(int ID){
    for (pair<int, Bucket*> element : ptr_map){
	    if(element.first == ID){
            BucketT<float>* temp = dynamic_cast<BucketT<float>*>(element.second);
            return to_string(*temp->getPtr());
        }
    }
}
string get_ptr_double(int ID){
    for (pair<int, Bucket*> element : ptr_map){
	    if(element.first == ID){
            BucketT<double>* temp = dynamic_cast<BucketT<double>*>(element.second);
            return to_string(*temp->getPtr());
        }
    }
}
string get_ptr_bool(int ID){
    for (pair<int, Bucket*> element : ptr_map){
	    if(element.first == ID){
            BucketT<bool>* temp = dynamic_cast<BucketT<bool>*>(element.second);
            return *temp->getPtr() ? "true" : "false";
        }
    }
}
string get_ptr_char(int ID){
    for (pair<int, Bucket*> element : ptr_map){
	    if(element.first == ID){
            BucketT<char>* temp = dynamic_cast<BucketT<char>*>(element.second);
            string s = "";
            return s += *temp->getPtr();
        }
    }
}
string get_ptr_string(int ID){
    for (pair<int, Bucket*> element : ptr_map){
	    if(element.first == ID){
            BucketT<string>* temp = dynamic_cast<BucketT<string>*>(element.second);
            return *temp->getPtr();
        }
    }
}