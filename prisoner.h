#ifndef PRISONER_H
#define PRISONER_H

#include <QString>
#include <coordinates.h>
#include <vector>
#include <functional>
#include <iostream>
#include <map>

using namespace std;

class Prisoner
{
public:
    Prisoner(const wstring& steamID, const wstring& name);

    void plusDeath(const wstring &killerName, bool event=0);
    void plusFrag(const wstring &fragName, bool event=0);
    void setCoordinates(double x,double y, bool event=0);
    void addSteamNames(wstring& steamName);
    void setMode(bool event, bool total, int mode);

    // Геттеры
    const wstring& getSteamID() const;
    const wstring& getName() const;

    int getKills(bool event=0, bool total=0) const;
    int getDeaths(bool event=0, bool total=0) const;

    const map<wstring,int>& getKillersNames(bool event=0, bool total=0) const;
    const map<wstring,int>& getFragsNames(bool event=0, bool total=0) const;

    const vector<wstring>& getSteamNames() const;
    double getKD(bool event=0, bool total=0) const;
    vector<Coordinates> &getCoordinates(bool event=0, bool total=0);
    //const map<wstring,int>& getKillSectors() const;

    friend bool operator< (Prisoner &pr1, Prisoner &pr2);


private:
    wstring m_steamID;
    wstring m_name;
    int m_kills=0;
    int m_deaths=0;
    int m_killsInEvents=0;
    int m_deathsInEvents=0;
    int m_killsTotal=0;
    int m_deathsTotal=0;

    vector<Coordinates> m_coordinates;
    vector<Coordinates> m_coordinatesEvents;
    vector<Coordinates> m_coordinatesTotal;
    //const map<wstring,int> &sectors;

    map<wstring,int> m_killersNames;
    map<wstring,int> m_killersNamesEvent;
    map<wstring,int> m_killersNamesTotal;

    map<wstring,int> m_fragsNames;
    map<wstring,int> m_fragsNamesEvent;
    map<wstring,int> m_fragsNamesTotal;

    vector<wstring> m_steamNames;

    double m_KD=0;
    double m_KDInEvents=0;
    double m_KDtotal=0;
    void KDCalculation();

    bool m_event;
    bool m_total;
    int m_mode; // 0-topKills, 1-topDeaths, 2-KD
};

#endif // PRISONER_H
