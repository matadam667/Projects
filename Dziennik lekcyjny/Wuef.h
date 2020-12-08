#pragma once
#include "Przedmiot.h"

class Wuef : public Przedmiot
{
public:
	void wpisz_ocene();
	void wszystkie_oceny(std::ostream&);
	bool edytuj_ocene();
	bool usun_ocene();
	Wuef();
	~Wuef();
};

