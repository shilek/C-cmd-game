#ifndef PRZEDMIOT_H_
#define PRZEDMIOT_H_

#include "game.h"
#include <string>
using namespace std;

class Przedmiot : public Game{
private:
    char typ;
    string nazwa;
    bool istnieje;
public:
    Przedmiot(int _x, int _y, char _typ, Kolory _color);
    ~Przedmiot();

    int GetX() const;
    int GetY() const;
    char GetTyp() const;
    string GetNazwa() const;
    bool GetIstnieje() const;

    void SetX(int);
    void SetY(int);
    void SetIstnieje(bool);

    Kolizje Rysuj();
    void PickUp();
};

#endif // PRZEDMIOT_H_
