//
// Created by raul_ on 05/06/2018.
//

#ifndef VATC_SOFT_AIRPORT_H
#define VATC_SOFT_AIRPORT_H
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include "vuelo.h"
#include <set>
using namespace std;

class Airport {
private:
    string ICAO;
    vector<string> pistas;
    vector<map<string,string>> SIDs;
    vector<map<string,string>> STARs;
    bool correct;
    int nrwy, qnh;
    /**@brief Map containing flights.
     *
     */
    map<string,vuelo> mfl; //Key: Callsign
    set<string> departures;
    set<string> arrivals;
    string torwy, ldrwy;
    int toID, ldID;

    //bool point_wr(string mode, int& nrwy);
public:
    Airport();

    explicit Airport(string& apt);

    /**@brief Sets runways in use and their code
 * \pre pistas is set up
 * \post runway info is set up and their position in the vectors (IDs) are found.
 *
 * @param to Take off runway
 * @param ld Landing runway
 */
    void setconfig(string to, string ld);

    /**@brief Check the SID of one point
     *
     * @param point The point to look up
     * @return The SID assigned to point
     */
    string getsid(string point);

    /**@brief Check the STAR of one point
     *
     * @param point The point to look up
     * @return The STAR assigned to point
     */
    string getstar(string point);

    /**@brief Checks if the airport has been loaded with the necessary info (SIDs and STARs)
     *
     * @return True if the airport has the information loaded. False otherwise
     */
    bool loaded() const;

    /**@brief Adds a new flight
     *
     * @param calls Callsign of the new flight
     * @param stat Status of the new flight: 1 if arrival, 0 if departure
     * @return True if the flight was added, false if the flight already existed
     */
    bool new_flight(const string& calls, string& stat);

    bool update_fl(string& calls, string field, string& info);

    void write_flight(string& calls);

    void setdeparr(string& call);

    /**@brief Auxiliar function to write a flight's readback
     *
     * @param callsign Callsign of the desired flight's readback
     */
    void fl_readback(string calls);

    /**@brief Deletes a flight
     *
     * @param cals Callsign of the flight to delete
     * @return True if the flight was deleted, False if the flight didn't exist.
     */
    bool del_fl(string cals);

    void set_qnh(int& val);

    void listf(string info);

    /**@brief Lists all flights currently in the system, with a brief information of each
     * 
     */
    void lfl();
};


#endif //VATC_SOFT_AIRPORT_H
