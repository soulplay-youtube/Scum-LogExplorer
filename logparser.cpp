#include "logparser.h"

LogParser::LogParser(list<Prisoner> &person, array<int,32> &sector)
    : prisoners(person), sectors(sector)
{

}

void LogParser::startParse(const string &fileName)
{
    inf.open(fileName);
    wstring strInput; //Строка из файла
    //string strOutput;
    wstring diedName;
    wstring diedSteamID;
    wstring killerName;
    wstring killerSteamID;
    double x,y;

    bool event{false}; // false - режим песочницы, true - режим event
    bool coordinates{false};

    getline(inf, strInput);
    while(inf)
    {
        event=false;
        coordinates=false;
        if(strInput.find(L"event")==-1) event=false;
        else event=true;

        // поиск Names и SteamID
        int positions[8];
        positions[0] = strInput.find(L"Died: ",0);
        positions[1] = strInput.find(L" (",positions[0]+6);
        positions[2] = strInput.find(L"), Killer: ",positions[1]+2);
        positions[3] = strInput.find(L" (",positions[2]+11);
        positions[4] = strInput.find(L")",positions[3]+2);
        // Если Names и SteamID не найдены переходим к следующему циклу
        if (positions[0]==-1 || positions[1]==-1 || positions[2]==-1 || positions[3]==-1 || positions[4]==-1)
        {
            getline(inf, strInput);
            continue;
        }
        // Обрезка строк
        diedName = strInput.substr(positions[0]+6,positions[1]-positions[0]-6);
        diedSteamID = strInput.substr(positions[1]+2,positions[2]-positions[1]-2);
        killerName = strInput.substr(positions[2]+11,positions[3]-positions[2]-11);
        killerSteamID = strInput.substr(positions[3]+2,positions[4]-positions[3]-2);
        // steamID убийцы и жертвы не должны быть равны, переходим к след циклу
        if (diedSteamID==killerSteamID)
        {
            getline(inf, strInput);
            continue;
        }

        //Получение координат
        positions[5]=strInput.find(L"VictimLoc: ",positions[4]+1);
        positions[6]=strInput.find(L", ",positions[5]+11);
        positions[7]=strInput.find(L", ",positions[6]+2);
        // Если координаты не найдены переходим к следующему циклу
        if (positions[5]!=-1 && positions[6]!=-1 && positions[7]!=-1)
        {
            x=stod(strInput.substr(positions[5]+11,positions[6]-positions[5]-11));
            y=stod(strInput.substr(positions[6]+2,positions[7]-positions[6]-2));
            coordinates=true;
        }

        // Внесение Names и SteamID в класс Prisoner
        // Запись Died
        bool personIsCreated {false};
        for (auto &it : prisoners)
        {
            if (it.getSteamID()==diedSteamID)
            {
                it.plusDeath(killerName,event);
                personIsCreated=true;
                break;
            }
        }
        if (!personIsCreated)
        {
            prisoners.push_back(Prisoner(diedSteamID,diedName));
            prisoners.back().plusDeath(killerName,event);
        }
        // Запись Killer
        personIsCreated = false;
        for (auto &it : prisoners)
        {
            if (it.getSteamID()==killerSteamID)
            {
                it.plusFrag(diedName,event);
                personIsCreated=true;
                if (coordinates) it.setCoordinates(x,y,event);
                break;
            }
        }
        if (!personIsCreated)
        {
            prisoners.push_back(Prisoner(killerSteamID,killerName));
            prisoners.back().plusFrag(diedName,event);
            if (coordinates) prisoners.back().setCoordinates(x,y,event);
        }

        if (coordinates) sectorCalculation(x,y,event);

        getline(inf, strInput);
    }
    if (inf.is_open()) inf.close();
}

void LogParser::topKillCalculation(bool event, bool total)
{
    for (auto &it : prisoners)
    {
        it.setMode(event,total,0);
    }
    prisoners.sort();
}

void LogParser::topDeathCalculation(bool event, bool total)
{
    for (auto &it : prisoners)
    {
        it.setMode(event,total,1);
    }
    prisoners.sort();
}

void LogParser::topKDCalculation(bool event, bool total)
{
    for (auto &it : prisoners)
    {
        it.setMode(event,total,2);
    }
    prisoners.sort();
}

void LogParser::sectorCalculation(double &x, double &y, bool event)
{
    int s = Coordinates::getSectorFromXY(x,y);
    if (!event) ++sectors[s-1];
    else ++sectors[15+s];
}

void LogParser::steamParser()
{
    for (auto &it : prisoners)
    {
        if (it.getName().find(L"?")!=-1)
        {
            QNetworkAccessManager manager;
            manager.setRedirectPolicy(QNetworkRequest::NoLessSafeRedirectPolicy);
            QString adress = "https://steamcommunity.com/profiles/" + QString::fromStdWString(it.getSteamID());
            QNetworkReply *response = manager.get(QNetworkRequest(QUrl(adress)));
            QEventLoop event;
            QObject::connect(response,SIGNAL(finished()),&event,SLOT(quit()));
            event.exec();
            QString html = response->readAll();
            //qDebug() << html;
            int beginNamePos, endNamePos;
            beginNamePos = html.indexOf("<span class=\"actual_persona_name\">",0);
            endNamePos = html.indexOf("</span>",beginNamePos+34);
            if (beginNamePos!=-1 && endNamePos!=-1)
            {
                QString profile = html.mid(beginNamePos+34,endNamePos-beginNamePos-34);
                if (profile.indexOf("☭",0)==-1 && profile.indexOf("︻",0)==-1 && profile.indexOf("デ",0)==-1 && profile.indexOf("═",0)==-1
                        && profile.indexOf("一",0)==-1 && profile.indexOf("芫",0)==-1 && profile.indexOf("丶",0)==-1)
                {
                    wstring strProfile = profile.toStdWString();
                    it.addSteamNames(strProfile);
                    wcout << it.getSteamID() << L" - " << strProfile << endl;
                }
            }
            QObject::disconnect(response,SIGNAL(finished()),&event,SLOT(quit()));
        }
    }
}
