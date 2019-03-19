#include <QCoreApplication>
#include <QDebug>
#include <vector>
#include <iostream>
#include <fstream>
#include <logparser.h>
#include <prisoner.h>
#include <QDebug>
#include <settings.h>
#include <outfile.h>
#include <drawmap.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    setlocale(LC_ALL,"Russian");

    Settings settings;

    list<Prisoner> prisoners;
    array<int, 32> sectors {0};
    LogParser parser(prisoners,sectors);

    // парсим лог файлы
    if (argc>1)
        for (int i=1;i<argc;++i)
        {
            parser.startParse(argv[i]);
        }
    else
        parser.startParse("Log_Kill.txt");

    // печать данных в файл
    if (settings.getRecordStats() && (settings.getSandbox() || settings.getEvents()))
    {

        Outfile outf(prisoners,sectors,parser,settings.getSandbox(),settings.getEvents(),settings.getAllStats());
        if (settings.getSteamID())
        {
            wcout << L"Идем обработка данных с steamcommunity.com ........" << endl;
            parser.steamParser();
            outf.setSteamName(settings.getSteamID());
        }
        outf.printToFile();
    }

    if (settings.getMap() || settings.getEvents())
        DrawMap drawmap(prisoners,settings.getMap(),settings.getEvents(),settings.getMapEvent(),settings.getMarkEvent());

    exit(0);

    return a.exec();
}

