#ifndef WEAPON_H_
#define WEAPON_H_

#include <string>
class Weapon{
protected:
    int dystans;
	int obrazenia;
	int amunicjaMagaz;
	int maxPojMagazynka;
	int predkoscAtaku;
    std::string nazwa;
public:
	Weapon();
    Weapon(int _dystans, int _obrazenia, int _amunicjaMagaz, int _maxPojMagazynka, int _predkoscAtaku, std::string _nazwa);
    ~Weapon();

    int GetDystans() const;
    int GetObrazenia() const;
    int GetAmmMag() const;
    int GetPojMagMax() const;
    int GetPredkoscAtaku() const;

    std::string GetNazwa() const;
    void SetDystans(int _dystans);
    void SetObrazenia(int _obrazenia);
    void SetAmmMag(int _pojMagazynka);
    void SetPojMagMax(int _maxPojMagazynka);
    void SetPredkoscAtaku(int _predkoscAtaku);
    void SetNazwa(std::string _nazwa);

    void ModifyMagAmmo(int _ammo);
};


#endif // WEAPON_H_
