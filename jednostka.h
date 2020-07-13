#ifndef JEDNOSTKA_H_
#define JEDNOSTKA_H_
#include "pocisk.h"
#include "game.h"

class Jednostka : public Game{
protected:

	int hp;
	int maxHp;
	int score;
    char kierunek;
    char model;

public:
    Jednostka(int _x, int _y, int _hp, char _model, char _kierunek, int _score);
    virtual ~Jednostka();


    int GetHP() const;
    int GetMaxHp() const;
    int GetScore() const;
    char GetKierunek() const;
    char GetModel() const;

    void SetHP(int _hp);
    void SetMaxHp(int _maxHp);
    void SetScore(int _score);
    void SetKierunek(char _kierunek);
    void SetModel(char _model);

    void ModifyScore(int _score);
    void ModifyHp(int _hp);

    /*
    virtual Pocisk* Getbullet(){};
    virtual void DeleteBullet(){};
    virtual Kolizje Move(){return Kolizje::Kbrak;}
    virtual int GetObrazenia() const{return 0;}
    */
};

#endif // JEDNOSTKA_H_

