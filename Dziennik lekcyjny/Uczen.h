#pragma once
#include "Data.h"
#include "Adres.h"
#include <iostream>
#include "Humanistyczny.h"
#include "Scisly.h"
#include "Wuef.h"
#include <fstream>
#include "PESEL.h"
#include <iomanip> 

class Uczen : public _PESEL_
{
public:	
	std::string imie;
	std::string nazwisko;
	std::string telefon;
	std::string pesel;
	char plec;
	Data urodziny;
	Adres zamieszkanie;
	float srednia_koncowa;
	Humanistyczny* Lista_human;
	Scisly* Lista_scislych;
	Wuef* wf;	
	Uczen* pNext;
	Uczen();
	void usun_humanistyczne();
	void usun_scisle();
	void szczegoly_ucznia(std::ostream&);
	void drukuj_swiadectwo(void);
	void dodaj_humanistyczny(Humanistyczny*&);
	void dodaj_scisly(Scisly*&);
	std::ostream& operator<<(std::ostream&);
	std::istream& operator>>(std::istream&);
	void wypisz_przedmioty();
	bool operator<(const Uczen&);
	void wpisz_do_pliku(std::ostream&);
	~Uczen(void);
	void zestaw_przedmiotow();
	void wystaw_koncowe();
	void set_imie(std::string);
	void set_nazwisko(std::string);
	void set_telefon(std::string);
	void set_pesel(std::string);
	std::string get_pesel();
	Adres get_adres();
	void set_adres(Adres);
	void set_data(Data);
	Data get_data();
	void set_plec(char);
};

