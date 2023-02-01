#define pair<int,int> pii

#include <iostream>
#include <string>
#include <chrono>
#include <vector>

using namespace std;


void time_it(){
    auto t1 = chrono::high_resolution_clock::now();
    for(int i=0;i<1000;i++){
        pair<string, vector<int>> result = checkType(c1);
    }
    auto t2 = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> ms_double = t2 - t1;
    cout << ms_double.count() << "ms\n";
}

// g++ -o libTest.so -shared -fPIC C_lib.cpp