#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <fstream>
using namespace std;

#include "game.h"
#include "gracz.h"
#include "przeciwnik.h"
#include "przedmiot.h"
#include "pocisk.h"

MenuStatus MainMenu();
void PrepareGame(MenuStatus menuState);
void GameLoop(Gracz* Player, Przeciwnik* Przeciwnicy[], Przedmiot* Przedmioty[], LevelStatus* LvlStat[], Weapon Bronie[]);
void Kolizja(Przeciwnik* J[], Pocisk* p[], Gracz* Player);
void MapDraw(string LevelName);
void UI(Gracz* Player);
void EndScreen(Gracz* Player, Przeciwnik* Przeciwnicy[], Przedmiot* Przedmioty[], Pocisk* Pociski[]);
void LoadEnemy(Przeciwnik* J[]);
void LoadItems(Przedmiot* Przedmioty[]);
void LoadWeapons(Weapon Bronie[]);
void LoadGameStatus(LevelStatus* LvlStat[]);
void GiveItem(Gracz& Player, char typ, Kolory color, Weapon Bronie[]);
void ActivateStatus(Przedmiot* Przedmioty[], LevelStatus* LvlStat, Gracz& Player);
void ActivateStatus(LevelStatus* LvlStat);
void LevelUp(Gracz& Player);
void InformacjeWindow();

Game gameObject;

int main(){
    bool EXIT = false;
    gameObject.HideCursor();

    while(!EXIT){
        MenuStatus Choice = MainMenu();

        switch(Choice){
            case _NowaGra: PrepareGame(_NowaGra);
                break;
            case _Wczytaj: PrepareGame(_Wczytaj);
                break;
            case _Informacje: InformacjeWindow();
                break;
            case _Wyjdz: EXIT = true;
                break;
        }
    }//while


return 0;
}

MenuStatus MainMenu(){
    char move = '\0';
    MenuStatus choice = _NowaGra;
    int y = 0;
    system("cls");

    gameObject.setPosition(80, 9);
    gameObject.TextColor(_Yellow);
    cout << "^";
    gameObject.setPosition(80, 10);
    cout << "W";


    gameObject.setPosition(75, 13);
    gameObject.TextColor(_White);
    cout << " NOWA GRA";

    gameObject.setPosition(75, 15);
    gameObject.TextColor(_White);
    cout << "WCZYTAJ GRE";

    gameObject.setPosition(75, 17);
    gameObject.TextColor(_White);
    cout << "INFORMACJE";

    gameObject.setPosition(75, 19);
    gameObject.TextColor(_White);
    cout << "   WYJDZ";

    gameObject.setPosition(80, 22);
    gameObject.TextColor(_Yellow);
    cout << "S";
    gameObject.setPosition(80, 23);
    cout << "v";

    do{

        gameObject.setPosition(67, 13+y);
        gameObject.TextColor(_Green);
        cout << "   ";

        gameObject.setPosition(90, 13+y);
        gameObject.TextColor(_Green);
        cout << "   ";

        if(move == 'w')
            y -= 2;
        if(move == 's')
            y += 2;

        if(y < 0)
            y = 6;
        if(y > 6)
            y = 0;

        if (y == 0) choice = _NowaGra;
        else if (y == 2) choice = _Wczytaj;
        else if (y == 4) choice = _Informacje;
        else if (y == 6) choice = _Wyjdz;

        gameObject.setPosition(67, 13+y);
        gameObject.TextColor(_Green);
        cout << "-->";

        gameObject.setPosition(90, 13+y);
        gameObject.TextColor(_Green);
        cout << "<--";

        gameObject.setPosition(0, 0);
        move = getch();

    }while(move != 13); // 13 == ENTER

    return choice;
}

void PrepareGame(MenuStatus menuState){

    Przeciwnik *Przeciwnicy[LiczbaPrzeciwnikow] = {NULL};
    Przedmiot *Przedmioty[LiczbaPrzedmiotow] = {NULL};
    LevelStatus* LvlStat[LiczbaStanowGry] = {NULL};
    Weapon Bronie[LiczbaBroni];

	MapDraw("level_1.txt");


    LoadWeapons(Bronie);
    LoadItems(Przedmioty);
    LoadGameStatus(LvlStat);
    LoadEnemy(Przeciwnicy);

	Gracz* player = new Gracz(3, 3, 100, 'w', PlayerModel_W, 1, 120, _Pink);

    player->SetWeapon(Bronie[_Pistolet]);

    GameLoop(player, Przeciwnicy, Przedmioty, LvlStat, Bronie);
}

void GameLoop(Gracz* Player, Przeciwnik* Przeciwnicy[], Przedmiot* Przedmioty[], LevelStatus* LvlStat[], Weapon Bronie[]){
    Pocisk *Bullet[LiczbaPociskow] = {NULL};
    Kolizje typKolizja = Kbrak;
    char ruch = '\0';
    unsigned int time=200;

    // PETLA GRY
	while(ruch != 'q')
	{
	    UI(Player);

	    if(kbhit()) { ruch = getch(); }

	    //Ruch gracza
        if(ruch == 'w' || ruch == 's' || ruch == 'a' || ruch == 'd' ||
           ruch == 'H' || ruch == 'P' || ruch == 'K' || ruch == 'M')
            Player->Move(ruch);

        Kolizja(Przeciwnicy, Bullet, Player);

        //Strzelanie
        if (ruch == 'j' && time>=Player->GetWeapon()->GetPredkoscAtaku()){
                if(Player->GetWeapon()->GetAmmMag() > 0){
                    time = 0;
                    for (int i=0; i<LiczbaPociskow; i++){
                        if (Bullet[i] == NULL) {
                            Player->GetWeapon()->ModifyMagAmmo(-1);
                            Bullet[i] = new Pocisk(Player->GetX(), Player->GetY(), Player->GetWeapon()->GetObrazenia(), BulletModel, Player->GetKierunek(), 1, _Blue, Player->GetWeapon()->GetDystans());
                            break;
                        }
                    }//for
                }//if(ammo)
        ruch = '\0';
        }//if(j)

        time++;

        if(ruch == 'r' && Player->GetAmunicja() > 0){
            if(Player->GetAmunicja() > Player->GetWeapon()->GetPojMagMax() - Player->GetWeapon()->GetAmmMag()){
                Player->ModifyAmunicja(Player->GetWeapon()->GetAmmMag()- Player->GetWeapon()->GetPojMagMax());
                Player->GetWeapon()->SetAmmMag(Player->GetWeapon()->GetPojMagMax());
            }
            else{
                Player->GetWeapon()->ModifyMagAmmo(Player->GetAmunicja());
                Player->SetAmunicja(0);
            }
            ruch=' ';
        }

        if(ruch == 'f'){
            for(int i = 0; i < LiczbaStanowGry && LvlStat[i] != NULL; ++i){
                if(Player->GetX() == LvlStat[i]->WymX &&  Player->GetY() == LvlStat[i]->WymY)
                    ActivateStatus(Przedmioty, LvlStat[i], *Player);
                }
            ruch = '\0';
        }

        for(int i = 0; i < LiczbaPrzedmiotow; ++i){
            if(Przedmioty[i] != NULL){
                if(Kgracz == Przedmioty[i]->Rysuj()){
                    GiveItem(*Player, Przedmioty[i]->GetTyp(), Przedmioty[i]->GetColor(), Bronie);
                    delete Przedmioty[i];
                    Przedmioty[i] = NULL;
                }
            }
        }

        for (int i = 0; i < LiczbaPociskow; i++){
            if (Bullet[i] != NULL) typKolizja = Bullet[i]->Shoot();
            if (typKolizja == Kgracz || typKolizja == Ksciana  || typKolizja == Kdystans){delete Bullet[i]; Bullet[i] = NULL;}
        }

        gameObject.setPosition(0,0);

        if (Player->GetHP() <= 0) break;
        if (Player->GetScore() >= 30) LevelUp(*Player);
        if (Player->GetX() >= 102 && Player->GetX() <= 122 && Player->GetY() == 23) break;
	}

    EndScreen(Player, Przeciwnicy, Przedmioty, Bullet);
}

void Kolizja(Przeciwnik *J[], Pocisk *p[], Gracz* Player){
    Kolizje kolizja;

    // KOLIZJA Z POCISKIEM DLA GRACZA

// KOLIZJA Z POCISKIEM DLA PRZECIWNIKOW
    for (int i = 0; i < LiczbaPrzeciwnikow; i++){

        if (J[i] != NULL){
                kolizja = J[i]->Shoot();
            if (kolizja == Kgracz){
                Player->ModifyHp(- J[i]->GetBullet()->GetObrazenia());
                J[i]->DeleteBullet();
            }
        }

        kolizja = Kbrak;
        if (J[i] != NULL){ kolizja = J[i]->Move();}
        if (kolizja == Kpocisk){
                for (int j=0;j<LiczbaPociskow;j++){
                    if (p[j] != NULL && p[j]->getX() == J[i]->GetX() && p[j]->getY() == J[i]->GetY()){
                        J[i]->SetHP (J[i]->GetHP() - p[j]->GetObrazenia());
                        delete p[j];
                        p[j] = NULL;
                    }
                }
                if (J[i]->GetHP() <= 0){
                    gameObject.setPosition(J[i]->GetX(),J[i]->GetY());
                    cout << ' ';
                    Player->ModifyScore(J[i]->GetScore()); // modyfikacja punktow gracza
                    delete J[i];
                    J[i] = NULL;
                }
        }
// KOLIZJA GRACZA Z PRZECIWNIKIEM
        else if (kolizja == Kgracz) {
                Player->SetHP(Player->GetHP() - J[i]->GetObrazenia());
                gameObject.setPosition(J[i]->GetX(),J[i]->GetY());
                Player->ModifyScore(-J[i]->GetScore()); // modyfikacja punktow gracza
                delete J[i];
                J[i] = NULL;
            }
    }
}
// RYSOWANIE MAPY
void MapDraw(string LevelName){

    gameObject.setPosition(0,0);
    gameObject.TextColor(_DarkSilver);
    ifstream input(LevelName);
    string line;
    while(getline(input, line))
        cout << line << endl;
    input.close();

    for(int i = 0; i < scrSzerokosc; ++i)
    {
        for(int j = 0; j < scrWysokosc; ++j)
        {
            gameObject.setPosition(i,j);
            if( gameObject.getCursorChar() == WallModel )
            {
                gameObject.PasekKolor(_White);
                cout << WallModel;
            }
        }
    }

    gameObject.setPosition(104,23);
    gameObject.TextColor(_Green);
    cout << "-> F I N I S H <-";

    gameObject.setPosition(135,3);
    gameObject.TextColor(_White);
    cout << "LEGENDA:";

    gameObject.setPosition(128,5);
    gameObject.TextColor(_Green);
    cout << HpBonusModel << " -> Dodatkowe Hp +25";
    gameObject.setPosition(128,6);
    gameObject.TextColor(_Yellow);
    cout << HpBonusModel << " -> Dodatkowe Hp +50";
    gameObject.setPosition(128,7);
    gameObject.TextColor(_Ocean);
    cout << HpBonusModel << " -> Dodatkowe Hp +100";

    gameObject.setPosition(128,9);
    gameObject.TextColor(_Gold);
    cout << AmmoBonusModel << " -> Dodatkowa amunicja +10";

    gameObject.setPosition(128,10);
    gameObject.TextColor(_DarkGreen);
    cout << MaxHpBonusModel << " -> Dodatkowe max Hp";

    gameObject.setPosition(128,11);
    gameObject.TextColor(_Purple);
    cout << ScoreBonusModel << " -> 2 Dodatkowe punkty";


    gameObject.setPosition(128,12);
    gameObject.TextColor(_Blue);
    cout << KeyModel << " -> Klucz";

    gameObject.setPosition(128,14);
    gameObject.TextColor(_Red);
    cout << EnemyModel_X << " -> Przeciwnik";

    gameObject.setPosition(128,15);
    gameObject.TextColor(_Red);
    cout << BulletModel << " -> Pocisk";

    gameObject.setPosition(128,17);
    gameObject.TextColor(_White);
    cout << "W S A D -> Ruch";

    gameObject.setPosition(128,18);
    gameObject.TextColor(_White);
    cout << "F -> Akcja";

    gameObject.setPosition(128,19);
    gameObject.TextColor(_White);
    cout << "J -> Strzal";

    gameObject.setPosition(128,20);
    gameObject.TextColor(_White);
    cout << "R -> Przeladowanie";

    gameObject.setPosition(128,21);
    gameObject.TextColor(_White);
    cout << "Q -> Wyjscie";

    //BRONIE
    gameObject.setPosition(128,23);
    gameObject.TextColor(_Ocean);
    cout << PistoletModel << " -> Pistolet";

    gameObject.setPosition(128,24);
    cout << MagnumModel << " -> Magnum .44";

    gameObject.setPosition(128,25);
    cout << KarabinModel << " -> Karabin";

    gameObject.setPosition(128,26);
    cout << SnajperkaModel << " -> Snajperka";

    gameObject.setPosition(128,27);
    cout << RPGModel << " -> RPG-7";

    gameObject.setPosition(128,28);
    cout << MachineGunPKPModel << " -> PKP-Pecheneg";
}

void UI(Gracz* Player){

    gameObject.setPosition(136,1);
    cout << "x:            ";
    gameObject.setPosition(136,1);
    gameObject.TextColor(_White);
    cout << "x: " << Player->GetX() << " y: " << Player->GetY();

    // STATYSTYKI GRACZA
    gameObject.setPosition(2,25);
    gameObject.TextColor(_Green);
    cout << "HP:           ";
    gameObject.setPosition(2,25);
    cout << "HP: " << Player->GetHP() << " / " << Player->GetMaxHp();


    gameObject.setPosition(2,26);
    gameObject.TextColor(_Yellow);
    cout << "Ammo:                  ";
    gameObject.setPosition(2,26);
    cout << "Ammo: "  << Player->GetWeapon()->GetAmmMag() << "/" << Player->GetWeapon()->GetPojMagMax() << " : " << Player->GetAmunicja();


    gameObject.setPosition(2,27);
    gameObject.TextColor(_Ocean);
    cout << "Score:                  ";
    gameObject.setPosition(2,27);
    cout << "Score: "  << Player->GetScore();

    gameObject.setPosition(2,28);
    gameObject.TextColor(_Pink);
    cout << "LVL:     ";
    gameObject.setPosition(2,28);
    cout << "LVL: "  << Player->GetLvl();

    gameObject.TextColor(_White);
    gameObject.setPosition(27,25);
    cout << "Bron:               ";
    gameObject.setPosition(27,25);
    cout << "Bron: " << Player->GetWeapon()->GetNazwa();

    gameObject.TextColor(_LightRed);
    gameObject.setPosition(30,26);
    cout << "DMG:                ";
    gameObject.setPosition(30,26);
    cout << "DMG: "  << Player->GetWeapon()->GetObrazenia();

    gameObject.TextColor(_LightBlue);
    gameObject.setPosition(30,27);
    cout << "Dystans:            ";
    gameObject.setPosition(30,27);
    cout << "Dystans: "  << Player->GetWeapon()->GetDystans();

    gameObject.TextColor(_DarkSilver);
    gameObject.setPosition(30,28);
    cout << "Predkosc Ataku: "  << Player->GetWeapon()->GetPredkoscAtaku();
}

void EndScreen(Gracz* Player, Przeciwnik* Przeciwnicy[], Przedmiot* Przedmioty[], Pocisk* Pociski[]){
    char action = '\0';
    system("cls");

    gameObject.PasekKolor(_White);
    for(int i = 0; i <= scrSzerokosc; ++i){
        gameObject.setPosition(i,0);
        cout << "#";
        gameObject.setPosition(i,32);
        cout << "#";

    }
    for(int i = 1; i <= 32; i++){
        gameObject.setPosition(0,i);
        cout << "#";
        gameObject.setPosition(scrSzerokosc,i);
        cout << "#";
    }

    gameObject.TextColor(_White);

    gameObject.setPosition(65,13);
    cout << "##############################";
    gameObject.setPosition(65,14);
    cout << "#                            #";
    gameObject.setPosition(65,15);
    cout << "#           LOSE             #";
    gameObject.setPosition(65,16);
    cout << "#     WCISNIJ Q ABY WYJSC    #";
    gameObject.setPosition(65,17);
    cout << "#                            #";
    gameObject.setPosition(65,18);
    cout << "##############################";

    for(int i = 0; i < LiczbaPociskow; ++i)
        if(Pociski[i] != NULL){
            delete Pociski[i];
            Pociski[i] = NULL;
        }


    for(int i = 0; i < LiczbaPrzeciwnikow; ++i)
        if(Przeciwnicy[i] != NULL){
            delete Przeciwnicy[i];
            Przeciwnicy[i] = NULL;
        }


    for(int i = 0; i < LiczbaPrzedmiotow; ++i)
        if(Przedmioty[i] != NULL){
            delete Przedmioty[i];
            Przedmioty[i] = NULL;
        }


    delete Player;
    Player = NULL;

    while(action != 'q')
        action = getch();
}

void LoadEnemy(Przeciwnik* J[]){

    ifstream input("ENEMY.txt");
    int licznik;
    int x;
    int y;
    int hp;
    char model;
    char kierunek;
    int dmg;
    int speed;
    int shootSpeed;
    unsigned int color;
    int score;
    bool shooting;
    bool moving;
    char shootDirection;

    input >> licznik;

	for(int i = 0; i < licznik; ++i)
    {
        input >> x;
        input >> y;
        input >> hp;
        input >> model;
        input >> kierunek;
        input >> dmg;
        input >> speed;
        input >> shootSpeed;
        input >> color;
        input >> score;
        input >> moving;
        input >> shooting;
        input >> shootDirection;
        J[i] = new Przeciwnik(x, y, hp, EnemyModel_X, kierunek, dmg, speed, shootSpeed, _Red, score, moving, shooting, shootDirection);
    }
    input.close();
}

void LoadItems(Przedmiot* Przedmioty[]){

    //AMUNICJA
    Przedmioty[0] = new Przedmiot(1, 1, AmmoBonusModel, _Gold);
    Przedmioty[1] = new Przedmiot(16, 3, AmmoBonusModel, _Gold);
    Przedmioty[2] = new Przedmiot(13, 22, AmmoBonusModel, _Gold);
    Przedmioty[3] = new Przedmiot(15, 9, AmmoBonusModel, _Gold);
    Przedmioty[4] = new Przedmiot(68, 8, AmmoBonusModel, _Gold);
    Przedmioty[5] = new Przedmiot(31, 21, AmmoBonusModel, _Gold);
    Przedmioty[6] = new Przedmiot(77, 23, AmmoBonusModel, _Gold);
    Przedmioty[7] = new Przedmiot(1, 15, AmmoBonusModel, _Gold);
    Przedmioty[8] = new Przedmiot(110, 17, AmmoBonusModel, _Gold);

    //HP
    Przedmioty[9] = new Przedmiot(30, 4, HpBonusModel, _Green);
    Przedmioty[10] = new Przedmiot(83, 1, HpBonusModel, _Green);
    Przedmioty[11] = new Przedmiot(47, 18, HpBonusModel, _Green);
    Przedmioty[12] = new Przedmiot(17, 14, HpBonusModel, _Green);
    Przedmioty[13] = new Przedmiot(110, 1, HpBonusModel, _Yellow);
    Przedmioty[14] = new Przedmiot(39, 15, HpBonusModel, _Yellow);
    Przedmioty[15] = new Przedmiot(9, 9, HpBonusModel, _Yellow);
    Przedmioty[16] = new Przedmiot(17, 22, HpBonusModel, _Ocean);
    Przedmioty[17] = new Przedmiot(62, 23, HpBonusModel, _Ocean);
    Przedmioty[18] = new Przedmiot(114, 14, HpBonusModel, _Ocean);


    //MAX HP BONUS
    Przedmioty[19] = new Przedmiot(15, 22, MaxHpBonusModel, _Green);
    Przedmioty[20] = new Przedmiot(24, 16, MaxHpBonusModel, _Green);
    Przedmioty[21] = new Przedmiot(122, 9, MaxHpBonusModel, _Green);
    Przedmioty[22] = new Przedmiot(70, 23, MaxHpBonusModel, _Green);
    Przedmioty[23] = new Przedmiot(120, 12, MaxHpBonusModel, _Green);

    //SCORE
    Przedmioty[24] = new Przedmiot(13, 8, ScoreBonusModel, _Purple);
    Przedmioty[25] = new Przedmiot(64, 4, ScoreBonusModel, _Purple);
    Przedmioty[26] = new Przedmiot(96, 3, ScoreBonusModel, _Purple);
    Przedmioty[27] = new Przedmiot(49, 16, ScoreBonusModel, _Purple);
    Przedmioty[28] = new Przedmiot(63, 16, ScoreBonusModel, _Purple);
    Przedmioty[29] = new Przedmiot(91, 17, ScoreBonusModel, _Purple);
    Przedmioty[30] = new Przedmiot(76, 19, ScoreBonusModel, _Purple);
    Przedmioty[31] = new Przedmiot(80, 21, ScoreBonusModel, _Purple);
    Przedmioty[32] = new Przedmiot(16, 16, ScoreBonusModel, _Purple);
    Przedmioty[33] = new Przedmiot(96, 4, ScoreBonusModel, _Purple);
    Przedmioty[34] = new Przedmiot(12, 7, ScoreBonusModel, _Purple);
    Przedmioty[35] = new Przedmiot(96, 2, ScoreBonusModel, _Purple);
    Przedmioty[36] = new Przedmiot(43, 4, ScoreBonusModel, _Purple);
    Przedmioty[37] = new Przedmiot(49, 6, ScoreBonusModel, _Purple);
    Przedmioty[38] = new Przedmiot(28, 9, ScoreBonusModel, _Purple);
    Przedmioty[39] = new Przedmiot(19, 13, ScoreBonusModel, _Purple);
    Przedmioty[40] = new Przedmiot(27, 11, ScoreBonusModel, _Purple);
    Przedmioty[41] = new Przedmiot(32, 14, ScoreBonusModel, _Purple);
    Przedmioty[42] = new Przedmiot(61, 12, ScoreBonusModel, _Purple);
    Przedmioty[43] = new Przedmiot(75, 9, ScoreBonusModel, _Purple);
    Przedmioty[44] = new Przedmiot(75, 12, ScoreBonusModel, _Purple);
    Przedmioty[45] = new Przedmiot(91, 13, ScoreBonusModel, _Purple);
    Przedmioty[46] = new Przedmiot(91, 9, ScoreBonusModel, _Purple);
    Przedmioty[47] = new Przedmiot(14, 18, ScoreBonusModel, _Purple);
    Przedmioty[48] = new Przedmiot(8, 12, ScoreBonusModel, _Purple);
    Przedmioty[49] = new Przedmiot(5, 19, ScoreBonusModel, _Purple);

    //WEAPONS
    Przedmioty[50] = new Przedmiot(1, 8, KarabinModel, _LightBlue);
    Przedmioty[51] = new Przedmiot(81, 9, MagnumModel, _LightBlue);
    Przedmioty[52] = new Przedmiot(20, 15, MachineGunPKPModel, _LightBlue);


    //QUEST
    Przedmioty[53] = new Przedmiot(115, 1, KeyModel, _Blue);
    Przedmioty[54] = new Przedmiot(1, 10, KeyModel, _Red);
    Przedmioty[55] = new Przedmiot(35, 23, KeyModel, _Gold);
}

void LoadWeapons(Weapon Bronie[]){

    Bronie[_Pistolet] = Weapon(10, 10, 5, 5, 15, "Pistolet");
	Bronie[_Magnum44] = Weapon(14, 30, 12, 12, 20, "Magnum .44");
    Bronie[_Karabin]  = Weapon(13, 25, 30, 30, 6, "Karabin");
    Bronie[_Snajperka] = Weapon(40, 75, 10, 10, 40, "Snajperka");
    Bronie[_RPG7] = Weapon(17, 100, 1, 1, 50, "RPG-7");
    Bronie[_MachineGunPKP] = Weapon(13, 20, 50, 50, 3, "PKP Pecheneg");

}

void LoadGameStatus(LevelStatus* LvlStat[]){
    LvlStat[0] = new LevelStatus(0, 0, 4, 4, 4, 5, 0, 0, "BonusHpWall", _DarkGreen, false, '\0');
    LvlStat[1] = new LevelStatus(84, 1, 83, 1, 34, 2, 40, 2, "WallChange", _Blue, false, '#');
    LvlStat[2] = new LevelStatus(84, 1, 83, 1, 44, 2, 52, 2, "WallChange", _Blue, false, '#');
    LvlStat[3] = new LevelStatus(118, 8, 118, 9, 110, 11, 116, 11, "WallChange", _Red, false, '#');
    LvlStat[4] = new LevelStatus(82, 8, 81, 8, 34, 19, 36, 19, "WallChange", _Gold, false, '#');
    LvlStat[5] = new LevelStatus(0, 0, 72, 4, 72, 5, 0, 0, "BonusHpWall", _DarkGreen, false, '\0');
    LvlStat[6] = new LevelStatus(0, 0, 20, 19, 20, 20, 0, 0, "SecretWall", _DarkGreen, false, '\0');
    LvlStat[7] = new LevelStatus(0, 0, 23, 6, 24, 6, 0, 0, "BonusWeaponSanajp", _DarkGreen, false, '\0');
    LvlStat[8] = new LevelStatus(0, 0, 110, 9, 110, 8, 0, 0, "SecretWall", _DarkGreen, false, '\0');
    LvlStat[9] = new LevelStatus(0, 0, 110, 8, 110, 7, 0, 0, "SecretWall", _DarkGreen, false, '\0');
    LvlStat[10] = new LevelStatus(0, 0, 110, 7, 111, 7, 0, 0, "BonusWeaponRPG7", _DarkGreen, false, '\0');
    LvlStat[11] = new LevelStatus(0, 0, 96, 14, 97, 14, 0, 0, "BunusAmmoWall", _DarkGreen, false, '\0');
    LvlStat[12] = new LevelStatus(0, 0, 29, 17, 28, 17, 0, 0, "BonusScoreWall", _DarkGreen, false, '\0');
    LvlStat[13] = new LevelStatus(0, 0, 91, 23, 92, 23, 0, 0, "BonusScoreWall", _DarkGreen, false, '\0');

    ActivateStatus(LvlStat[1]);
    ActivateStatus(LvlStat[2]);
    ActivateStatus(LvlStat[3]);
    ActivateStatus(LvlStat[4]);
}

void GiveItem(Gracz& Player, char typ, Kolory color, Weapon Bronie[]){
    if(typ == HpBonusModel && color == _Green)  Player.ModifyHp(25);
    if(typ == HpBonusModel && color == _Yellow)  Player.ModifyHp(50);
    if(typ == HpBonusModel && color == _Ocean)  Player.ModifyHp(100);

    if(typ == AmmoBonusModel)  Player.ModifyAmunicja(10);
    if(typ == MaxHpBonusModel) {Player.SetMaxHp( Player.GetMaxHp() + 10); Player.SetHP(Player.GetMaxHp());}
    if(typ == ScoreBonusModel && color == _Purple) Player.ModifyScore(10);
    if(typ == ScoreBonusModel && color == _DarkBlue) Player.ModifyScore(20);


    if(typ == KarabinModel) Player.SetWeapon(Bronie[_Karabin]);
    if(typ == MagnumModel) Player.SetWeapon(Bronie[_Magnum44]);
    if(typ == MachineGunPKPModel) Player.SetWeapon(Bronie[_MachineGunPKP]);
    if(typ == SnajperkaModel) Player.SetWeapon(Bronie[_Snajperka]);
    if(typ == RPGModel) Player.SetWeapon(Bronie[_RPG7]);

    if(typ == KeyModel && color == _Blue) Player.SetKeyColor(_Blue);
    if(typ == KeyModel && color == _Red) Player.SetKeyColor(_Red);
    if(typ == KeyModel && color == _Gold) Player.SetKeyColor(_Gold);
}

void ActivateStatus(Przedmiot* Przedmioty[], LevelStatus* LvlStat, Gracz& Player){

    if(LvlStat->Tag == "BonusHpWall" && LvlStat->Active == true){
        for(int i = 0; i < LiczbaPrzedmiotow; ++i)
        if(Przedmioty[i] == NULL){
            Przedmioty[i] = new Przedmiot(LvlStat->EfektXmin, LvlStat->EfektYmin, MaxHpBonusModel, _DarkGreen);
            LvlStat->Active =  false;
            break;
        }
    }

    if(LvlStat->Tag == "BunusAmmoWall" && LvlStat->Active == true){
        for(int i = 0; i < LiczbaPrzedmiotow; ++i)
        if(Przedmioty[i] == NULL){
            Przedmioty[i] = new Przedmiot(LvlStat->EfektXmin, LvlStat->EfektYmin, AmmoBonusModel, _Gold);
            LvlStat->Active =  false;
            break;
        }
    }

    if(LvlStat->Tag == "BonusScoreWall" && LvlStat->Active == true){
        for(int i = 0; i < LiczbaPrzedmiotow; ++i)
        if(Przedmioty[i] == NULL){
            Przedmioty[i] = new Przedmiot(LvlStat->EfektXmin, LvlStat->EfektYmin, ScoreBonusModel, _DarkBlue);
            LvlStat->Active =  false;
            break;
        }
    }

    if(LvlStat->Tag == "BonusWeaponSanajp" && LvlStat->Active == true){
        for(int i = 0; i < LiczbaPrzedmiotow; ++i)
        if(Przedmioty[i] == NULL){
            Przedmioty[i] = new Przedmiot(LvlStat->EfektXmin, LvlStat->EfektYmin, SnajperkaModel, _LightBlue);
            LvlStat->Active =  false;
            break;
        }
    }

    if(LvlStat->Tag == "BonusWeaponRPG7" && LvlStat->Active == true){
        for(int i = 0; i < LiczbaPrzedmiotow; ++i)
        if(Przedmioty[i] == NULL){
            Przedmioty[i] = new Przedmiot(LvlStat->EfektXmin, LvlStat->EfektYmin, RPGModel, _LightBlue);
            LvlStat->Active =  false;
            break;
        }
    }


    if(LvlStat->Tag == "SecretWall" && LvlStat->Active == true){
        gameObject.setPosition(LvlStat->EfektXmin, LvlStat->EfektYmin);
        gameObject.TextColor(_White);
        cout << ' ';
        LvlStat->Active = false;
    }

    if(LvlStat->Tag == "WallChange" && LvlStat->Active == true && LvlStat->Color == Player.GetKeyColor()){
        gameObject.setPosition(LvlStat->DrX, LvlStat->DrY);
        gameObject.PasekKolor(_White);
        cout << LvlStat->DrawChar;
         gameObject.TextColor(_White);
        for(int i = LvlStat->EfektXmin; i <= LvlStat->EfektXmax; ++i){
            for(int j = LvlStat->EfektYmin; j <= LvlStat->EfektYmax; ++j){
                gameObject.setPosition(i,j);
                cout << ' ';
            }
        }
        LvlStat->Active = false;
    }
}

void ActivateStatus(LevelStatus* LvlStat){

    if(LvlStat->Tag == "WallChange" && LvlStat->Active == true){
        gameObject.setPosition(LvlStat->DrX, LvlStat->DrY);
        gameObject.PasekKolor(LvlStat->Color);
        cout << LvlStat->DrawChar;

        for(int i = LvlStat->EfektXmin; i <= LvlStat->EfektXmax; ++i){
            for(int j = LvlStat->EfektYmin; j <= LvlStat->EfektYmax; ++j){
                gameObject.setPosition(i,j);
                gameObject.PasekKolor(LvlStat->Color);
                cout << WallModel;
            }
        }
    }
}

void LevelUp(Gracz& Player){

    Player.SetScore(0);
    Player.SetMaxHp(Player.GetMaxHp() + 5);
    Player.SetHP(Player.GetMaxHp());
    Player.ModifyLvl(1);
    Player.ModifyAmunicja(5);
    Player.GetWeapon()->SetObrazenia(Player.GetWeapon()->GetObrazenia() + 5);
}

void InformacjeWindow(){

    system("cls");
    char action = '\0';

    gameObject.PasekKolor(_White);
    for(int i = 0; i <= scrSzerokosc; ++i){
        gameObject.setPosition(i,0);
        cout << "#";
        gameObject.setPosition(i,32);
        cout << "#";

    }
    for(int i = 1; i <= 32; i++){
        gameObject.setPosition(0,i);
        cout << "#";
        gameObject.setPosition(scrSzerokosc,i);
        cout << "#";
    }

    gameObject.TextColor(_White);
    gameObject.setPosition(60, 2);
    cout << "PROPONOWANE USTAWIENIA OKNA";

    gameObject.setPosition(65, 4);
    cout << "Czcionka: Consolas";

    gameObject.setPosition(65, 5);
    cout << "Rozmiar: 24";

    gameObject.setPosition(65, 6);
    cout << "Szerokosc okna: " << scrSzerokosc;

    gameObject.setPosition(65, 7);
    cout << "Wyskosc okna: " << scrWysokosc;

    gameObject.setPosition(65, 8);
    cout << "Szerokosc bufora ekranu: " << scrSzerokosc;

    gameObject.setPosition(65, 9);
    cout << "Wyskosc bufora ekranu: " << scrWysokosc;


    gameObject.setPosition(65, 13);
    cout << "  AUTORZY:";

    gameObject.setPosition(60, 15);
    gameObject.TextColor(_LightBlue);
    cout << "-->  ";
    gameObject.TextColor(_Yellow);
    cout << "MICHAL MAGDON";
    gameObject.TextColor(_LightBlue);
    cout << "  <--";

    gameObject.setPosition(60, 17);
    gameObject.TextColor(_LightBlue);
    cout << "-->  ";
    gameObject.TextColor(_Yellow);
    cout << "DAWID SAWICKI";
    gameObject.TextColor(_LightBlue);
    cout << "  <--";

    gameObject.TextColor(_White);
    gameObject.setPosition(65, 25);
    cout << "Wersja: 1.0v";

    gameObject.TextColor(_White);
    gameObject.setPosition(58, 30);
    cout << "nacisnij enter aby kontynuowac.";

    gameObject.TextColor(_White);
    while(action != 13)
        action = getch();
}

