/**@file*/
#ifndef FUNKCJE_H
#define FUNKCJE_H
#include "struktury.h"
#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <time.h>
/**funkcja tworzaca nowy element listy dwukierunkowej typu Wspolrzedne_x
@param pHead_ref adres pierwszego elementu listy
@param X informacja jaka wspolrzedna przypisac elementowi*/
void nowy_X(struct Wspolrzedne_x** pHead_ref, int X);
/**funkcja tworzaca nowy element listy dwukierunkowej typu Wspolrzedne_y
@param pHead_ref adres pierwszego elementu listy
@param Y informacja jaka wspolrzedna przypisac elementowi*/
void nowy_Y(struct Wspolrzedne_y** pHead_ref, int Y);
/**funkcja ktora przypisuje graczowi standardowy zestaw do gry
@param uzytkownik_ref adres gracza*/
void Standardowy_zestaw(struct Uzytkownik** uzytkownik_ref);
/**funckcja, ktora wyswietla tablice gracza
@param tablica adres pierwszego elementu listy*/
void wyswietl_tablice(struct Wspolrzedne_y* tablica);
/**funkcja ktora sprawdza czy proponowane ustawienie statku spelnia zasady gry
@param pHead adres pierwszego elementu listy
@param yPoczatkowe poczatkowy koordynat statku na osi y
@param xPocatkowe, poczatkowy koordynat statku na osi x
@param yKoncowe koncowy koordynat statku na osi y
@param xKoncowe koncowy koordynat statku na osi x*/
bool walidacja_statku(struct Wspolrzedne_y** pHead, int yPoczatkowe, int xPoczatkowe, int yKoncowe, int xKoncowe);
/**funkcja sprawdzajaca czy gracz nie wyczerpal juz statkow rodzaju, ktory chce ustawic
@param uzytkownik adres uzytkownika
@param rodzaj sprawdzany rodzaj statku*/
bool walidacja_ilosci(struct Uzytkownik* uzytkownik, int rodzaj);
/**funckcja ktora sprawdzaca czy uzytkwonik podal prawidlowy rodzaj statku
@param uzytkownik adres uzytkownika
@param rodzaj sprawdzany rodzaj statku*/
bool walidacja_rodzaju(int rodzaj, struct Uzytkownik* uzytkownik);
/**funckja ktora sprawdzca czy koordynaty nie wykraczaja poza plansze do gry
@param x sprawdzany koordynat x
@param y sprawdzany koordynat y*/
bool walidacja_koordynatow(int x, int y);
/**funckja w ktorej gracz ustawia statki na planszy
@param uzytkownik_ref adres gracza
@param plik adres pliku, w ktorym zostanie zapisana informacja o ustawieniu statku
@param nazwa nazwa gracza, ktory ustawia statek*/
void ustaw_statek(struct Uzytkownik** uzytkownik_ref, char* nazwa);
/**funkcja ktora zmienia status odpowiednich pol na planszy na statek
@param pHead_ref adres glowy listy
@param Ypoczatkowe poczatkowy koordynat na osi y
@param Xpoczatkowe poczatkowy koordynat na osi x
@param Ykoncowe koncowy koordynat na osi y
@param Xkoncowe koncowy koordynat na osi x*/
void statek_na_plansze(struct Wspolrzedne_y** pHead_ref, int Ypoczatkowe, int Xpoczatkowe, int Ykoncowe, int Xkoncowe);
/**funckja ktora zapisuje do pliku informacje o ustawieniu statku na danych koordynatach
@param plik adres pliku, w ktorym zapisywana jest informacja
@param xp poczatkowy koordynat na osi x
@param yp poczatkowy koorynat na osi y
@param xk koncowy koordynat na osi x
@param yk koncowy koordynat na osi y
@param nazwa nazwa gracza ustawiajacego statki*/
void zapisz_ustawienie_do_pliku(int xp, int yp, int xk, int yk, char* nazwa);
/**funkcja blizniacza do funkcji "wyswietl_tablice, ktora nie rozroznia pol pustych i pol zajetych przez statek
@param tablica adres glowy listy*/
void wyswietl_tablice_przeciwnika(struct Wspolrzedne_y* tablica);
/**funkcja w ktorej uzytkownik strzela w plansze przeciwnika
@param pHead_ref adres glowy listy
@param nazwa nazwa gracza, ktorzy strzela
@param plik adres pliku, w ktorym zapisana bedzie informacja o oddanym strzale
funckja zwraca 0 jezeli strzal jest nieprawidlowy, 2 jezeli gracz trafi w statek, 3 jezeli uzytkownik zatopi statek, 4 jezeli spudluje i 5 jezeli ruch bedzie wykraczal poza tablice*/
int strzal(struct Wspolrzedne_y** pHead_ref, char* nazwa);
/**funkcja, ktora zapisuje do pliku informacje o wykonanym strzale
@param plik adres pliku
@param x koordynat x strzalu
@param y koordynat y strzalu
@paran status rezutat strzalu
@param nazwa nazwa gracza, ktory strzela*/
void zapisz_strzal_do_pliku(int x, int y, int status, char* nazwa);
/**funckja sprawdzajaca czy uzytkownik zatopil statek
@Param pHead adres glowy listy glownej
@param pHeadx adres elementu listy w ktory trafil gracz*/
bool walidacja_zbicia(struct Wspolrzedne_y* pHead, struct Wspolrzedne_x* pHeadx);
/**funkcja ktora zmienia status pol zajetych przez statek jak i pola do okola niego na zbity
@param pHead_ref adres glowy glownej listy
@param pHeadx_ref adres elementu listy, w ktory trafil gracz*/
void zbij(struct Wspolrzedne_y** pHead_ref, struct Wspolrzedne_x** pHeadx_ref);
/**funkcja w ktorej odbywa sie rozgrywka typu Gracz na Gracza
@param Gracz1_ref adres pierwszego gracza
@param Gracz2_ref adres drugiego gracza*/
void Gracz_na_Gracza(struct Uzytkownik** Gracz1_ref, struct Uzytkownik** Gracz2_ref);
/**funkcja, ktora usuwa liste typu Wspolrzedne_x
@param pHead_ref adres glowy listy*/
void usun_X(struct Wspolrzedne_x** pHead_ref);
/**funkcja, ktora usuwa liste typu Wsolrzedne_y i wywoluje funkcje usun_X
@param pHead_ref adres glowy listy*/
void usun_listy(struct Wspolrzedne_y** pHead_ref);
/**funkcja ktora usuwa strukture Uzytkownik
@param Gracz_ref adres gracza*/
void usun_gracza(struct Uzytkownik** Gracz_ref);
/**funkcja, ktora przypisuje komputerowi jego standardowy zestaw do gry
@param Komputer_ref adres komputera*/
void komputer_standardowy_zestaw(struct Komputer** Komputer_ref);
/**funkcja ktora dodaje nowy element do listy kierunkow
@param pHead_ref adres glowy listy
@param kierunek dodawany kierunek*/
void komputer_dodaj_kierunek(struct Lista_kierunkow** pHead_ref, int kierunek);
/**funkcja ktora sprawdza, czy komputer nie strzelal juz w wybranym kierunku
@param pHead adres glowy
@param kierunek wybrany kierunek*/
bool komputer_walidacja_kierunku(struct Lista_kierunkow* pHead, int kierunek);
/**funkcja, ktora ustawia statek wybranego rodzaju na planszy komputera
@param pHead_ref adres glowy listy
@param rodzaj rodzaj statku
@param plik adres pliku, w ktorym zostanie zapisana informacja o ustawieniu statku na plansze*/
void komputer_dostaw_statek(struct Wspolrzedne_y** pHead_ref, int rodzaj, char* nazwa);
/**funkcja, ktora pobiera z pliku presety.txt losowy gotowy zestaw ustawien statkow, ktore wykorzysta komputer
@param Komputer_ref adres Komputera
@param plik_wyjsciowy wskaznik na plik, w ktorym sa zapisywane logi gry
@param set informacja o tym, ktory set statkow nie moze byc pobrany do uzycia*/
void komputer_pobierz_statki(struct Komputer** Komputer_ref, int set);
/**funkcja, ktora pobiera z pliku presety.txt losowy gotowy zestaw ustawien statkow, ktore zostana ustawione na planszy uzytkownika
@param uzytkownik_ref adres uzytkownika
@param nazwa nazwa uzytkownika
@param set informacja o tym, ktory set nie moze byc pobrany do uzycia*/
int pobierz_statki_dla_uzytkownika(struct Uzytkownik** Uzytkownik_ref, char* nazwa, int set);
/**funckja, ktora dodaje ustawienie statkow do listy poprawnych ustaiwnien, by potym moc wylosowac statek
@param pHead_ref adres glowy listy
@param xp poczatkowy koordynat statku na osi x
@param xk koncowy koordynat statku na osi x
@param yp poczatkowy koordynat statku na osi y
@param yk koncowy koordynat statku na osi y*/
void nowe_ustawienie(struct Lista_ustawien** pHead_ref, int xp, int xk, int yp, int yk);
/**funkcja, ktora usuwa elementy z listy ustawien
@param pHead_ref adres glowy listy*/
void usun_ustawienia(struct Lista_ustawien** pHead_ref);
/**funkcja, ktora usuwa elementy z listy kierunkow
@param pHead_ref adres glowy listy*/
void komputer_usun_kierunki(struct Lista_kierunkow** pHead_ref);
/**funkcja, ktora dodaje do listy strzalow nowy element
@param pHead_ref adres glowy listy
@param x koordynat x strzalu
@param y koordynat y strzalu
@param kierunek kierunek, w ktorym szedl komputer wykonujac strzal
@param trafienie informacja o tym, czy komputer trafil w statek, czy nie*/
void komputer_dodaj_strzal(struct Komputer_strzelanie** pHead_ref, int x, int y, int kierunek, bool trafienie);
/**funkcja, ktora sprawdza czy proponowany przez komputer strzal jest poprawny
@param pHead adres glowy listy bedacej plansza przeciwnika
@param Strzaly adres glowy listy strzalow komputera
@param x koordynat x strzalu
@param y koordynat y strzalu
funkcja zwraca 0 jezeli komputer strzelal juz w te miejsce, 1 jezeli ruch jest niepoprawny ze wzgledu na status pola lub 2 jezeli ruch jest poprawny*/
int komputer_walidacja_ruchu(struct Wspolrzedne_y* pHead, struct Komputer_strzelanie* Strzaly, int x, int y);
/**funkcja, ktora strzela w wybrane przez komputer miejsce
@param pHead_ref adres listy bedacej plansza przeciwnika
@param x koordynat x strzalu
@param y koordynat y strzalu
@param plik adres pliku, w ktorym zostanie zapisana informacja o ruchu
funkcja zwraca 2 jezeli komputer trafi w statek, 3 jezeli komputer zatopi statek lub 4 jezeli spudluje */
int komputer_strzal(struct Wspolrzedne_y** pHead_ref, int x, int y);
/**funkcja, ktora losuje miejsce, w ktore strzeli komputer
@param Komputer_ref adres komputera
@param Tablica_przeciwnika_ref adres glowy listy bedaca plansza przeciwnika
@param plik adres pliku, w ktorym zostanie zapisana informacja o strzale
funkcja zwraca 0 jezeli strzal jest nieprawidlowy, 2 jezeli komputer trafi w statek - wtedy rowniez Komputer->status_strzalu zmieniany jest na true, 3 jezeli zatopi statek i 4 jezeli spudluje*/
int komputer_pierwszy_strzal(struct Komputer** Komputer_ref, struct Wspolrzedne_y** Tablica_przeciwnika_ref);
/**funkcja, ktora po trafieniu w statek probuje trafic w statek losujac kierunek strzalu
@param Komputer_ref adres komputera
@param Tablica przeciwnika_ref adres glowy listy bedaca plansza przeciwnika
@param plik adres pliku, w ktorym zostanie zapisana informacja o strzale
funkcja zwraca 0 jezeli strzal jest nieprawidlowy, 2 jezeli komputer trafi w statek - wtedy rowniez Komputer->status_drugiego_strzalu zmieniany jest na true, 3 jezeli zatopi statek -wtedy tez Komputer->status_strzalu zostanie zmieniony na false, i 4 jezeli spudluje*/
int komputer_drugi_strzal(struct Komputer** Komputer_ref, struct Wspolrzedne_y** Tablica_przeciwnika_ref);
/**funkcja ktora po znalezieniu osi, w ktorej lezy statek stara sie go zatopic, jezeli status ostatniego ruchu bedzie negatywny funkcja wroci sie do pierwszego strzalu w aktualnie ostrzeliwanym statku i zacznie strzelac w przeciwnym kierunku
@param Komputer_ref adres komputera
@param Tablica_przeciwnika_ref adres glowy listy bedacej plansza przeciwnika
@param plik adres pliku, w ktorym zostanie zapisana informacja o strzale
funkcja zwraca 0 jezeli strzal jest nieprawidlowy, 2 jezeli komputer trafi w statek, 3 jezeli zatopi statek -wtedy tez Komputer->status_strzalu jak i Komputer->status_drugiego_strzalu zostanie zmieniony na false, i 4 jezeli spudluje*/
int komputer_dalszy_strzal(struct Komputer** Komputer_ref, struct Wspolrzedne_y** Tablica_przeciwnika_ref);
/**funkcja w ktorej odbywa sie rozgrywka typu Gracz na Komputer
@param Gracz_ref adres gracza
@param Komputer_ref adres komputera*/
void Gracz_na_Komputer(struct Uzytkownik** Gracz_ref, struct Komputer** Komputer_ref);
/**funkcja ktora usuwa liste strzalow komputera
@param pHead_ref adres glowy listy*/
void komputer_usun_strzaly(struct Komputer_strzelanie** pHead_ref);
/**funkcja, ktora usuwa strukture komputera wywoluje funkcje komputer_usun_strzaly oraz komputer_usun_kierunki
@param Komputer_ref adres komputera*/
void usun_komputer(struct Komputer** Komputer_ref);
/**funckcja ktora wyswietla menu projektu*/
void menu();
#endif
