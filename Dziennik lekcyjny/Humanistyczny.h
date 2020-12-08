#pragma once
#include "Przedmiot.h"
class Humanistyczny : public Przedmiot
{
public:
	Humanistyczny* pNext;
	void wpisz_ocene();
	void wszystkie_oceny(std::ostream&);
	bool edytuj_ocene();
	bool usun_ocene();
	Humanistyczny();
	~Humanistyczny();
};


