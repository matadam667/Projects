#include "PESEL.h"
bool _PESEL_::liczba_kontrolna(std::string pesel)
{
	if (pesel.length() != 11)
		return false;
	int kontrolna = 0;
	for (int i = 0;i < 10;i++)
	{
		if (i == 0 || i == 4 || i == 8)
		{
			kontrolna = kontrolna + int(pesel[i] - 48);
			int dzielnik = kontrolna / 10;
			kontrolna = kontrolna - 10 * dzielnik;
		}
		else if (i == 1 || i == 5 || i == 9)
		{
			int pomocnicza = 3 * int(pesel[i] - 48);
			kontrolna = kontrolna + pomocnicza;
			int dzielnik = kontrolna / 10;
			kontrolna = kontrolna - 10 * dzielnik;
		}
		else if (i == 2 || i == 6)
		{
			int pomocnicza = 7 * int(pesel[i] - 48);
			kontrolna = kontrolna + pomocnicza;
			int dzielnik = kontrolna / 10;
			kontrolna = kontrolna - 10 * dzielnik;
		}
		else
		{
			int pomocnicza = 9 * int(pesel[i] - 48);
			kontrolna = kontrolna + pomocnicza;
			int dzielnik = kontrolna / 10;
			kontrolna = kontrolna - 10 * dzielnik;
		}
	}
	if (10 - kontrolna == int(pesel[10] - 48))
		return true;
	else
		return false;
}
int _PESEL_::get_rok_urodzenia(std::string pesel)
{
	return(int(pesel[0] - 48) * 10 + int(pesel[1] - 48));
}
int _PESEL_::get_stulecie(int rok, std::string pesel)
{
	if (int(pesel[2] - 48) == 0 || int(pesel[2] - 48) == 1)
		return 1900 + rok;
	else if (int(pesel[2] - 48) == 2 || int(pesel[2] - 48) == 3)
		return 2000 + rok;
	else if (int(pesel[2] - 48) == 4 || int(pesel[2] - 48) == 5)
		return 2100 + rok;
	else if (int(pesel[2] - 48) == 6 || int(pesel[2] - 48) == 7)
		return 2200 + rok;
}
int _PESEL_::get_dni(std::string pesel)
{
	return (int(pesel[4] - 48) * 10 + int(pesel[5] - 48));
}
int _PESEL_::get_miesiac(std::string pesel)
{
	if (pesel[2] == '8' || pesel[2] == '0' || pesel[2] == '2' || pesel[2] == '4' || pesel[2] == '6')
	{
		if (pesel[3] == '1')
			return 1;
		else if (pesel[3] == '2')
			return 2;
		else if (pesel[3] == '3')
			return 3;
		else if (pesel[3] == '4')
			return 4;
		else if (pesel[3] == '5')
			return 5;
		else if (pesel[3] == '6')
			return 6;
		else if (pesel[3] == '7')
			return 7;
		else if (pesel[3] == '8')
			return 8;
		else if (pesel[3] == '9')
			return 9;
	}
	else if (pesel[2] == '9' || pesel[2] == '1' || pesel[2] == '3' || pesel[2] == '5' || pesel[2] == '7')
	{
		if (pesel[3] == '1')
			return 11;
		if (pesel[3] == '2')
			return 12;
		else
			return 10;
	}
}
char _PESEL_::get_plec(std::string pesel)
{
	if (int(pesel[9]) % 2 == 0)
		return 'K';
	else
		return 'M';
}