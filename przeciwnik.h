#ifndef PRZECIWNIK_H_
#define PRZECIWNIK_H_

#include "pocisk.h"
#include "jednostka.h"


class Przeciwnik : public Jednostka{
private:
    int obrazenia;
	int moveSpeed;
	int timeMove;
	int PredkoscAtaku;
	Pocisk* bullet;
	char ShootDirection;
	bool EnableMove;
	bool EnableShoot;
	bool Exist;
public:
     Przeciwnik(int x, int y, int hp, char znak, char kierunek, int _obrazenia, int _moveSpeed, int _predkoscAtaku, Kolory _color, int _score, bool _moveable, bool _shootable, char _shootDirection):
        Jednostka(x,y,hp,znak,kierunek, _score), obrazenia(_obrazenia), moveSpeed(_moveSpeed), PredkoscAtaku(_predkoscAtaku), ShootDirection(_shootDirection), EnableMove(_moveable), EnableShoot(_shootable){
            timeMove = 0;
            Color = _color;
            bullet = NULL;
        }

    virtual ~Przeciwnik();

    int GetObrazenia() const;
    int GetMoveSpeed() const;
    Pocisk* GetBullet();

    void SetObrazenia(int obr);
    void SetMoveSpeed(int _moveSpeed);

    void DeleteBullet();

    virtual Kolizje Move();
    Kolizje Shoot();
};

#endif // PRZECIWNIK_H_
