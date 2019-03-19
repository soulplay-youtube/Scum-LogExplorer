#include "coordinates.h"

Coordinates::Coordinates(double setX, double setY)
    : x(setX), y(setY)
{
calculations();
}

double Coordinates::getX()
{
    return x;
}

double Coordinates::getY()
{
    return y;
}

const map<wstring,int>& Coordinates::getSectors() const
{
    return m_sectors;
}

void Coordinates::calculations()
{
    int sector;
    double widthOfSector=(x1-x0)/4.00;
    double heightOfSector=(y1-y0)/4.00;
    if (x<=(x0+widthOfSector)) sector=1;
    else
    {
        if (x<=(x0+2.00*widthOfSector)) sector=2;
        else
        {
            if (x<=(x0+3.00*widthOfSector)) sector=3;
            else sector=4;
        }
    }
    if (y<=(y0+heightOfSector)) ;
    else
    {
        if (y<=(y0+2.00*heightOfSector)) sector += 4;
        else
        {
            if (y<=(y0+3.00*heightOfSector)) sector += 8;
            else sector += 12;
        }
    }
    wstring strSector;
    switch (sector) {
        case 1: strSector=L"A1"; break;
        case 2: strSector=L"A2"; break;
        case 3: strSector=L"A3"; break;
        case 4: strSector=L"A4"; break;
        case 5: strSector=L"B1"; break;
        case 6: strSector=L"B2"; break;
        case 7: strSector=L"B3"; break;
        case 8: strSector=L"B4"; break;
        case 9: strSector=L"C1"; break;
        case 10: strSector=L"C2"; break;
        case 11: strSector=L"C3"; break;
        case 12: strSector=L"C4"; break;
        case 13: strSector=L"D1"; break;
        case 14: strSector=L"D2"; break;
        case 15: strSector=L"D3"; break;
        case 16: strSector=L"D4"; break;
    default:
        break;
    }
    auto it = m_sectors.find(strSector);
    if (it==m_sectors.end()) m_sectors.insert(make_pair(strSector,1));
    else ++m_sectors[strSector];
}

void Coordinates::refGetCoordinates(double &x, double &y)
{
    x=this->x;
    y=this->y;
}

int Coordinates::getSectorFromXY(double x, double y)
{
    int sector;
    const double x0 = -595844.00;
    const double x1 = 622131.00;
    const double y0 = -597251.00;
    const double y1 = 617530.00;
    double widthOfSector=(x1-x0)/4.00;
    double heightOfSector=(y1-y0)/4.00;
    if (x<=(x0+widthOfSector)) sector=1;
    else
    {
        if (x<=(x0+2.00*widthOfSector)) sector=2;
        else
        {
            if (x<=(x0+3.00*widthOfSector)) sector=3;
            else sector=4;
        }
    }
    if (y<=(y0+heightOfSector)) ;
    else
    {
        if (y<=(y0+2.00*heightOfSector)) sector += 4;
        else
        {
            if (y<=(y0+3.00*heightOfSector)) sector += 8;
            else sector += 12;
        }
    }
    return sector;
}
