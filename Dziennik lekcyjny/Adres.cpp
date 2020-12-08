#include "Adres.h"
Adres::Adres(void)
{
	miasto = "brak_miasta";
	ulica = "brak_ulicy";
	dom = 1111;
	mieszkanie = 1111;
}
void Adres::set_dom(int _dom)
{
	dom = _dom;
}
void Adres::set_miasto(std::string _miasto)
{
	miasto = _miasto;
}
void Adres::set_ulica(std::string _ulica)
{
	ulica = _ulica;
}
void Adres::set_mieszkanie(int _mieszkanie)
{
	mieszkanie = _mieszkanie;
}
std::ostream& Adres::operator<<(std::ostream& wyjscie)
{
	wyjscie << "Miasto: " << miasto << " Ulica: " << ulica << " Numer domu: " << dom << " Numer mieszkania: " << mieszkanie << "\n";
	return wyjscie;
}
std::istream& Adres::operator>>(std::istream& wejscie)
{
	std::string bufor;
	wejscie >> bufor >> miasto >> bufor >> ulica >> bufor >> bufor >> dom >> bufor >> bufor >> mieszkanie;
	return wejscie;
}
bool Adres::operator<(const Adres& a2)
{
	if (miasto.compare(a2.miasto) == 1)
		return false;
	else if (miasto.compare(a2.miasto) == -1)
		return true;
	else if (ulica.compare(a2.ulica) == 1)
		return false;
	else if (ulica.compare(a2.ulica) == -1)
		return true;
	else if (dom > a2.dom)
		return false;
	else if (dom < a2.dom)
		return true;
	else if (mieszkanie < a2.mieszkanie)
		return true;
	else
		return false;
}