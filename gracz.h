#ifndef GRACZ_H_
#define GRACZ_H_

#include "jednostka.h"
#include "weapon.h"

using namespace std;

class Gracz : public Jednostka{
private:
    Weapon bron;
    int lvl;
	int amunicja;
	Kolory KeyColor;
public:
    Gracz(int _x, int _y, int _hp, char _kierunek, char model, int _lvl, int _amunicja, Kolory _Color);
    virtual ~Gracz();

    Weapon* GetWeapon();
    int GetLvl() const;
    int GetAmunicja() const;
    Kolory GetKeyColor() const;

    void SetLvl(int _lvl);
    void SetAmunicja(int _amunicja);
    void SetWeapon(Weapon ptr);
    void SetKeyColor(Kolory kolor);

    void ModifyAmunicja(int _amunicja);
    void ModifyLvl(int _lvl);
    void Move(char&);



};

#endif // GRACZ_H_
