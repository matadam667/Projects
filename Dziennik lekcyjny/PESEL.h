#pragma once
#include <iostream>
class _PESEL_
{
public:
	bool liczba_kontrolna(std::string);
	int get_rok_urodzenia(std::string);
	int get_stulecie(int, std::string);
	int get_dni(std::string);
	int get_miesiac(std::string);
	char get_plec(std::string);
};

