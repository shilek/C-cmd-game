#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <windows.h>
#include <string>


enum Kolizje{Kbrak, Kgracz, Kpocisk, Ksciana, Kdystans, Kprzedmiot};
enum Kolory{_DarkBlue = 1, _DarkGreen, _LightBlue, _Red, _Purple, _Yellow, _White, _DarkSilver, _Blue, _Green, _Ocean, _LightRed, _Pink, _Gold, _Silver};
enum MenuStatus{_NowaGra, _Wczytaj, _Informacje, _Wyjdz};
enum Bronie{_Pistolet, _Magnum44, _Karabin, _Snajperka, _RPG7, _MachineGunPKP};

const char WallModel = '#';
const char PlayerModel_D = '>';
const char PlayerModel_A = '<';
const char PlayerModel_W = '^';
const char PlayerModel_S = 'v';
const char BulletModel = 'o';
const char HpBonusModel = '+';
const char ScoreBonusModel = '*';
const char TeleportModel = '@';
const char MaxHpBonusModel = 'A';
const char AmmoBonusModel = '&';
const char KeyModel = '|';
const char EnemyModel_X = 'x';
const char PistoletModel = 'P';
const char MagnumModel = 'M';
const char KarabinModel = 'K';
const char SnajperkaModel = 'S';
const char RPGModel = 'R';
const char MachineGunPKPModel = 'G';

const int LiczbaPrzeciwnikow = 90;
const int LiczbaPociskow = 15;
const int LiczbaPrzedmiotow = 70;
const int LiczbaStanowGry = 15;
const int LiczbaBroni = 6;

const int scrSzerokosc = 160;
const int scrWysokosc = 35;

struct LevelStatus{
    std::string Tag;
    Kolory Color;
    int DrX;
    int DrY;
    int WymX;
    int WymY;
    int EfektXmin;
    int EfektYmin;
    int EfektXmax;
    int EfektYmax;
    bool Active;
    bool DrawAble;
    char DrawChar;

    LevelStatus(int drawX, int drawY, int wymX, int wymY, int _EfektXmin, int _EfektYmin, int _EfektXmax, int _EfektYmax,  std::string _tag, Kolory color, bool drawAble, char drawChar){
        Tag = _tag;
        DrX = drawX;
        DrY = drawY;
        WymX = wymX;
        WymY = wymY;
        EfektXmin = _EfektXmin;
        EfektYmin = _EfektYmin;
        EfektXmax = _EfektXmax;
        EfektYmax = _EfektYmax;
        Active = true;
        Color = color;
        DrawAble = drawAble;
        DrawChar = drawChar;
    }
};

class Game{
protected:
    int x;
	int y;
    Kolory Color;

public:
    Game();
    Game(int _x, int _y);
    ~Game();

	char getCursorChar();
	char readChar(int x,int y);
	void setPosition(int x, int y);
	void ShowCursor();
	void HideCursor();
	void TextColor(Kolory kolor);
    void PasekKolor(Kolory kolor);

    int GetX() const;
    int GetY() const;

    void SetX(int _x);
    void SetY(int _y);

    void SetColor(Kolory _color);
    Kolory GetColor() const;
};

#endif // GAME_H_
