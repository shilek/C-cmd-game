#include "przeciwnik.h"
using namespace std;


Przeciwnik::~Przeciwnik(){
    if(bullet != NULL){
        setPosition(bullet->getX(), bullet->getY());
        cout << ' ';
        delete bullet;
    }
}

int Przeciwnik::GetObrazenia() const {return obrazenia;}
int Przeciwnik::GetMoveSpeed() const {return moveSpeed;}
Pocisk* Przeciwnik::GetBullet(){if (bullet != NULL) return bullet;}

void Przeciwnik::SetObrazenia(int obr){obrazenia = obr;}
void Przeciwnik::SetMoveSpeed(int _moveSpeed){moveSpeed = _moveSpeed;}
void Przeciwnik::DeleteBullet(){
    delete bullet;
    bullet = NULL;
}

Kolizje Przeciwnik::Move(){

   if (timeMove == moveSpeed && EnableMove == true){
    setPosition(x,y);
    TextColor(_White);
    cout << ' ';

    // DO GORY
    if (kierunek == 'w' && readChar(x,y-1) != WallModel) {y=y-1;}
    // NA DOL
    if (kierunek == 's' && readChar(x,y+1) != WallModel) {y=y+1;}
    // W LEWO
    if (kierunek == 'a' && readChar(x-1,y) != WallModel) {x=x-1;}
    // W PRAWO
    if (kierunek == 'd' && readChar(x+1,y) != WallModel) {x=x+1;}

    if (kierunek == 'w' && readChar(x,y-1) == WallModel) {kierunek = 's';}
    if (kierunek == 's' && readChar(x,y+1) == WallModel) {kierunek = 'w';}
    if (kierunek == 'a' && readChar(x-1,y) == WallModel) {kierunek = 'd';}
    if (kierunek == 'd' && readChar(x+1,y) == WallModel) {kierunek = 'a';}

    timeMove = 0;

    }

    setPosition(x,y);
    if (readChar(x,y) == PlayerModel_A || readChar(x,y) == PlayerModel_D ||  readChar(x,y)== PlayerModel_W ||  readChar(x,y) == PlayerModel_S) return Kolizje::Kgracz;
    if (readChar(x,y) == BulletModel) {if (hp>0) cout << model; return Kolizje::Kpocisk;}

    if(hp >= 70) Color = _Red;
    if(hp < 70 && hp >=60) Color = _LightRed;
    if(hp < 60 && hp >=30) Color = _DarkSilver;
    if(hp < 30 && hp >=10) Color = _Silver;

    TextColor(Color);
    cout << model;
    timeMove++;

    return Kolizje::Kbrak;
}

Kolizje Przeciwnik::Shoot(){

    Kolizje typKolizji = Kbrak;
    if(EnableShoot == true){
        if(bullet == NULL)
            bullet = new Pocisk(x, y, obrazenia/2, BulletModel, ShootDirection, PredkoscAtaku, _Red, 12);
        else
            typKolizji = bullet->Shoot();
    }

    if(typKolizji == Kolizje::Ksciana || typKolizji == Kolizje::Kdystans)
        this->DeleteBullet();

    return typKolizji;
}
