/**@file**/
#ifndef STRUKTURY_H
#define STRUKTURY_H
#include <stdbool.h>
/**
Podwieszana lista dwukierunkowa, ktorej elementami sa:
@param x koordynat x
@param status ustala status danego pola. 0 - oznacza puste pole. 1 - oznacza pole zajete przez statek 2 - oznacza trafiony statek 3 - oznacza zbity statek i pole dookola niego 4 - oznacza pudlo
@param ustawienie przyjmuje wartosc false, jezeli obecny na nim statek jest utawiony horyzontalnie lub true, gdy ustawiony na nim statek jest ustawiony wertykalnie*/
struct Wspolrzedne_x
{
	int x;
	int status;
	struct Wspolrzedne_x* pNext;
	struct Wspolrzedne_x* pPrev;
	bool ustawienie;
};
/**Lista dwukierunkowa, ktorej elementami sa:
@param y koordynat y
@param pHeadx glowa listy podwieszanej typu Wspolrzedne_x*/
struct Wspolrzedne_y
{
	int y;
	struct Wspolrzedne_x* pHeadx;
	struct Wspolrzedne_y* pUp;
	struct Wspolrzedne_y* pDown;
};
/** Struktura, ktora zawiera w sobie informacje o graczu
@param Tablica glowa listy typu Wspolrzedne_y, ktora pelni role planszy do gry
@param punkty ilosc punktow, ktore aktualnie posiada gracz
@param ilosc_czworek informacja ile statkow typu czwartego gracz moze jeszcze polozyc na planszy
@Param ilosc_trojek informacja ile statkow typu trzeciego gracz moze jeszcze polozyc na planszy
@param ilosc_dwojek informacja ile statkow typu drugiogo gracz moze jeszcze polozyc na planszy
@paran ilosc_jedynek informacje ile statkow typu pierwszego gracz moze jeszcze polozyc na planszy*/
struct Uzytkownik
{
	struct Wspolrzedne_y* Tablica;
	int punkty;
	int ilosc_czworek;
	int ilosc_trojek;
	int ilosc_dwojek;
	int ilosc_jedynek;
};
/**Lista dwukierunkowa, ktora przechowuje pola z planszy przeciwnika, w ktore strzelal juz komputer
@param x koordynat x pola z planszy przeciwnika
@param y koordynat y pola z planszy przeciwnika
@param kierunek informacja w ktorym kierunku szedl komputer strzelajac w te pole
@param status_strzalu informacja o tym czy komputer trafil czy spudlowal*/
struct Komputer_strzelanie
{
	int x;
	int y;
	struct Komputer_strzelanie* pNext;
	struct Komputer_strzelanie* pPrev;
	int kierunek;
	bool status_strzalu;
};
/**Lista jednokierunkowa przechowujaca kierunki w ktore z danego pola szedl komputer
@param kierunek informacja w kierunku w ktorym probowal isc komputer*/
struct Lista_kierunkow
{
	int kierunek;
	struct Lista_kierunkow* pNext;
};
/**Struktura, ktora zawiera w sobie informacje o komputerze
@param Tablica glowa listy typu Wspolrzedne_y, ktora pelni role planszy do gry
@param punkty ilosc punktow, ktore aktualnie posiada komputer
@param ilosc_czworek informacja ile statkow typu czwartego komputer moze jeszcze polozyc na planszy
@Param ilosc_trojek informacja ile statkow typu trzeciego komputer moze jeszcze polozyc na planszy
@param ilosc_dwojek informacja ile statkow typu drugiogo komputer moze jeszcze polozyc na planszy
@paran ilosc_jedynek informacje ile statkow typu trzeciego komputer moze jeszcze polozyc na planszy
@param Strzaly glowa na liste typu Komputer_strzelanie
@param Kierunki glowa na liste typu Lista_kierunkow
@bool status_strzalu informacja o tym, czy komputer moze przejsc do drugiego strzalu
@bool status_drugiego_strzalu informacja o tym, czy komputer moze przejsc do dalszego strzelu*/
struct Komputer
{
	struct Wspolrzedne_y* Tablica;
	int punkty;
	int ilosc_czworek;
	int ilosc_trojek;
	int ilosc_dwojek;
	int ilosc_jedynek;
	struct Komputer_strzelanie* Strzaly;
	struct Lista_kierunkow* Kierunki;
	bool status_strzalu;
	bool status_drugiego_strzalu;
};
/**Lista jednokierunkowa ktora zawiera koordynaty statkow wykorzystywane w ustawianiu losowo statkow przez komputer
@param xp poczatkowy koordynat statku na osi x 
@param xk koncowy koordynat statku na osi x
@param yp poczatkowy koordynat statku na osi y
@param yk koncowy koordynat statku na osi y
@param pNext wskaznik na nastepny element listy*/
struct Lista_ustawien
{
	int xp;
	int xk;
	int yp;
	int yk;
	struct Lista_ustawien* pNext;
};
#endif