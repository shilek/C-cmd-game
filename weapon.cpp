#include "weapon.h"

Weapon::Weapon(){}

Weapon::Weapon(int _dystans, int _obrazenia, int _amunicjaMagaz, int _maxPojMagazynka, int _predkoscAtaku, std::string _nazwa) :
		dystans(_dystans), obrazenia(_obrazenia), amunicjaMagaz(_amunicjaMagaz), maxPojMagazynka(_maxPojMagazynka), predkoscAtaku(_predkoscAtaku), nazwa(_nazwa){}

Weapon::~Weapon(){}

int Weapon::GetDystans() const  {return dystans;}
int Weapon::GetObrazenia() const  {return obrazenia;}
int Weapon::GetAmmMag() const  {return amunicjaMagaz;}
int Weapon::GetPojMagMax() const  {return maxPojMagazynka;}
int Weapon::GetPredkoscAtaku() const  {return predkoscAtaku;}
std::string Weapon::GetNazwa() const  {return nazwa;}

void Weapon::SetDystans(int _dystans) {dystans = _dystans;}
void Weapon::SetObrazenia(int _obrazenia) {obrazenia = _obrazenia;}
void Weapon::SetAmmMag(int _amunicjaMagaz) {amunicjaMagaz = _amunicjaMagaz;}
void Weapon::SetPojMagMax(int _maxPojMagazynka) {maxPojMagazynka = _maxPojMagazynka;}
void Weapon::SetPredkoscAtaku(int _predkoscAtaku) {predkoscAtaku = _predkoscAtaku;}
void Weapon::SetNazwa(std::string _nazwa) {nazwa = _nazwa;}

void Weapon::ModifyMagAmmo(int _ammo) {amunicjaMagaz += _ammo;}
