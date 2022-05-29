//
// Created by kay on 22.04.22.
//

#include <iostream>
#ifndef SO2_FFXIII_POSTAC_H
#define SO2_FFXIII_POSTAC_H

using namespace std;

class Postac {

private:
    bool pokonany;
    int HP, MP, AD, AP, MR, ARMOR, DELAY, turns_executed;
    int baseHP, baseMP;
    string NAME;

public:
    Postac(string name, int hp, int mp, int ad, int ap, int mr, int armor, int delay);

    string atakuj(Postac &enemy);
    string czaruj(Postac &enemy);
    string lecz();
    string obrona_fizyczna();
    string zaslona_antymagiczna();

    int getHp() const;

    int getMp() const;

    int getAd() const;
    int getAp() const;
    int getMr() const;

    int getArmor() const;
    int getDelay() const;

    bool isPokonany() const;

    void setPokonany(bool pokonany);

    int getTurnsExecuted() const;

    void setTurnsExecuted(int turnsExecuted);

    const string &getName() const;
};


#endif //SO2_FFXIII_POSTAC_H
