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
    string ins, callsgn, state;
    while (cin >> ins and ins != "end"){

        if (ins == "new"){ //Add new flight
            cin >> state >> callsgn;
            if (not apt.new_flight(callsgn,state)) cout << "El vuelo ya existe" << endl; //1 arrival 0 dep
            if (state == "departure"){
                cout << "¿Añadir destino? (S/N)" << endl;
                string t;
                cin >> t;
                if (t == "S"){
                    cout << "Destino: ";
                    cin >> t;
                    cout << endl;
                    apt.update_fl(callsgn,"destination",t);
                }
            }
        }
        else if (ins == "upd"){
            string param, value;
            cout << "enter callsign: ";
            cin >> callsgn;
            cout << endl << "parametro: ";
            cin >>param;
            cout << endl << "nuevo valor: ";
            cin >> value;
            apt.update_fl(callsgn,param,value);
        }
        else if (ins == "readback"){
            //Show copy details
        }
        else if (ins == "sid"){
            string point;
            cin >> point;
            cout << apt.getsid(point) << endl;
        }
        else if (ins == "star"){
            string point;
            cin >> point;
            cout << apt.getstar(point) << endl;
        }
        else if (ins == "del"){
            cin >> callsgn;
            if(not apt.del_fl(callsgn)) cout << "El vuelo no existe" << endl;
        }
        else if (ins == "flight"){
            cin >> callsgn;
            apt.write_flight(callsgn);
        }
    }
}