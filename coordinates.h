#ifndef COORDINATES_H
#define COORDINATES_H

#include <map>
#include <iostream>
using namespace std;

class Coordinates
{
public:
    Coordinates(double setX, double setY);
    double getX();
    double getY();
    const map<wstring,int> &getSectors() const;
    void refGetCoordinates(double &x, double &y);
    static int getSectorFromXY(double x, double y);

private:
    double x;
    double y;
    map<wstring,int> m_sectors;
    void calculations();
    const double x0 = -595844.00;
    const double x1 = 622131.00;
    const double y0 = -597251.00;
    const double y1 = 617530.00;
};

#endif // COORDINATES_H
