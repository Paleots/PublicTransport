#ifndef Structure_hpp
#define Structure_hpp

#include "Stations.hpp"
#include "stdc++.hpp"
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Structure {
    
public:
    Structure():root_(nullptr),openFileCheck("Yes"){};
    ~Structure();
    void openTerminal();
    
private:
    
    void load(string stations, string lines);
    void LoadInformationsAboutMap(const string& filepath);
    void LoadInformationsAboutStations(const string& filepath);
    Stations* find(string& NumberOfStation);
    void createBinaryTree();
    bool insert(string& NumberOfStation,const string& NameOfStation, const string& Importance);
    void addDirectLines();
    void addDirectStations(Stations* Node);
    void addDirectStations1();
    vector<vector<string>> MinRoute(string src, string dst);
    void SecondStrategy(string src, string dst);
    void FirstStrategy(string src,string dst);
    void ConstractPath(vector<vector<string>>,ofstream&);
    void ThirthStrayegy(string& src , string& dst);
    void Informations1(string& sifra);
    void Informations2(string& oznaka);
    
    void deleteTree(Stations*);
    Stations* root_;
    vector<vector<string>> Stanice_input;
    map<string, vector<string>> MapOfLines;
    vector<string> Linije_redom;
    vector<string> ImportantStations;
    string openFileCheck;
    
};
    

#endif
