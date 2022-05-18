#include <iostream>
#include "Postac.h"
#include <pthread.h>
#include <unistd.h>
#include <random>
#include <vector>


using namespace std;


#define ROWS 9
#define COLUMNS 8
const string V_CUR = "  V  ";
string siatka[ROWS][COLUMNS];
Postac gracz("Light", 1000, 100, 100, 100, 100, 100, 7);
int seconds_passed = 0;
bool is_end = false;
vector<Postac> wrogowie;
int vertical_cursor_position = 3;
string komunikat = "Start";
string komunikatRDY = "   ";
string timerWroga = "   ";
int akcja = 0;

bool areAllDefated(vector<Postac> enemies) {
    for (int i = 0; i < enemies.size(); i++) {
        if (!enemies[i].isPokonany()) {
            return false;
        }
    }
    return true;
}

bool is_dead(Postac entity) {
    if (entity.getHp() <= 0) {
        komunikat = entity.getName() + " died.";
        return true;
    } else {
        return false;
    }
}

void *enemyAction(void *hero) {

    auto *postac = (Postac *) hero;

    while (!is_end && !postac->isPokonany()) {
        timerWroga = to_string(wrogowie[vertical_cursor_position - 3].getDelay() * (wrogowie[vertical_cursor_position - 3].getTurnsExecuted() + 1) - seconds_passed);
        if (seconds_passed >= postac->getDelay() * (postac->getTurnsExecuted() + 1)) {
            postac->setTurnsExecuted(postac->getTurnsExecuted() + 1);

            random_device dev;
            mt19937 rng(dev());
            uniform_int_distribution<std::mt19937::result_type> dist(1, 5);

            int wybor = dist(rng);

            switch (wybor) {
                case 1:
                    komunikat = postac->obrona_fizyczna();
                    break;
                case 2:
                    komunikat = postac->zaslona_antymagiczna();
                    break;
                case 3:
                    komunikat = postac->lecz();
                    break;
                case 4:
                    komunikat = postac->atakuj(gracz);
                    is_end = is_dead(gracz);
                    break;
                case 5:
                    komunikat = postac->czaruj(gracz);
                    is_end = is_dead(gracz);
                    break;
                default:
                    break;
            }
        }

    }
    return nullptr;
}

void *secondsCounter(void *args) {
    while (seconds_passed < 120 && !is_end) {
        sleep(1);
        seconds_passed = seconds_passed + 1;

    }
    is_end = true;
    return nullptr;
}

void *updateScreen(void *hero) {

    int ile_wrogow = wrogowie.size();

    while (!is_end) {

        siatka[5][4] = "( ͡° ͜ʖ ͡°)";

        for (int j = 0; j < ile_wrogow; j++) {
            siatka[0][j + 3] = "  " + to_string(j+1);
            if (!wrogowie[j].isPokonany())
                siatka[1][j + 3] = "d-_-b";
            else
                siatka[1][j + 3] = " [*] ";
        }

        siatka[0][vertical_cursor_position] = V_CUR;

        switch (akcja) {
            case 1:
                siatka[3][1] = "->ATAK";
                siatka[4][1] = "  MAGIA";
                siatka[5][1] = "  LECZENIE";
                siatka[6][1] = "  PANCERZ";
                siatka[7][1] = "  ODPORNOŚĆ";
                break;
            case 2:
                siatka[3][1] = "  ATAK";
                siatka[4][1] = "->MAGIA";
                siatka[5][1] = "  LECZENIE";
                siatka[6][1] = "  PANCERZ";
                siatka[7][1] = "  ODPORNOŚĆ";
                break;
            case 3:
                siatka[3][1] = "  ATAK";
                siatka[4][1] = "  MAGIA";
                siatka[5][1] = "->LECZENIE";
                siatka[6][1] = "  PANCERZ";
                siatka[7][1] = "  ODPORNOŚĆ";
                break;
            case 4:

                siatka[3][1] = "  ATAK";
                siatka[4][1] = "  MAGIA";
                siatka[5][1] = "  LECZENIE";
                siatka[6][1] = "->PANCERZ";
                siatka[7][1] = "  ODPORNOŚĆ";

                break;
            case 5:

                siatka[3][1] = "  ATAK";
                siatka[4][1] = "  MAGIA";
                siatka[5][1] = "  LECZENIE";
                siatka[6][1] = "  PANCERZ";
                siatka[7][1] = "->ODPORNOŚĆ";
            default:

                siatka[3][1] = "  ATAK";
                siatka[4][1] = "  MAGIA";
                siatka[5][1] = "  LECZENIE";
                siatka[6][1] = "  PANCERZ";
                siatka[7][1] = "  ODPORNOŚĆ";
                break;
        }



        siatka[8][3] = komunikat;
        siatka[8][0] = komunikatRDY;
        siatka[1][6] = timerWroga;
        siatka[0][0] = to_string(seconds_passed);


        Postac zaznaczonyWrog = wrogowie[vertical_cursor_position - 3];

        siatka[0][7] = wrogowie[vertical_cursor_position - 3].getName();
        siatka[1][7] = "HP: " + to_string(zaznaczonyWrog.getHp()) + " | MP: " + to_string(zaznaczonyWrog.getMp());
        siatka[2][7] = "AD: " + to_string(zaznaczonyWrog.getAd()) + " | AP: " + to_string(zaznaczonyWrog.getAp());
        siatka[3][7] = "ARMOR: " + to_string(zaznaczonyWrog.getArmor()) + " | MR: " + to_string(zaznaczonyWrog.getMr());

        siatka[4][7] = gracz.getName();
        siatka[5][7] = "       HP: " + to_string(gracz.getHp()) + " | MP: " + to_string(gracz.getMp());
        siatka[6][7] = "AD: " + to_string(gracz.getAd()) + " | AP: " + to_string(gracz.getAp());
        siatka[7][7] = "  ARMOR: " + to_string(gracz.getArmor()) + " | MR: " + to_string(gracz.getMr());


        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 8; j++) {
                cout.width(15);
                cout << left << siatka[i][j] << " ";
            }
            cout << endl;
        }
        usleep(50000);
        system("clear");
    }
    return nullptr;
}

void *inputReader(void *hero) {
    int c;
    while (!is_end) {
        c = getchar();
        if (c == '1' && !is_dead(wrogowie[3 - 3]))
            vertical_cursor_position = 3;
        if (c == '2' && !is_dead(wrogowie[4 - 3]))
            vertical_cursor_position = 4;
        if (c == '3' && !is_dead(wrogowie[5 - 3]))
            vertical_cursor_position = 5;
       /* if (c == 'q')
            akcja = 1;
        komunikatRDY = "   ";
        if (c == 'w')
            akcja = 2;
        komunikatRDY = "   ";
        if (c == 'e')
            akcja = 3;
        komunikatRDY = "   ";
        if (c == 'r')
            akcja = 4;
        komunikatRDY = "   ";
        if (c == 't')
            akcja = 5;
        komunikatRDY = "   ";
    }*/
    }
    return nullptr;
}

void *mainHero(void *hero) {
    while (!is_end) {
        komunikatRDY = to_string(gracz.getDelay() * (gracz.getTurnsExecuted() + 1) - seconds_passed);
        if (seconds_passed >= gracz.getDelay() * (gracz.getTurnsExecuted() + 1)) {
            random_device dev;
            mt19937 rng(dev());
            uniform_int_distribution<std::mt19937::result_type> dist(1, 5);
            uniform_int_distribution<std::mt19937::result_type> distWrog(3, 5);
            int nr_wroga;
            akcja = dist(rng);
            /*do {
                vertical_cursor_position = distWrog(rng);*/
                nr_wroga = vertical_cursor_position - 3;
            /*} while (wrogowie[nr_wroga].getHp() <= 0);
*/
            gracz.setTurnsExecuted(gracz.getTurnsExecuted() + 1);

            switch (akcja) {
                case 3:
                    komunikat = gracz.lecz();
                    break;
                case 4:
                    komunikat = gracz.obrona_fizyczna();
                    break;
                case 5:
                    komunikat = gracz.zaslona_antymagiczna();
                    break;
                case 1:

                    komunikat = gracz.atakuj(wrogowie[nr_wroga]);
                    wrogowie[nr_wroga].setPokonany(is_dead(wrogowie[nr_wroga]));
                    is_end = areAllDefated(wrogowie);

                    break;
                case 2:

                    komunikat = gracz.czaruj(wrogowie[nr_wroga]);
                    wrogowie[nr_wroga].setPokonany(is_dead(wrogowie[nr_wroga]));
                    is_end = areAllDefated(wrogowie);

                    break;
                default:
                    break;
            }
        }
    }
    return nullptr;
}


int main() {


    Postac Bomb("Bomb", 1, 20, 150, 150, 20, 20, 20);
    Postac Frajer("Es", 2, 20, 10, 10, 10, 10, 50);
    Postac Kizers("Kizers", 100, 20, 10, 10, 10, 10, 55);

    wrogowie.push_back(Bomb);
    wrogowie.push_back(Frajer);
    wrogowie.push_back(Kizers);
    pthread_t input;
    pthread_t screen, timer, bohater, wrog1, wrog2, wrog3;

    pthread_create(&timer, nullptr, secondsCounter, nullptr);
    pthread_create(&screen, nullptr, updateScreen, nullptr);
    pthread_create(&input, nullptr, inputReader, nullptr);
    pthread_create(&bohater, nullptr, mainHero, nullptr);
    pthread_create(&wrog1, nullptr, enemyAction, &wrogowie[0]);
    pthread_create(&wrog2, nullptr, enemyAction, &wrogowie[1]);
    pthread_create(&wrog3, nullptr, enemyAction, &wrogowie[2]);

    pthread_join(screen, nullptr);
    pthread_join(timer, nullptr);
    pthread_join(input, nullptr);
    pthread_join(bohater, nullptr);
    pthread_join(wrog1, nullptr);
    pthread_join(wrog2, nullptr);
    pthread_join(wrog3, nullptr);

    cout << "Koniec gry!" << endl;
    bool remis = false;
    if (is_dead(gracz)) {
        cout << "Porażka..." << endl;
    } else {
        for (auto &j: wrogowie) {
            if (!j.isPokonany()) {
                cout << "Remis!" << endl;
                remis = true;
                break;
            }
        }
        if (!remis) {
            cout << "ZWYCIĘSTWO!!!" << endl;
            getchar();
        }
    }
    return 0;
}
