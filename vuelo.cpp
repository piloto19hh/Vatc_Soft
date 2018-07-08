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
    qnh = "NULL";
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
    qnh = "NULL";
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

void vuelo::setpoint(const string &point) {
    pnt = point;
    //establish via to correct departure. ej: EPAMA, RWY 24R -- EPAMA1A
    if (rwy == "NULL") cout << "Pista no especificada." << endl;
    else if (inout == 0){ //departure

    }
}

void vuelo::update(string field, string info) {
    if (field == "origin") ori = info;
    else if (field == "destination") dest = info;
    else if (field == "point") pnt = info;
    else if (field == "altitude") inalt = info;
    else if (field == "rwy") rwy = info;
    else if (field == "qnh") qnh = info;
    else if (field == "sqwk") sqwk = info;
    else if (field == "mode"){
        if (info == "arrival") inout = 1;
        else inout = 0;
    }
    else if (field == "status"){
        if (info == "blocks") status = 0;
        else if (info == "taxi") status = 1;
        else if (info == "take off") status = 2;
        else if (info == "climbing") status = 3;
        else if (info == "cruise") status = 4;
        else if (info == "descend") status = 5;
        else if (info == "app") status = 6;
        else if (info == "landing") status = 7;
    }
    else cout << "'" << field << "' no es un parametro válido" << endl;
}

void vuelo::write() const {
    cout << endl << "CALLSIGN: "<< callsign << endl << "ESTADO:   ";
    if (status == 0) cout << "On Blocks" << endl;
    else if (status == 1) cout << "Taxiing" << endl;
    else if (status == 2) cout << "Taking Off" << endl;
    else if (status == 3) cout << "Climbing" << endl;
    else if (status == 4) cout << "Cruise" << endl;
    else if (status == 5) cout << "Descending"<< endl;
    else if (status == 6) cout << "Approach" << endl;
    else if (status == 7) cout << "Landing" << endl;
    else cout << "NULL" << endl;
    cout << "ORIGEN:   " << ori << endl << "DESTINO:  " << dest << endl;
    if (inout == 1) cout << "LLEGADA:  ";
    else cout << "SALIDA:   ";
    cout << via << endl << "SQUAWK:   " << sqwk << endl;
}
}
