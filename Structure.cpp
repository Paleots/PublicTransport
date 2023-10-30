#include "Structure.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <map>
#include "stdc++.hpp"
#include "Exceptions.hpp"

void Structure::LoadInformationsAboutMap(const string &filepath){
    ifstream input(filepath);
    if (input.is_open()){
        string random;
        while (getline(input,random)) {
            string word;
            string NameOfStation;
            istringstream iss(random);
            int n = 0;
            while (iss >> word) {
                if(n!=1){
                    NameOfStation = word;
                    MapOfLines[word];
                    n++;
                    continue;
                }
                MapOfLines[NameOfStation].push_back(word);
            }
        }
    }else {cout<<"Fajl ne moze da se otvori"<<endl; openFileCheck = "No";}
}
//Ucitam sve stanice u jedan vektor, a u tom vectoru ce biti vektori gde je prvo jedno ime pa onda stanica, pa bitnost
void Structure::LoadInformationsAboutStations(const string &filepath){
    ifstream input(filepath);
    if (input.is_open()){
        string word;
        while(getline(input,word)){
            //string word;
            if(word[word.length()-1] == '\r'){
                int pos = 0;
                for(int  i = 0;i<word.length();i++){
                    if((word[i]+word[i+1]) == '\r'){pos = i;break;};
                }
                word = word.substr(0,pos);
                pos = 0;
            }
            int pos = 0;
            for (int  i = 0 ;i <word.length();i++){
                if(word[i] == ' '){pos = i+1;break;};
            }
            string token1 =word.substr(0,pos-1); // broj stanice
            string token2 = word.substr(pos,pos+word.length()); // ime i vaznost
            vector<string> T;
            string token3;
            T.push_back(token1);
            int i = 0;
            if(token2[token2.length()-1] == ']'){
                for(; i<token2.length() && token2[i] != '[';i++){
                };
                i = i-1;
                token3 = token2.substr(i+1,i+token2.length());
                token2 = token2.substr(0,i-1);
                T.push_back(token2);
                T.push_back(token3);
                ImportantStations.push_back(token1);
            }else T.push_back(token2);
            
            
            Stanice_input.push_back(T);
        }
    }else {cout<<"Fajl ne moze da se otvori"<<endl; openFileCheck = "No";}
}


bool Structure::insert(string& NumberOfStation, const string &NameOfStation,const string& Importance){
    if (root_ == nullptr) {
        root_ = new Stations(NumberOfStation,NameOfStation,Importance);
        return true;
    }
    Stations* curr = root_;
    while (curr != nullptr) {
        if (stoi(NumberOfStation) < stoi(curr->getNumber())) {
            if (curr->RetrunStationLeft()) curr = curr->RetrunStationLeft();
            else {
                curr->setLeft(new Stations(NumberOfStation,NameOfStation,Importance));
                return true;
            }
        }
        else if (stoi(NumberOfStation) > stoi(curr->getNumber())) {
            if (curr->RetrunStationRight()) curr = curr->RetrunStationRight();
            else {
                curr->setRight(new Stations(NumberOfStation,NameOfStation,Importance));
                return true;
            }
        }
        else return false;
    }
    return true;
}

void Structure::createBinaryTree(){
    for(auto& e : Stanice_input){
        if(e.size()>2){
            insert(e[0], e[1], e[2]);
        }else insert(e[0], e[1], "no");
    }
}



void Structure::addDirectLines(){
    for(auto& e : Stanice_input){
        string number = e[0];
        for (auto it = MapOfLines.begin(); it != MapOfLines.end(); ++it) {
            for(auto& l : it->second){
                if(l == number){
                    Stations* L =find(number);
                    
                    L->addToVector(it->first);
                }
            }
            
        }
    }
}

void Structure::addDirectStations(Stations* Node){ // krecem prvo od roota
    if(Node == nullptr)
        return;
    vector<string> T;
    //int n = 0;
    for (auto& e : Node->getDirectLines()){
        for(auto& g : MapOfLines[e]){
            int n = 0;
            for(auto& h: T){
                if( g == h)n++;
            }
            if(n==0 && g!= Node->getNumber()) T.push_back(g);
        }
    }
    Node->getDirectStations() = T;
    addDirectStations(Node->RetrunStationLeft());
    addDirectStations(Node->RetrunStationRight());
    
}

//----------------------------------------------------------------------------------------------------

void Structure::addDirectStations1(){
    addDirectStations(root_);
}

Stations* Structure::find(string& NumberOfStation){
    Stations* curr = root_;
    while (curr != nullptr) {
        if (stoi(NumberOfStation) < stoi(curr->getNumber())) {
            if (curr->RetrunStationLeft()) curr = curr->RetrunStationLeft();
                else curr = nullptr;
        }
        else if (stoi(NumberOfStation) > stoi(curr->getNumber())) {
            if (curr->RetrunStationRight()) curr = curr->RetrunStationRight();
                else curr = nullptr;
        }
        else return curr;
    }
    return nullptr;
}




vector<vector<string>> Structure::MinRoute(string src, string dst){
    if(src != dst){
        set<string> ZAKRAJ;
        set<string> ForStations;
        Stations*  T = find(src);
        vector<string> que;
        vector<string> G = T->RetrunDirectStartions();
        ForStations.insert(src);
        for(int i = 0; i < G.size(); i++){
            if (G[i] == dst){
                
                vector<vector<string>> a ;
                vector<string> c;
                //c.push_back(T->DirectLines[0]);
                /*
                 Stations* L =find(number);
                 
                 L->getDirectLines().push_back(it->first);
                 */
                //vector<string> P = T->DirectLines;
                for(auto& e : T->getDirectLines()){
                    bool  n = false;
                    bool  l = false;
                    for(int  k = 0 ; k<MapOfLines[e].size();k++){
                        if((MapOfLines[e][k] == dst)) n =true;
                        if(MapOfLines[e][k] == src) l = true;
                    };
                    if((n == true)&&(l==true)) {c.push_back(e); break;}
                }
                c.push_back(src);
                c.push_back(dst);
                a.push_back(c);
                return a;
            }
            ZAKRAJ.insert(G[i]);
            que.push_back(G[i]);
            ForStations.insert(G[i]);
        }
        
        string l ;
        int  i = 0;
        string m;
        string first_diff;
        vector<string> specialStations;
        map<string, vector<string>> Map;
        while(l != dst){
            int n = 0;
            Stations* L = find(que[i]);
            vector<string> M = L->RetrunDirectStartions();
            // ovde sam stavio umesto i<M.size j
            for(int j = 0; j < M.size(); j++){
                if(ForStations.count(M[j])>0){continue;}
                if(ForStations.count(M[j]) == 0){
                    if(n==0) {Map[que[i]];n++;specialStations.push_back(M[j]);}
                    ForStations.insert(M[j]);
                    Map[que[i]].push_back(M[j]);
                };
                if(M[j] == dst) { l = dst; first_diff = M[j];  i--;break;} // Map[que[i]][0]; mala izmena kod first diff
                if(M[j] != dst){ que.push_back(M[j]);}
            }
            i++;
        }
        
        string c = first_diff;
        vector<string> ZAKRAJ1;
        ZAKRAJ1.push_back(c);
        while(ZAKRAJ.count(c) != 1 ){
            for (auto& e: Map) {
                vector<string> K = e.second;
                for(int  i = 0;i < K.size();i++){
                    if(K[i] == c){
                        c = e.first;
                        ZAKRAJ1.push_back(e.first);
                    }
                }
            }
        }
        Stations* A = find(src);
        vector<string> DirektneLinije = A->getDirectLines();
        reverse(ZAKRAJ1.begin(), ZAKRAJ1.end());
        int f = 0;
        vector<vector<string>> StaniceKojeOdgovaraju;
        for(int i = 0 ; i< ZAKRAJ1.size();i++){
            //if((i+1) > ZAKRAJ1.size()){continue;}
            if((i+1) > ZAKRAJ1.size()-1){continue;}
            Stations* Prvi = find(ZAKRAJ1[i]);
            if(f==0){
                Stations* P = find(src);
                vector<string> l = P->getDirectLines();
                vector<string> c;
                c.push_back(src+"->"+ZAKRAJ1[i]);
                // zamenjujem i
                for(int t = 0 ; t<l.size();t++){
                    for(int j = 0 ;j<MapOfLines[l[t]].size();j++){
                        if(MapOfLines[l[t]][j] == ZAKRAJ1[t]){
                            c.push_back(l[t]);
                            break;};
                    }
                }
                StaniceKojeOdgovaraju.push_back(c);
                f++;
            }
            
            // do ovde je zamena
            //Stations* Drugi = find(ZAKRAJ1[i+1]);
            vector<string> PrviLinije = Prvi->getDirectLines();
            //int t = ZAKRAJ1.size();
            
            //ovde umesto i stavljam neko drugo slovo svuda dole
            
            //menjam i sa necim druigm
            for(int r = 0 ; r<PrviLinije.size();r++){
                for(int j = 0 ;j<MapOfLines[PrviLinije[r]].size();j++){
                    //
                    int n = 0;
                    vector<string> y = ZAKRAJ1;
                    string q = y[ZAKRAJ1.size()-1];
                    if(ZAKRAJ1[i+1] == q ){
                        for(int  k = 0 ; k<MapOfLines[PrviLinije[r]].size();k++){
                            if((MapOfLines[PrviLinije[r]][k] == dst)) n++;
                        };
                        if((MapOfLines[PrviLinije[r]][j] == ZAKRAJ1[i+1]) && n>0){
                            vector<string> c;
                            c.push_back(ZAKRAJ1[i]+"->"+ZAKRAJ1[i+1]);
                            c.push_back(PrviLinije[r]);
                            StaniceKojeOdgovaraju.push_back(c);
                            break;};
                    }else{
                        //
                        if(MapOfLines[PrviLinije[r]][j] == ZAKRAJ1[i+1]){
                            vector<string> c;
                            c.push_back(ZAKRAJ1[i]+"->"+ZAKRAJ1[i+1]);
                            c.push_back(PrviLinije[r]);
                            StaniceKojeOdgovaraju.push_back(c);
                            break;};
                    }
                }
            }
        }
        return StaniceKojeOdgovaraju;
    }else {cout<<"Vec se nalazite na datoj stanici"<<endl;vector<vector<string>> T ;return T;}
}

void Structure::load(string stations, string lines){
    LoadInformationsAboutStations(stations);
    LoadInformationsAboutMap(lines);
    createBinaryTree();
    addDirectLines();
    addDirectStations1();
}

void Structure::SecondStrategy(string src, string dst){
    
        int n = 0;
        for(auto& e :Stanice_input){ if(e[0]==src)n++;}
           if(n==0) throw (new Exceptions("Ne postoji prva stanica"));
    
        int g = 0;
        for(auto& e :Stanice_input){ if(e[0]==dst)g++;}
           if(g==0) throw (new Exceptions("Ne postoji druga stanica"));

    
    string q = "putanja_"+src+"_"+dst+"_"+"kraj.txt";
    ofstream output(q);
    vector<vector<string>> T = MinRoute(src, dst);
    ConstractPath(T,output);
}



void Structure::FirstStrategy(string src, string dst){
    
     
         int n = 0;
         for(auto& e :Stanice_input){ if(e[0]==src)n++;}
            if(n==0) throw (new Exceptions("Ne postoji prva stanica"));
     
         int g = 0;
         for(auto& e :Stanice_input){ if(e[0]==dst)g++;}
            if(g==0) throw (new Exceptions("Ne postoji druga stanica"));
    
     
     
    string q = "putanja_"+src+"_"+dst+"_"+"kraj.txt";
    ofstream output(q);
    string c = Stanice_input[0][0];
    vector<vector<string>> T =  MinRoute(src, c);
    
    output<<endl;
    vector<vector<string>> G = MinRoute(c, dst);
    ConstractPath(T,output);
    output<<endl;
    output<<endl;
    ConstractPath(G,output);
}

// dodam parametar za ispisni tok
void Structure::ThirthStrayegy(string& src, string& dst){
        int n = 0;
        for(auto& e :Stanice_input){ if(e[0]==src)n++;}
           if(n==0) throw (new Exceptions("Ne postoji prva stanica"));
    
        int g = 0;
        for(auto& e :Stanice_input){ if(e[0]==dst)g++;}
           if(g==0) throw (new Exceptions("Ne postoji druga stanica"));
    //catch (Exceptions* e){e->print() ; return;};
    if(ImportantStations.empty()){return;}
    string q = "putanja_"+src+"_"+dst+"_"+"kraj.txt";
    ofstream output(q);
    ConstractPath(MinRoute(src, ImportantStations[0]),output);
    output<<endl;
    for(int  i = 0 ; i < ImportantStations.size()-1;i++){
        ConstractPath(MinRoute(ImportantStations[i], ImportantStations[i+1]),output);
        output<<endl;
    }
    //cout<<endl;
    ConstractPath(MinRoute(ImportantStations[ImportantStations.size()-1], dst),output);
}


void Structure::ConstractPath(vector<vector<string>> T,ofstream& output){
    if(T.empty()){return;};
    if(T.size() != 1){
        //creating output file
        //
        int n = 0;
        int j = 0;
        for(auto& e : T){
            string Bus = e[1];
            char t;
            string rutA;
            string rutB;
            int  i = 0;
            while(e[0][i]!='-'){
                i++;
            }
            rutA = e[0].substr(0,i);
            rutB = e[0].substr(i+2,i+e[0].length());
            vector<string> path;
            //path.push_back(rutA);
            int indexA;
            int indexB;
            vector<string> BusLine = MapOfLines[Bus];
            int g = 0;
            int brojac=0;
            while(g == 0 ){
                if(BusLine[brojac] == rutA) {indexA = brojac;g++;};
                brojac++;
            }
            
            g = 0;
            brojac=0;
            while(g == 0 ){
                if(BusLine[brojac] == rutB) {indexB = brojac;g++;};
                brojac++;
            }
            if(indexB < indexA){
                int temp = indexA;
                indexA = indexB;
                indexB = temp;
               
                for(int i  = indexA; i < indexB+1; i++){
                    path.push_back(BusLine[i]);
                }
                reverse(path.begin(), path.end());
            }else{
                for(int i  = indexA; i < indexB+1; i++){
                    path.push_back(BusLine[i]);
                }
            }
            
            if(n==0){
                output<<"->"+Bus<<endl;
                for(int i = 0 ; i<path.size();i++){
                    output<<path[i]<<" ";
                }
                n++;
            }else{
                if(j+1<T.size()+1){
                    output<<endl;
                    output<<T[j-1][1]<<"->"<<T[j][1]<<endl;
                    for(int i = 0 ; i<path.size();i++){
                        output<<path[i]<<" ";
                        
                    }
                   
                }else continue;
            }
            j++;
            
        }
    }else{
        vector<string> path;
        vector<string> c = T[0];
        string Bus = c[0];
        
        string rutA = c[1];
        string rutB = c[2];
        int indexA;
        int indexB;
        vector<string> BusLine = MapOfLines[Bus];
        int g = 0;
        int brojac=0;
        while(g == 0 ){
            if(BusLine[brojac] == rutA) {indexA = brojac;g++;};
            brojac++;
        }
        
        g = 0;
        brojac=0;
        while(g == 0 ){
            if(BusLine[brojac] == rutB) {indexB = brojac;g++;};
            brojac++;
        }
        if(indexB < indexA){
            int temp = indexA;
            indexA = indexB;
            indexB = temp;
            
            for(int i  = indexA; i < indexB+1; i++){
                path.push_back(BusLine[i]);
            }
            reverse(path.begin(), path.end());
        }else{
            for(int i  = indexA; i < indexB+1; i++){
                path.push_back(BusLine[i]);
            }
        }
        //
        
        //
        output<<"->"+Bus<<endl;
        for(int i = 0 ; i<path.size();i++){
            output<<path[i]<<" ";
        }
    }
        
}

void Structure::deleteTree(Stations * t){
    if(t->RetrunStationLeft()!=nullptr) deleteTree(t->RetrunStationLeft());
    if(t->RetrunStationRight()!= nullptr) deleteTree(t->RetrunStationRight());
    delete t;
}

Structure::~Structure(){
    if(root_!=nullptr){
        deleteTree(root_);
        this->root_ = nullptr;
    }
}
 
void Structure::Informations1(string& sifra){
    try{
        int n = 0;
        for(auto& e :Stanice_input){ if(e[0]==sifra)n++;}
        if(n==0) throw (new Exceptions("Ne postoji data stanica"));
    }
    catch (Exceptions* e){e->print() ; return;};
    Stations* T = find(sifra);
    string q = "stajaliste_"+sifra+".txt";
    ofstream output(q);
    if(output.is_open()){
        output<<T->getNumber()<<" ";
        output<<T->getName()<<" ";
        output<<"[";
        vector<string> L = T->ReturnDirectLines();
        vector<string> K = T->RetrunDirectStartions();
        //vector<string> c;
        sort(L.begin(),L.end());
        for(const auto& str: L){
            output<<str<<" ";
        }
        output<<"]"<<" ";
        output<<"{!";
        for(auto& e:K){
            Stations* t = find(e);
            if(t->getImportance() == "[!]") output<<e<<" ";
        }
        output<<"!}";
        cout<<"Generisan je fajl stajaliste_"+sifra+".txt" +"sa informacijama o datom stajalistu"<<endl;
        
    }else cout<<"Nije otvoren fajl"<<endl;
    
}
void Structure::Informations2(string &oznaka){
    try{
        int  n = 0;
        for(auto&  e: MapOfLines){if(e.first == oznaka) n++;}
        if(n==0) {throw (new Exceptions("Ne postoji data linija"));return;}
    }
    catch (Exceptions* e){e->print() ; return;};
    string q = "linija_"+oznaka+".txt";
    ofstream output(q);
    output<<oznaka<<" ";
    vector<string> T = MapOfLines[oznaka];
    string c = T[0];
    string g = T[T.size()-1];
    Stations* L = find(c);
    Stations* K = find(g);
    output<<L->getName()<<"->"<<K->getName()<<endl;
    for(auto& e:T){
        Stations* U = find(e);
        if(U->getImportance() == "[!]")
            output<<e<<" "<<U->getName()<<" "<< "[!]"<<endl;
        else
            output<<e<<" "<<U->getName()<<endl;
    }
    cout<<"Generisan je fajl linija_"+oznaka+".txt"+"sa informacijama o datoj liniji"<<endl;
}

void Structure::openTerminal(){
    cout<<"Dobro dosli u simulator mreze gradskog prevoza. Molim Vas, odaberite opciju:"<<endl;
    cout<<"1. Ucitavanje podataka o mrezi gradskog saobracaja"<<endl;
    cout<<"0. Kraj rada"<<endl;
    string c ;
    getline(cin, c);
    if(c=="1"){
        cout<<"Molim Vas, unesite putaju do fajla sa stajalistima i putanju sa linijama respektivno:";
        cout<<endl;
        cout<<"Fajl sa stajalistima: ";
        string a ;
        getline(cin,a);
        cout<<endl;
        cout<<"Fajl sa linijama: ";
        string h;
        getline(cin, h);
        //ovde bih mogao da hvatam izuzetak
            load(a, h);
        if(openFileCheck!="No"){
            cout<<"Mreza je uspesno ucitana"<<endl;
            string n = "1";
            while(n!="0"){
                cout<<"Odaberite opicju:"<<endl;
                cout<<"1. Prikaz informacija o stajalistu"<<endl;
                cout<<"2. Prikaz informacija o liniji gradskog prevoza"<<endl;
                cout<<"3. Pronalazak putanja izmedju dva stajalista(bilo koja putanja)"<<endl;
                cout<<"4. Pronalazak najkrace putanje izmedju dva stajalista"<<endl;
                cout<<"5. Obilazak svih bitnih destinacija grada u putanji"<<endl;
                cout<<"0. Kraj rada"<<endl;
                string q;
                getline(cin, q);
                if(q == "1"){
                    cout<<"Unesite sifru stajalista: ";
                    string j ;
                    getline(cin, j);
                    Informations1(j);
                    
                }
                if(q=="2"){
                    cout<<"Unesite sifru linije: ";
                    string j ;
                    getline(cin, j);
                    Informations2(j);
                    
                }
                if(q=="3"){
                    cout<<"Unesite sifru polazista: ";
                    string c;
                    getline(cin, c);
                    cout<<"Unesite sifru stajalista do kog zelite da idete: ";
                    string g ;
                    getline(cin, g);
                    try{
                        FirstStrategy(c, g);
                    }catch (Exceptions* e){e->print() ; continue;};
                    cout<<"Generisan je fajl putanja_"+c+"_"+g+"kraj.txt"+"sa informacijama kako doci do date lokacije"<<endl;
                }
                if(q=="4"){
                    cout<<"Unesite sifru polazista: ";
                    string c;
                    getline(cin, c);
                    cout<<"Unesite sifru stajalista do kog zelite da idete: ";
                    string g ;
                    getline(cin, g);
                    try{
                        SecondStrategy(c, g);
                        
                    }
                    catch (Exceptions* e){e->print() ; continue;};
                    cout<<"Generisan je fajl putanja_"+c+"_"+g+"kraj.txt"+"sa informacijama kako doci do date lokacije"<<endl;
                }
                if(q=="5"){
                    cout<<"Unesite sifru polazista: ";
                    string c;
                    getline(cin, c);
                    cout<<"Unesite sifru stajalista do kog zelite da idete: ";
                    string g ;
                    getline(cin, g);
                    try{
                        ThirthStrayegy(c, g);
                    
                    }catch (Exceptions* e){e->print() ; continue;};
                    cout<<"Generisan je fajl putanja_"+c+"_"+g+"kraj.txt"+"sa informacijama kako doci do date lokacije"<<endl;
                    
                }
                if(q=="0"){n="0";}
            }
            cout<<"Mreza se zatvara"<<endl;
            return;
        }else{cout<<"Mreza se zatvara"<<endl;
            return;}
    }else return;
}
 
/*
 void Structure::LoadInformationsAboutMap(const string &filepath){
     ifstream input(filepath);
     if (input.is_open()){
         string random;
         while (getline(input,random)) {
             string word;
             string NameOfStation;
             istringstream iss(random);
             int n = 0;
             while (iss >> word) {
                 if(n!=1){
                     NameOfStation = word;
                     //set_Linije_redom_u_vektor(word);
                     MapOfLines[word];
                     n++;
                     continue;
                 }
                 //Stanice_Linija_Redom.push_back(word);
                 MapOfLines[NameOfStation].push_back(word);
             }
         }
     }
 }
 //Ucitam sve stanice u jedan vektor, a u tom vectoru ce biti vektori gde je prvo jedno ime pa onda stanica, pa bitnost
 void Structure::LoadInformationsAboutStations(const string &filepath){
     ifstream input(filepath);
     if (input.is_open()){
         string word;
         while(getline(input,word)){
             //string word;
             if(word[word.length()-1] == '\r'){
                 int pos = 0;
                 for(int  i = 0;i<word.length();i++){
                     if((word[i]+word[i+1]) == '\r'){pos = i;break;};
                 }
                 word = word.substr(0,pos);
                 pos = 0;
             }
             int pos = 0;
             for (int  i = 0 ;i <word.length();i++){
                 if(word[i] == ' '){pos = i+1;break;};
             }
             string token1 =word.substr(0,pos-1); // broj stanice
             string token2 = word.substr(pos,pos+word.length()); // ime i vaznost
             vector<string> T;
             string token3;
             T.push_back(token1);
             int i = 0;
             if(token2[token2.length()-1] == ']'){
                 for(; i<token2.length() && token2[i] != '[';i++){
                 };
                 i = i-1;
                 token3 = token2.substr(i+1,i+token2.length());
                 token2 = token2.substr(0,i-1);
                 T.push_back(token2);
                 T.push_back(token3);
                 ImportantStations.push_back(token1);
             }else T.push_back(token2);
             
             
             Stanice_input.push_back(T);
         }
     }
 }


 bool Structure::insert(string& NumberOfStation, const string &NameOfStation,const string& Importance){
     if (root_ == nullptr) {
         root_ = new Stations(NumberOfStation,NameOfStation,Importance);
         return true;
     }
     Stations* curr = root_;
     while (curr != nullptr) {
         if (stoi(NumberOfStation) < stoi(curr->getNumber())) {
             if (curr->left) curr = curr->left;
             else {
                 curr->left = new Stations(NumberOfStation,NameOfStation,Importance);
                 return true;
             }
         }
         else if (stoi(NumberOfStation) > stoi(curr->getNumber())) {
             if (curr->right) curr = curr->right;
             else {
                 curr->right = new Stations(NumberOfStation,NameOfStation,Importance);
                 return true;
             }
         }
         else return false;
     }
     return true;
 }

 void Structure::createBinaryTree(){
     for(auto& e : Stanice_input){
         if(e.size()>2){
             insert(e[0], e[1], e[2]);
         }else insert(e[0], e[1], "no");
     }
 }



 void Structure::addDirectLines(){
     for(auto& e : Stanice_input){
         string number = e[0];
         for (auto it = MapOfLines.begin(); it != MapOfLines.end(); ++it) {
             for(auto& l : it->second){
                 if(l == number){
                     Stations* L =find(number);
                     L->DirectLines.push_back(it->first);
                 }
             }
             
         }
     }
 }

 void Structure::addDirectStations(Stations* Node){ // krecem prvo od roota
     if(Node == nullptr)
         return;
     vector<string> T;
     //int n = 0;
     for (auto& e : Node->DirectLines){
         for(auto& g : MapOfLines[e]){
             int n = 0;
             for(auto& h: T){
                 if( g == h)n++;
             }
             if(n==0 && g!= Node->getNumber()) T.push_back(g);
         }
     }
     Node->DirectStations = T;
     addDirectStations(Node->left);
     addDirectStations(Node->right);
     
 }

 */



//2.
/*
 
 void Structure::addDirectStations1(){
     addDirectStations(root_);
 }

 Stations* Structure::find(string& NumberOfStation){
     Stations* curr = root_;
     while (curr != nullptr) {
         if (stoi(NumberOfStation) < stoi(curr->getNumber())) {
             if (curr->left) curr = curr->left;
                 else curr = nullptr;
         }
         else if (stoi(NumberOfStation) > stoi(curr->getNumber())) {
             if (curr->right) curr = curr->right;
                 else curr = nullptr;
         }
         else return curr;
     }
     return nullptr;
 }




 vector<vector<string>> Structure::MinRoute(string src, string dst){
     if(src != dst){
         set<string> ZAKRAJ;
         set<string> ForStations;
         Stations*  T = find(src);
         vector<string> que;
         vector<string> G = T->RetrunDirectStartions();
         ForStations.insert(src);
         for(int i = 0; i < G.size(); i++){
             if (G[i] == dst){
                 
                 vector<vector<string>> a ;
                 vector<string> c;
                 //c.push_back(T->DirectLines[0]);
                 vector<string> P = T->DirectLines;
                 for(auto& e : T->DirectLines){
                     bool  n = false;
                     bool  l = false;
                     for(int  k = 0 ; k<MapOfLines[e].size();k++){
                         if((MapOfLines[e][k] == dst)) n =true;
                         if(MapOfLines[e][k] == src) l = true;
                     };
                     if((n == true)&&(l==true)) {c.push_back(e); break;}
                 }
                 c.push_back(src);
                 c.push_back(dst);
                 a.push_back(c);
                 return a;
             }
             ZAKRAJ.insert(G[i]);
             que.push_back(G[i]);
             ForStations.insert(G[i]);
         }
         
         string l ;
         int  i = 0;
         string m;
         string first_diff;
         vector<string> specialStations;
         map<string, vector<string>> Map;
         while(l != dst){
             int n = 0;
             Stations* L = find(que[i]);
             vector<string> M = L->RetrunDirectStartions();
             // ovde sam stavio umesto i<M.size j
             for(int j = 0; j < M.size(); j++){
                 if(ForStations.count(M[j])>0){continue;}
                 if(ForStations.count(M[j]) == 0){
                     if(n==0) {Map[que[i]];n++;specialStations.push_back(M[j]);}
                     ForStations.insert(M[j]);
                     Map[que[i]].push_back(M[j]);
                 };
                 if(M[j] == dst) { l = dst; first_diff = M[j];  i--;break;} // Map[que[i]][0]; mala izmena kod first diff
                 if(M[j] != dst){ que.push_back(M[j]);}
             }
             i++;
         }
         
         string c = first_diff;
         vector<string> ZAKRAJ1;
         ZAKRAJ1.push_back(c);
         while(ZAKRAJ.count(c) != 1 ){
             for (auto& e: Map) {
                 vector<string> K = e.second;
                 for(int  i = 0;i < K.size();i++){
                     if(K[i] == c){
                         c = e.first;
                         ZAKRAJ1.push_back(e.first);
                     }
                 }
             }
         }
         Stations* A = find(src);
         vector<string> DirektneLinije = A->DirectLines;
         reverse(ZAKRAJ1.begin(), ZAKRAJ1.end());
         int f = 0;
         vector<vector<string>> StaniceKojeOdgovaraju;
         for(int i = 0 ; i< ZAKRAJ1.size();i++){
             //if((i+1) > ZAKRAJ1.size()){continue;}
             if((i+1) > ZAKRAJ1.size()-1){continue;}
             Stations* Prvi = find(ZAKRAJ1[i]);
             if(f==0){
                 Stations* P = find(src);
                 vector<string> l = P->DirectLines;
                 vector<string> c;
                 c.push_back(src+"->"+ZAKRAJ1[i]);
                 // zamenjujem i
                 for(int t = 0 ; t<l.size();t++){
                     for(int j = 0 ;j<MapOfLines[l[t]].size();j++){
                         if(MapOfLines[l[t]][j] == ZAKRAJ1[t]){
                             c.push_back(l[t]);
                             break;};
                     }
                 }
                 StaniceKojeOdgovaraju.push_back(c);
                 f++;
             }
             
             // do ovde je zamena
             //Stations* Drugi = find(ZAKRAJ1[i+1]);
             vector<string> PrviLinije = Prvi->DirectLines;
             //int t = ZAKRAJ1.size();
             
             //ovde umesto i stavljam neko drugo slovo svuda dole
             
             //menjam i sa necim druigm
             for(int r = 0 ; r<PrviLinije.size();r++){
                 for(int j = 0 ;j<MapOfLines[PrviLinije[r]].size();j++){
                     //
                     int n = 0;
                     vector<string> y = ZAKRAJ1;
                     string q = y[ZAKRAJ1.size()-1];
                     if(ZAKRAJ1[i+1] == q ){
                         for(int  k = 0 ; k<MapOfLines[PrviLinije[r]].size();k++){
                             if((MapOfLines[PrviLinije[r]][k] == dst)) n++;
                         };
                         if((MapOfLines[PrviLinije[r]][j] == ZAKRAJ1[i+1]) && n>0){
                             vector<string> c;
                             c.push_back(ZAKRAJ1[i]+"->"+ZAKRAJ1[i+1]);
                             c.push_back(PrviLinije[r]);
                             StaniceKojeOdgovaraju.push_back(c);
                             break;};
                     }else{
                         //
                         if(MapOfLines[PrviLinije[r]][j] == ZAKRAJ1[i+1]){
                             vector<string> c;
                             c.push_back(ZAKRAJ1[i]+"->"+ZAKRAJ1[i+1]);
                             c.push_back(PrviLinije[r]);
                             StaniceKojeOdgovaraju.push_back(c);
                             break;};
                     }
                 }
             }
         }
         return StaniceKojeOdgovaraju;
     }else {cout<<"Vec se nalazite na datoj stanici"<<endl;vector<vector<string>> T ;return T;}
 }


 void Structure::FirstStrategy(string src, string dst){
     string c = Stanice_input[0][0];
     vector<vector<string>> T =  MinRoute(src, c);
     
     cout<<endl;
     vector<vector<string>> G = MinRoute(c, dst);
     ConstractPath(T);
     cout<<endl;
     cout<<endl;
     ConstractPath(G);
 }


 void Structure::ThirthStrayegy(string& src, string& dst){
     if(ImportantStations.empty()){return;}
     ConstractPath(MinRoute(src, ImportantStations[0]));
     cout<<endl;
     for(int  i = 0 ; i < ImportantStations.size()-1;i++){
         ConstractPath(MinRoute(ImportantStations[i], ImportantStations[i+1]));
         cout<<endl;
     }
     //cout<<endl;
     ConstractPath(MinRoute(ImportantStations[ImportantStations.size()-1], dst));
 }


 void Structure::ConstractPath(vector<vector<string>> T){
     if(T.empty()){return;};
     if(T.size() != 1){
         int n = 0;
         int j = 0;
         for(auto& e : T){
             string Bus = e[1];
             char t;
             string rutA;
             string rutB;
             int  i = 0;
             while(e[0][i]!='-'){
                 i++;
             }
             rutA = e[0].substr(0,i);
             rutB = e[0].substr(i+2,i+e[0].length());
             vector<string> path;
             //path.push_back(rutA);
             int indexA;
             int indexB;
             vector<string> BusLine = MapOfLines[Bus];
             int g = 0;
             int brojac=0;
             while(g == 0 ){
                 if(BusLine[brojac] == rutA) {indexA = brojac;g++;};
                 brojac++;
             }
             
             g = 0;
             brojac=0;
             while(g == 0 ){
                 if(BusLine[brojac] == rutB) {indexB = brojac;g++;};
                 brojac++;
             }
             if(indexB < indexA){
                 int temp = indexA;
                 indexA = indexB;
                 indexB = temp;
                
                 for(int i  = indexA; i < indexB+1; i++){
                     path.push_back(BusLine[i]);
                 }
                 reverse(path.begin(), path.end());
             }else{
                 for(int i  = indexA; i < indexB+1; i++){
                     path.push_back(BusLine[i]);
                 }
             }
             
             if(n==0){
                 cout<<"->"+Bus<<endl;
                 for(int i = 0 ; i<path.size();i++){
                     cout<<path[i]<<" ";
                 }
                 n++;
             }else{
                 if(j+1<T.size()+1){
                     cout<<endl;
                     cout<<T[j-1][1]<<"->"<<T[j][1]<<endl;
                     for(int i = 0 ; i<path.size();i++){
                         cout<<path[i]<<" ";
                         
                     }
                    
                 }else continue;
             }
             j++;
             
         }
     }else{
         vector<string> path;
         vector<string> c = T[0];
         string Bus = c[0];
         
         string rutA = c[1];
         string rutB = c[2];
         int indexA;
         int indexB;
         vector<string> BusLine = MapOfLines[Bus];
         int g = 0;
         int brojac=0;
         while(g == 0 ){
             if(BusLine[brojac] == rutA) {indexA = brojac;g++;};
             brojac++;
         }
         
         g = 0;
         brojac=0;
         while(g == 0 ){
             if(BusLine[brojac] == rutB) {indexB = brojac;g++;};
             brojac++;
         }
         if(indexB < indexA){
             int temp = indexA;
             indexA = indexB;
             indexB = temp;
             
             for(int i  = indexA; i < indexB+1; i++){
                 path.push_back(BusLine[i]);
             }
             reverse(path.begin(), path.end());
         }else{
             for(int i  = indexA; i < indexB+1; i++){
                 path.push_back(BusLine[i]);
             }
         }
         cout<<"->"+Bus<<endl;
         for(int i = 0 ; i<path.size();i++){
             cout<<path[i]<<" ";
         }
     }
         
 }
 */
