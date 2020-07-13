#include "gracz.h"
using namespace std;

Gracz::Gracz(int _x, int _y, int _hp, char _kierunek, char model, int _lvl, int _amunicja, Kolory _Color) :
	Jednostka(_x,_y,_hp, model,_kierunek,0), lvl(_lvl), amunicja(_amunicja){
	    Color = _Color;
        score = 0;
        KeyColor = _White;
    }

Gracz::~Gracz(){}

Weapon* Gracz::GetWeapon() {return &bron;}
int Gracz::GetLvl() const {return lvl;}
int Gracz::GetAmunicja() const {return amunicja;}
Kolory Gracz::GetKeyColor() const {return KeyColor;}

void Gracz::SetLvl(int _lvl) {lvl = _lvl;}
void Gracz::SetAmunicja(int _amunicja) {amunicja = _amunicja;}
void Gracz::SetWeapon(Weapon ptr) {bron = ptr;}
void Gracz::SetKeyColor(Kolory kolor) {KeyColor = kolor;}

void  Gracz::ModifyAmunicja(int _amunicja) {amunicja += _amunicja;}
void  Gracz::ModifyLvl(int _lvl) { lvl += _lvl;}

void Gracz::Move(char& key){

	setPosition(x, y);
	TextColor(_White);
	std::cout << " ";

	//Kierunek w ktorym zwrocony jest gracz
	if(key == 'H'){
        model = PlayerModel_W;
		kierunek = 'w';
	}
	if(key == 'P'){
        model = PlayerModel_S;
		kierunek = 's';
	}
	if(key == 'K'){
        model = PlayerModel_A;
		kierunek = 'a';
	}
	if(key == 'M'){
        model = PlayerModel_D;
		kierunek = 'd';
	}

	if(key == 'd'){
		if (readChar(x+1, y) != WallModel){++x;}
		model = PlayerModel_D;
		kierunek = 'd';
	}
	if(key == 'a'){
		if (readChar(x-1, y) != WallModel){--x;}
		model = PlayerModel_A;
		kierunek = 'a';
	}

	if(key == 's'){
		if (readChar(x, y+1) != WallModel){++y;}
		model = PlayerModel_S;
		kierunek = 's';
	}

	if(key == 'w'){
		if (readChar(x, y-1) != WallModel){--y;}
		model = PlayerModel_W;
		kierunek = 'w';
	}

    key = ' ';
	setPosition(x,y);
	TextColor(Color);
	cout << model;
}
