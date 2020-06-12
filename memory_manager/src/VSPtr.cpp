
#include <VSPtr.hpp>
#include <control.hpp>
#include <fstream>

using namespace std;

static unordered_map<int, Bucket*> ptr_map;
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
        cout<<"(id "<< element.first << ") has: "<< element.second->getCount()->get() <<endl;
	    if(element.second->getCount()->get() == 0){
            cout<< "deleting (id " << element.first <<")"<< endl;
            delete element.second;
        }
    }
}

void g_collector::add_ptr(int id, Bucket* b){
    ptr_map[id] = b;
}

//Gets the data pointed by the pointer.
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

//Generates a JSON file with the pointers information.
void g_collector::generate_data(){
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


void make_json(){
    g_collector::getInstance()->generate_data();
}