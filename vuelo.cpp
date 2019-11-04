//
// Created by raul_ on 05/06/2018.
//

#include "vuelo.h"

vuelo::vuelo(){
    callsign = "NULL";
    ori = "NULL";
    dest = "NULL";
    via = "NULL";
    pnt = "NULL";
    inalt = "NULL";
    rwy = "NULL";
    sqwk = "NULL";
    status = 0;
}

vuelo::vuelo(string call){
    callsign = call;
    ori = "NULL";
    dest = "NULL";
    via = "NULL";
    pnt = "NULL";
    inalt = "NULL";
    rwy = "NULL";
    sqwk = "NULL";
}
/*
vuelo::vuelo(string& call, string& org, string& des){
    callsign = call;
    ori = org;
    dest = des;
    via = "NULL";
    pnt = "NULL";
    inalt = "NULL";
    rwy = "NULL";
    qnh = "NULL";
    sqwk = "NULL";
}

vuelo::vuelo(string call, string& stt){ //TODO: Modify; inout removed
    callsign = call;
    ori = "NULL";
    dest = "NULL";
    via = "NULL";
    pnt = "NULL";
    inalt = "NULL";
    rwy = "NULL";
    qnh = "NULL";
    sqwk = "NULL";
    status = 0;

}
*/
vuelo::~vuelo() = default;

string vuelo::checkCS()const {
    return callsign;
}

string vuelo::fldest() const{
    return dest;
}

string vuelo::state() const{
    if (status == blocks) return "On Blocks |";
    else if (status == taxi) return "Taxiing   |";
    else if (status == takeoff) return "Take Off  |";
    else if (status == climbing) return "Climbing  |";
    else if (status == cruise) return "Cruise    |";
    else if (status == descend) return "Descending|";
    else if (status == app) return "Approach  |";
    else if (status == landing) return "Landing   |";
    else return "Error";
}

pair<int,string> vuelo::getpoint() {
    //Returns status and point
    pair<int,string> p1;
    if (rwy == "NULL") {
        cout << "Pista no especificada." << endl << endl;
        p1.first = 0;
        p1.second = "0";
    }
    else {
        p1.first = inout;
        p1.second = pnt;
    }
    return p1;
}

void vuelo::viaset(string& name) {
    via = name;
}

void vuelo::update(string field, string info) {
    if (field == "origin") ori = info;
    else if (field == "destination") dest = info;
    else if (field == "point") pnt = info;
    else if (field == "altitude") inalt = info;
    else if (field == "rwy" or field == "r" or field == "runway") rwy = info;
    else if (field == "sqwk" or field == "sk" or field == "sq" or field == "s") sqwk = info;
    else if (field == "mode"){
        if (info == "arrival") inout = 1;
        else inout = 0;
    }
    else if (field == "status"){
        if (info == "++") ++status;
        else if (info == "blocks") status = blocks;
        else if (info == "taxi") status = taxi;
        else if (info == "take off") status = takeoff;
        else if (info == "climbing") status = climbing;
        else if (info == "cruise") status = cruise;
        else if (info == "descend") status = descend;
        else if (info == "app") status = app;
        else if (info == "landing") status = landing;
    }
    else cout << "'" << field << "' no es un parametro válido" << endl << endl;
}

void vuelo::write() const {
    cout << endl << "CALLSIGN: "<< callsign << endl << "ESTADO:   ";
    if (status == 0) cout << "On Blocks" << endl;
    else if (status == taxi) cout << "Taxiing" << endl;
    else if (status == takeoff) cout << "Taking Off" << endl;
    else if (status == climbing) cout << "Climbing" << endl;
    else if (status == cruise) cout << "Cruise" << endl;
    else if (status == descend) cout << "Descending"<< endl;
    else if (status == app) cout << "Approach" << endl;
    else if (status == landing) cout << "Landing" << endl;
    else cout << "NULL" << endl;
    cout << "ORIGEN:   " << ori << endl << "DESTINO:  " << dest << endl;
    if (inout == 1) cout << "LLEGADA:  ";
    else cout << "SALIDA:   ";
    cout << via << endl << "SQUAWK:   " << sqwk << endl << endl;
}

void vuelo::readback(int& qnh) const {
cout << callsign << " cleared to " << dest << " via " << via << ". Active runway is " << rwy << ", initial level " << inalt;
cout << ". Sqwawk " << sqwk << " Actual QNH is " << qnh << endl << endl;
}