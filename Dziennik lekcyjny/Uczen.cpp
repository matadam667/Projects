#include "Uczen.h"
Uczen::Uczen(void)
{
	Lista_human = nullptr;
	Lista_scislych = nullptr;
	wf = new Wuef();
	pNext = nullptr;
	urodziny.set_dzien(11);
	urodziny.set_miesiac(11);
	urodziny.set_rok(1111);
	zamieszkanie.set_dom(1);
	zamieszkanie.set_miasto("brak");
	zamieszkanie.set_ulica("brak");
	zamieszkanie.set_mieszkanie(1);
	plec = 'B';
	nazwisko = "brak_nazwiska";
	imie = "brak_imienia";
	telefon = "brak_telefonu";
	pesel = "brak_peselu";
	srednia_koncowa = 0;
}
void Uczen::szczegoly_ucznia(std::ostream& wyjscie)
{
	wyjscie << "\nImie i nazwisko: " << imie << " " << nazwisko << "\n";
	wyjscie << "Numer kontaktowy: " << telefon << " ";
	urodziny.operator<<(wyjscie);
	zamieszkanie.operator<<(wyjscie);
	wyjscie << "Plec: " << plec << " ";
	wyjscie << "Pesel: " << pesel << "\n";
}

void Uczen::drukuj_swiadectwo(void)
{
	std::ofstream plik;
	wystaw_koncowe();
	plik.open(this->nazwisko + this->pesel + ".txt");
	if (plik.good())
	{
		bool promocja = true;
		operator<<(plik);plik << "\n";
		Humanistyczny* tmp = this->Lista_human;
		while (tmp)
		{
			tmp->wpisz_w_swiadectwo(plik);
			if (tmp->sprawdz_koncowa(1))
				promocja = false;
			tmp = tmp->pNext;

		}
		Scisly* tmp2 = this->Lista_scislych;
		while (tmp2)
		{
			tmp2->wpisz_w_swiadectwo(plik);
			if (tmp2->sprawdz_koncowa(1))
				promocja = false;
			tmp2 = tmp2->pNext;
		}
		wf->wpisz_w_swiadectwo(plik);
		if (wf->sprawdz_koncowa(1))
			promocja = false;
		plik << "Srednia ocen: " << std::setprecision(2)<<this->srednia_koncowa << "\n";
		plik << "Pasek: ";
		if (srednia_koncowa >= 4.75)
			plik << "TAK\n";
		else
			plik << "NIE\n";
		plik << "PROMOCJA: ";
		if (promocja == true)
			plik << "TAK\n";
		else
			plik << "NIE\n";
	}
}

std::ostream& Uczen::operator<<(std::ostream& wyjscie)
{
	wyjscie << nazwisko << " " << imie;
	return wyjscie;
}

std::istream& Uczen::operator>>(std::istream& wejscie)
{
	std::string linijka;
	wejscie >> linijka>>linijka>>linijka>>imie >> nazwisko >> linijka >> linijka >> telefon >> linijka;
	urodziny.operator>>(wejscie);
	zamieszkanie.operator>>(wejscie);
	wejscie >>linijka>> plec>>linijka  >> pesel;
	getline(wejscie, linijka);
	for (int i = 0;i < 10;i++)
	{
		if (i < 4)
		{
			Humanistyczny* tmp = new Humanistyczny();
			for (int j = 0;j < 7;j++)
			{
				std::getline(wejscie, linijka);
				if (j == 0)
					tmp->set_nazwa(linijka);
				else if (j == 2)
				{
					std::stringstream ss;
					std::string tymczasowy;
					ss << linijka;
					if (linijka != "")
					{
						while (ss >> tymczasowy)
						{
							float _ocena = tmp->reinterpretacja_oceny(tymczasowy);
							Ocena* nowa_ocena = new Ocena(_ocena, 3);
							tmp->dodaj_ocene(nowa_ocena);
						}
					}
				}
				else if (j == 4)
				{
					std::stringstream ss;
					std::string tymczasowy;
					ss << linijka;
					if (linijka != "")
					{
						while (ss >> tymczasowy)
						{
							float _ocena = tmp->reinterpretacja_oceny(tymczasowy);
							Ocena* nowa_ocena = new Ocena(_ocena, 2);
							tmp->dodaj_ocene(nowa_ocena);
						}
					}
				}
				else if (j == 6)
				{
					std::stringstream ss;
					std::string tymczasowy;
					ss << linijka;
					if (linijka != "")
					{
						while (ss >> tymczasowy)
						{
							float _ocena = tmp->reinterpretacja_oceny(tymczasowy);
							Ocena* nowa_ocena = new Ocena(_ocena, 1);
							tmp->dodaj_ocene(nowa_ocena);
						}
					}
					dodaj_humanistyczny(tmp);
				}
			}
		}
		else if (i < 9)
		{
			Scisly* tmp = new Scisly();
			for (int j = 0;j < 7;j++)
			{
				getline(wejscie, linijka);
				if (j == 0)
					tmp->set_nazwa(linijka);
				else if (j == 2)
				{
					std::stringstream ss;
					std::string tymczasowy;
					ss << linijka;
					if (linijka != "")
					{
						while (ss >> tymczasowy)
						{
							float _ocena = tmp->reinterpretacja_oceny(tymczasowy);
							Ocena* nowa_ocena = new Ocena(_ocena, 3);
							tmp->dodaj_ocene(nowa_ocena);
						}
					}
				}
				else if (j == 4)
				{
					std::stringstream ss;
					std::string tymczasowy;
					ss << linijka;
					if (linijka != "")
					{
						while (ss >> tymczasowy)
						{
							float _ocena = tmp->reinterpretacja_oceny(tymczasowy);
							Ocena* nowa_ocena = new Ocena(_ocena, 2);
							tmp->dodaj_ocene(nowa_ocena);
						}
					}
				}
				else if (j == 6)
				{
					std::stringstream ss;
					std::string tymczasowy;
					ss << linijka;
					if (linijka != "")
					{
						while (ss >> tymczasowy)
						{
							float _ocena = tmp->reinterpretacja_oceny(tymczasowy);
							Ocena* nowa_ocena = new Ocena(_ocena, 1);
							tmp->dodaj_ocene(nowa_ocena);
						}
					}
					dodaj_scisly(tmp);
				}
			}
		}
		else
		{
			for (int j = 0;j < 7;j++)
			{
				getline(wejscie, linijka);
				if (j == 0)
					wf->set_nazwa(linijka);
				else if (j == 2)
				{
					std::stringstream ss;
					std::string tymczasowy;
					ss << linijka;
					if (linijka != "")
					{
						while (ss >> tymczasowy)
						{
							float _ocena = wf->reinterpretacja_oceny(tymczasowy);
							Ocena* nowa_ocena = new Ocena(_ocena, 3);
							wf->dodaj_ocene(nowa_ocena);
						}
					}
				}
				else if (j == 4)
				{
					std::stringstream ss;
					std::string tymczasowy;
					ss << linijka;
					if (linijka != "")
					{
						while (ss >> tymczasowy)
						{
							float _ocena = wf->reinterpretacja_oceny(tymczasowy);
							Ocena* nowa_ocena = new Ocena(_ocena, 2);
							wf->dodaj_ocene(nowa_ocena);
						}
					}
				}
				else if (j == 6)
				{
					std::stringstream ss;
					std::string tymczasowy;
					ss << linijka;
					if (linijka != "")
					{
						while (ss >> tymczasowy)
						{
							float _ocena = wf->reinterpretacja_oceny(tymczasowy);
							Ocena* nowa_ocena = new Ocena(_ocena, 1);
							wf->dodaj_ocene(nowa_ocena);
						}
					}
				}
			}
		}
	}
	return wejscie;
}
void Uczen::usun_humanistyczne()
{
	Humanistyczny* tmp = Lista_human;
	while (tmp)
	{
		Humanistyczny* tmp2 = tmp->pNext;
		delete tmp;
		tmp = tmp2;
	}
}
void Uczen::usun_scisle()
{
	Scisly* tmp = Lista_scislych;
	while (tmp)
	{
		Scisly* tmp2 = tmp->pNext;
		delete tmp;
		tmp = tmp2;
	}
}
Uczen::~Uczen(void)
{
	usun_humanistyczne();
	usun_scisle();
	delete wf;
}

void Uczen::wypisz_przedmioty()
{
	Humanistyczny* tmp = Lista_human;
	int i = 1;
	while (tmp)
	{
		tmp->wystaw_koncowa();
		std::cout << "[" << i << "] ";tmp->wpisz_w_swiadectwo(std::cout);
		tmp = tmp->pNext;
		i++;
	}
	Scisly* tmp2 = Lista_scislych;
	while (tmp2)
	{
		tmp2->wystaw_koncowa();
		std::cout << "[" << i << "] ";tmp2->wpisz_w_swiadectwo(std::cout);
		tmp2 = tmp2->pNext;
		i++;
	}
	std::cout << "[" << i << "] "; 
	wf->wystaw_koncowa();
	wf->wpisz_w_swiadectwo(std::cout);;
}
bool Uczen::operator<(const Uczen& u2)
{
	if (nazwisko.compare(u2.nazwisko) == -1)
		return true;
	else if (nazwisko.compare(u2.nazwisko) == 0)
	{
		if (imie.compare(u2.imie) == -1)
			return true;
	}
	return false;
}
void Uczen::wpisz_do_pliku(std::ostream& wyjscie)
{
	szczegoly_ucznia(wyjscie);
	Humanistyczny* human = Lista_human;
	while (human)
	{
		human->wszystkie_oceny(wyjscie);
		human = human->pNext;
	}
	Scisly* Sc = Lista_scislych;
	while (Sc)
	{
		Sc->wszystkie_oceny(wyjscie);
		Sc = Sc->pNext;
	}
	wf->wszystkie_oceny(wyjscie);
}

void Uczen::dodaj_humanistyczny(Humanistyczny*& nowy)
{
	if (Lista_human == nullptr)
		Lista_human = nowy;
	else
	{
		Humanistyczny* tmp = Lista_human;
		while (tmp->pNext)
			tmp = tmp->pNext;
		tmp->pNext = nowy;
	}
}
void Uczen::dodaj_scisly(Scisly*& nowy)
{
	if (Lista_scislych == nullptr)
		Lista_scislych = nowy;
	else
	{
		Scisly* tmp = Lista_scislych;
		while (tmp->pNext)
			tmp = tmp->pNext;
		tmp->pNext = nowy;
	}
}
void Uczen::zestaw_przedmiotow()
{
	for (int i = 0;i < 4;i++)
	{
		Humanistyczny* nowy = new Humanistyczny();
		if (i == 0)
			nowy->set_nazwa("Jezyk polski");
		else if (i == 1)
			nowy->set_nazwa("Jezyk angielski");
		else if (i == 2)
			nowy->set_nazwa("Jezyk niemiecki");
		else if (i == 3)
			nowy->set_nazwa("Historia");
		dodaj_humanistyczny(nowy);
	}
	for (int i = 0;i < 5;i++)
	{
		Scisly* nowy = new Scisly();
		if (i == 0)
			nowy->set_nazwa ("Matematyka");
		else if (i == 1)
			nowy->set_nazwa("Fizyka");
		else if (i == 2)
			nowy->set_nazwa("Informatyka");
		else if (i == 3)
			nowy->set_nazwa("Biologia");
		else if (i == 4)
			nowy->set_nazwa("Chemia");
		dodaj_scisly(nowy);
	}
}
void Uczen::wystaw_koncowe()
{
	float srednia = 0;
	Humanistyczny* tmp = Lista_human;
	for (int i = 0;i < 4;i++)
	{
		tmp->wystaw_koncowa();
		srednia = srednia + tmp->get_koncowa();
		tmp = tmp->pNext;
	}
	Scisly* tmp2 = Lista_scislych;
	for (int i = 0;i < 5;i++)
	{
		tmp2->wystaw_koncowa();
		srednia = srednia + tmp2->get_koncowa();
		tmp2 = tmp2->pNext;
	}
	wf->wystaw_koncowa();
	srednia = srednia + wf->get_koncowa();
	srednia_koncowa = srednia / 10;
	
}

void Uczen::set_imie(std::string _imie)
{
	imie = _imie;
}

void Uczen::set_nazwisko(std::string _nazwisko)
{
	nazwisko = _nazwisko;
}

void Uczen::set_pesel(std::string _pesel)
{
	pesel = _pesel;
}

void Uczen::set_telefon(std::string _telefon)
{
	telefon = _telefon;
}

Adres Uczen::get_adres()
{
	return this->zamieszkanie;
}

void Uczen::set_adres(Adres _adr)
{
	zamieszkanie.miasto = _adr.miasto;
	zamieszkanie.ulica = _adr.ulica;
	zamieszkanie.dom = _adr.dom;
	zamieszkanie.mieszkanie = _adr.mieszkanie;
}

std::string Uczen::get_pesel()
{
	return this->pesel;
}

void Uczen::set_data(Data d2)
{
	urodziny.dzien = d2.dzien;
	urodziny.miesiac = d2.miesiac;
	urodziny.rok = d2.rok;
}

Data Uczen::get_data()
{
	return this->urodziny;
}

void Uczen::set_plec(char P)
{
	plec = P;
}