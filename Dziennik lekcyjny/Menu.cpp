#include "Menu.h"
Menu::Menu()
{
	ilosc = 0;
	Uczen_lista = nullptr;
}
void Menu::wypisz_uczniow(void)
{
	Uczen* tmp = Uczen_lista;
	int i = 1;
	while (tmp)
	{
		std::cout << i << ". ";
		tmp->operator<<(std::cout);std::cout << "\n";
		tmp = tmp->pNext;
		i++;
	}
}
void Menu::dodaj_ucznia(Uczen*& nowy)
{
	if (Uczen_lista == nullptr)
	{
		Uczen_lista = nowy;
	}
	else
	{
		Uczen* tmp = Uczen_lista;
		while (tmp->pNext)
		{
			tmp = tmp->pNext;
		}
		tmp->pNext = nowy;
	}
}
void Menu::usun_ucznia(Uczen*& podany)
{
	if (Uczen_lista == podany)
	{
		Uczen* tmp = Uczen_lista->pNext;
		delete Uczen_lista;
		Uczen_lista = tmp;
	}
	else
	{
		Uczen* tmp = Uczen_lista;
		while (tmp->pNext&&tmp->pNext != podany)
			tmp = tmp->pNext;
		if (tmp->pNext == podany)
		{
			Uczen* tmp2 = tmp->pNext->pNext;
			delete podany;
			tmp->pNext = tmp2;
		}
	}
}
void Menu::usun_wszystkich()
{
	Uczen* tmp = Uczen_lista;
	while (tmp)
	{
		Uczen* tmp2 = tmp->pNext;
		delete tmp;
		tmp = tmp2;
	}
}
Menu::~Menu()
{
	usun_wszystkich();
}

void Menu::glowne()
{
	while (true)
	{
		system("cls");
		std::cout << "Dziennik szkolny\n[1] Wyswietl liste uczniow\n[2] Oceny \n[3] Drukuj swiadectwa\n[4] Inne\n\n[ESC] Wyjscie z programu\n";
		int wybor = _getch();
		if (wybor == '1')
		{
			int wybor2 = lista_uczniow();
			while (wybor2 != 27)
			{
				if (wybor2 == '1')
				{
					if (uczen_szczegoly() == 27)
						break;
				}
				else if (wybor2 == '2')
				{
					Dodaj_nowego();
					break;
				}
				else if (wybor2 == '3')
				{
					usuwanie();
					break;
				}
				else if(wybor2!=27)
				{
					std::cout << "Niepoprawny wybor\nNacisnij dowolny przycisk by kontynuowac\n";
					int wez = _getch();
				}
			}
		}
		else if (wybor == '2')
		{
			int wybor2;
			wybor2= Oceny_menu();
			do 
			{
				if (wybor2 == '1')
				{
					if (dodawanie_ocen() == 27)
						break;
				}
				else if (wybor2 == '2')
				{
					if (wyswietalnie_ocen() == 27)
						break;
				}
				else if (wybor2 == '3')
				{
					if (usuwanie_ocen() == 27)
						break;
				}
				else if (wybor2 == '4')
				{
					if (edytowanie_ocen() == 27)
						break;
				}
				else if (wybor2 != 27)
				{
					std::cout << "Nieporawny wybor\nNacisnij dowolny przycisk by kontynowac\n";
					int wez = _getch();
				}
			}while (true);
		}
		else if (wybor == '3')
		{
			swiadectwa();
		}
		else if (wybor == '4')
		{
			int wybor2;
			do
			{
				system("cls");
				std::cout << "Wybierz rodzaj sortowania:\n\n[1]Sortuj afabetycznie\n[2]Sortuj wg wieku\n[3]Sortuj wg zamieszkania\n";
				wybor2=_getch()-48;
				if (wybor2 < 1 && wybor2>4)
				{
					std::cout << "\nNieporawny wybor\nNacisnij dowolny przycisk by kontynuowac\n";
					int wez = _getch();
				}
			} while (wybor2 < 1 && wybor2>4);
			Sortowanie_przez_scalanie(Uczen_lista, wybor2);
		}
		else if (wybor == 27)
		{
			wpisz_do_pliku();
			break;
		}
	}
}

int Menu::lista_uczniow()
{
	system("cls");
	wypisz_uczniow();
	std::cout << "\nDostepne dzialania:\n[1] Wyswietl szczegolowe informacje \n[2] Dodaj ucznia\n[3] Skresl ucznia\n[ESC] Wroc do menu glownego\n";
	int wybor = _getch();
	return wybor;
}

int Menu::Oceny_menu()
{
	system("cls");
	wypisz_uczniow();
	std::cout << "\nDostepne dzialania:\n[1] Dodaj ocene\n[2] Wyswietl wszystkie oceny ucznia\n[3] Usun ocene\n[4] Edytuj ocene\n[ESC] Wroc do menu glownego\n";
	int wybor = _getch();
	return wybor;
}

void Menu::swiadectwa()
{
	Uczen* tmp = Uczen_lista;
	while (tmp)
	{
		tmp->drukuj_swiadectwo();
		tmp = tmp->pNext;
	}
	system("cls");
	std::cout << "Swiadectwa zostaly wydrukowane\nNacisnij dowolny przycisk by wrocic do menu glownego\n";
	int wybor = _getch();
}

int Menu::inne()
{
	wypisz_uczniow();
	std::cout << "\nDostepne dzialania:\n[1]Znajdz najlepszego ucznia w klasie\n[2]Znajdz najlepszego ucznia z kazdego przedmiotu\n[3]Posortuj uczniow\n";
	int wybor = _getch();
	return wybor;
}

int Menu::uczen_szczegoly()
{
	int numer;
	do {
		system("cls");
		wypisz_uczniow();
		std::cout << "Podaj numer ucznia, ktorego szczegolowe informacje chcesz wyswietlic: ";
		std::cin >> numer;
		if (ilosc-numer<  0)
			std::cout << "Nieporawny numer!\n";
	} while (ilosc-numer < 0);
	Uczen* tmp = Uczen_lista;
	for (int i = 0;i < numer - 1;i++)
		tmp = tmp->pNext;
	int wybor;
	tmp->szczegoly_ucznia(std::cout);
	std::cout << "\n\n[1] Edytuj ucznia\n[ESC] Wroc do menu glownego\n\nNacisnij dowolny inny przycisk by wyswietlic szczegoly innego ucznia\n";
	wybor = _getch();
	if (wybor == '1')
	{
		while (true)
		{
			system("cls");
			tmp->szczegoly_ucznia(std::cout);
			std::cout << "\n\nDostepne Opcje: \n[1]Edytuj imie \n[2]Edytuj nazwisko\n[3]Edytuj adres zamieszkania\n[4]Edytuj telefon kontaktowy\n[5]Edytuj PESEL\n[ESC]Powrot\n";
			int wybor2 = _getch();
			system("cls");
			tmp->szczegoly_ucznia(std::cout);
			if (wybor2 == '1')
			{
				std::cout << "Podaj imie ucznia: ";
				std::string nowe;
				std::cin >> nowe;
				tmp->set_imie(nowe);
				std::cout << "Imie zostalo edytowane\nNacisnij dowolny przycisk by kontynowac\n";
				int wez=_getch();
			}
			else if (wybor2 == '2')
			{
				std::cout << "Podaj nazwisko ucznia: ";
				std::string nowe;
				std::cin >> nowe;
				tmp->set_nazwisko(nowe);
				std::cout << "Nazwisko zostalo edytowane\nNacisnij dowolny przycisk by kontynowac\n";
				int wez = _getch();
			}
			else if (wybor2 == '3')
			{
				Adres _zamieszkanie = tmp->get_adres();
				std::cout << "Podaj miejscowosc, w ktorej mieszka uczen: ";
				std::string _miasto;
				std::cin >> _miasto;
				_zamieszkanie.set_miasto(_miasto);
				std::cout << "Podaj ulice, na ktorej mieszka uczen: ";
				std::string _ulica;
				std::cin >> _ulica;
				_zamieszkanie.set_ulica(_ulica);
				std::cout << "Podaj numer domu ucznia: ";
				int _dom;
				std::cin >> _dom;
				_zamieszkanie.set_dom(_dom);
				std::cout << "Podaj numer mieszkania ucznia: ";
				int _mieszkanie;
				std::cin >> _mieszkanie;
				_zamieszkanie.set_mieszkanie(_mieszkanie);
				tmp->set_adres(_zamieszkanie);
				std::cout << "Adres zostal edytowany\nNacisnij dowolny przycisk by kontynuowac\n";
				int wez=_getch();
			}
			else if (wybor2 == '4')
			{
				std::cout << "Podaj nowy numer kontaktowy: ";
				std::string nowy;
				std::cin >> nowy;
				tmp->set_telefon(nowy);
				std::cout << "Pomyslnie edytowano numer telefonu\nNacisnij dowolny przycisk by kontynuowac\n";
				int wez = _getch();
			}
			else if (wybor2 == 27)
				break;
			else if (wybor2 == '5')
			{
				std::string _pesel;
				do
				{
					std::cout << "Podaj PESEL  ucznia: ";
					std::cin >> _pesel;
					if (tmp->liczba_kontrolna(_pesel) == false)
					{
						std::cout << "Niepoprawny PESEL.\nNacisnij dowolny przycisk by kontynuowac\n";
						int wez = _getch();
					}
					if (walidacja_pesel(_pesel) == false)
					{
						std::cout << "Istnieje juz uczen o takim numerze PESEL.\n[ESC] Powrot do menu glownego\nNacisnij dowolny inny przycisk by wpisac inny numer PESEL\n";
						int wez = _getch();
					}
				} while (tmp->liczba_kontrolna(_pesel) == false || walidacja_pesel(_pesel) == false);
				tmp->set_pesel(_pesel);
				char _plec = tmp->get_plec(_pesel);
				tmp->set_plec(_plec);
				int dziesietne = tmp->get_rok_urodzenia(_pesel);
				int _dzien = tmp->get_stulecie(dziesietne, _pesel);
				int _miesiac = tmp->get_miesiac(_pesel);
				int _rok = tmp->get_dni(_pesel);
				Data d2 = Data(_dzien, _miesiac, _rok);
				tmp->set_data(d2);
				std::cout << "Pesel zostal zmieniony\nNacisnij dowolny przycisk by kontynuowac\n[ESC] Powrot do menu glownego\n";
				int wez = _getch();
				if (wez == 27)
					break;
			}
			else
			{
				std::cout << "Niepoprawny wybor!\nNacisnij dowolny przycisk by kontynowac\n";
				int wez = _getch();
			}
		}
	}
	return wybor;
}
void Menu::Dodaj_nowego()
{
	system("cls");
	Uczen* nowy = new Uczen();
	std::cout << "Podaj imie nowego ucznia: ";
	std::string _imie;
	std::cin >> _imie;
	nowy->set_imie(_imie);
	std::cout << "Podaj nazwisko nowego ucznia: ";
	std::string _nazwisko;
	std::cin >> _nazwisko;
	nowy->set_nazwisko(_nazwisko);
	std::string _pesel;
	do {
		system("cls");
		std::cout << "Podaj imie nowego ucznia: " << _imie << "\n";
		std::cout << "Podaj nazwisko nowego ucznia: " << _nazwisko << "\n";
		std::cout << "Podaj PESEL nowego ucznia: ";
		std::cin >> _pesel;
		if (nowy->liczba_kontrolna(_pesel) == false)
		{
			std::cout << "Niepoprawny PESEL.\nNacisnij dowolny przycisk by kontynuowac\n";
			int wez = _getch();
		}
		if (walidacja_pesel(_pesel) == false)
		{
			std::cout << "Istnieje juz uczen o takim numerze PESEL.\n[ESC] Powrot do menu glownego\nNacisnij dowolny inny przycisk by wpisac inny numer PESEL\n";
			int wez = _getch();
			if (wez == 27)
				return;
		}
	} while (nowy->liczba_kontrolna(_pesel) == false||walidacja_pesel(_pesel)==false);
	
	char _plec = nowy->get_plec(_pesel);
	nowy->set_plec(_plec);
	int dziesietne = nowy->get_rok_urodzenia(_pesel);
	int _dzien = nowy->get_stulecie(dziesietne, _pesel);
	int _miesiac = nowy->get_miesiac(_pesel);
	int _rok = nowy->get_dni(_pesel);
	nowy->set_pesel(_pesel);
	Data d2 = Data(_dzien, _miesiac, _rok);
	nowy->set_data(d2);
	Adres a2 = Adres();
	std::cout << "Podaj miejscowosc, z ktorej jest nowy uczen: ";
	std::cin >> a2.miasto;
	std::cout << "Podaj ulice, na ktorej mieszka nowy uczen: ";
	std::cin >> a2.ulica;
	std::cout << "Podaj numer domu nowego ucznia: ";
	std::cin >> a2.dom;
	std::cout << "Podaj numer mieszkania nowego ucznia: ";
	std::cin >> a2.mieszkanie;
	nowy->set_adres(a2);
	std::cout << "Podaj numer kontaktowy nowego ucznia: ";
	std::string _tel;
	std::cin >> _tel;
	nowy->set_telefon(_tel);
	nowy->zestaw_przedmiotow();
	dodaj_ucznia(nowy);
	ilosc++;
	std::cout << "Uczen zostal dodany do dziennika\nNacisnij dowolny przycisk by wrocid do menu glownego\n";
	int wez = _getch();
}
int Menu::wyswietalnie_ocen()
{
	int numer;
	do {
		system("cls");
		wypisz_uczniow();
		std::cout << "\n\nPodaj numer ucznia, ktorego oceny chcesz wyswietlic: ";
		std::cin >> numer;
		if (ilosc-numer < 0)
			std::cout << "Nieporawny numer!\n";
	} while (ilosc- numer< 0);
	Uczen* tmp = Uczen_lista;
	for (int i = 0;i < numer - 1;i++)
		tmp = tmp->pNext;
	wyswietl_wszystkie(tmp);
	std::cout << "\n[ESC] Powrot do menu glownego\nNacisnij dowolny inny przycisk by wyswietlic oceny innego ucznia\n";
	int wez = _getch();
	return wez;
}

void Menu::usuwanie()
{
	int numer;
	do {
		system("cls");
		wypisz_uczniow();
		std::cout << "Podaj numer ucznia, ktorego chcesz usunac: ";
		std::cin >> numer;
		if (ilosc - numer < 0)
		{
			std::cout << "Niepoprawny numer!\nNacisnij dowolny przycisk by kontynowac";
			int wez = _getch();
		}
	} while (ilosc - numer < 0);
	Uczen* tmp = Uczen_lista;
	for (int i = 0;i < numer - 1;i++)
		tmp = tmp->pNext;
	std::cout << "\n\n";
	tmp->szczegoly_ucznia(std::cout);
	std::cout << "Wprowadz pesel ucznia, by potwierdzic jego usuniecie: ";
	std::string weryfikacja;
	std::cin >> weryfikacja;
	std::string _psl = tmp->get_pesel();
	if (weryfikacja == _psl)
	{
		usun_ucznia(tmp);
		std::cout << "\nUsunieto ucznia z dziennika klasowego\nNacisnij dowolny przycisk by kontynuowac\n";
		int wez = _getch();
	}
	else
	{
		std::cout << "Podano zly PESEL. Uczen nie zostal usuniety.\nNacisnij dowolny przycisk by kontynuowac\n";
		int wez = _getch();
	}
}
int Menu::edytowanie_ocen()
{
	int numer;
	do {
		system("cls");
		wypisz_uczniow();
		std::cout << "Podaj numer ucznia, ktoremu chcesz edytowac ocene: ";
		std::cin >> numer;
		if (ilosc - numer < 0)
		{
			std::cout << "Niepoprawny numer!\nNacisnij dowolny przycisk by kontynowac";
			int wez = _getch();
		}
	} while (ilosc - numer < 0);
	Uczen* tmp = Uczen_lista;
	for (int i = 0;i < numer - 1;i++)
		tmp = tmp->pNext;
	int wybor;
	do
	{
		int lp;
		do {
			system("cls");
			tmp->operator<<(std::cout);
			std::cout << "\n";
			tmp->wypisz_przedmioty();
			std::cout << "\nWybierz przedmdiot, z ktorgo ocene chcesz edytowac: ";
			std::cin >> lp;
			if (lp < 1 || lp>10)
			{
				std::cout << "Niepoprawny numer przedmiotu\nNacisnij dowolny przycisk by kontynuowac\n";
				int wez = _getch();
			}
		} while (lp < 1 || lp>10);
		if (lp < 5)
		{
			Humanistyczny* tmp2 = tmp->Lista_human;
			for (int i = 0;i < lp - 1;i++)
				tmp2 = tmp2->pNext;
			if (tmp2->edytuj_ocene() == true)
			{
				std::cout << "Poprawnie edytowano ocene\n";
			}
			else
			{
				std::cout << "Ocena nie zostala edytowana. Sprobuj ponowanie\n";
			}
		}
		else if (lp < 10)
		{
			Scisly* tmp2 = tmp->Lista_scislych;
			for (int i = 0;i < lp - 1;i++)
				tmp2 = tmp2->pNext;
			if (tmp2->edytuj_ocene() == true)
			{
				std::cout << "Poprawnie edytowano ocene\n";
			}
			else
			{
				std::cout << "Ocena nie zostala edytowana. Sprobuj ponowanie\n";
			}
		}
		else
		{
			if (tmp->wf->edytuj_ocene() == true)
			{
				std::cout << "Poprawnie edytowano ocene\n";
			}
			else
			{
				std::cout << "Ocena nie zostala edytowana. Sprobuj ponowanie\n";
			}
		}
		std::cout << "\n[1] Edytuj ocene innego ucznia\n[ESC] Wroc do menu glownego\nNacisnij dowolny inny przycisk by wpisac "; tmp->operator<<(std::cout);std::cout << " nastepna ocene\n";
		wybor = _getch();
	} while (wybor != 27 && wybor != '1');
	return wybor;
}
int Menu::dodawanie_ocen()
{
	int numer;
	do {
		system("cls");
		wypisz_uczniow();
		std::cout << "Podaj numer ucznia, ktoremu chcesz wspisac ocene: ";
		std::cin >> numer;
		if (ilosc - numer < 0)
		{
			std::cout << "Niepoprawny numer!\nNacisnij dowolny przycisk by kontynowac";
			int wez = _getch();
		}
	} while (ilosc - numer < 0);
	Uczen* tmp = Uczen_lista;
	for (int i = 0;i < numer - 1;i++)
		tmp = tmp->pNext;
	int wybor;
	do
	{

		int lp;
		do {
			system("cls");
			tmp->operator<<(std::cout);
			std::cout << "\n";
			tmp->wypisz_przedmioty();
			std::cout << "\nWybierz przedmdiot, z ktorgo ocene chcesz wpisac: ";
			std::cin >> lp;
			if (lp < 1 || lp>10)
			{
				std::cout << "Niepoprawny numer przedmiotu\nNacisnij dowolny przycisk by kontynuowac\n";
				int wez = _getch();
			}
		} while (lp < 1 || lp>10);
		if (lp < 5)
		{
			Humanistyczny* tmp2 = tmp->Lista_human;
			for (int i = 0;i < lp - 1;i++)
				tmp2 = tmp2->pNext;
			tmp2->wpisz_ocene();
		}
		else if (lp < 10)
		{
			Scisly* tmp2 = tmp->Lista_scislych;
			for (int i = 0;i < lp - 1-4;i++)
				tmp2 = tmp2->pNext;
			tmp2->wpisz_ocene();
		}
		else
		{
			tmp->wf->wpisz_ocene();
		}
		std::cout << "Ocena zostala wpisana.\n[1]Wpisz ocene innego uczniowi\n[ESC]Wroc do menu glownego\nNacisnij dowolny inny przycisk by wpisac ";tmp->operator<<(std::cout);std::cout << " nastepna ocene\n";
		wybor = _getch();
	} while (wybor != 27 && wybor != '1');
	return wybor;
}
int Menu::usuwanie_ocen()
{
	int numer;
	do {
		system("cls");
		wypisz_uczniow();
		std::cout << "Podaj numer ucznia, ktoremu chcesz usun ocene: ";
		std::cin >> numer;
		if (ilosc - numer < 0)
		{
			std::cout << "Niepoprawny numer!\nNacisnij dowolny przycisk by kontynowac";
			int wez = _getch();
		}
	} while (ilosc - numer < 0);
	Uczen* tmp = Uczen_lista;
	for (int i = 0;i < numer - 1;i++)
		tmp = tmp->pNext;
	int wybor;
	do
	{
		int lp;
		do {
			system("cls");
			tmp->operator<<(std::cout);
			std::cout << "\n";
			tmp->wypisz_przedmioty();
			std::cout << "\nWybierz przedmdiot, z ktorgo ocene chcesz usunac: ";
			std::cin >> lp;
			if (lp < 1 || lp>10)
			{
				std::cout << "Niepoprawny numer przedmiotu\nNacisnij dowolny przycisk by kontynuowac\n";
				int wez = _getch();
			}
		} while (lp < 1 || lp>10);
		if (lp < 5)
		{
			Humanistyczny* tmp2 = tmp->Lista_human;
			for (int i = 0;i < lp - 1;i++)
				tmp2 = tmp2->pNext;
			if (tmp2->usun_ocene() == true)
			{
				std::cout << "Poprawnie usunieto ocene\n";
			}
			else
			{
				std::cout << "Ocena nie zostala usunieta. Sprobuj ponowanie\n";
			}
		}
		else if (lp < 10)
		{
			Scisly* tmp2 = tmp->Lista_scislych;
			for (int i = 0;i < lp - 1;i++)
				tmp2 = tmp2->pNext;
			if (tmp2->usun_ocene() == true)
			{
				std::cout << "Poprawnie usunieto ocene\n";
			}
			else
			{
				std::cout << "Ocena nie zostala usunieta. Sprobuj ponowanie\n";
			}
		}
		else
		{
			if (tmp->wf->usun_ocene() == true)
			{
				std::cout << "Poprawnie usunieto ocene\n";
			}
			else
			{
				std::cout << "Ocena nie zostala usunieta. Sprobuj ponowanie\n";
			}
		}
		std::cout << "\n[1] Usun ocene innego ucznia\n[ESC] Wroc do menu glownego\nNacisnij dowolny inny przycisk by wpisac "; tmp->operator<<(std::cout);std::cout << " nastepna ocene\n";
		wybor = _getch();
	} while (wybor != 27 && wybor != '1');
	return wybor;
}
void Menu::wyswietl_wszystkie(Uczen* podany)
{
	Humanistyczny* tmp = podany->Lista_human;
	for (int i = 0;i < 4;i++)
	{
		tmp->wszystkie_oceny(std::cout);
		tmp = tmp->pNext;
	}
	Scisly* tmp2 = podany->Lista_scislych;
	for (int i = 0;i < 5;i++)
	{
		tmp2->wszystkie_oceny(std::cout);
		tmp2 = tmp2->pNext;
	}
	podany->wf->wszystkie_oceny(std::cout);
}
void Menu::Sortowanie_przez_scalanie(Uczen*&pHead,int wybor)
{
	Uczen* pierwszy,* drugi;
	if (pHead == nullptr || pHead->pNext == nullptr)
		return;
	podziel_liste(pHead, pierwszy, drugi);
	Sortowanie_przez_scalanie(pierwszy,wybor);
	Sortowanie_przez_scalanie(drugi,wybor);
	pHead = sortuj(pierwszy, drugi, wybor);
}

void Menu::podziel_liste(Uczen* pHead, Uczen*& poczatek, Uczen*& koniec)
{
	Uczen* pierwsza;
	Uczen* druga;
	druga = pHead;
	pierwsza = pHead->pNext;
	while (pierwsza != nullptr)
	{
		pierwsza = pierwsza->pNext;
		if (pierwsza != nullptr)
		{
			druga = druga->pNext;
			pierwsza = pierwsza->pNext;
		}
	}
	poczatek = pHead;
	koniec = druga->pNext;
	druga->pNext = nullptr;
}

Uczen* Menu::sortuj(Uczen*& pierwszy,Uczen*&drugi, int wybor)
{
	Uczen* zwracany = nullptr;
	if (pierwszy == nullptr)
		return drugi;
	else if (drugi == nullptr)
		return pierwszy;
	if (wybor == 1)//alfabetycznie
	{
		if (pierwszy->operator<(*drugi))
		{
			zwracany = pierwszy;
			zwracany->pNext = sortuj(pierwszy->pNext, drugi, wybor);
		}
		else
		{
			zwracany = drugi;
			zwracany->pNext = sortuj(pierwszy, drugi->pNext, wybor);
		}
	}
	else if (wybor == 2)//wg daty urodzenia
	{
		Data d1 = pierwszy->get_data();
		Data d2 = drugi->get_data();
		if (d1.operator<(d2))
		{
			zwracany = pierwszy;
			zwracany->pNext = sortuj(pierwszy->pNext, drugi, wybor);
		}
		else
		{
			zwracany = drugi;
			zwracany->pNext = sortuj(pierwszy, drugi->pNext, wybor);
		}
	}
	else if (wybor == 3)//wg adresu
	{
		Adres a1 = pierwszy->get_adres();
		Adres a2 = drugi->get_adres();
		if (a1.operator<(a2))
		{
			zwracany = pierwszy;
			zwracany->pNext = sortuj(pierwszy->pNext, drugi, wybor);
		}
		else
		{
			zwracany = drugi;
			zwracany->pNext = sortuj(pierwszy, drugi->pNext, wybor);
		}
	}
	return zwracany;
}

void Menu::wpisz_do_pliku()
{
	std::ofstream plik;
	plik.open("uczniowie.txt");
	if (plik.good())
	{
		Uczen_lista->wpisz_do_pliku(plik);
	}
	plik.close();
	plik.open("uczniowie.txt", std::ios_base::app);
	if (plik.good())
	{
		Uczen* tmp = Uczen_lista->pNext;
		while (tmp)
		{
			tmp->wpisz_do_pliku(plik);
			tmp = tmp->pNext;
		}
	}
	plik.close();
}
void Menu::pobierz_z_pliku()
{
	std::ifstream plik;
	plik.open("uczniowie.txt");
	if (plik.good())
	{
		while (!plik.eof())
		{
			Uczen* nowy = new Uczen();
			nowy->operator>>(plik);
			dodaj_ucznia(nowy);
			ilosc++;
		}
	}
	plik.close();
}
bool Menu::walidacja_pesel(std::string _pesel)
{
	Uczen* tmp = Uczen_lista;
	while (tmp)
	{
		std::string _psl = tmp->get_pesel();
		if (_psl.compare(_pesel) == 0)
			return false;
		tmp = tmp->pNext;
	}
	return true;
}