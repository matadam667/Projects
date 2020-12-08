#include "Ocena.h"
Ocena::Ocena()
{
	ocena = 0;
	rodzaj = 0;
	pNext = nullptr;
}
Ocena::Ocena(float oc, int rdz)
{
	ocena = oc;
	rodzaj = rdz;
	pNext = nullptr;
}
std::ostream& Ocena::operator<<(std::ostream& wyjscie)
{
	if (this->rodzaj == 3)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 12);
		wyjscie << pisemna_ocena(this->ocena) << " ";
	}
	else if (this->rodzaj == 2)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 9);
		wyjscie << pisemna_ocena(this->ocena) << " ";
	}
	else
	{
		wyjscie << pisemna_ocena(this->ocena) << " ";
	}
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
	return wyjscie;
}
std::string Ocena::pisemna_ocena(float ocena)
{
	if (ocena == 1)
		return "1";
	else if (ocena == 1.5)
		return "1+";
	else if (ocena == 2)
		return "2";
	else if (ocena == 2.5)
		return "2+";
	else if (ocena == 2.75)
		return "3-";
	else if (ocena == 3)
		return "3";
	else if (ocena == 3.5)
		return "3+";
	else if (ocena == 3.75)
		return "4-";
	else if (ocena == 4)
		return "4";
	else if (ocena == 4.5)
		return "4+";
	else if (ocena == 4.75)
		return "5-";
	else if (ocena == 5)
		return "5";
	else if (ocena == 5.5)
		return "5+";
	else if (ocena == 5.75)
		return "6-";
	else
		return "6";
}

bool Ocena::operator>(const Ocena& o2)
{
	if (&o2==nullptr)
		return false;
	if (this->rodzaj > o2.rodzaj)
		return true;
	else if (this->rodzaj < o2.rodzaj)
		return false;
	else
	{
		if (this->ocena > o2.ocena)
			return true;
		else
			return false;
	}
}
float Ocena::operator+=(float _podany)
{
	return _podany + this->rodzaj * this->ocena;
}

bool Ocena::operator==(int _rodzaj)
{
	if (this->rodzaj == _rodzaj)
		return true;
	else
		return false;
}
bool Ocena::operator==(float _ocena)
{
	if (ocena == _ocena)
		return true;
	else
		return false;
}

Ocena& Ocena::operator=(const Ocena& o2)
{
	ocena = o2.ocena;
	rodzaj = o2.rodzaj;
	return *this;
}
