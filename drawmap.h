#ifndef DRAWMAP_H
#define DRAWMAP_H

#include <QPainter>
#include <QImage>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <prisoner.h>

class DrawMap
{
public:
    DrawMap(list<Prisoner> &prisoners, bool map=1, bool event=0, bool mapevent=0, bool markevent=0);
};

#endif // DRAWMAP_H
