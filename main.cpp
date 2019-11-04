#include <iostream>
#include "vuelo.h"
#include "airport.h"

int main() {
    cout << "Bienvenido al asistente ATC. Por favor, introduce el codigo OACI del aeropuerto." << endl;
    string arpt;
    cin >> arpt;
    Airport apt(arpt);
    if (not apt.loaded()) return 0;
    cout << "introducir pista ativa para despegue: ";
    string to,ld;
    cin >> to;
    cout << endl << "introducir pista activa para aterrizaje: ";
    cin >> ld;
    cout << endl;
    apt.setconfig(to,ld);
    int qnh = 1013;
    apt.set_qnh(qnh);
    for (int i = 0; i < 10; ++i) cout << endl;
    string ins, callsgn, state;

    while (cin >> ins and ins != "end" and ins != "stop"){
        
        if (ins == "new"){ //Add new flight
            cin >> state >> callsgn;
            if (not apt.new_flight(callsgn,state)) cout << "El vuelo ya existe" << endl; //1 arrival 0 dep
            if (state == "departure"){
                cout << "¿Establecer destino? (S/N)" << endl;
                string t;
                cin >> t;
                if (t == "S"){
                    cout << "Destino: ";
                    cin >> t;
                    apt.update_fl(callsgn,"destination",t);
                }
            }
            cout << endl;
        }
        else if (ins == "upd"){
            cin >> callsgn;
            if(callsgn == "h" or callsgn == "help") {
                cout << "[CALLSIGN] [point, mode, origin, destination, altitude, runway/rwy/r, sqwk/sk/sq/s, status]" << endl;
            }
            else{
                string param, value;
                //cout << endl << "parametro: ";
                cin >>param;
                //cout << endl << "nuevo valor: ";
                cin >> value;
                apt.update_fl(callsgn,param,value);
            }
        }
        else if (ins == "readback"){
            cin >> callsgn;
            apt.fl_readback(callsgn);
        }
        else if (ins == "sid"){
            string point;
            cin >> point;
            cout << apt.getsid(point) << endl << endl;
        }
        else if (ins == "star"){
            string point;
            cin >> point;
            cout << apt.getstar(point) << endl << endl;
        }
        else if (ins == "del"){
            cin >> callsgn;
            if(not apt.del_fl(callsgn)) cout << "El vuelo no existe" << endl << endl;
        }
        else if (ins == "flight" or ins == "fl"){
            cin >> callsgn;
            apt.write_flight(callsgn);
        }
        else if (ins == "runway"){
            string field, value;
            cout << "departure/arrival?" << endl;
            cin >> field >> value;
            if (field == "departure"){
                apt.setconfig(value, "NULL");
            }
            else if (field == "arrival"){
                apt.setconfig("NULL",value);
            }
            else cout << "Error" << endl;
        }
        else if (ins == "set"){
            string field;
            int valuen;
            cin >> field >> valuen;
            if (field == "qnh") apt.set_qnh(valuen);
            cout << endl;
        }
        else if (ins == "departures"){ //List departing aircraft
            apt.listf("departures");
        }
        else if (ins == "arrivals"){ //List arriving aircraft
            apt.listf("arrivals");
        }
        else if (ins == "lfl" or ins == "all"){
            apt.lfl();
        }
        else if (ins == "help" or ins == "commands"){
            cout << "new [departure/arrival] [CALLSIGN] --> Creates new flight" << endl;
            cout << "upd [CALLSIGN/help] [PARAM] [VALUE] -- PARAMS on 'upd help' --> Updates the specified flight's PARAM with VALUE." << endl;
            cout << "++/next/step [CALLSIGN]            --> Steps forward the flight's status (ex.On blocks -> Taxiing) More in Usage.txt" << endl;
            cout << "readback [CALLSIGN]                --> Shows copy/readback for the flight" << endl;
            cout << "sid [VOR]                          --> Shows the SID for the specified VOR" << endl;
            cout << "star [VOR]                         --> Shows the STAR for the specified VOR" << endl;
            cout << "del [CALLSIGN]                     --> Delete the specified flight" << endl;
            cout << "flight/fl [CALLSIGN]               --> Shows the full information for the specified flight" << endl;
            cout << "runway                             --> Used to change active runways. Does NOT affect already existing flights (must be changed individualy)" << endl;
            cout << "set qnh [QNH]                      --> Changes the QNH of the airport" << endl;
            cout << "departures/arrivals                --> Lists all existing departures/arrivals in alphabetical order" << endl;
            cout << "lfl/all                            --> Lists all existing flights an a brief overview of each, sorted in cration order." << endl;
        }
        else if (ins == "++" or ins == "advace" or ins == "step" or ins == "next"){
            cin >> callsgn;
            apt.update_fl(callsgn,"status","++");
        }
    }
    cout << "Gracias por utilizar el asistente." << endl;
}