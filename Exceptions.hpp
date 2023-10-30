#ifndef Exceptions_hpp
#define Exceptions_hpp

#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

class Exceptions{
public:
    Exceptions(const string& greska):c(greska){}
    void print();
private:
    string c;
};



#endif
