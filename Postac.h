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
    float ATB_GAUGE{};
    string NAME;

public:
    Postac(string name, int hp, int mp, int ad, int ap, int mr, int armor, int delay);

    string atakuj(Postac &enemy);
    string czaruj(Postac &enemy);
    string lecz();
    string obrona_fizyczna();
    string zaslona_antymagiczna();

    int getHp() const;
    void setHp(int hp);

    int getMp() const;
    void setMp(int mp);

    int getAd() const;
    void setAd(int ad);

    int getAp() const;
    void setAp(int ap);

    int getMr() const;
    void setMr(int mr);

    int getArmor() const;
    void setArmor(int armor);

    int getDelay() const;
    void setDelay(int haste);

    bool isPokonany() const;

    void setPokonany(bool pokonany);

    int getTurnsExecuted() const;

    void setTurnsExecuted(int turnsExecuted);

    int getBaseHp() const;

    void setBaseHp(int baseHp);

    int getBaseMp() const;

    void setBaseMp(int baseMp);

    float getAtbGauge() const;
    void setAtbGauge(float atbGauge);

    const string &getName() const;
    void setName(const string &name);
};


#endif //SO2_FFXIII_POSTAC_H
