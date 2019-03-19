#ifndef SETTINGS_H
#define SETTINGS_H

#include <fstream>
#include <iostream>
using namespace std;

class Settings
{
public:
    Settings();
    bool getSandbox() const;
    bool getEvents() const;
    bool getAllStats() const;
    bool getRecordStats() const;
    bool getMap() const;
    bool getMapEvent() const;
    bool getMarkEvent() const;
    bool getSteamID() const;

private:
    bool sandbox=true;
    bool events=false;
    bool allstats=false;
    bool recordstats=true;
    bool map=true;
    bool mapevent=false;
    bool markevent=false;
    bool steamid=false;
};

#endif // SETTINGS_H
