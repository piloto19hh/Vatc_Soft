//
// Created by raul_ on 05/06/2018.
//

#include "airport.h"

Airport::Airport() = default;

Airport::Airport(string& apt) {
    ifstream datasid;
    ifstream datastar;
    ICAO = apt;
    if (ICAO == "LEPA"){ //fill map with points and their departure
        datasid.open("./docs/LEPASID.txt");
        datastar.open("./docs/LEPASTAR.txt");
    }
    else if (ICAO == "LEAL"){ //fill map with points and their departure
        datasid.open("./docs/LEALSID.txt");
        datastar.open("LEALSTAR.txt");
    }
    else {
        cout << "El aeropuerto no se encuentra en la base de datos." << endl;
        correct = false;
    }

    if (datasid.fail() or datastar.fail()) cout << "Se ha producido un error al leer los datos del aeropuerto" << endl;
    else if (datasid.is_open() and datastar.is_open()) {
        unsigned int n;
        datasid >> n; //Number of Rumways
        nrwy = n;
        string pista;
        pistas = vector<string>(2*n); //Will contain the runways and its order
        for (int i = 0; i < n; ++i){
            datasid >> pista;
            pistas[i] = pista;
        }
        SIDs = vector<map<string,string>>(n);
        STARs = vector<map<string,string>>(n);
        int nrwy;
        datasid >> nrwy; //Number of possible departures on each runway
        for (int pst = 0; pst < n; ++pst) { //Filling vectors with departures
            for (int i = 0; i < nrwy; ++i) {
                string pont, route;
                datasid >> pont >> route;
                SIDs[pst][pont] = route;
            }
        }
        for (int i = n; i < 2*n; ++i){
            datastar >> pista;
            pistas[i] = pista;
        }
        datastar >> nrwy;
        for (int pst = 0; pst < n; ++pst) { //Filling vectors with arrivals
            for (int i = 0; i < nrwy; ++i) {
                string pont, route;
                datastar >> pont >> route;
                STARs[pst][pont] = route;
            }
        }
        correct = true;
    }
    datasid.close();
    datastar.close();
}

/*
bool Airport::point_wr(string mode, int& nrwy){
    if (mode == "dep"){
        cout << "Pista " << torwy << ":" << endl;
        for (auto it = SIDs[toID].begin(); it != SIDs[toID].end(); ++it) {
            string pont, route;
            cout << it->first << " -- " << it ->second << endl;
        }
    }
    else {
        cout << "Pista " << ldrwy << ":" << endl;
        for (auto it = STARs[ldID].begin(); it != STARs[ldID].end(); ++it) {
            string pont, route;
            cout << it->first << " -- " << it ->second << endl;
        }
    }
    return true;
}
 */

void Airport::setconfig(string to, string ld) {
    if (to == "NULL"){
        ldrwy = ld;
    }
    else if (ld == "NULL"){
        torwy = to;
    }
    else {
        torwy = to;
        ldrwy = ld;
    }
    for (int i = 0; i < pistas.size(); ++i){
        if (pistas[i] == torwy) toID = i;
        if (pistas[i] == ldrwy) ldID = i;
    }
    ldID -= nrwy;
    /*
    int nrwy = 13;
    int nrwy1 = 12;
    bool donedep = point_wr("dep",nrwy);
    cout << endl;
    bool donearr = point_wr("arr",nrwy1);
     */
}

string Airport::getsid(string point) {
    map<string,string>::iterator it;
    it = SIDs[toID].find(point);
    if (it != SIDs[toID].end()) return (*it).second;
    return "Punto no valido";
}

string Airport::getstar(string point) {
    map<string,string>::iterator it;
    it = STARs[ldID].find(point);
    if (it != STARs[ldID].end()){
        return (*it).second;
    }
    return "Punto no valido";
}

bool Airport::loaded() const{
    return correct;
}

bool Airport::new_flight(const string &calls, string& stat) {
    map<string,vuelo>::iterator it;
    it = mfl.find(calls);
    if (it != mfl.end()) return false;
    vuelo f1(calls);
    if (stat == "arrival"){
        f1.update("status","app");
        f1.update("mode","arrival");
        f1.update("destination",ICAO);
        f1.update("rwy",ldrwy);
    }
    else {
        f1.update("status","blocks");
        f1.update("mode","departure");
        f1.update("origin",ICAO);
        f1.update("rwy",torwy);
    }
    mfl[calls] = f1;
    return true;
}

bool Airport::update_fl(string& calls, string field, string& info) {
    map<string,vuelo>::iterator it;
    it = mfl.find(calls);
    if (it == mfl.end()) return false;
    if (field == "point") {
        mfl[calls].update(field,info);
        setdeparr(calls);
    }
    else mfl[calls].update(field,info);
    return true;
}

void Airport::write_flight(string &calls)  {
    map<string,vuelo>::const_iterator it;
    it = mfl.find(calls);
    if (it == mfl.end()) {
        cout << "El vuelo " << calls << " no existe." << endl;
        return;
    }
    mfl[calls].write();
}

void Airport::setdeparr(string& call) {
    map<string,vuelo>::iterator it;
    it = mfl.find(call);
    if (it == mfl.end()) return;
    pair<int,string> info;
    info = mfl[call].getpoint();
    if (info.first == 0){ //Departure
        mfl[call].viaset(SIDs[toID][info.second]);
    }
    else mfl[call].viaset(STARs[ldID][info.second]);
}

void Airport::fl_readback(string calls) {
    map<string,vuelo>::const_iterator it;
    it = mfl.find(calls);
    if (it == mfl.end()){
        cout << "El vuelo " << calls << " no existe." << endl;
        return;
    }
    mfl[calls].readback(qnh);
}

bool Airport::del_fl(string cals) {
    map<string,vuelo>::iterator it;
    it = mfl.find(cals);
    if (it != mfl.end()) {
        mfl.erase(it);
        return true;
    }
    return false;
}

void Airport::set_qnh(int& val) {
    qnh = val;
}