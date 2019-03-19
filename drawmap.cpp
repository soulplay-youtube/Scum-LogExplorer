#include "drawmap.h"

DrawMap::DrawMap(list<Prisoner> &prisoners, bool mapsandbox, bool event, bool mapevent, bool markevent)
{

    // координаты карты
    const double x0 = -595844.00;
    const double x1 = 622131.00;
    const double y0 = -597251.00;
    const double y1 = 617530.00;

    const double x = fabs(x0) + fabs(x1);
    const double y = fabs(y0) + fabs(y1);

    QString mapName;
    QImage imgmap("map.png");
    QImage imgmap2("map.png");
    QImage imgdot("dot.png");
    QImage imgdotevent("dot2.png");
    if (imgmap.isNull() || imgdot.isNull())
        exit(1);
    if (markevent && imgdotevent.isNull())
        exit(1);

    const int widthOfMap = imgmap.width();
    const int heightOfMap = imgmap.height();
    const int widthOfDot = imgdot.width();
    const int heightOfDot = imgdot.height();

    const double coorXForOnePix = x / static_cast<double>(widthOfMap);
    const double coorYForOnePix = y / static_cast<double>(heightOfMap);

    QPainter painter;
    painter.begin(&imgmap);
    QPainter painter2;
    painter2.begin(&imgmap2);

    bool tTotal=0; bool tEvent=0;
    int xDraw, yDraw;

    //рисуем sandbox
    if (mapsandbox)
    {
        for (auto &it : prisoners)
        {
            if (!it.getCoordinates(tEvent,tTotal).empty())
            {
                vector<Coordinates> &coordinates = it.getCoordinates(tEvent,tTotal);
                for (auto &it2 : coordinates)
                {
                    xDraw = static_cast<int>((x1-it2.getX())/coorXForOnePix)-(widthOfDot/2);
                    yDraw = static_cast<int>((y1-it2.getY())/coorYForOnePix)-(heightOfDot/2);
                    painter.drawImage(xDraw,yDraw,imgdot);
                }
            }
        }
    }

    //рисуем event
    if (event)
    {
        tEvent=1;
        for (auto &it : prisoners)
        {
            if (!it.getCoordinates(tEvent,tTotal).empty())
            {
                vector<Coordinates> &coordinates = it.getCoordinates(tEvent,tTotal);
                for (auto &it2 : coordinates)
                {
                    xDraw = static_cast<int>((x1-it2.getX())/coorXForOnePix)-(widthOfDot/2);
                    yDraw = static_cast<int>((y1-it2.getY())/coorYForOnePix)-(heightOfDot/2);
                    if (!mapevent && !markevent) painter.drawImage(xDraw,yDraw,imgdot);
                    if (mapevent && markevent) painter2.drawImage(xDraw,yDraw,imgdotevent);
                    if (mapevent && !markevent) painter2.drawImage(xDraw,yDraw,imgdot);
                    if (!mapevent && markevent) painter.drawImage(xDraw,yDraw,imgdotevent);
                    //painter.drawImage(xDraw,yDraw,imgdot);
                }
            }
        }
    }

    // Конвертация даты в строку
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, ".\\Maps\\Map-%Y-%m-%d-%H-%M-%S.png");
    auto str = oss.str();
    std::ostringstream oss2;
    oss2 << std::put_time(&tm, ".\\Maps\\MapEvent-%Y-%m-%d-%H-%M-%S.png");
    auto str2 = oss2.str();

    painter.end();
    painter2.end();
    if (mapsandbox || (event && !mapevent))
        imgmap.save(QString::fromStdString(str));
    if (mapevent)
        imgmap2.save(QString::fromStdString(str2));
}
