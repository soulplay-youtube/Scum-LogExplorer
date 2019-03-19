#ifndef OUTFILE_H
#define OUTFILE_H

#include "coordinates.h"
#include "logparser.h"
#include "prisoner.h"
#include <iomanip>
#include <ctime>
#include <sstream>
#include <iostream>

using namespace std;

class Outfile
{
public:
    Outfile(list<Prisoner> &prisoner, array<int, 32> &sector, LogParser &parse, bool sandbox=0, bool event=0, bool total=0);
    void printToFile();
    void setSteamName(bool findName);
    ~Outfile();

private:
    wofstream outf;
    list<Prisoner> &prisoners;
    array<int, 32> &sectors;
    LogParser &parser;
    bool sandbox=0;
    bool event=0;
    bool total=0;
    bool findSteamName=0;
};

#endif // OUTFILE_H
