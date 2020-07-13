#include "jednostka.h"
using namespace std;

Jednostka::Jednostka(int _x, int _y, int _hp, char _model, char _kierunek, int _score) : Game(_x, _y), hp(_hp), score(_score), kierunek(_kierunek), model(_model){
    maxHp = hp;
}
Jednostka::~Jednostka(){}


int Jednostka::GetHP() const {return hp;}
int Jednostka::GetMaxHp() const {return maxHp;}
int Jednostka::GetScore() const {return score;}
char Jednostka::GetKierunek() const {return kierunek;}
char Jednostka::GetModel() const {return model;}

void Jednostka::SetHP(int _hp) {hp = _hp;}
void Jednostka::SetMaxHp(int _maxHp) {maxHp = _maxHp;}
void Jednostka::SetScore(int _score) {score = _score;}
void Jednostka::SetKierunek(char _kierunek) {kierunek = _kierunek;}
void Jednostka::SetModel(char _model) {model = _model;}

void  Jednostka::ModifyScore(int _score) {score += _score;}
void Jednostka::ModifyHp(int _hp){
    hp += _hp;
    if (hp > maxHp)
        hp = maxHp;
}
