#include "Data.h"
#include "data.h"
Data::Data() :dzien(), rok(), miesiac() {}
Data::Data(int _dzien, int _mies, int _rok) : dzien(_dzien), miesiac(_mies), rok(_rok) {}
int Data::get_dzien()
{
	return dzien;
}
int Data::get_miesiac()
{
	return miesiac;
}
int Data::get_rok()
{
	return rok;
}
void Data::set_dzien(int _dzien)
{
	this->dzien = _dzien;
}
void Data::set_miesiac(int _mies)
{
	this->miesiac = _mies;
}
void Data::set_rok(int _rok)
{
	this->rok = _rok;
}

bool Data::operator<(const Data& d2)
{
	if (this->rok > d2.rok)
		return false;
	else if (this->rok < d2.rok)
		return true;
	else if (this->miesiac > d2.miesiac)
		return false;
	else if (this->miesiac < d2.miesiac)
		return true;
	else if (this->dzien < d2.dzien)
		return true;
	else
		return false;
}

std::ostream& Data::operator<<(std::ostream& wyjscie)
{
	wyjscie << "Data urodzenia: " << dzien << " " << miesiac << " " << rok << "\n";
	return wyjscie;
}
std::istream& Data::operator>>(std::istream& wejscie)
{
	std::string bufor;
	wejscie >> bufor >> dzien >> miesiac >> rok;
	return wejscie;
}
