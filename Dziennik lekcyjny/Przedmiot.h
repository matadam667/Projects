#pragma once
#include "Ocena.h"
#include <conio.h>
class Przedmiot
{
protected:
	std::string nazwa;
	Ocena* Lista_ocen;
	float koncowa;
public:	
	float reinterpretacja_oceny(std::string);
	bool walidacja_oceny(std::string);
	bool walidacja_rodzaju(int);
	virtual void wpisz_ocene() = 0;
	virtual void wszystkie_oceny(std::ostream&) = 0;
	virtual bool edytuj_ocene() = 0;
	virtual bool usun_ocene() = 0;
	void dodaj_ocene(Ocena*&);
	void usun_wszystkie_oceny();
	void wystaw_koncowa();
	bool sprawdz_koncowa(int);
	void wpisz_w_swiadectwo(std::ostream&);
	void set_nazwa(std::string);
	float get_koncowa();
	Przedmiot();
};

