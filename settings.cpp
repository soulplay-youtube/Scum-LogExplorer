#include "settings.h"

Settings::Settings()
{
    ifstream inf;
    inf.open("settings.ini");
    string strInput;
    if (inf.is_open())
    {
        getline(inf, strInput);
        while(inf)
        {
            if (strInput[0]=='#')
            {
                getline(inf, strInput);
                continue;
            }
            if (strInput.find("sandbox=",0)!=-1) sandbox=stoi(strInput.substr(8,1));
            if (strInput.find("events=",0)!=-1) events=stoi(strInput.substr(7,1));
            if (strInput.find("allstats=",0)!=-1) allstats=stoi(strInput.substr(9,1));
            if (strInput.find("recordstats=",0)!=-1) recordstats=stoi(strInput.substr(12,1));
            if (strInput.find("map=",0)!=-1) map=stoi(strInput.substr(4,1));
            if (strInput.find("mapevent=",0)!=-1) mapevent=stoi(strInput.substr(9,1));
            if (strInput.find("markevent=",0)!=-1) markevent=stoi(strInput.substr(10,1));
            if (strInput.find("steamid=",0)!=-1) steamid=stoi(strInput.substr(8,1));

            getline(inf, strInput);
        }
    }
    if (inf.is_open()) inf.close();
}

bool Settings::getSandbox() const { return sandbox; }
bool Settings::getEvents() const { return events; }
bool Settings::getAllStats() const { return allstats; }
bool Settings::getRecordStats() const { return recordstats; }
bool Settings::getMap() const { return map; }
bool Settings::getMapEvent() const { return mapevent; }
bool Settings::getMarkEvent() const { return markevent; }
bool Settings::getSteamID() const { return steamid; }
