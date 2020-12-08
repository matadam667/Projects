#pragma once
#include <iostream>
class Data
{
public:	
	int dzien;
	int miesiac;
	int rok;
	Data();
	Data(int, int, int);
	int get_dzien();
	int get_miesiac();
	int get_rok();
	void set_dzien(int);
	void set_miesiac(int);
	void set_rok(int);
	std::ostream& operator<<(std::ostream&);
	std::istream& operator>>(std::istream&);
	bool operator<(const Data&);
};

