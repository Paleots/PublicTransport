#ifndef Stations_hpp
#define Stations_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "stdc++.hpp"
using namespace std;

class Stations{

public:
    Stations(string& NumberOfStation ,const string& name,const string& importance):name_(name),Importance_(importance),NumberOfStation_(NumberOfStation),left(nullptr),right(nullptr){}
    Stations(string& NumberOfStation ,const string& name):name_(name),NumberOfStation_(NumberOfStation){}
    ~Stations();
    string getNumber();
    string getName();
    string getImportance();
    
    string setName(const string&);
    string setImportance(const string&);
    string setNumber(string&);
    
    vector<string> RetrunDirectStartions();
    vector<string> ReturnDirectLines();
    
    Stations* RetrunStationLeft();
    Stations* RetrunStationRight();
    
    vector<string>& getDirectStations();
    vector<string>& getDirectLines();
    void addToVector(string value);
    void setRight(Stations* right);
    void setLeft(Stations* right);
private:
    string NumberOfStation_;
    vector<string> DirectStations;
    vector<string> DirectLines;
    string name_;
    string Importance_;
    Stations* left, * right;
};


#endif
