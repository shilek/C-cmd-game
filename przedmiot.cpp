#include "przedmiot.h"
using namespace std;

Przedmiot::Przedmiot(int _x, int _y, char _typ, Kolory _color) : Game(_x, _y), typ(_typ){Color = _color;}
Przedmiot::~Przedmiot(){}

int Przedmiot::GetX() const {return x;}
int Przedmiot::GetY() const {return y;}
char Przedmiot::GetTyp() const {return typ;}
string Przedmiot::GetNazwa() const {return nazwa;}
bool Przedmiot::GetIstnieje() const {return istnieje;}

void Przedmiot::SetX(int _x){x = _x;}
void Przedmiot::SetY(int _y){y = _y;}
void Przedmiot::SetIstnieje(bool _istnieje){istnieje=_istnieje;}

Kolizje Przedmiot::Rysuj(){

    setPosition(x,y);

    if(getCursorChar() == PlayerModel_W || getCursorChar() == PlayerModel_D || getCursorChar() == PlayerModel_A || getCursorChar() == PlayerModel_S){
       return Kolizje::Kgracz;
    }
    else{
        TextColor(Color);
        cout << typ;
    }
    return Kolizje::Kbrak;

}
void Przedmiot::PickUp(){}
