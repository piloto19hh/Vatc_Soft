//
// Created by raul_ on 05/06/2018.
//

#ifndef VATC_SOFT_VUELO_H
#define VATC_SOFT_VUELO_H

#include <iostream>
using namespace std;

class vuelo {
private:
    string callsign, ori, dest, via, pnt, inalt, rwy, qnh, sqwk;
    int status; //0 on blocks, 1 taxiing, 2 t/o, 3 dep, 4 cruise, 5 desc, 6 app, 7 land
    int inout; //1 arrival 0 departure

public:

    vuelo();

    vuelo(string call);

    //vuelo(string call, string org, string des);

    //vuelo(string call, string stt);

    ~vuelo();

    /**@brief checks a flight's callsign
     *
     * @return The callsign of the flight
     */
    string checkCS() const;

    /**@brief Sets the initial point to the flight and its corresponding arrival or departure.
     *
     * @param point initial point of the route (if departure) or last route point (if arrival)
     */
    void setpoint(const string& point);

    void update(string field, string info);

    void write() const;
    
    void readback() const;
};


#endif //VATC_SOFT_VUELO_H
