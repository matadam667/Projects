#include "Przedmiot.h"
Przedmiot::Przedmiot(void)
{
	Lista_ocen = nullptr;
	koncowa = 0;
}
bool Przedmiot::walidacja_oceny(std::string ocena_str)
{
	if (ocena_str.length() == 1)
	{
		if (ocena_str[0] == '1' || ocena_str[0] == '2' || ocena_str[0] == '3' || ocena_str[0] == '4' || ocena_str[0] == '5' || ocena_str[0] == '6')
			return true;
	}
	else if (ocena_str[1] == '+' || ocena_str[1] == '-')
	{
		if (ocena_str[0] == '2' || ocena_str[0] == '3' || ocena_str[0] == '4' || ocena_str[0] == '5')
			return true;
		else if (ocena_str[0] == 1 && ocena_str[1] == '+')
			return true;
		else if (ocena_str[0] == 6 && ocena_str[1] == '-')
			return true;
	}
	return false;
}
bool Przedmiot::walidacja_rodzaju(int rodzaj)
{
	if (rodzaj == 1 || rodzaj == 2 || rodzaj == 3)
		return true;
	else
		return false;
}
float Przedmiot::reinterpretacja_oceny(std::string ocena_str)
{
	float ocena = ocena_str[0] - 48;
	if (ocena_str.length() != 1)
	{
		if (ocena_str[1] == '+')
			ocena = ocena + 0.5;
		else if (ocena_str[1] == '-')
			ocena = ocena - 0.25;
	}
	return ocena;
}
void Przedmiot::usun_wszystkie_oceny(void)
{
	Ocena* tmp = Lista_ocen;
	while (tmp)
	{
		Ocena* tmp2 = tmp->pNext;
		delete tmp;
		tmp = tmp2;
	}
}
void Przedmiot::wystaw_koncowa(void)
{
	Ocena* tmp = Lista_ocen;
	int trojki, dwojki, jedynki;
	trojki = dwojki = jedynki = 0;
	float suma = 0;
	while (tmp)
	{
		if (tmp->operator==(3))
		{
			suma = tmp->operator+=(suma);
			trojki++;
		}
		else if (tmp->operator==(2))
		{
			suma = tmp->operator+=(suma);
			dwojki++;
		}
		else
		{
			suma = tmp->operator+=(suma);
			jedynki++;
		}
		tmp = tmp->pNext;
	}
	koncowa = round(suma / (3*trojki + 2*dwojki + jedynki));
}
void Przedmiot::dodaj_ocene(Ocena*& nowa)
{
	if (nowa->operator>(*Lista_ocen)||Lista_ocen==nullptr)
	{
		Ocena* tmp = Lista_ocen;
		Lista_ocen = nowa;
		nowa->pNext = tmp;
	}
	else
	{
		Ocena* tmp = Lista_ocen;
		while (tmp->pNext && tmp->pNext->operator>(*nowa))
			tmp = tmp->pNext;
		Ocena* tmp2 = tmp->pNext;
		tmp->pNext = nowa;
		nowa->pNext = tmp2;
	}
}

bool Przedmiot::sprawdz_koncowa(int _koncowa)
{
	if (koncowa == _koncowa)
		return true;
	else
		return false;
}

void Przedmiot::wpisz_w_swiadectwo(std::ostream& wyjscie)
{
	wyjscie << nazwa << " " << koncowa << "\n";
}

void Przedmiot::set_nazwa(std::string _nazwa)
{
	nazwa = _nazwa;
}

float Przedmiot::get_koncowa()
{
	return this->koncowa;
}