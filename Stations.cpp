#include "Stations.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "stdc++.hpp"
using namespace std;

string Stations::getNumber(){
    return NumberOfStation_;
}

string Stations::getName(){
    return name_;
}

string Stations::getImportance(){
    return Importance_;
}

vector<string> Stations::RetrunDirectStartions(){
    return DirectStations;
}


vector<string> Stations::ReturnDirectLines(){
    return DirectLines;
}



Stations* Stations::RetrunStationLeft(){
    return this->left;
}
Stations* Stations::RetrunStationRight(){
    return this->right;
}


//nove fje.
void Stations::setRight(Stations *t){
    right = t;
}

void Stations::setLeft(Stations *t){
    left = t;
}

vector<string>& Stations::getDirectLines(){
    return DirectLines;
}

vector<string>& Stations::getDirectStations(){
    return DirectStations;
}

void Stations::addToVector(string value){
    DirectLines.push_back(value);
}

Stations::~Stations(){
    left = nullptr;
    right = nullptr;
    delete left;
    delete right;
}

