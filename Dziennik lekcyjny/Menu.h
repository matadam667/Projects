#pragma once
#include <iostream>
#include "Uczen.h"
#include <conio.h>

class Menu
{

	Uczen* Uczen_lista;
	int ilosc;
public:
	Menu();
	void wypisz_uczniow();
	void dodaj_ucznia(Uczen*&);
	void usun_ucznia(Uczen*&);
	void pobierz_z_pliku();
	void wpisz_do_pliku();
	void usun_wszystkich();
	~Menu();
	void glowne();
	int lista_uczniow();
	int Oceny_menu();
	void swiadectwa();
	int inne();
	int uczen_szczegoly();
	void Dodaj_nowego();
	void usuwanie();
	int dodawanie_ocen();
	void wyswietl_wszystkie(Uczen*);
	void Sortowanie_przez_scalanie(Uczen*&, int);
	void podziel_liste(Uczen*,Uczen*&,Uczen*&);
	Uczen* sortuj(Uczen*&, Uczen*&, int);
	bool walidacja_pesel(std::string);
	int wyswietalnie_ocen();
	int edytowanie_ocen();
	int usuwanie_ocen();
};


