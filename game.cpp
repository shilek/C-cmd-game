#include "game.h"

Game::Game(){}
Game::Game(int _x, int _y) : x(_x), y(_y){}
Game::~Game(){}


void Game::HideCursor()
{
    HANDLE handle = GetStdHandle( STD_OUTPUT_HANDLE );
    CONSOLE_CURSOR_INFO hCCI;
    GetConsoleCursorInfo( handle, & hCCI );
    hCCI.bVisible = FALSE;
    SetConsoleCursorInfo( handle, & hCCI );
}
void Game::ShowCursor()
{
    HANDLE handle =GetStdHandle( STD_OUTPUT_HANDLE );
    CONSOLE_CURSOR_INFO hCCI;
    GetConsoleCursorInfo( handle, & hCCI );
    if( hCCI.bVisible != TRUE )
    {
        hCCI.bVisible = TRUE;
        SetConsoleCursorInfo( handle, & hCCI );
    }
}

void Game::setPosition(int x, int y){
	COORD coord;
  	coord.X = x;
  	coord.Y = y;
  	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

char Game::readChar(int x,int y){
    setPosition(x,y);
    char znak = getCursorChar();
    return znak;
}

char Game::getCursorChar(){
    char znak = '\0';
    CONSOLE_SCREEN_BUFFER_INFO con;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (handle != INVALID_HANDLE_VALUE &&
        GetConsoleScreenBufferInfo(handle,&con))
    {
        DWORD read = 0;
        if (!ReadConsoleOutputCharacterA(handle,&znak,1,
            con.dwCursorPosition,&read) || read != 1
            )
            znak = '\0';
    }
    return znak;
}

void Game::PasekKolor(Kolory kolor)
{
	HANDLE handle;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	if(kolor == _White)
		SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED);
	else if (kolor == _Red)
		SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_INTENSITY);
	else if (kolor == _Green)
		SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	else if (kolor == _Blue)
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	else if (kolor == _Purple)
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_RED);
	else if (kolor == _Gold)
		SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	else if (kolor == _Yellow)
		SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_RED);
	else if (kolor == _Pink)
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
	else if (kolor == _LightBlue)
		SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	else if (kolor == _Ocean)
		SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_BLUE);
	else
		SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
}
void Game::TextColor(Kolory kolor)
{
	HANDLE handle;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);

	if(kolor == _DarkBlue)
		SetConsoleTextAttribute(handle, _DarkBlue);
    else if(kolor == _DarkGreen)
		SetConsoleTextAttribute(handle, _DarkGreen);
    else if(kolor == _LightBlue)
		SetConsoleTextAttribute(handle, _LightBlue);
    else if(kolor == _Red)
		SetConsoleTextAttribute(handle, _Red);
    else if(kolor == _Purple)
		SetConsoleTextAttribute(handle, _Purple);
    else if(kolor == _Yellow)
		SetConsoleTextAttribute(handle, _Yellow);
    else if(kolor == _White)
		SetConsoleTextAttribute(handle, _White);
    else if(kolor == _DarkSilver)
		SetConsoleTextAttribute(handle, _DarkSilver);
    else if(kolor == _Blue)
		SetConsoleTextAttribute(handle, _Blue);
    else if(kolor == _Green)
		SetConsoleTextAttribute(handle, _Green);
    else if(kolor == _Ocean)
		SetConsoleTextAttribute(handle, _Ocean);
    else if(kolor == _LightRed)
		SetConsoleTextAttribute(handle, _LightRed);
    else if(kolor == _Pink)
		SetConsoleTextAttribute(handle, _Pink);
    else if(kolor == _Gold)
		SetConsoleTextAttribute(handle, _Gold);
    else if(kolor == _Silver)
		SetConsoleTextAttribute(handle, _Silver);

}
int Game::GetX() const {return x;}
int Game::GetY() const {return y;}


void Game::SetX(int _x){x = _x;}
void Game::SetY(int _y){y = _y;}


void Game::SetColor(Kolory _color){Color = _color;}
Kolory Game::GetColor() const {return Color;}
