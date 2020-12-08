#pragma once
#include <iostream>
#include <sstream>
class Adres
{
public:
	std::string miasto;
	std::string ulica;
	int dom;
	int mieszkanie;
	Adres();
	void set_miasto(std::string);
	void set_ulica(std::string);
	void set_dom(int);
	void set_mieszkanie(int);
	std::ostream& operator<<(std::ostream&);
	std::istream& operator>>(std::istream&);
	bool operator<(const Adres&);
};

