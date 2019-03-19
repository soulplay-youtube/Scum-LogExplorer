#include "prisoner.h"

Prisoner::Prisoner(const wstring& steamID, const wstring& name)
    : m_steamID(steamID), m_name(name)
{
}

const wstring& Prisoner::getSteamID() const
{
    return m_steamID;
}

const wstring& Prisoner::getName() const
{
    return m_name;
}

int Prisoner::getKills(bool event, bool total) const
{
    if (total && event) return m_killsTotal;
    else
    {
        if (event) return m_killsInEvents;
        else return m_kills;
    }
}

int Prisoner::getDeaths(bool event, bool total) const
{
    if (total && event) return m_deathsTotal;
    else
    {
        if (event) return m_deathsInEvents;
        else return m_deaths;
    }
}

void Prisoner::plusDeath(const wstring &killerName, bool event)
{
    if (!event)
    {
        ++m_deaths;
        ++m_deathsTotal;
        auto it = m_killersNames.find(killerName);
        if (it==m_killersNames.end()) m_killersNames.insert(make_pair(killerName,1));
        else ++m_killersNames[killerName];
    }
    else
    {
        ++m_deathsInEvents;
        ++m_deathsTotal;
        auto it = m_killersNamesEvent.find(killerName);
        if (it==m_killersNamesEvent.end()) m_killersNamesEvent.insert(make_pair(killerName,1));
        else ++m_killersNamesEvent[killerName];
    }
    auto it = m_killersNamesTotal.find(killerName);
    if (it==m_killersNamesTotal.end()) m_killersNamesTotal.insert(make_pair(killerName,1));
    else ++m_killersNamesTotal[killerName];
    KDCalculation();
}

void Prisoner::plusFrag(const wstring &fragName, bool event)
{
    if (!event)
    {
        ++m_kills;
        ++m_killsTotal;
        auto it = m_fragsNames.find(fragName);
        if (it==m_fragsNames.end()) m_fragsNames.insert(make_pair(fragName,1));
        else ++m_fragsNames[fragName];
    }
    else
    {
        ++m_killsInEvents;
        ++m_killsTotal;
        auto it = m_fragsNamesEvent.find(fragName);
        if (it==m_fragsNamesEvent.end()) m_fragsNamesEvent.insert(make_pair(fragName,1));
        else ++m_fragsNamesEvent[fragName];
    }
    auto it = m_fragsNamesTotal.find(fragName);
    if (it==m_fragsNamesTotal.end()) m_fragsNamesTotal.insert(make_pair(fragName,1));
    else ++m_fragsNamesTotal[fragName];
    KDCalculation();
}

void Prisoner::setCoordinates(double x,double y,bool event)
{
    if (!event)
    {
        m_coordinates.push_back(Coordinates(x,y));
    }
    else
    {
        m_coordinatesEvents.push_back(Coordinates(x,y));
    }
    m_coordinatesTotal.push_back(Coordinates(x,y));
}

void Prisoner::addSteamNames(wstring& steamName)
{
    m_steamNames.push_back(steamName);
}

const map<wstring,int>& Prisoner::getKillersNames(bool event, bool total) const
{
    if (total && event) return m_killersNamesTotal;
    else
    {
        if (event) return m_killersNamesEvent;
        else return m_killersNames;
    }
}

const map<wstring,int>& Prisoner::getFragsNames(bool event, bool total) const
{
    if (total && event) return m_fragsNamesTotal;
    else
    {
        if (event) return m_fragsNamesEvent;
        else return m_fragsNames;
    }
}

const vector<wstring>& Prisoner::getSteamNames() const
{
    return m_steamNames;
}

void Prisoner::KDCalculation()
{
    if (m_deaths!=0) m_KD=static_cast<double>(m_kills)/static_cast<double>(m_deaths);
    else m_KD=m_kills;
    if (m_deathsInEvents!=0) m_KDInEvents=static_cast<double>(m_killsInEvents)/static_cast<double>(m_deathsInEvents);
    else m_KDInEvents=m_killsInEvents;
    if ((m_deathsTotal)!=0)
        m_KDtotal=static_cast<double>(m_killsTotal)/static_cast<double>(m_deathsTotal);
    else m_KDtotal=m_killsTotal;
}

double Prisoner::getKD(bool event, bool total) const
{
    if (total && event) return m_KDtotal;
    else
    {
        if (event) return m_KDInEvents;
        else return m_KD;
    }
}

void Prisoner::setMode(bool event, bool total, int mode)
{
    m_event=event; m_total=total; m_mode=mode;
}

vector<Coordinates>& Prisoner::getCoordinates(bool event, bool total)
{
    if (total && event) return m_coordinatesTotal;
    else
    {
        if (event) return m_coordinatesEvents;
        else return m_coordinates;
    }
}

//const map<wstring,int>& getKillSectors() const
//{
//    return
//}

bool operator< (Prisoner &pr1, Prisoner &pr2)
{
    // Cортировка топ смертей
    if (pr1.m_mode==1)
    {
        if (!pr1.m_event)
        {
            if (pr1.m_deaths>pr2.m_deaths) return true;
            return false;
        }
        if (!pr1.m_total)
        {
            if (pr1.m_deathsInEvents>pr2.m_deathsInEvents) return true;
            return false;
        }

        if (pr1.m_deathsTotal>pr2.m_deathsTotal) return true;
        return false;
    }
    if (pr1.m_mode==0)
    {
        if (!pr1.m_event)
        {
            if (pr1.m_kills>pr2.m_kills) return true;
            return false;
        }
        if (!pr1.m_total)
        {
            if (pr1.m_killsInEvents>pr2.m_killsInEvents) return true;
            return false;
        }

        if (pr1.m_killsTotal>pr2.m_killsTotal) return true;
        return false;
    }
    if (pr1.m_mode==2)
    {
        if (!pr1.m_event)
        {
            if (pr1.m_KD>pr2.m_KD) return true;
            return false;
        }
        if (!pr1.m_total)
        {
            if (pr1.m_KDInEvents>pr2.m_KDInEvents) return true;
            return false;
        }

        if (pr1.m_KDtotal>pr2.m_KDtotal) return true;
        return false;
    }
}
