#include "outfile.h"

Outfile::Outfile(list<Prisoner> &prisoner, array<int, 32> &sector, LogParser &parse, bool sandbox, bool event, bool total)
    : prisoners(prisoner), sectors(sector), parser(parse)
{
    this->sandbox=sandbox;
    this->event=event;
    this->total=total;
    // Конвертация даты в строку
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, ".\\Stats\\ScumStats-%Y-%m-%d-%H-%M-%S.txt");
    auto str = oss.str();

    // открытие файла для записи
    outf.open(str);
    if (!outf.is_open()) exit(1);
}

void Outfile::printToFile()
{
    // Топ убийств
    bool tTotal=total; if (!sandbox) tTotal=0;
    int iter = 1;
    int deadBodySandbox=0; int deadBodyEvent=0;
    if (event && !total) iter=2;
    while (iter)
    {
        bool tEvent=1;

        if ((!event || (!total && iter==2))&&sandbox)
        {
            outf << L"Топ убийств в режиме свободной игры:" << endl;
            tEvent=0;
        }
        if ((!sandbox || (!total && iter==1))&&event)
        {
            outf << L"Топ убийств в режиме event:" << endl;
            tEvent=1;
        }
        if (sandbox && event && total) outf << L"Топ убийств в режимах свободной игры и в event:" << endl;
        if (sandbox || event)
        {
            parser.topKillCalculation(tEvent,tTotal);
            for (auto &it : prisoners)
            {
            if (!it.getSteamNames().empty())
                outf << it.getSteamNames()[0];
            else
                outf << it.getName();
            outf << ": " << it.getKills(tEvent,tTotal) << endl;

            //считаем количество трупов
            if ((!tEvent && !tTotal) || (tEvent && tTotal)) deadBodySandbox += it.getKills(tEvent,tTotal);
            if (tEvent && !tTotal) deadBodyEvent += it.getKills(tEvent,tTotal);
            }
            outf << endl;
        }
        --iter;
    }

    // Кол-во трупов
    iter = 1;
    if (event && !total) iter=2;
    while (iter)
    {
        if ((!event || (!total && iter==2))&&sandbox)
            outf << L"Общее количество убийств в режиме свободной игры: " << deadBodySandbox << endl << endl;
        if ((!sandbox || (!total && iter==1))&&event)
            outf << L"Общее количество убийств в режиме event: " << deadBodyEvent << endl << endl;
        if (sandbox && event && total)
            outf << L"Общее количество убийств в режимах свободной игры и в event: " << deadBodySandbox << endl << endl;
        --iter;
    }

    // Топ смертей
    iter = 1;
    if (event && !total) iter=2;
    while (iter)
    {
        bool tEvent=1;

        if ((!event || (!total && iter==2))&&sandbox)
        {
            outf << L"Топ смертей в режиме свободной игры:" << endl;
            tEvent=0;
        }
        if ((!sandbox || (!total && iter==1))&&event)
        {
            outf << L"Топ смертей в режиме event:" << endl;
            tEvent=1;
        }
        if (sandbox && event && total) outf << L"Топ смертей в режимах свободной игры и в event:" << endl;
        if (sandbox || event)
        {
            parser.topDeathCalculation(tEvent,tTotal);
            for (auto &it : prisoners)
            {
                if (!it.getSteamNames().empty())
                    outf << it.getSteamNames()[0];
                else
                    outf << it.getName();
                outf << ": " << it.getDeaths(tEvent,tTotal) << endl;
            }
            outf << endl;
        }

        --iter;
    }

    // Топ KD
    iter = 1;
    if (event && !total) iter=2;
    while (iter)
    {
        bool tEvent=1;

        if ((!event || (!total && iter==2))&&sandbox)
        {
            outf << L"KD в режиме свободной игры:" << endl;
            tEvent=0;
        }
        if ((!sandbox || (!total && iter==1))&&event)
        {
            outf << L"KD в режиме event:" << endl;
            tEvent=1;
        }
        if (sandbox && event && total) outf << L"KD в режимах свободной игры и в event:" << endl;
        if (sandbox || event)
        {
            parser.topKDCalculation(tEvent,tTotal);
            for (auto &it : prisoners)
            {
                if (!it.getSteamNames().empty())
                    outf << it.getSteamNames()[0];
                else
                    outf << it.getName();
                outf << ": " << it.getKD(tEvent,tTotal) << endl;
            }
            outf << endl;
        }

        --iter;
    }

    // Топ секторов
    if ((sandbox && !event) || (sandbox && event && !total))
    {
        outf << L"Кол-во убийств по секторам в режиме свободной игры: " << endl;
        for (int i=0; i<16; i++)
        {
            switch (i) {
            case 0: outf << L"A1 - " << sectors[i] << endl; break;
            case 1: outf << L"A2 - " << sectors[i] << endl; break;
            case 2: outf << L"A3 - " << sectors[i] << endl; break;
            case 3: outf << L"A4 - " << sectors[i] << endl; break;
            case 4: outf << L"B1 - " << sectors[i] << endl; break;
            case 5: outf << L"B2 - " << sectors[i] << endl; break;
            case 6: outf << L"B3 - " << sectors[i] << endl; break;
            case 7: outf << L"B4 - " << sectors[i] << endl; break;
            case 8: outf << L"C1 - " << sectors[i] << endl; break;
            case 9: outf << L"C2 - " << sectors[i] << endl; break;
            case 10: outf << L"C3 - " << sectors[i] << endl; break;
            case 11: outf << L"C4 - " << sectors[i] << endl; break;
            case 12: outf << L"D1 - " << sectors[i] << endl; break;
            case 13: outf << L"D2 - " << sectors[i] << endl; break;
            case 14: outf << L"D3 - " << sectors[i] << endl; break;
            case 15: outf << L"D4 - " << sectors[i] << endl; break;
            default: break;
            }
        }
        outf << endl;
    }
    if ((!sandbox && event) || (sandbox && event && !total))
    {
        outf << L"Кол-во убийств по секторам в режиме Event: " << endl;
        for (int i=16; i<31; i++)
        {
            switch (i) {
            case 16: outf << L"A1 - " << sectors[i] << endl; break;
            case 17: outf << L"A2 - " << sectors[i] << endl; break;
            case 18: outf << L"A3 - " << sectors[i] << endl; break;
            case 19: outf << L"A4 - " << sectors[i] << endl; break;
            case 20: outf << L"B1 - " << sectors[i] << endl; break;
            case 21: outf << L"B2 - " << sectors[i] << endl; break;
            case 22: outf << L"B3 - " << sectors[i] << endl; break;
            case 23: outf << L"B4 - " << sectors[i] << endl; break;
            case 24: outf << L"C1 - " << sectors[i] << endl; break;
            case 25: outf << L"C2 - " << sectors[i] << endl; break;
            case 26: outf << L"C3 - " << sectors[i] << endl; break;
            case 27: outf << L"C4 - " << sectors[i] << endl; break;
            case 28: outf << L"D1 - " << sectors[i] << endl; break;
            case 29: outf << L"D2 - " << sectors[i] << endl; break;
            case 30: outf << L"D3 - " << sectors[i] << endl; break;
            case 31: outf << L"D4 - " << sectors[i] << endl; break;
            default: break;
            }
        }
        outf << endl;
    }
    if (sandbox && event && total)
    {
        outf << L"Кол-во убийств по секторам в режимах свободной игры и в event: " << endl;
        for (int i=0; i<16; i++)
        {
            switch (i) {
            case 0: outf << L"A1 - " << sectors[i]+sectors[i+16] << endl; break;
            case 1: outf << L"A2 - " << sectors[i]+sectors[i+16] << endl; break;
            case 2: outf << L"A3 - " << sectors[i]+sectors[i+16] << endl; break;
            case 3: outf << L"A4 - " << sectors[i]+sectors[i+16] << endl; break;
            case 4: outf << L"B1 - " << sectors[i]+sectors[i+16] << endl; break;
            case 5: outf << L"B2 - " << sectors[i]+sectors[i+16] << endl; break;
            case 6: outf << L"B3 - " << sectors[i]+sectors[i+16] << endl; break;
            case 7: outf << L"B4 - " << sectors[i]+sectors[i+16] << endl; break;
            case 8: outf << L"C1 - " << sectors[i]+sectors[i+16] << endl; break;
            case 9: outf << L"C2 - " << sectors[i]+sectors[i+16] << endl; break;
            case 10: outf << L"C3 - " << sectors[i]+sectors[i+16] << endl; break;
            case 11: outf << L"C4 - " << sectors[i]+sectors[i+16] << endl; break;
            case 12: outf << L"D1 - " << sectors[i]+sectors[i+16] << endl; break;
            case 13: outf << L"D2 - " << sectors[i]+sectors[i+16] << endl; break;
            case 14: outf << L"D3 - " << sectors[i]+sectors[i+16] << endl; break;
            case 15: outf << L"D4 - " << sectors[i]+sectors[i+16] << endl; break;
            default: break;
            }
        }
        outf << endl;
    }

    // Альтернативные имена
    if (findSteamName)
    {
        outf << L"Подмена имени с сайта https://steamcommunity.com: " << endl;
        for (auto &it : prisoners)
        {
            if (!it.getSteamNames().empty())
            {
                outf << it.getSteamID() << " - " << it.getName() << " - "
                     << it.getSteamNames()[0] << endl;
            }
        }
        outf << endl;
    }

    // Описание каждого игрока
    iter = 1;
    if (event && !total) iter=2;
    while (iter)
    {
        bool tEvent=1;

        if ((!event || (!total && iter==2))&&sandbox)
        {
            outf << L"Достижения игроков в режиме свободной игры:" << endl << endl;
            tEvent=0;
        }
        if ((!sandbox || (!total && iter==1))&&event)
        {
            outf << L"Достижения игроков в режиме event:" << endl << endl;
            tEvent=1;
        }
        if (sandbox && event && total) outf << L"Достижения игроков в режимах свободной игры и в event:" << endl << endl;
        if (sandbox || event)
        {
            parser.topKillCalculation(tEvent,tTotal);
            for (auto &it : prisoners)
            {
                outf << L"         " << it.getName();
                if (!it.getSteamNames().empty())
                    outf << L" /// " << it.getSteamNames()[0];
                outf << endl;
                outf << L"SteamID: " << it.getSteamID() << endl;
                outf << L"Убийств: " << it.getKills(tEvent,tTotal) << endl;
                outf << L"Смертей: " << it.getDeaths(tEvent,tTotal) << endl;
                outf << L"KD: " << it.getKD(tEvent,tTotal) << endl;
                if (!it.getKillersNames(tEvent,tTotal).empty())
                {
                    outf << L"Убит игроками: " << endl;
                    const map<wstring,int> &killersNames = it.getKillersNames(tEvent,tTotal);
                    for (auto &it2 : killersNames)
                        outf << "   " << it2.first << L" x " << it2.second << endl;
                }
                if (!it.getFragsNames(tEvent,tTotal).empty())
                {
                    outf << L"Имена жертв: " << endl;
                    const map<wstring,int> &fragsNames = it.getFragsNames(tEvent,tTotal);
                    for (auto &it2 : fragsNames)
                        outf << "   " << it2.first << L" x " << it2.second << endl;
                }
                outf << endl;
            }
            outf << endl;
        }
        --iter;
    }

}

void Outfile::setSteamName(bool findName)
{
    findSteamName=findName;
}

Outfile::~Outfile()
{
    outf.close();
}
