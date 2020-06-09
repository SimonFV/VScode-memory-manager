#ifndef CONTROL_H
#define CONTROL_H

#include <unordered_map>
#include <VSPtr.hpp>
#include <g_collector.hpp>

using namespace std;

void start();

extern "C"{
    string getData();
}


#endif