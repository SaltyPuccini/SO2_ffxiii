//
// Created by kay on 22.04.22.
//

#include "Postac.h"

string Postac::czaruj(Postac &enemy) {
    if (MP>4){
        int DMG = 0.5 * AP - 0.1 * enemy.MR;
        if (DMG < 0){
            DMG = 0;
        }
        enemy.HP = enemy.HP - DMG;
        MP = MP - 4;
        return getName()+" zadał "+ to_string(DMG)+" obrażeń magicznych. "+enemy.getName()+" ma teraz "+ to_string(enemy.getHp())+" HP.";
    }else{
        return getName()+ " posiada za mało MP na czarowanie.";
    }
}

string Postac::atakuj(Postac &enemy) {
    int DMG = 0.5 * AD - 0.3 * enemy.ARMOR;
    if (DMG < 0){
        DMG = 0;
    }
    enemy.HP = enemy.HP - DMG;
    return getName()+" zadał " + to_string(DMG) +" obrażeń fizycznych. "+enemy.getName()+" ma teraz "+to_string(enemy.getHp())+" HP.";
}

string Postac::lecz() {
    if (MP>4) {
        int leczonko = 0.3 * AP;
        HP = HP + leczonko;
        if (HP > baseHP){
            HP = baseHP;
        }
        MP = MP - 4;
        return getName()+" wyleczył się za "+ to_string(leczonko)+" punktów zdrowia. Ma teraz "+ to_string(getHp())+" HP.";
    }
    else{
        return getName()+ " posiada za mało MP na leczenie.";
    }
}

string Postac::obrona_fizyczna() {
    ARMOR = ARMOR + 1;
    return getName()+" broni się przed atakami fizycznymi.";
}

string Postac::zaslona_antymagiczna() {
    MR = MR + 1;
    return getName()+" broni się przed atakami magicznymi.";
}

int Postac::getHp() const {
    return HP;
}



int Postac::getMp() const {
    return MP;
}



int Postac::getAd() const {
    return AD;
}



int Postac::getAp() const {
    return AP;
}



int Postac::getMr() const {
    return MR;
}



int Postac::getArmor() const {
    return ARMOR;
}



int Postac::getDelay() const {
    return DELAY;
}



const string &Postac::getName() const {
    return NAME;
}



Postac::Postac(string name, int hp, int mp, int ad, int ap, int mr, int armor, int delay) {
    NAME = name;
    HP = hp;
    MP = mp;
    baseHP = hp;
    baseMP = mp;
    AD = ad;
    AP = ap;
    MR = mr;
    ARMOR = armor;
    DELAY = delay;
    pokonany = false;
    turns_executed = 0;
}

bool Postac::isPokonany() const {
    return pokonany;
}

void Postac::setPokonany(bool pokonany) {
    Postac::pokonany = pokonany;
}

int Postac::getTurnsExecuted() const {
    return turns_executed;
}

void Postac::setTurnsExecuted(int turnsExecuted) {
    turns_executed = turnsExecuted;
}
