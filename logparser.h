#ifndef LOGPARSER_H
#define LOGPARSER_H

#include <fstream>
#include <prisoner.h>
#include <list>
#include <iostream>
#include <functional>
#include <QtNetwork>
#include <locale>
#include <codecvt>
using namespace std;

class LogParser
{
public:
    LogParser(list<Prisoner> &person, array<int, 32> &sector);
    void startParse(const string &fileName);
    void topKillCalculation(bool event=0, bool total=0);
    void topDeathCalculation(bool event=0, bool total=0);
    void topKDCalculation(bool event=0, bool total=0);
    //void testPrint();
    void steamParser();

private:
    wifstream inf;
    list<Prisoner> &prisoners;
    array<int,32> &sectors;
    void sectorCalculation(double &x, double &y, bool event);
};

#endif // LOGPARSER_H
