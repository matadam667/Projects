#include "Scisly.h"
void Scisly::wpisz_ocene()
{
	int _rodzaj;
	do
	{
		system("cls");
		std::cout <<nazwa<< "\n\nPodaj rodzaj oceny, ktora chcesz wpisac:\n[1]Odpowiedz ustna\n[2]Sprawdzian\n[3]Kartkowka\n";
		_rodzaj = _getch() - 48;
		if (_rodzaj > 3 || _rodzaj < 1)
		{
			std::cout << "Nieporawny rodzaj\nNacisnij dowolny przycisk by kontynowac\n";
			int wez = _getch();
		}
	} while (_rodzaj > 3 || _rodzaj < 1);
	if (_rodzaj == 1)
		_rodzaj = 3;
	else if (_rodzaj == 3)
		_rodzaj = 1;
	std::string nowa_ocn_str;
	do
	{
		system("cls");
		std::cout << nazwa << "\n";
		if (_rodzaj == 3)
		{
			std::cout << "Odpowiedz ustna\n";
		}
		if (_rodzaj == 2)
		{
			std::cout << "Sprawdzian\n";
		}
		else if(_rodzaj==1)
		{
			std::cout << "Kartkowka\n\n";
		}
		std::cout << "Podaj ocene, ktora chcesz wpisac: ";
		std::cin >> nowa_ocn_str;
		if (walidacja_oceny(nowa_ocn_str) == false)
		{
			std::cout << "Niepoprawny format oceny\nNacisnij dowolny przycisk by kontynuowac\n";
			int wez = _getch();
		}
	} while (walidacja_oceny(nowa_ocn_str) == false);
	float nowa_ocn = reinterpretacja_oceny(nowa_ocn_str);
	Ocena* nowa = new Ocena(nowa_ocn, _rodzaj);
	dodaj_ocene(nowa);
}
void Scisly::wszystkie_oceny(std::ostream& wyjscie)
{
	wyjscie << nazwa << "\n";
	Ocena* tmp = Lista_ocen;
	wyjscie << "Odpowiedzi ustne: \n";
	while (tmp&&tmp->operator==(3))
	{
		tmp->operator<<(wyjscie);
		tmp = tmp->pNext;
	}
	wyjscie << "\n";
	wyjscie << "Sprawdziany: \n";
	while (tmp&&tmp->operator==(2))
	{
		tmp->operator<<(wyjscie);
		tmp = tmp->pNext;
	}
	wyjscie << "\n";
	wyjscie << "Kartkowki: \n";
	while (tmp)
	{
		tmp->operator<<(wyjscie);
		tmp = tmp->pNext;
	}
	wyjscie << "\n";
}
Scisly::Scisly(void)
{
	pNext = nullptr;
}
Scisly::~Scisly()
{
	usun_wszystkie_oceny();
}

bool Scisly::edytuj_ocene()
{
	int _rodzaj;
	do
	{
		system("cls");
		wszystkie_oceny(std::cout);
		std::cout << "\nPodaj rodzaj oceny, ktora chcesz edytowac: \n[1]Odpowiedz ustna\n[2]Sprawdzian\n[3]Kartkowka\n";
		_rodzaj = _getch()-48;
	} while (_rodzaj < 0 && _rodzaj < 4);
	if (_rodzaj == 1)
		_rodzaj = 3;
	else if (_rodzaj == 3)
		_rodzaj = 1;
	std::string str_ocn;
	do
	{
		system("cls");
		wszystkie_oceny(std::cout);
		std::cout << "\nPodaj rodzaj oceny, ktora chcesz edytowac: \n[1]Odpowiedz ustna\n[2]Sprawdzian\n[3]Kartkowka\n";
		std::cout << "Podaj ocene, ktora chcesz edytowac: ";
		std::cin >> str_ocn;
	} while (walidacja_oceny(str_ocn) == false);
	float _ocn = reinterpretacja_oceny(str_ocn);
	if (Lista_ocen->operator==( _rodzaj) && Lista_ocen->operator== (_ocn))
	{
		Ocena* tmp = Lista_ocen->pNext;
		delete Lista_ocen;
		Lista_ocen = tmp;
	}
	else
	{
		Ocena* tmp = Lista_ocen;
		while (tmp)
		{
			if (tmp->pNext->operator==( _ocn) && tmp->pNext->operator==( _rodzaj))
			{
				std::string nowa_ocn_str;
				do
				{
					std::cout << "Popraw ocene: ";
					std::cin >> nowa_ocn_str;
					if (walidacja_oceny(nowa_ocn_str) == false)
						std::cout << "Nieporawny format oceny\n";
				} while (walidacja_oceny(nowa_ocn_str) == false);
				float nowa_ocn = reinterpretacja_oceny(nowa_ocn_str);
				Ocena o2 = Ocena(nowa_ocn, _rodzaj);
				tmp->operator=(o2);
				return true;
			}
			tmp = tmp->pNext;
		}
		return false;
	}
}

bool Scisly::usun_ocene()
{
	int _rodzaj;
	do
	{
		system("cls");
		wszystkie_oceny(std::cout);
		std::cout << "\nPodaj rodzaj oceny, ktora chcesz usunac: \n[1]Odpowiedz ustna\n[2]Sprawdzian\n[3]Kartkowka\n";
		_rodzaj = _getch()-48;
	} while (_rodzaj < 0 && _rodzaj < 4);
	if (_rodzaj == 1)
		_rodzaj = 3;
	else if (_rodzaj == 3)
		_rodzaj = 1;
	std::string str_ocn;
	do
	{
		system("cls");
		wszystkie_oceny(std::cout);
		std::cout << "\nPodaj rodzaj oceny, ktora chcesz usunac: \n[1]Odpowiedz ustna\n[2]Sprawdzian\n[3]Kartkowka\n";
		std::cout << "Podaj ocene, ktora chcesz edytowac: ";
		std::cin >> str_ocn;
	} while (walidacja_oceny(str_ocn) == false);
	float _ocn = reinterpretacja_oceny(str_ocn);
	Ocena* tmp = Lista_ocen;
	while (tmp)
	{
		if (tmp->pNext->operator==( _ocn) && tmp->pNext->operator==( _rodzaj))
		{
			Ocena* tmp2 = tmp->pNext->pNext;
			delete tmp->pNext;
			tmp->pNext = tmp2;
			return true;
		}
		tmp = tmp->pNext;
	}
	return false;
}