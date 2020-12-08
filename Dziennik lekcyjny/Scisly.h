#pragma once
#include "Przedmiot.h"

class Scisly : public Przedmiot
{
public:
	Scisly* pNext;
	void wpisz_ocene();
	void wszystkie_oceny(std::ostream&);
	bool edytuj_ocene();
	bool usun_ocene();
	Scisly();
	~Scisly();
};



