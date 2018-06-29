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
        //datasid.open("C:\\Users\\raul_\\Desktop\\Vatc soft\\docs\\docs\\LEPA_SID.txt");
        //datastar.open("C:\\Users\\raul_\\Desktop\\Vatc soft\\docs\\docs\\LEPA_STAR.txt");
        datasid.open("LEPASID.txt");
        datastar.open("LEPASTAR.txt");
    }
    else if (ICAO == "LEAL"){ //fill map with points and their departure
        datasid.open("LEALSID.txt");
        datastar.open("LEALSTAR.txt");
    }
    else {
        cout << "El aeropuerto no se encuentra en la base de datos." << endl;
        correct = false;
    }

    if (datasid.fail() or datastar.fail()) cout << "Se ha producido un error al leer los datos del aeropuerto" << endl;
    else if (datasid.is_open() and datastar.is_open()) {
        unsigned int n;
        datasid >> n;
        string pista;
        pistas = vector<string>(n);
        for (int i = 0; i < n; ++i){
            datasid >> pista;
            pistas[i] = pista;
        }
        SIDs = vector<map<string,string>>(n);
        STARs = vector<map<string,string>>(n);
        int nrwy;
        datasid >> nrwy;
        for (int pst = 0; pst < n; ++pst) {
            for (int i = 0; i < nrwy; ++i) {
                string pont, route;
                datasid >> pont >> route;
                //SIDs.insert(pont);
                SIDs[pst][pont] = route;
            }
        }
        for (int pst = 0; pst < n; ++pst) {
            for (int i = 0; i < nrwy; ++i) {
                string pont, route;
                datastar >> pont >> route;
                //SIDs.insert(pont);
                STARs[pst][pont] = route;
            }
        }
        /*
        while (not datasid.eof()) {
            string pont, route;
            datasid >> pont >> route;
            //SIDs.insert(pont);
            SIDs[pont] = route;
        }
        while (not datastar.eof()) {
            string pont, route;
            datastar >> pont >> route;
            //SIDs.insert(pont);
            STARs[pont] = route;
        }
         */
        correct = true;
    }
    datasid.close();
    datastar.close();
}

void Airport::setconfig(string& to, string& ld) {
    torwy = to;
    ldrwy = ld;
    for (int i = 0; i < pistas.size(); ++i){
        if (pistas[i] == torwy) toID = i;
        if (pistas[i] == ldrwy) ldID = i;
    }
}

string Airport::getsid(string point) {
    map<string,string>::iterator it;
    it = SIDs[toID].find(point);
    return (*it).second;
}

string Airport::getstar(string point) {
    map<string,string>::iterator it;
    it = STARs[ldID].find(point);
    return (*it).second;
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
    mfl[calls].update(field,info);
    return true;
}

void Airport::write_flight(string &calls)  {
    map<string,vuelo>::const_iterator it;
    it = mfl.find(calls);
    if (it == mfl.end()) cout << "El vuelo " << calls << " no existe." << endl;
    mfl[calls].write();
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
