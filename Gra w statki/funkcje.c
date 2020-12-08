#define _CRT_SECURE_NO_WARNINGS
#include "funkcje.h"
#include "struktury.h"
#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <time.h>
void zapisz_ustawienie_do_pliku(int xp, int yp, int xk, int yk, char* nazwa)
{
	FILE* plik;
	time_t czas = time(NULL);//pobranie czasu
	char* czas_str = ctime(&czas);//konwersja zmiennej czas na string
	czas_str[strlen(czas_str) - 1] = '\0';//ustawienie ostatniego znaku w stringu na koniec stringa
	plik = fopen("logi.txt", "a+");//otworzenie pliku w trybie dodawania na koniec
	if (plik)
	{
		if (yp == yk)//jezeli statek jest ustawiony horyzontalnie
		{
			fprintf(plik, "%s %s miedzy x=%d a x=%d ustawil statek na wysokosci y= %d.\n", czas_str, nazwa, xp, xk, yp);
		}
		else//jezeli statek jest ustawiony wertykalnie
		{
			fprintf(plik, "%s %s miedzy y=%d a y=%d ustawil statek na szerokosci x= %d.\n", czas_str, nazwa, yp, yk, xp);
		}
		fclose(plik);
	}
}
void zapisz_strzal_do_pliku(int x, int y, int status, char* nazwa)
{
	FILE* plik;
	time_t czas = time(NULL);//pobranie czasu
	char* czas_str = ctime(&czas);//konwersja zmiennej czas na string
	czas_str[strlen(czas_str) - 1] = '\0';//ustawienie ostatniego znaku w stringu na koniec stringa
	plik = fopen("logi.txt", "a+");//otwarcie pliku w trybie dodawania na koniec
	if (plik)
	{
		if (status == 4)//jezeli pudlo
		{
			fprintf(plik, "%s %s spudlowal strzelajac w pole x= %d y= %d.\n", czas_str, nazwa, x, y);
		}
		else if (status == 3)//jezeli zbicie
		{
			fprintf(plik, "%s %s trafil w statek na polu x= %d y= %d - statek zatopiony.\n", czas_str, nazwa, x, y);
		}
		else if (status == 2)//jezeli trafienie
		{
			fprintf(plik, "%s %s trafil w statek na polu x= %d y= %d.\n", czas_str, nazwa, x, y);
		}
		fclose(plik);
	}
}
bool walidacja_statku(struct Wspolrzedne_y** pHead, int yPoczatkowe, int xPoczatkowe, int yKoncowe, int xKoncowe)
{
	if (xKoncowe < xPoczatkowe)//zamiana koordynatow tak by xKonocwe zawsze bylo wieksze od xPoczatkowego
	{
		int tmp = xKoncowe;
		xKoncowe = xPoczatkowe;
		xPoczatkowe = tmp;
	}
	if (yKoncowe < yPoczatkowe)//zamiana koordynatow tak by yKomcowe zawsze bylo wieksze od yPoczatkowego
	{
		int tmp = yKoncowe;
		yKoncowe = yPoczatkowe;
		yPoczatkowe = tmp;
	}
	struct Wspolrzedne_y* pomocniczy = *pHead;
	struct Wspolrzedne_x* pomocniczy2;
	if (yPoczatkowe == yKoncowe)//jezeli statek ma byc ustawiony wertykalnie
	{
		if (yPoczatkowe == 1)//jezeli statek jest na samym dole planszy
		{
			while (pomocniczy->pDown->y != 1)
				pomocniczy = pomocniczy->pDown;//zjazd na przedostatni rzad planszy
			for (int i = 0;i < 2;i++)//sprawdzanie ostatniego oraz przedostatniego pola planszy
			{
				pomocniczy2 = pomocniczy->pHeadx;//wejscie na koordynaty X
				if (xPoczatkowe == 1)//jezeli statek jest na poczatku osi x
				{
					while (pomocniczy2->x != xKoncowe + 2)//przejscie przez caly statek i jedno pole za
					{
						{
							if (pomocniczy2->status != 0)//jezeli pole nie jest puste statek nie moze byc postawiony
								return false;
							pomocniczy2 = pomocniczy2->pNext;
						}
					}
				}
				else if (xKoncowe == 10)//jezeli statek jest na koncu osi x
				{
					while (pomocniczy2->pNext->x != xPoczatkowe)//przejscie na jedno pole przed statkiem
						pomocniczy2 = pomocniczy2->pNext;
					while (pomocniczy2->x != xKoncowe)//dojscie do konca statku
					{
						if (pomocniczy2->status != 0)//jezeli pole nie jest puste statek nie moze byc postawiony
							return false;
						pomocniczy2 = pomocniczy2->pNext;
					}
					if (pomocniczy2->status != 0)//jezeli pole nie jest puste statek nie moze byc postawiony
						return false;
				}
				else//w przypadku gdy statek jest w srodku planszy
				{
					while (pomocniczy2->pNext->x != xPoczatkowe)//przejscie na pole poprzedzajace statek
						pomocniczy2 = pomocniczy2->pNext;
					while (pomocniczy2->x != xKoncowe + 1)//przejscie na koniec statku
					{
						if (pomocniczy2->status != 0)//jezeli pole nie jest puste statek nie moze byc postawiony
							return false;
						pomocniczy2 = pomocniczy2->pNext;
					}
					if (pomocniczy2->status != 0)//sprawdzenie pola za statkiem
						return false;
				}
				pomocniczy = pomocniczy->pDown;//przejscie na ostatni rzad planszy
			}
		}
		else if (yKoncowe == 10)//jezeli statek znajduje sie na najwyzszym rzedzie planszy
		{
			for (int i = 0;i < 2;i++)//sprawdzenie najwyzszego oraz nastepnego rzedu planszy
			{
				pomocniczy2 = pomocniczy->pHeadx;//wejsice na koordynaty X
				if (xPoczatkowe == 1)//jezeli statek jest na poczatku osi X
				{
					while (pomocniczy2->x != xKoncowe + 2)//przejscie przez caly statek oraz pole za nim
					{
						{
							if (pomocniczy2->status != 0)//jezeli pole nie jest puste statek nie moze byc postawiony
								return false;
							pomocniczy2 = pomocniczy2->pNext;
						}
					}
				}
				else if (xKoncowe == 10)//jezeli statek jest na koncu osi X
				{
					while (pomocniczy2->pNext->x != xPoczatkowe)//przejscie na pole przed poprzedzajace statek
						pomocniczy2 = pomocniczy2->pNext;
					while (pomocniczy2->x != xKoncowe)//przejscie przez statek
					{
						if (pomocniczy2->status != 0)//jezeli pole nie jest puste statek nie moze byc postawiony
							return false;
						pomocniczy2 = pomocniczy2->pNext;
					}
					if (pomocniczy2->status != 0)//sprawdzenie ostatniego pola statku
						return false;
				}
				else//statek jest w srodku planszy
				{
					while (pomocniczy2->pNext->x != xPoczatkowe)//przejscie na pole poprzedzajace statek
						pomocniczy2 = pomocniczy2->pNext;
					while (pomocniczy2->x != xKoncowe + 1)//przejscie przez caly statek 
					{
						if (pomocniczy2->status != 0)//jezeli pole nie jest puste statek nie moze byc postawiony
							return false;
						pomocniczy2 = pomocniczy2->pNext;
					}
					if (pomocniczy2->status != 0)//sprawdzenie pola za statkiem
						return false;
				}
				pomocniczy = pomocniczy->pDown;//przejscie na rzad ponizej statku
			}
		}
		else//statek nie znajduje sie w skrajnych rzedach osi Y
		{
			while (pomocniczy->pDown->y != yKoncowe)//przejscie na rzad o jeden wyzej niz statek
				pomocniczy = pomocniczy->pDown;
			pomocniczy2 = pomocniczy->pHeadx;//wejscie w koordynaty X
			for (int i = 0;i < 3;i++)//sprawdzenie rzedu nad statkiem, rzedu statku oraz rzedu pod statkiem
			{
				pomocniczy2 = pomocniczy->pHeadx;//wejscie na koordynaty X
				if (xPoczatkowe == 1)//jezeli statek lezy na poczatku osi X
				{
					while (pomocniczy2->x != xKoncowe + 2)//przejscie przez caly statek oraz jedno pole za nim
					{
						{
							if (pomocniczy2->status != 0)//jezeli pole nie jest puste statek nie moze byc postawiony
								return false;
							pomocniczy2 = pomocniczy2->pNext;
						}
					}
				}
				else if (xKoncowe == 10)//jezeli statek lezy na koncu osi X
				{
					while (pomocniczy2->pNext->x != xPoczatkowe)//przejscie na pole poprzedzajace statek
						pomocniczy2 = pomocniczy2->pNext;
					while (pomocniczy2->x != xKoncowe)//przejscie przez caly statek
					{
						if (pomocniczy2->status != 0)//jezeli pole nie jest puste statek nie moze byc postawiony
							return false;
						pomocniczy2 = pomocniczy2->pNext;
					}
					if (pomocniczy2->status != 0)//sprawdzenie pola za statkiem
						return false;
				}
				else//jezeli statek jest w srodku planszy
				{
					while (pomocniczy2->pNext->x != xPoczatkowe)//przejscie na pole poprzedzajace statek
						pomocniczy2 = pomocniczy2->pNext;
					while (pomocniczy2->x != xKoncowe + 1)//przejscie przez statek
					{
						if (pomocniczy2->status != 0)//jezeli pole nie jest puste statek nie moze byc postawiony
							return false;
						pomocniczy2 = pomocniczy2->pNext;
					}
					if (pomocniczy2->status != 0)//sprawdzenie pola za statkiem
						return false;
				}
				pomocniczy = pomocniczy->pDown;//zejscie na rzad nizej
			}
		}
	}
	else//statek jest ustawiony wertykalnie
	{
		if (yPoczatkowe == 1)//jezeli statek jest ustawiony na dole planszy
		{
			while (pomocniczy->y != 1)//przejscie na dol planszy
				pomocniczy = pomocniczy->pDown;
			if (xPoczatkowe == 1)//jezeli statek jest ustawiony na poczatku osi X
			{
				while (pomocniczy->y != yKoncowe + 2)//sprawdzenie rzedow na ktorych jest statek oraz jednego nad statkiem
				{
					pomocniczy2 = pomocniczy->pHeadx;//wejscie na koordynaty X
					if (pomocniczy2->status != 0 || pomocniczy2->pNext->status != 0)//sprawdzenie pola statku oraz pola za statkiem
						return false;//jezeli pole nie jest puste statek nie moze byc postawiony
					pomocniczy = pomocniczy->pUp;//wejscie rzad wyzej
				}
			}
			else if (xKoncowe == 10)//jezeli statek jest ustawiony na koncu osi X
			{
				while (pomocniczy->y != yKoncowe + 1)//przejscie przez statek 
				{
					pomocniczy2 = pomocniczy->pHeadx;//przejscie na koordynaty X
					while (pomocniczy2->x != 9)//przejscie na pole poprzedzajace statek
						pomocniczy2 = pomocniczy2->pNext;
					if (pomocniczy2->status != 0 || pomocniczy2->pNext->status != 0)//sprawdzenie pola przed statkiem i pola statku
						return false;//jezeli pole nie jest puste statek nie moze byc postawiony
					pomocniczy = pomocniczy->pUp;//przejscie wyzej
				}
				pomocniczy2 = pomocniczy->pHeadx;//przejscie na koordynaty X w rzedzie nad statkiem
				while (pomocniczy2->x != 9)
					pomocniczy2 = pomocniczy2->pNext;
				if (pomocniczy2->status != 0 || pomocniczy2->pNext->status != 0)//sprawdzenie pola przed statkiem i pola statku
					return false;
			}
			else//jezeli statek jest w srodku planszy
			{
				while (pomocniczy->y != yKoncowe + 1)//przejscie przez statek
				{
					pomocniczy2 = pomocniczy->pHeadx;//wejscie na koordynaty X
					while (pomocniczy2->pNext->x != xPoczatkowe)//przejscie na pole poprzedzajace statek
						pomocniczy2 = pomocniczy2->pNext;
					if (pomocniczy2->status != 0 || pomocniczy2->pNext->status != 0 || pomocniczy2->pNext->pNext->status != 0)//sprawdzenie pola przed statkiem, pola statku oraz pola za statkiem
						return false;
					pomocniczy = pomocniczy->pUp;//przejscie wyzej
				}
				pomocniczy2 = pomocniczy->pHeadx;//przejscie na koordynaty X na wysokosci nad statkiem
				while (pomocniczy2->pNext->x != xPoczatkowe)
					pomocniczy2 = pomocniczy2->pNext;
				if (pomocniczy2->status != 0 || pomocniczy2->pNext->status != 0 || pomocniczy2->pNext->pNext->status != 0)//sprawdzenie pola przed statkiem,pola statku oraz pola za statkiem
					return false;
			}
		}
		else if (yKoncowe == 10)//jezeli statek jest u gory planszy
		{
			if (xPoczatkowe == 1)//jezeli statek jest na poczatku osi X
			{
				while (pomocniczy->y != yPoczatkowe - 2)//przejscie za statek
				{
					pomocniczy2 = pomocniczy->pHeadx;//przejscie na koordynaty X
					if (pomocniczy2->status != 0 || pomocniczy2->pNext->status != 0)//sprawdzenie pola statku oraz pola za statkiem
						return false;
					pomocniczy = pomocniczy->pDown;//przejscie nizej
				}
			}
			else if (xKoncowe == 10)//jezeli statek jest na koncu osi X
			{
				while (pomocniczy->y != yPoczatkowe - 2)//przejscie za statek
				{
					pomocniczy2 = pomocniczy->pHeadx;//przejscie na koordynaty X
					while (pomocniczy2->pNext->x != 10)
						pomocniczy2 = pomocniczy2->pNext;
					if (pomocniczy2->status != 0 || pomocniczy2->pNext->status != 0)//sprawdzenie pola statku oraz pola za statkiem
						return false;
					pomocniczy = pomocniczy->pDown;//zejscie nizej
				}
			}
			else//jezeli statek jest po srodku planszy
			{
				while (pomocniczy->y != yPoczatkowe - 2)//przejscie za statek
				{
					pomocniczy2 = pomocniczy->pHeadx;//wejscie na koordynaty X
					while (pomocniczy2->pNext->x != xPoczatkowe)//przejscie na pole poprzzedzajace statek
						pomocniczy2 = pomocniczy2->pNext;
					if (pomocniczy2->status != 0 || pomocniczy2->pNext->status != 0 || pomocniczy2->pNext->pNext->status != 0)//sprawdzenie pola przed statkiem, pola statku oraz pola za statkiem
						return false;
					pomocniczy = pomocniczy->pDown;//zejscie nizej
				}
			}
		}
		else//jezeli statek nie jest na krawedziach osi Y
		{
			while (pomocniczy->pDown->y != yKoncowe)//zejscie na wysokosc poprzedzajaca statek
				pomocniczy = pomocniczy->pDown;
			if (xPoczatkowe == 1)//jezeli statek jest na poczatku osi X
			{
				while (pomocniczy->y != yPoczatkowe - 1)//przejscie przez statek
				{
					pomocniczy2 = pomocniczy->pHeadx;
					if (pomocniczy2->status != 0 || pomocniczy2->pNext->status != 0)//sprawdzenie pola statku oraz pola za statkiem
						return false;
					pomocniczy = pomocniczy->pDown;//zejscie nizej
				}
				pomocniczy2 = pomocniczy->pHeadx;//wejscie na koordynaty X pod statkiem
				if (pomocniczy2->status != 0 || pomocniczy2->pNext->status != 0)//sprawdzenie pola statku oraz pola za statkiem
					return false;
			}
			else if (xKoncowe == 10)//jezeli statek jest na koncu osi X
			{
				while (pomocniczy->y != yPoczatkowe - 1)//zejscie na wysokosc poprzedzajaca statek
				{
					pomocniczy2 = pomocniczy->pHeadx;//wejscie na koordynaty X
					while (pomocniczy2->pNext->x != 10)//przejscie na pole poprzedzajaca statek
						pomocniczy2 = pomocniczy2->pNext;
					if (pomocniczy2->status != 0 || pomocniczy2->pNext->status != 0)///sprawdzenie pola statku oraz pola poprzedzajacego
						return false;
					pomocniczy = pomocniczy->pDown;//zejscie nizej
				}
				pomocniczy2 = pomocniczy->pHeadx;//wejscie na koordynaty X pod statkiem
				while (pomocniczy2->pNext->x != 10)//przejscie na pole poprzedzajace statek
					pomocniczy2 = pomocniczy2->pNext;
				if (pomocniczy2->status != 0 || pomocniczy2->pNext->status != 0)//sprawdzenie pola poprzedzjacego statek oraz pole statku
					return false;
			}
			else//jezeli statek jest po srodku planszy
			{
				while (pomocniczy->y != yPoczatkowe - 1)//przejscie na wysokosc poprzedzajaca statek
				{
					pomocniczy2 = pomocniczy->pHeadx;//wejscie na koordynaty X
					while (pomocniczy2->pNext->x != xPoczatkowe)//przejscie na pole poprzedzajace statek
						pomocniczy2 = pomocniczy2->pNext;
					if (pomocniczy2->status != 0 || pomocniczy2->pNext->status != 0 || pomocniczy2->pNext->pNext->status != 0)//sprawdzenie pola poprzedzajacego statek, pole statku oraz pola za statkiem
						return false;
					pomocniczy = pomocniczy->pDown;//zzejscie nizej
				}
				pomocniczy2 = pomocniczy->pHeadx;//wejscie na koordynaty X na wysokosci ponizej statku
				while (pomocniczy2->pNext->x != xPoczatkowe)//przejscie pole poprzedzajace statek
					pomocniczy2 = pomocniczy2->pNext;
				if (pomocniczy2->status != 0 || pomocniczy2->pNext->status != 0 || pomocniczy2->pNext->pNext->status != 0)//sprawdzenie pola poprzedzajacego statek, pole statku oraz pole za statkiem
					return false;
			}
		}
	}
	return true;//jezeli zadne pole nie zlamamlo zasad gry oznacza to ze statek moze zostac postawiony
}
void Standardowy_zestaw(struct Uzytkownik** uzytkownik_ref)//przypisanie odpowiedniej ilosci danego rodzaju statku oraz wyzerowanie punktow
{
	struct Uzytkownik* uzyt = *uzytkownik_ref;
	uzyt->ilosc_czworek = 1;
	uzyt->ilosc_trojek = 2;
	uzyt->ilosc_dwojek = 3;
	uzyt->ilosc_jedynek = 4;
	uzyt->punkty = 0;
}
void wyswietl_tablice(struct Wspolrzedne_y* tablica)
{
	struct Wspolrzedne_y* pomocnicza1 = tablica;
	while (pomocnicza1 != NULL)
	{
		if (pomocnicza1->y != 10)
		{
			printf(" %d ", pomocnicza1->y);//wyswietlanie koordynatow osi Y od 9 do 1
		}
		else
			printf("10 ");//wyswietlanie koordynatu 10
		struct Wspolrzedne_x* pomocnicza2 = pomocnicza1->pHeadx;
		while (pomocnicza2 != NULL)
		{

			if (pomocnicza2->status == 0)
				printf(" . ");//wyswietlanie pustego pola
			else if (pomocnicza2->status == 1)
			{
				printf(" O ");//wyswietlanie pola zajetego przez statek
			}
			else if (pomocnicza2->status == 2)
			{
				printf("\033[1;34m");//zmiana koloru na bold blue
				printf(" X ");//wyswietlenie pola trafionego
				printf("\033[0m");//powrot do bialego koloru
			}
			else if (pomocnicza2->status == 3)
			{
				printf("\033[1;31m");//zmiana koloru na bold red
				printf(" X ");//wyswietlenie pola zbitego
				printf("\033[0m");//powrot do koloru bialego
			}
			else if (pomocnicza2->status == 4)
			{
				printf(" X ");//wyswietlenie pudla
			}
			pomocnicza2 = pomocnicza2->pNext;
		}
		printf("\n");
		pomocnicza1 = pomocnicza1->pDown;
	}
	for (int i = 0;i < 11;i++)
		printf(" %d ", i);//wyswietlenie koordynatow osi X
	printf("\n\n");
}
void wyswietl_tablice_przeciwnika(struct Wspolrzedne_y* tablica)
{
	struct Wspolrzedne_y* pomocnicza1 = tablica;
	while (pomocnicza1 != NULL)
	{
		if (pomocnicza1->y != 10)
		{
			printf(" %d ", pomocnicza1->y);//wyswietlenie koordynatow osi Y od 9 do 1
		}
		else
			printf("10 ");//wyswietlenie koordynatu 10
		struct Wspolrzedne_x* pomocnicza2 = pomocnicza1->pHeadx;
		while (pomocnicza2 != NULL)
		{
			if (pomocnicza2->status == 0 || pomocnicza2->status == 1)
				printf(" . ");//wyswietlenie pola pustego oraz pola zajetego przez statek tak by przeciwnikow nie mogl ich rozroznic
			else if (pomocnicza2->status == 2)
			{
				printf("\033[1;34m");//zmiana koloru na bold blue
				printf(" X ");//wyswietlenie pola trafionego
				printf("\033[0m");//powrot do koloru bialego
			}
			else if (pomocnicza2->status == 3)
			{
				printf("\033[1;31m");//zmiana koloru na bold red
				printf(" X ");//wyswietielnie pola zbitego
				printf("\033[0m");//powrot do koloru bialego
			}
			else if (pomocnicza2->status == 4)
			{
				printf(" X ");//wyswwietlenie pudla
			}
			pomocnicza2 = pomocnicza2->pNext;
		}
		printf("\n");
		pomocnicza1 = pomocnicza1->pDown;
	}
	for (int i = 0;i < 11;i++)
		printf(" %d ", i);//wyswietlenie koordynatow osi X
	printf("\n\n");
}
void nowy_X(struct Wspolrzedne_x** pHead_ref, int X)
{
	struct Wspolrzedne_x* nowy = (struct Wspolrzedne_x*)malloc(sizeof(struct Wspolrzedne_x));
	nowy->x = X;//przypisanie wartosci koordynatu X nowemu wezlowi
	nowy->status = 0;//ustawienie podstawowego statusu
	nowy->pNext = nowy->pPrev = NULL;//wyzerowanie NULL na wskaznikach pobocznych
	if (!(*pHead_ref))//jezeli nie ma glowy
		*pHead_ref = nowy;//nowy staje sie glowa
	else//jezeli jest glowa
	{
		struct Wspolrzedne_x* pomocniczy = *pHead_ref;
		while (pomocniczy->pNext != NULL)//przejdzie na koniec listy
			pomocniczy = pomocniczy->pNext;
		pomocniczy->pNext = nowy;//polaczenie ostatniego elementu listy z nowym
		nowy->pPrev = pomocniczy;//polaczenie nowego z ostatnim elementem listy
	}
}
void nowy_Y(struct Wspolrzedne_y** pHead_ref, int Y)
{
	struct Wspolrzedne_y* nowy = (struct Wspolrzedne_y*)malloc(sizeof(struct Wspolrzedne_y));
	nowy->y = Y;//przypisanie wartosci koordynatu Y nowemu wezlowi
	nowy->pDown = nowy->pUp = NULL;//ustawienie NULL na wskaznikach pobocznych
	nowy->pHeadx = NULL;//ustawienie NULL na glowe listy koordynatow X
	if (!(*pHead_ref))//jezzeli nie ma glowy
	{
		*pHead_ref = nowy;//nowy staje sie glowa
	}
	else
	{
		struct Wspolrzedne_y* pomocniczy = *pHead_ref;//przechowujemy stara glowe
		*pHead_ref = nowy;//nowy staje sie glowa
		nowy->pDown = pomocniczy;//polaczenie nowego ze stara glowa
		pomocniczy->pUp = nowy;//polaczenie starej glowy z nowym
	}
	for (int i = 0;i < 10;i++)
	{
		nowy_X(&nowy->pHeadx, i + 1);//wylowanie funkcji nowy_X by stworzyc os X
	}
}
bool walidacja_koordynatow(int x, int y)
{
	if (x > 0 && x < 11 && y>0 && y < 11)//sprawdzenie czy koordynaty sa od 1 do 10
		return true;
	else
		return false;
}
void statek_na_plansze(struct Wspolrzedne_y** pHead_ref, int Ypoczatkowe, int Xpoczatkowe, int Ykoncowe, int Xkoncowe)
{
	if (Ypoczatkowe < Ykoncowe)//ustawienie koordynatow tak, by Ypoczatkowe zawsze bylo wieksze od Ykoncowe
	{
		int tmp = Ypoczatkowe;
		Ypoczatkowe = Ykoncowe;
		Ykoncowe = tmp;
	}
	if (Xpoczatkowe > Xkoncowe)//ustawienie koordynatow tak, by Xkoncowe zawsze bylo wieksze od Xpoczatkowe
	{
		int tmp = Xkoncowe;
		Xkoncowe = Xpoczatkowe;
		Xpoczatkowe = tmp;
	}
	struct Wspolrzedne_y* pomocniczy = *pHead_ref;
	struct Wspolrzedne_x* pomocniczy2;
	if (Ypoczatkowe == Ykoncowe)//jezeli statek ma byc ustawiony horyzontalnie
	{
		while (pomocniczy->y != Ypoczatkowe)//przejscie na wysokosc statku
			pomocniczy = pomocniczy->pDown;
		pomocniczy2 = pomocniczy->pHeadx;//wejscie na koordynaty X
		if (Xpoczatkowe != Xkoncowe)//jezeli statek nie jest rodzaju 1
		{
			while (pomocniczy2->x != Xpoczatkowe)//przejsice na poczatek statku
				pomocniczy2 = pomocniczy2->pNext;
			while (pomocniczy2->x != Xkoncowe && pomocniczy2->pNext != NULL)//przejscie do przedostatniego koordynatu statku
			{
				pomocniczy2->status = 1;//zmiana statusu pola na status pola zajetego przez statek
				pomocniczy2->ustawienie = false;//ustawienie horyzontalne
				pomocniczy2 = pomocniczy2->pNext;
			}
			pomocniczy2->status = 1;//zmiana statusu pola na status pola zajetego przez statek
			pomocniczy2->ustawienie = false;//zmiana statusu pola na status pola zajetego przez statek
		}
		else
		{
			pomocniczy2 = pomocniczy->pHeadx;//przejscie na koordynaty X ostatniego pola statku
			while (pomocniczy2->x != Xpoczatkowe)//przejscie na koordynat statku
				pomocniczy2 = pomocniczy2->pNext;
			pomocniczy2->status = 1;//zmiana statusu pola na status pola zajetego przez statek
			pomocniczy2->ustawienie = false;//ustawienie horyzontalne
		}
	}
	else//ustawienie wertykalne
	{
		while (pomocniczy->y != Ypoczatkowe)//przejscie na poczatkowa wysokosc statku
			pomocniczy = pomocniczy->pDown;
		while (pomocniczy->y != Ykoncowe)//przejscie przez statek
		{
			pomocniczy2 = pomocniczy->pHeadx;//wejscie na koordynaty X
			while (pomocniczy2->x != Xkoncowe && pomocniczy2->pNext != NULL)
				pomocniczy2 = pomocniczy2->pNext;
			pomocniczy2->status = 1;//zmiana statusu pola na status pola zajetego przez statek
			pomocniczy2->ustawienie = true;//ustawienie wertykalne
			pomocniczy = pomocniczy->pDown;
		}
		pomocniczy2 = pomocniczy->pHeadx;//wejscie na koordynaty X ostatniego pola statku
		while (pomocniczy2->x != Xkoncowe && pomocniczy2->pNext != NULL)
			pomocniczy2 = pomocniczy2->pNext;
		pomocniczy2->status = 1;//zmiana statusu pola na status pola zajetego przez statek
		pomocniczy2->ustawienie = true;//ustawienie wertykalne
	}
}
bool walidacja_ilosci(struct Uzytkownik* uzytkownik, int rodzaj)
{
	//jezeli uzytkownik wykorzystal juz wszystkie dostepne statki tego rodzaju zwraca false, inaczej true
	if (rodzaj == 1)
	{
		if (uzytkownik->ilosc_jedynek == 0)
			return false;
		else
		{
			return true;
		}
	}
	else if (rodzaj == 2)
	{
		if (uzytkownik->ilosc_dwojek == 0)
			return false;
		else
		{
			return true;
		}
	}
	else if (rodzaj == 3)
	{
		if (uzytkownik->ilosc_trojek == 0)
			return false;
		else
		{
			return true;
		}
	}
	else
	{
		if (uzytkownik->ilosc_czworek == 0)
			return false;
		else
		{
			return true;
		}
	}
}
bool walidacja_rodzaju(char rodzaj, struct Uzytkownik* uzytkownik)
{
	if (rodzaj == '1' || rodzaj == '2' || rodzaj == '3' || rodzaj == '4')//sprawdzenie czy rodzaj istnieje
	{
		bool ilosc = walidacja_ilosci(uzytkownik, rodzaj-48);
		if (ilosc == true)//sprawdzenie czy uzytkownik ma jeszcze takie statki
		{
			return true;
		}
		else//jezeli nie sa dostepne
		{
			printf("Przekroczono maksymalna ilosc statkow tego rodzaju.\n");
			Sleep(3000);
			return false;
		}
	}
	else//jezeli zly rodzaj
	{
		printf("Statki maja rodzaj od 1 do 4!\n");
		Sleep(3000);
		return false;
	}
}
void ustaw_statek(struct Uzytkownik** uzytkownik_ref, char* nazwa)
{
	struct Uzytkownik* uzytkownik = *uzytkownik_ref;
	struct Wspolrzedne_y* pHead = uzytkownik->Tablica;
	printf("Podaj rodzaj statku: ");
	char rodzaj_c;
	scanf(" %c", &rodzaj_c);
	bool rodzaj_w = walidacja_rodzaju(rodzaj_c, uzytkownik);//sprawdzenie poprawnosci rodzaju
	if (rodzaj_w == true)
	{
		printf("Podaj poczatkowe koordynaty statku(x y): ");
		char yp_c, xp_c;
		int yp, xp;
		scanf(" %c %c", &xp_c, &yp_c);
		xp = xp_c - 48;
		yp = yp_c - 48;
		bool koordy_poczatkowe = walidacja_koordynatow(xp, yp);//sprawdzenie czy koordynaty sa poprawne
		if (koordy_poczatkowe == true)
		{
			int rodzaj = rodzaj_c-48;
			int yk, xk;
			char kierunek;
			if (rodzaj != 1)//jezeli rodzaj nie jest rowny 1 to statek bedzie mial rozne koordynaty
			{
				printf("Podaj kierunek ustawienia statku(<, >, v, ^): ");
				scanf(" %c", &kierunek);//ustalenie kierunku statku
				if ((int)kierunek == 60)//kierunek w lewo
				{
					xk = xp - rodzaj + 1;//ustawienie odpowiednich koordynatow X
					yk = yp;
				}
				else if ((int)kierunek == 62)//kierunek w prawo
				{
					xk = xp + rodzaj - 1;//ustawienie odpowiednich koordynatow X
					yk = yp;
				}
				else if ((int)kierunek == 118 || (int)kierunek == 86)//kierunek w dol
				{
					xk = xp;
					yk = yp - rodzaj + 1;//ustaiwnie odpowiednich koordynatow Y
				}
				else if ((int)kierunek == 94)//kierunek w gore
				{
					xk = xp;
					yk = yp + rodzaj - 1;//ustawienie odpowiednich koordynatow Y
				}
				else//niepoprawny kierunek
				{
					printf("Niepoprawny kierunek!\n");
					Sleep(2500);
					return;
				}
			}
			else//jezeli rodzaj jest rowny 1 koordynaty sa takie same 
			{
				xk = xp;
				yk = yp;
			}
			bool koordy_koncowe = walidacja_koordynatow(yk, xk);//sprawdzenie czy koordynaty koncowe spelniaja zasady gry
			if (koordy_koncowe == true)//jezeli tak
			{
				bool statek = walidacja_statku(&pHead, yp, xp, yk, xk);//sprawdzenie czy statek spelnia zasady gry
				if (statek == true)//jezeli tak
				{
					statek_na_plansze(&pHead, yp, xp, yk, xk);//statek zostaje ustawiony na plansze i zmniejszana jest ilosc dostepnych statkow danego rodzaju o 1
					if (rodzaj == 1)
					{
						uzytkownik->ilosc_jedynek = uzytkownik->ilosc_jedynek - 1;
					}
					else if (rodzaj == 2)
					{
						uzytkownik->ilosc_dwojek = uzytkownik->ilosc_dwojek - 1;
					}
					else if (rodzaj == 3)
					{
						uzytkownik->ilosc_trojek = uzytkownik->ilosc_trojek - 1;
					}
					else
					{
						uzytkownik->ilosc_czworek = uzytkownik->ilosc_czworek - 1;
					}
					zapisz_ustawienie_do_pliku(xp, yp, xk, yk, nazwa);//zapis ustawienia statku do pliku
				}
				else//jezeli statek nie spelnia zasad gry
				{
					printf("Nie udalo sie ustawic statku, zastanow sie nad swoim ruchem.\n");
					Sleep(2500);
				}
			}
			else//niepoprawne koordynaty
			{
				printf("Koordynaty musza byc z zakresu od 1 do 10.\n");
				Sleep(2500);
			}
		}
		else//niepoprawne koordynaty
		{
			printf("Koordynaty musza byc z zakresu od 1 do 10.\n");
			Sleep(2500);
		}
	}
}
bool walidacja_zbicia(struct Wspolrzedne_y* pHead, struct Wspolrzedne_x* pHeadx)
{
	if (pHeadx->ustawienie == false)//jezeli statek jest ustawiony horyzontalnie
	{
		if (pHeadx->x == 1)//jezeli statek jest na poczatku osi X
		{
			while (pHeadx->status != 0 && pHeadx->status != 3 && pHeadx->status != 4)//dopoki nie trafiono na pole ktore oznaczaja koniec statku
			{
				if (pHeadx->status == 1)//jezeli istnieje jeszcze statek
					return false;
				pHeadx = pHeadx->pNext;//przejscie w prawo
			}
			return true;//zatwierdz zbicie
		}
		else if (pHeadx->x == 10)//jezeli statek jest na koncu osi X
		{
			while (pHeadx->status != 0 && pHeadx->status != 3 && pHeadx->status != 4)//dopoki nie trafiono na pole ktore oznaczaja koniec statku
			{
				if (pHeadx->status == 1)//jezeli istnieje jeszcze statek
					return false;
				pHeadx = pHeadx->pPrev;//przejscie w lewo
			}
			return true;//zatwierdz zbicie
		}
		else
		{
			struct Wspolrzedne_x* wlasciwy = pHeadx;
			while (pHeadx->status != 0 && pHeadx->status != 3 && pHeadx->status != 4)//dopoki nie trafiono na pole ktore oznacza koniec statku
			{
				if (pHeadx == NULL)//jezeli przekroczono granice planszy
					break;
				if (pHeadx->status == 1)//jezeli istneieje statek
					return false;
				pHeadx = pHeadx->pNext;//przejscie w prawo
				if (pHeadx == NULL)//jezeli przekroczono granice planszy
					break;
			}
			pHeadx = wlasciwy;//powrot do punktu wyjscia
			while (pHeadx->status != 0 && pHeadx->status != 3 && pHeadx->status != 4)
			{
				if (pHeadx == NULL)//jezeli przekroczono granice planszy
					break;
				if (pHeadx->status == 1)//jezeli istnieje statek
					return false;
				pHeadx = pHeadx->pPrev;//przejscie e lewo
				if (pHeadx == NULL)//jezeli przekroczono granice planszy
					break;
			}
			return true;//zatwierdz zbicie
		}
	}
	else//ustawienie wertykalne
	{
		struct Wspolrzedne_y* wlasciwy = pHead;
		int polozenie = pHeadx->x;
		if (pHead->y == 1)//jezeli statek jest na dole planszy
		{
			for (int i = 0;i < 4;i++)//statek ma maksymalnie wielkosc 4, stad 4 przejscia
			{
				pHeadx = pHead->pHeadx;//wejscie na koordynaty X
				while (pHeadx->x != polozenie)//przejscie do miejsca statku
					pHeadx = pHeadx->pNext;
				if (pHeadx->status == 0 || pHeadx->status == 3 || pHeadx->status == 4)//jezeli trafiono na pole ktore oznacza koniec statku
					break;
				if (pHeadx->status == 1)//jezeli istnieje statek
					return false;
				pHead = pHead->pUp;//przejscie wyzej
			}
			return true;//zatwierdz zbicie
		}
		else if (pHead->y == 10)//jezeli statek jest na gorze planszy
		{

			for (int i = 0;i < 4;i++)//statek ma maksymalnie wielkosc 4 stad 4 przejscia
			{
				pHeadx = pHead->pHeadx;//przejsice na koordynaty X
				while (pHeadx->x != polozenie)//przejscie do miejsca statku
					pHeadx = pHeadx->pNext;
				if (pHeadx->status == 0 || pHeadx->status == 3 || pHeadx->status == 4)//jezeli trafiono na pole, ktore oznacza koniec statku
					break;
				if (pHeadx->status == 1)//jezeli istnieje statek
					return false;
				pHead = pHead->pDown;//przejscie nizej
			}
			return true;//zatwierdz zbicie
		}
		else
		{
			for (int i = 0;i < 4;i++)//statek ma maksymalnie wielkosc 4, stad 4 przejscia
			{
				if (pHead == NULL)//jezeli przekroczono granice planszy
					break;
				pHeadx = pHead->pHeadx;//wejscie na koordynaty X
				while (pHeadx->x != polozenie)//przejscie na miejsce statku
					pHeadx = pHeadx->pNext;
				if (pHeadx->status == 0 || pHeadx->status == 3 || pHeadx->status == 4)//jezeli trafiono na pole, ktore oznacza koniec statku
					break;
				if (pHeadx->status == 1)//jezeli istnieje statek
					return false;
				pHead = pHead->pDown;//przejscie nizej
				if (pHead == NULL)//jezeli przekroczono granice planszy
					break;
			}
			pHead = wlasciwy;//powrot do punktu wyjscia
			for (int i = 0;i < 4;i++)//statek ma maksymalnie wielkosc 4, stad 4 przejscia
			{
				if (pHead == NULL)//jezeli przekroczono granice planszy
					break;
				pHead = pHead->pUp;//przejscie wyzej
				if (pHead == NULL)//jezeli przekroczono granice planszy
					break;
				pHeadx = pHead->pHeadx;//przejscie na koordynaty X
				while (pHeadx->x != polozenie)//przejscie na miejsce statku
					pHeadx = pHeadx->pNext;
				if (pHeadx->status == 0 || pHeadx->status == 3 || pHeadx->status == 4)//jezeli trafiono na pole ktore oznacza koniec statku
					break;
				if (pHeadx->status == 1)//jezeli istnieje statek
					return false;

			}
			return true;//zatwierdz zbicie
		}
	}
}
void zbij(struct Wspolrzedne_y** pHead_ref, struct Wspolrzedne_x** pHeadx_ref)
{
	struct Wspolrzedne_y* pomocniczy = *pHead_ref;
	struct Wspolrzedne_x* pomocniczy2 = *pHeadx_ref;
	int polozenie = pomocniczy2->x;
	int koniec, poczatek;
	if (pomocniczy2->ustawienie == false)//jezeli statek jest ustawiony horyzontalnie
	{
		if (pomocniczy->y == 1 || pomocniczy->y == 10)//jezeli statek jest na skrajnych wartosciach koordynatow Y
		{
			if (polozenie == 1)//jezeli statek jest na poczatku osi X
			{
				while (pomocniczy2->status == 2 || pomocniczy2->status == 3)//dopoki pola maja odpowiedni status
				{
					pomocniczy2->status = 3;//zmien na zbite
					pomocniczy2 = pomocniczy2->pNext;//przejdz w prawo
					if (pomocniczy2->status == 3)//jezeli juz jest zbite
						break;
				}
				pomocniczy2->status = 3;//zmien na zbite
				koniec = pomocniczy2->x;//zapamietaj koncowy koordynat X
				if (pomocniczy->y == 1)//jezeli statek znajdowal sie na dole planszy przejdz w gore
					pomocniczy = pomocniczy->pUp;
				else if (pomocniczy->y == 10)//jezeli statek znajdowal sie na gorze planszy przejdz w dol
					pomocniczy = pomocniczy->pDown;
				pomocniczy2 = pomocniczy->pHeadx;//wejdz na koordynaty X
				while (pomocniczy2->x != koniec)//przejdzie na koniec statku
				{
					pomocniczy2->status = 3;//ustawienie statusu na zbity
					pomocniczy2 = pomocniczy2->pNext;
				}
				pomocniczy2->status = 3;//ustawienie statusu ostatniego pola na zbity
			}
			else if (polozenie == 10)//jezeli statek znajduje sie na koncu osi X
			{
				pomocniczy2 = pomocniczy->pHeadx;//przejscie na koordynaty X
				while (pomocniczy2->x != 10)//przejscie na koniec osi X
				{
					pomocniczy2 = pomocniczy2->pNext;
				}
				while (pomocniczy2->status == 2 || pomocniczy2->status == 3)//dopoki pola maja odpowiedni status
				{
					pomocniczy2->status = 3;//zmiana statusu na zbity
					pomocniczy2 = pomocniczy2->pPrev;//przejscie w lewo
					if (pomocniczy2->status == 3)//jezeli juz jest zbite
						break;
				}
				pomocniczy2->status = 3;//zmiana statusu na 3
				koniec = pomocniczy2->x;//zapamietanie koncowego koordynatu
				if (pomocniczy->y == 1)//jezeli statek jest na dole planszy pojdz w gore
					pomocniczy = pomocniczy->pUp;
				else if (pomocniczy->y == 10)//jezeli statek jest na gorze planszy pojdz w dol
					pomocniczy = pomocniczy->pDown;
				pomocniczy2 = pomocniczy->pHeadx;//przejscie na koordynaty X
				while (pomocniczy2->x != koniec)//przejscie do zapamietego koordynatu
					pomocniczy2 = pomocniczy2->pNext;
				while (pomocniczy2->x != 10)//dopoki nie dojdzie do ostatniego pola
				{
					pomocniczy2->status = 3;//zmien status na zbity
					pomocniczy2 = pomocniczy2->pNext;
				}
				pomocniczy2->status = 3;//zmien status ostatniego pola na zbity
			}
			else//jezeli statek jest w srodku planszy
			{
				struct Wspolrzedne_x* wlasciwy = pomocniczy2;//zapamietanie punktu wyjscia
				while (pomocniczy2->status == 2 || pomocniczy2->status == 3)//dopki pola maja odpowiednia wartosc
				{
					pomocniczy2->status = 3;//zmiana statusu na zbity
					if (pomocniczy2->pNext == NULL)//jezeli koniec planszy
						break;
					pomocniczy2 = pomocniczy2->pNext;//przejscie w prawo
					if (pomocniczy2->status == 3)//jezeli juz zbito
						break;
				}
				pomocniczy2->status = 3;//zmiana statusu na zbity
				koniec = pomocniczy2->x;//zapamietanie koncowego koordynatu
				pomocniczy2 = wlasciwy;//powrot do punktu wyjscia
				while (pomocniczy2->status == 2 || pomocniczy2->status == 3)//dopoki pola maja odpowiednia wartosc
				{
					pomocniczy2->status = 3;//zmiana statusu na zbity
					if (pomocniczy2->pPrev == NULL)//jezeli koniec planszy
						break;
					pomocniczy2 = pomocniczy2->pPrev;//przejscie w lewo
					if (pomocniczy2->status == 3)//jezeli juz zbito
						break;
				}
				pomocniczy2->status = 3;//zmiana statusu na zbity
				poczatek = pomocniczy2->x;//zapamietanie poczatkowego koordynatu
				if (pomocniczy->y == 1)//jezeli statek znajdowaol sie na dole planszy pojdz w gore
					pomocniczy = pomocniczy->pUp;
				else if (pomocniczy->y == 10)//jezeli statek znajdowal na gorze planszy pojdz w dol
					pomocniczy = pomocniczy->pDown;
				pomocniczy2 = pomocniczy->pHeadx;//przejdzie na koordynaty X
				while (pomocniczy2->x != poczatek)//przejdzie na poczatkowe pole
					pomocniczy2 = pomocniczy2->pNext;
				while (pomocniczy2->x != koniec)//przejdzie do koncowego pola
				{
					pomocniczy2->status = 3;//zmiana statusu na zbity
					pomocniczy2 = pomocniczy2->pNext;
				}
				pomocniczy2->status = 3;//zmiana statusu ostatniego pola na zbity
			}
		}
		else//jezeli statek jest na srodkowych wysokosciach
		{
			if (polozenie == 1)//jezeli statek jest na poczatku osi X
			{
				while (pomocniczy2->status == 2 || pomocniczy2->status == 3)//dopoki pola maja odpowiedni status
				{
					pomocniczy2->status = 3;//zmiana statusu na zbity
					pomocniczy2 = pomocniczy2->pNext;//przejscie w prawo
					if (pomocniczy2->status == 3)//jezeli juz zbito
						break;
				}
				pomocniczy2->status = 3;//zmien status na zbity
				koniec = pomocniczy2->x;//zapamietaj koncowy koordynat 
				for (int i = 0;i < 2;i++)//2 przejscia poniewaz zbijane beda pola pod i nad statkiem
				{
					if (i == 0)
						pomocniczy = pomocniczy->pDown;//najpierw przejdz w dol
					else
						pomocniczy = pomocniczy->pUp->pUp;//potem w gore
					pomocniczy2 = pomocniczy->pHeadx;//przejdzie na koordynaty X
					while (pomocniczy2->x != koniec)//przejscie przez wszystkie koordynaty
					{
						pomocniczy2->status = 3;//zmiana statusu na zbity
						pomocniczy2 = pomocniczy2->pNext;//przejdzie w prawo
					}
					pomocniczy2->status = 3;//zmiana statusu na zbity
				}
			}
			else if (polozenie == 10)//jezeli statek jest na koncu osi X
			{
				pomocniczy2 = pomocniczy->pHeadx;//wejscie na koordynaty X
				while (pomocniczy2->x != 10)//przejscie do konca osi X
				{
					pomocniczy2 = pomocniczy2->pNext;
				}
				while (pomocniczy2->status == 2 || pomocniczy2->status == 3)//dopki pola maja opdowiedni status
				{
					pomocniczy2->status = 3;//zmiana statusu na zbity
					pomocniczy2 = pomocniczy2->pPrev;//przejdzie w lewo
					if (pomocniczy2->status == 3)//jezeli juz zbito 
						break;
				}
				pomocniczy2->status = 3;//zmiana statusu na zbity
				koniec = pomocniczy2->x;//zapamietanie koncowego koordynatu
				for (int i = 0;i < 2;i++)//2 przejscia poniewaz zbijane beda pola pod i nad statkiem
				{
					if (i == 0)
						pomocniczy = pomocniczy->pDown;//na poczatku przejdz w dol
					else
						pomocniczy = pomocniczy->pUp->pUp;//potem przejdz w gore
					pomocniczy2 = pomocniczy->pHeadx;//przejscie na koordynaty X
					while (pomocniczy2->x != 10)//przejscie na koniec osi X
					{
						pomocniczy2 = pomocniczy2->pNext;
					}
					while (pomocniczy2->x != koniec)//przejdzie przez wszystkie wymagane koordynaty
					{
						pomocniczy2->status = 3;//zmiana statusu na zbity
						pomocniczy2 = pomocniczy2->pPrev;//przejdzie w lewo
					}
					pomocniczy2->status = 3;//zmiana statusu na zbity
				}
			}
			else//jezeli statek jest na srodku planszy
			{
				struct Wspolrzedne_x* wlasciwy = pomocniczy2;//powrot do punktu wyjscia
				while (pomocniczy2->status == 2 || pomocniczy2->status == 3)//dopoki pola maja odpowiedni status
				{
					pomocniczy2->status = 3;//zmiana statusu na zbity
					if (pomocniczy2->pNext == NULL)//jezeli koniec planszy
						break;
					pomocniczy2 = pomocniczy2->pNext;//przejscie w prawo
					if (pomocniczy2->status == 3)//jezeli juz zbity
						break;
				}
				pomocniczy2->status = 3;//zmiana statusu na zbity
				koniec = pomocniczy2->x;//zapamietanie koncowego koordynatu
				pomocniczy2 = wlasciwy;//powrot do punktu wyjscia
				while (pomocniczy2->status == 2 || pomocniczy2->status == 3)//dopoki pola maja odpowiedni status
				{
					pomocniczy2->status = 3;//zmiana statusu na zbity
					if (pomocniczy2->pPrev == NULL)//jezeli koniec planszy
						break;
					pomocniczy2 = pomocniczy2->pPrev;//przejdzie w lewo
					if (pomocniczy2->status == 3)//jezeli juz zbito
						break;
				}
				pomocniczy2->status = 3;//zmiana statusu na zbity
				poczatek = pomocniczy2->x;//zapamietanie poczatkowego koordynatu
				for (int i = 0;i < 2;i++)//2 przejscia poniewaz zbijane beda pola pod i nad statkiem
				{
					if (i == 0)
						pomocniczy = pomocniczy->pDown;//najpierw przejdz w dol
					else
						pomocniczy = pomocniczy->pUp->pUp;//potem w gore
					pomocniczy2 = pomocniczy->pHeadx;//przejdzie na koordynaty X
					while (pomocniczy2->x != poczatek)//przejdz do poczatku
						pomocniczy2 = pomocniczy2->pNext;
					while (pomocniczy2->x != koniec)//dopoki nie dojedzie do konca
					{
						pomocniczy2->status = 3;//zmien status na zbity
						pomocniczy2 = pomocniczy2->pNext;//przejdz w prawo
					}
					pomocniczy2->status = 3;//zmien status na zbity
				}
			}
		}
	}
	else//ustawienie wertykalne
	{
		if (pomocniczy->y == 1)//jezeli statek byl na dole listy
		{
			if (polozenie == 1)//jezeli statek byl ma poczatku osi X
			{
				for (int i = 0;i < 5;i++)//jako ze statek moze miec maksymalnie rozmiar 4 i potrzebne jest przejdzie powyzej statku to petla wykonuje sie 5 razy
				{
					pomocniczy2 = pomocniczy->pHeadx;//wejscie na koordynaty X
					if (pomocniczy2->status == 0 || pomocniczy2->status == 3 || pomocniczy2->status == 4)//jezeli koniec statku przestan
						break;
					pomocniczy2->status = 3;//zmien status na zbity
					pomocniczy2->pNext->status = 3;//zmien status pola za statkiem na zbity
					pomocniczy = pomocniczy->pUp;//wejdz wyzej
				}
				pomocniczy2->status = 3;//zmien status pola powyzej statku na zbity
				pomocniczy2->pNext->status = 3;//zmien status pola osob na zbity
			}
			else if (polozenie == 10)//jezeli statek znajduje sie na koncu osi X
			{
				for (int i = 0;i < 5;i++)//jako ze statek moze miec maksymalnie rozmiar 4 i potrzebne jest przejdzie powyzej statku to petla wykonuje sie 5 razy
				{
					pomocniczy2 = pomocniczy->pHeadx;//wejscie na koordynaty X
					while (pomocniczy2->x != 10)//przejscie na koniec osi X
						pomocniczy2 = pomocniczy2->pNext;
					if (pomocniczy2->status == 0 || pomocniczy2->status == 3 || pomocniczy2->status == 4)//jezeli koniec statku przestan
						break;
					pomocniczy2->status = 3;//zmien status pola na zbity
					pomocniczy2->pPrev->status = 3;//zmien status pola poprzedzajacego statek na zbity
					pomocniczy = pomocniczy->pUp;//wejdz wyzej
				}
				pomocniczy2->status = 3;//zmien status pola na zbity
				pomocniczy2->pPrev->status = 3;//zmien status pola poprzedzajacego statek na zbity
			}
			else//jezeli statek jest po srodku planszy
			{
				for (int i = 0;i < 5;i++)//jako ze statek moze miec maksymalnie rozmiar 4 i potrzebne jest przejdzie powyzej statku to petla wykonuje sie 5 razy
				{
					pomocniczy2 = pomocniczy->pHeadx;//wejdzie na koordynaty X
					while (pomocniczy2->x != polozenie)
						pomocniczy2 = pomocniczy2->pNext;//przejscie na pole gdzie znajdowal sie statek
					if (pomocniczy2->status == 0 || pomocniczy2->status == 3 || pomocniczy2->status == 4)//jezeli koniec statku przestan
						break;
					pomocniczy2->status = 3;//zmien status statku na zbity
					pomocniczy2->pPrev->status = 3;//zmien status pola poprzedzajacego statek na zbity
					pomocniczy2->pNext->status = 3;//zmien status pola za statkiem na zbity
					pomocniczy = pomocniczy->pUp;//wejdz wyzej
				}
				pomocniczy2->status = 3;//zmien status pola nad statkiem na zbity
				pomocniczy2->pPrev->status = 3;//zmien status pola poprzedzajacego na zbity
				pomocniczy2->pNext->status = 3;//zmien status pola za na zbity
			}
		}
		else if (pomocniczy->y == 10)//jezeli statek znajduje sie na gorze planszy
		{
			if (polozenie == 1)///jezeli statek jest na poczatku osi X
			{
				for (int i = 0;i < 5;i++)//jako ze statek moze miec maksymalnie rozmiar 4 i potrzebne jest przejdzie ponizej statku to petla wykonuje sie 5 razy
				{
					pomocniczy2 = pomocniczy->pHeadx;//wejscie na koordynaty X
					if (pomocniczy2->status == 0 || pomocniczy2->status == 3 || pomocniczy2->status == 4)//jezeli koniec statku przestan
						break;
					pomocniczy2->status = 3;//zmien status na zbity
					pomocniczy2->pNext->status = 3;//zmien status pola za statkiem na zbity
					pomocniczy = pomocniczy->pDown;//zejdz nizej
				}
				pomocniczy2->status = 3;//zmien status pola pod statkiem na zbity
				pomocniczy2->pNext->status = 3;//zmien status pola za na zbiity
			}
			else if (polozenie == 10)//jezeli statek byl na koncu osi X
			{
				for (int i = 0;i < 5;i++)//jako ze statek moze miec maksymalnie rozmiar 4 i potrzebne jest przejdzie ponizej statku to petla wykonuje sie 5 razy
				{
					pomocniczy2 = pomocniczy->pHeadx;//wejscie na koordynaty X
					while (pomocniczy2->x != 10)//przejdz na koniec osi X
						pomocniczy2 = pomocniczy2->pNext;
					if (pomocniczy2->status == 0 || pomocniczy2->status == 3 || pomocniczy2->status == 4)//jezeli koniec statku przestan
						break;
					pomocniczy2->status = 3;//zmien status pola na zbity
					pomocniczy2->pPrev->status = 3;//zmien status pola poprzedzajacego statek na zbity
					pomocniczy = pomocniczy->pDown;//zejdz nizej
				}
				pomocniczy2->status = 3;//zmien status pola pod statkiem na zbity
				pomocniczy2->pPrev->status = 3;//zmien status pola poprzedzjacego na zbity
			}
			else//jezeli statek jest po srodku planszy
			{
				for (int i = 0;i < 5;i++)//jako ze statek moze miec maksymalnie rozmiar 4 i potrzebne jest przejdzie ponizej statku to petla wykonuje sie 5 razy
				{
					pomocniczy2 = pomocniczy->pHeadx;//wejscie na koordynaty X
					while (pomocniczy2->x != polozenie)//przejscie do koordynatow statku
						pomocniczy2 = pomocniczy2->pNext;
					if (pomocniczy2->status == 0 || pomocniczy2->status == 3 || pomocniczy2->status == 4)//jezeli koniec statku przestan
						break;
					pomocniczy2->status = 3;//zmien status na zbity
					pomocniczy2->pPrev->status = 3;//zmien status pola poprzedzajacego na zbity
					pomocniczy2->pNext->status = 3;//zmien status pola za statkiem na zbity
					pomocniczy = pomocniczy->pDown;//zejdz nizej
				}
				pomocniczy2->status = 3;//zmien status pola na zbity
				pomocniczy2->pPrev->status = 3;//zmien status pola poprzedzjacego na zbity
				pomocniczy2->pNext->status = 3;//zmien status pola za na zbity
			}
		}
		else//jezeli statek nie znajduje sie na krawedzi osi Y
		{
			int y = pomocniczy->y;//zapamietatnie punktu wyjscia na osi Y
			if (polozenie != 10 && polozenie != 1)//jezeli statek jest po srodku planszy
			{
				for (int i = 0;i < 5;i++)//jako ze statek moze miec maksymalnie rozmiar 4 i potrzebne jest przejdzie powyzej statku to petla wykonuje sie 5 razy
				{
					pomocniczy2 = pomocniczy->pHeadx;//wejscie na koordynaty X
					while (pomocniczy2->x != polozenie)//przejscie na miejsce statku
						pomocniczy2 = pomocniczy2->pNext;
					if (pomocniczy2->status == 0 || pomocniczy2->status == 4 || pomocniczy2->status == 3)//jezeli koniec statku przestan
						break;
					pomocniczy2->status = 3;//zmiana statusu na zbity
					pomocniczy2->pPrev->status = 3;//zmiana statusu pola poprzedzajacego na zbity
					pomocniczy2->pNext->status = 3;//zmiana statusu pola za statkiem na zbity
					if (pomocniczy->pUp == NULL)//jezeli koniec planszy
						break;
					pomocniczy = pomocniczy->pUp;//pojdz w gore
				}
				if (pomocniczy != NULL)//jezeli nie wykroczono za granice planszy
				{
					while (pomocniczy2->x != polozenie)//przejscie do polozenia statku
						pomocniczy2 = pomocniczy2->pNext;
					pomocniczy2->status = 3;//zmiana statusu na zbity
					pomocniczy2->pPrev->status = 3;//zmiana statusu pola poprzedzajacego na zbity
					pomocniczy2->pNext->status = 3;//zmiana pola za na zbity
				}
				while (pomocniczy->y != y - 1)//przejscie na pozycje o jedna nizej niz pozycja wyjsciowa
					pomocniczy = pomocniczy->pDown;
				for (int i = 0;i < 5;i++)//jako ze statek moze miec maksymalnie rozmiar 4 i potrzebne jest przejdzie ponizej statku to petla wykonuje sie 5 razy
				{
					pomocniczy2 = pomocniczy->pHeadx;//wejscie na koordynaty X
					while (pomocniczy2->x != polozenie)//przejscie do polozenia statku
						pomocniczy2 = pomocniczy2->pNext;
					if (pomocniczy2->status == 0 || pomocniczy2->status == 4 || pomocniczy2->status == 3)//jezeli koniec statku przestan
						break;
					pomocniczy2->status = 3;//zmiana statusu na zbity
					pomocniczy2->pPrev->status = 3;//zmiana statusu pola poprzedzajacego na zbity
					pomocniczy2->pNext->status = 3;//zmiana statusu pola za statkiem na zbity
					pomocniczy = pomocniczy->pDown;//zejdz nizej
					if (pomocniczy == NULL)//jezeli wykroczono poza plansze przestan
						break;
				}
				if (pomocniczy != NULL)//jezeli nie wykroczono poza plansze
				{
					while (pomocniczy2->x != polozenie)//przejscie do polozenia statku
						pomocniczy2 = pomocniczy2->pNext;
					pomocniczy2->pPrev->status = 3;//zmiana statusu pola poprzedzajacego na zbity
					pomocniczy2->pNext->status = 3;//zmiana statusu pola za statkiem na zbity
					pomocniczy2->status = 3;//zmiana statusu na zbity
				}
			}
			else if (polozenie == 10)//jezeli statek znajduje sie na koncu osi X
			{
				for (int i = 0;i < 5;i++)//jako ze statek moze miec maksymalnie rozmiar 4 i potrzebne jest przejdzie powyzej statku to petla wykonuje sie 5 razy
				{
					pomocniczy2 = pomocniczy->pHeadx;//przejscie na koordynaty X
					while (pomocniczy2->x != polozenie)//przejscie do polozenia statku
						pomocniczy2 = pomocniczy2->pNext;
					if (pomocniczy2->status == 0 || pomocniczy2->status == 4 || pomocniczy2->status == 3)//jezeli koniec statku przestan
						break;
					pomocniczy2->status = 3;//zmiana statusu na zbity
					pomocniczy2->pPrev->status = 3;//zmiana statusu pola 
					if (pomocniczy->pUp == NULL)//jezeli koniec planszy koniec
						break;
					pomocniczy = pomocniczy->pUp;//przejdz wyzej
				}
				if (pomocniczy != NULL)//jezeli nie przekoroczno graniczy planszy
				{
					while (pomocniczy2->x != polozenie)//przejscie do polozenia statku
						pomocniczy2 = pomocniczy2->pNext;
					pomocniczy2->status = 3;//zmiana statusu na zbity
					pomocniczy2->pPrev->status = 3;//zmiana statusu pola poprzedzjacego na zbity
				}
				while (pomocniczy->y != y - 1)//przejscie na wysokosc o jedna nizsza niz wyjsciowa
					pomocniczy = pomocniczy->pDown;
				for (int i = 0;i < 5;i++)//jako ze statek moze miec maksymalnie rozmiar 4 i potrzebne jest przejdzie ponizej statku to petla wykonuje sie 5 razy
				{
					pomocniczy2 = pomocniczy->pHeadx;//wejscie na koordynaty X
					while (pomocniczy2->x != polozenie)//przejscie do polozenia statku
						pomocniczy2 = pomocniczy2->pNext;
					if (pomocniczy2->status == 0 || pomocniczy2->status == 4 || pomocniczy2->status == 3)//jezeli koniec statku przestan
						break;
					pomocniczy2->status = 3;//zmiana statusu na zbity
					pomocniczy2->pPrev->status = 3;//zmiana statusu pola poprzedzajacego na zbity
					pomocniczy = pomocniczy->pDown;//zejscie nizej
					if (pomocniczy == NULL)//jezeli przekroczono granice planszy przestan
						break;
				}
				if (pomocniczy != NULL)//jezeli nie wykroczono poza plansze
				{
					while (pomocniczy2->x != polozenie)//przejscie do polozenia statku
						pomocniczy2 = pomocniczy2->pNext;
					pomocniczy2->pPrev->status = 3;//zmiana statusu pola poprzedzajacego na zbity
					pomocniczy2->status = 3;//zmiana statusu pola na zbity
				}
			}
			else//jezeli statek znajduje sie na poczatku osi X
			{
				for (int i = 0;i < 5;i++)//jako ze statek moze miec maksymalnie rozmiar 4 i potrzebne jest przejdzie powyzej statku to petla wykonuje sie 5 razy
				{
					pomocniczy2 = pomocniczy->pHeadx;//przejscie na koordynaty X
					while (pomocniczy2->x != polozenie)//przejscie do polozenia statkku
						pomocniczy2 = pomocniczy2->pNext;
					if (pomocniczy2->status == 0 || pomocniczy2->status == 4 || pomocniczy2->status == 3)//jezeli koniec statku przestan
						break;
					pomocniczy2->status = 3;//zmien status na zbity
					pomocniczy2->pNext->status = 3;//zmien status pola za statkiem na zbity
					if (pomocniczy->pUp == NULL)//jezeli koniec planszy przestan
						break;
					pomocniczy = pomocniczy->pUp;//przejdz wyzej
				}
				if (pomocniczy != NULL)//jezeli nie przekroczono granicy planszy
				{
					while (pomocniczy2->x != polozenie)//przejscie do polozenia statku
						pomocniczy2 = pomocniczy2->pNext;
					pomocniczy2->status = 3;//zmien status na zbity
					pomocniczy2->pNext->status = 3;//zmien status pola za na zbity
				}
				while (pomocniczy->y != y - 1)//przejscie na wysokosc o jedno mniejsza niz wyjsciowa
					pomocniczy = pomocniczy->pDown;
				for (int i = 0;i < 5;i++)//jako ze statek moze miec maksymalnie rozmiar 4 i potrzebne jest przejdzie ponizej statku to petla wykonuje sie 5 razy
				{
					pomocniczy2 = pomocniczy->pHeadx;//przejscie na koordynaty X
					while (pomocniczy2->x != polozenie)//przejscie do polozenia statku
						pomocniczy2 = pomocniczy2->pNext;
					if (pomocniczy2->status == 0 || pomocniczy2->status == 4 || pomocniczy2->status == 3)//jezeli koniec statku przestan
						break;
					pomocniczy2->status = 3;//zmien status na zbity
					pomocniczy2->pNext->status = 3;//zmien status pola za statkiem na zbity
					pomocniczy = pomocniczy->pDown;//przejdz nizej
					if (pomocniczy == NULL)//jezeli koniec planszy przestan
						break;
				}
				if (pomocniczy != NULL)//jezeli nie przekroczono granicy planszy 
				{
					while (pomocniczy2->x != polozenie)//przejscie do polozenia statku
						pomocniczy2 = pomocniczy2->pNext;
					pomocniczy2->pNext->status = 3;//zmiana statusu pola za na zbity
					pomocniczy2->status = 3;//zmiana statusu na zbity
				}
			}
		}
	}
}
int strzal(struct Wspolrzedne_y** pHead_ref, char* nazwa)
{
	int X, Y;
	printf("Podaj koordynaty strzalu(x y): ");
	scanf(" %d %d", &X, &Y);
	bool walidacja = walidacja_koordynatow(X, Y);//sprawdzenie czy koordynaty spelniaja zasady gry
	if (walidacja == true)//jezeli tak
	{
		bool zbicie;
		struct Wspolrzedne_y* pomocniczy = *pHead_ref;
		while (pomocniczy->y != Y)
			pomocniczy = pomocniczy->pDown;//zejscie podana wysokosc
		struct Wspolrzedne_x* pomocniczy2 = pomocniczy->pHeadx;//przejscie na os X
		while (pomocniczy2->x != X)//przejscie na odpowiedni koordynat X
			pomocniczy2 = pomocniczy2->pNext;
		if (pomocniczy2->status == 1)//jezeli statek
		{
			pomocniczy2->status = 2;//zmien status na zbity
			zbicie = walidacja_zbicia(pomocniczy, pomocniczy2);//sprawdz czy zbito
			if (zbicie == true)//jezeli tak
			{
				zbij(&pomocniczy, &pomocniczy2);//zbij statek
				zapisz_strzal_do_pliku(X, Y, 3, nazwa);
				return 3;//zwroc informacje o zbiciu
			}
			else//jezeli nie
			{
				zapisz_strzal_do_pliku(X, Y, 2, nazwa);
				return 2;//zwroc informacje o trafieniu
			}
		}
		else if (pomocniczy2->status == 0)//jezeli pudlo
		{
			zapisz_strzal_do_pliku(X, Y, 4, nazwa);
			pomocniczy2->status = 4;//zmien status na pudlo
			return 4;//zwroc informacje o pudle
		}
		else//jezeli niepoprawny ruch
			return 0;//zwroc informacje o niepoprawnym ruchu
	}
	else//niepoprawne koordynaty
	{
		printf("Koordynaty musza byc z zakresu od 1 do 10.\n");
		Sleep(2500);
		return 5;//zwroc informacje o niepoprawnych koordynatach
	}
}
void usun_X(struct Wspolrzedne_x** pHead_ref)
{
	//usuwanie rekurencyjne koordynatow X
	if (*pHead_ref)
	{
		struct Wspolrzedne_x* pomocnicza = *pHead_ref;
		usun_X(&pomocnicza->pNext);
		free(pomocnicza);
	}
}
void usun_listy(struct Wspolrzedne_y** pHead_ref)
{
	//usuwanie rekurencyjne usuwanie koordynatow Y
	if (*pHead_ref)
	{
		struct Wspolrzedne_y* pomocnicza = *pHead_ref;
		usun_listy(&pomocnicza->pDown);
		usun_X(&pomocnicza->pHeadx);//usuwanie koordynatow X przypisanych do danej wysokosci
		free(pomocnicza);
	}
}
void usun_gracza(struct Uzytkownik** Gracz_ref)
{
	//usuwanie struktury gracza
	struct Uzytkownik* pomocnicza = *Gracz_ref;
	usun_listy(&pomocnicza->Tablica);//usuwananie tablicy gracza 
	free(pomocnicza);
}
int pobierz_statki_dla_uzytkownika(struct Uzytkownik** Uzytkownik_ref, char* nazwa, int set)
{
	FILE* plik;
	plik = fopen("presety.txt", "r");//otworz plik w trybie czytania
	if (plik)
	{
		struct Komputer* Uzytkownik = *Uzytkownik_ref;
		struct Wspolrzedne_y* pomocnicza = Uzytkownik->Tablica;
		srand(time(NULL));
		int numer;
		do
		{
			numer = rand() % 100 + 1;
		} while (numer == set);//wylosuj zestaw ktory nie byl wczesniej uzyty
		char szukany[19];
		snprintf(szukany, 19, "SET %d:\n", numer);//stworz linijke ktorej bedziesz szukac
		char linijka[19];
		int porownanie = 1;
		while (porownanie != 0 && fgets(linijka, 19, plik) != NULL)//szukanie linijki
		{
			porownanie = strcmp(linijka, szukany);//porownaj linijki
		}
		int pierwsza, druga, trzecia, rodzaj, number;
		for (int i = 0;i < 10;i++)//10 statkow wiec 10 przejsc
		{
			fscanf(plik, "%d.%d:\n", &rodzaj, &number);//pobranie linijki oraz liczby porzadkowej statku zadnego rodzaju
			fgets(linijka, 19, plik);
			if (strcmp(linijka, "USTAWIENIE:FALSE\n") == 0)//jezeli ustawienie horyzontalne
			{
				if (rodzaj == 1 || rodzaj == 2 || rodzaj == 3 || rodzaj == 4)//jezeli rodzaj spelnia zasady gry
				{

					fscanf(plik, "1:%d\n2:%d\n3:%d\n", &pierwsza, &druga, &trzecia);//pobierz koordynaty
					bool koordy_walidacja = walidacja_koordynatow(pierwsza, druga);//sprawdz czy koordynaty spelniaja zasady gry
					bool koordy_walidacja2 = walidacja_koordynatow(trzecia, trzecia);//sprawdz czy koordynaty spelniaja zasady gry
					if (koordy_walidacja == true && koordy_walidacja2 == true)//jezeli tak
					{
						bool statek = walidacja_statku(&pomocnicza, pierwsza, druga, pierwsza, trzecia);//sprawdzenie czy koordynaty spelniaja zasady gry
						if (statek == true)//jezeli tak
						{
							statek_na_plansze(&pomocnicza, pierwsza, druga, pierwsza, trzecia);//ustaw statek na plansze
							zapisz_ustawienie_do_pliku(druga, pierwsza, trzecia, pierwsza, nazwa);
							//zminiejsz ilosc dostepnych statkow odpowiedniego rodzaju
							if (rodzaj == 4)
								Uzytkownik->ilosc_czworek = 0;
							else if (rodzaj == 3)
								Uzytkownik->ilosc_trojek = Uzytkownik->ilosc_trojek - 1;
							else if (rodzaj == 2)
								Uzytkownik->ilosc_dwojek = Uzytkownik->ilosc_dwojek - 1;
							else
								Uzytkownik->ilosc_jedynek = Uzytkownik->ilosc_jedynek - 1;
						}
					}
				}

			}
			else//jezeli ustawienie wertykalne
			{
				if (rodzaj == 1 || rodzaj == 2 || rodzaj == 3 || rodzaj == 4)//sprawdz czy rodzaj spelnia zasady gry
				{
					fscanf(plik, "1:%d\n2:%d\n3:%d\n", &pierwsza, &druga, &trzecia);//pobierz koordynaty
					bool koordy_walidacja = walidacja_koordynatow(pierwsza, druga);//sprawdz czy koordynaty spelniaja zasady gry
					bool koordy_walidacja2 = walidacja_koordynatow(trzecia, trzecia);//sprawdz czy koordynaty spelniaja zasady gry
					if (koordy_walidacja == true && koordy_walidacja2 == true)//jezeli tak
					{
						bool statek = walidacja_statku(&pomocnicza, druga, pierwsza, trzecia, pierwsza);//sprawdz czy statek spelnia zasady gry
						if (statek == true)//jezeli tak
						{
							statek_na_plansze(&pomocnicza, druga, pierwsza, trzecia, pierwsza);//ustaw go na planszy
							zapisz_ustawienie_do_pliku(pierwsza, druga, pierwsza, trzecia, nazwa);
							//zminiejsz ilosc dostepnych statkow odpowiedniego rodzaju
							if (rodzaj == 4)
								Uzytkownik->ilosc_czworek = 0;
							else if (rodzaj == 3)
								Uzytkownik->ilosc_trojek = Uzytkownik->ilosc_trojek - 1;
							else if (rodzaj == 2)
								Uzytkownik->ilosc_dwojek = Uzytkownik->ilosc_dwojek - 1;
							else
								Uzytkownik->ilosc_jedynek = Uzytkownik->ilosc_jedynek - 1;
						}
					}
				}
			}
		}
		fclose(plik);//zamknij plik
		return numer;//zwroc informacje o uzytym zestawie statkow
	}
	return 0;//jezeli nie udalo sie otworzyc plikow oznacza to ze zaden zestaw nie zostal uzyty 
}
//FUNKCJE KOMPUTERA
void komputer_dodaj_kierunek(struct Lista_kierunkow** pHead_ref, int kierunek)
{
	struct Lista_kierunkow* nowy = (struct Lista_kierunkow*)malloc(sizeof(struct Lista_kierunkow));
	nowy->kierunek = kierunek;//zapisanie kierunku w ktorym ostatnio poszedl komputer
	nowy->pNext = NULL;//przypisanie wartosci NULL dla pNext
	if (!(*pHead_ref))//jezeli nie ma glowy
	{
		*pHead_ref = nowy;//nowy staje sie glowa
	}
	else//jezeli jest glowa
	{
		struct Lista_kierunkow* pomocniczy = *pHead_ref;//zapamietanie starej glowy
		*pHead_ref = nowy;//nowy staje sie nowa glowa
		nowy->pNext = pomocniczy;//przyczepienie starej glowy do nowej
	}
}
void komputer_usun_kierunki(struct Lista_kierunkow** pHead_ref)
{
	//iteracyjne usuwanie listy kierunkow
	if (*pHead_ref)
	{
		struct Lista_kierunkow* tmp = *pHead_ref;
		struct Lista_kierunkow* tmp2;
		while (tmp)//dopoki istnieje lista
		{
			tmp2 = tmp->pNext;//zapamietanie pNexta 
			free(tmp);//usuniecie wezla
			tmp = tmp2;//przypsisanie wezlowi pNexta
		}
	}
	*pHead_ref = NULL;
}
bool komputer_walidacja_kierunku(struct Lista_kierunkow* pHead, int kierunek)
{
	if (pHead)//jezeli istnieje lista
	{
		while (pHead != NULL)//dopoki nie dotarto do konca listy
		{
			if (pHead->kierunek == kierunek)//jezeli kierunek juz byl uzyty
				return false;
			pHead = pHead->pNext;//przejdz dalej
		}
	}
	return true;//zatwierdz kierunek
}
void komputer_pobierz_statki(struct Komputer** Komputer_ref, int set)
{
	FILE* plik;
	plik = fopen("presety.txt", "r");//otworz plik w trybie czytania
	if (plik)//jezeli otwarto
	{
		struct Komputer* komputer = *Komputer_ref;
		struct Wspolrzedne_y* pomocnicza = komputer->Tablica;
		srand(time(NULL));
		int numer;
		do
		{
			numer = rand() % 100 + 1;
		} while (numer == set);//wygeneruj numer ktory nie byl wczesniej uzyty
		char szukany[19];
		snprintf(szukany, 19, "SET %d:\n", numer);//tworzenie szukanej linii
		char linijka[19];
		int porownanie = 1;
		while (porownanie != 0 && fgets(linijka, 19, plik) != NULL)//dopoki linia nie jest rowna szukanej
		{
			porownanie = strcmp(linijka, szukany);//porownaj linie
		}
		int pierwsza, druga, trzecia, rodzaj, number;
		for (int i = 0;i < 10;i++)//10 statkow wiec 10 przejsc
		{
			fscanf(plik, "%d.%d:\n", &rodzaj, &number);//zapisz rodzaj statku oraz liczbe porzadkowa tego statku
			fgets(linijka, 19, plik);
			if (strcmp(linijka, "USTAWIENIE:FALSE\n") == 0)//jezeli statki sa ustawiane horyzontalnie
			{
				if (rodzaj == 1 || rodzaj == 2 || rodzaj == 3 || rodzaj == 4)//jezeli odpowiedni rodzaj
				{

					fscanf(plik, "1:%d\n2:%d\n3:%d\n", &pierwsza, &druga, &trzecia);//pobierz koordynaty
					bool koordy_walidacja = walidacja_koordynatow(pierwsza, druga);//sprawdz czy koordynaty spelniaja zasady gry
					bool koordy_walidacja2 = walidacja_koordynatow(trzecia, trzecia);//sprawdz czy koordynaty spelniaja zasady gry
					if (koordy_walidacja == true && koordy_walidacja2 == true)//jezeli tak
					{
						bool statek = walidacja_statku(&pomocnicza, pierwsza, druga, pierwsza, trzecia);//sprawdz czy statek spelnia zasady gry 
						if (statek == true)//jezeli spelnia
						{
							statek_na_plansze(&pomocnicza, pierwsza, druga, pierwsza, trzecia);//ustaw statek na planszy
							zapisz_ustawienie_do_pliku(druga, pierwsza, trzecia, pierwsza, "Komputer");
							//w zaleznosci od rodzaju zmniejsz ilosc dostepnych statkow
							if (rodzaj == 4)
								komputer->ilosc_czworek = 0;
							else if (rodzaj == 3)
								komputer->ilosc_trojek = komputer->ilosc_trojek - 1;
							else if (rodzaj == 2)
								komputer->ilosc_dwojek = komputer->ilosc_dwojek - 1;
							else
								komputer->ilosc_jedynek = komputer->ilosc_jedynek - 1;
						}
					}
				}

			}
			else//jezeli wertykalnie
			{
				if (rodzaj == 1 || rodzaj == 2 || rodzaj == 3 || rodzaj == 4)//jezeli odpowiedni rodzaj
				{
					fscanf(plik, "1:%d\n2:%d\n3:%d\n", &pierwsza, &druga, &trzecia);//pobierz koordynaty
					bool koordy_walidacja = walidacja_koordynatow(pierwsza, druga);//sprawdz czy koordynaty spelniaja zasady gry
					bool koordy_walidacja2 = walidacja_koordynatow(trzecia, trzecia);//sprawdz czy koordynaty spelniaja zasady gry
					if (koordy_walidacja == true && koordy_walidacja2 == true)//jezeli tak
					{
						bool statek = walidacja_statku(&pomocnicza, druga, pierwsza, trzecia, pierwsza);//sprawdz czy statek spelnia zasady gry
						if (statek == true)//jezeli tak
						{
							statek_na_plansze(&pomocnicza, druga, pierwsza, trzecia, pierwsza);//ustaw statek na planszy
							zapisz_ustawienie_do_pliku(pierwsza, druga, pierwsza, trzecia, "Komputer");
							//w zaleznosci od rodzaju zmniejsz ilosc dostepnych statkow
							if (rodzaj == 4)
								komputer->ilosc_czworek = 0;
							else if (rodzaj == 3)
								komputer->ilosc_trojek = komputer->ilosc_trojek - 1;
							else if (rodzaj == 2)
								komputer->ilosc_dwojek = komputer->ilosc_dwojek - 1;
							else
								komputer->ilosc_jedynek = komputer->ilosc_jedynek - 1;
						}
					}
				}
			}
		}
	fclose(plik);//zamknij plik
	}
}
void nowe_ustawienie(struct Lista_ustawien** pHead_ref, int xp, int xk, int yp, int yk)
{
	struct Lista_ustawien* nowy = (struct Lista_ustawien*)malloc(sizeof(struct Lista_ustawien));
	nowy->xp = xp;//przypisanie odpowiednich wartosci koordynatom statku
	nowy->xk = xk;
	nowy->yp = yp;
	nowy->yk = yk;
	nowy->pNext = NULL;//ustawienie pNext jako NULL
	if (!(*pHead_ref))//jezeli nie ma glowy
		*pHead_ref = nowy;//nowy staje sie glowa
	else//jezeli jest glowa
	{
		struct Lista_ustawien* pomocniczy = *pHead_ref;
		while (pomocniczy->pNext != NULL)//przejscie na koniec listy
			pomocniczy = pomocniczy->pNext;
		pomocniczy->pNext = nowy;//nowy staje sie ostatnim elementem listy
		nowy->pNext = NULL;
	}
}
void usun_ustawienia(struct Lista_ustawien** pHead_ref)
{
	//rekurencyjne usuwanie elemntow listy
	if (*pHead_ref)
	{
		struct Lista_ustawien* pomocniczy = *pHead_ref;
		usun_ustawienia(&pomocniczy->pNext);
		free(pomocniczy);
	}
}
void komputer_dostaw_statek(struct Wspolrzedne_y** pHead_ref, int rodzaj, char* nazwa)
{
	struct Lista_ustawien* ustawienia = NULL;
	srand(time(NULL));
	int licznik = 0;
	for (int i = 10;i > 0;i--)//przejscie przez wszystkie koordynaty Y
	{
		for (int j = 0;j < 10;j++)//przejscie przez wszystkie koordynaty X
		{
			bool koordy = walidacja_koordynatow(j + rodzaj, i);//sprawdzenie czy koordynaty statku wykraczaja za plansze
			if (koordy == false)//jezeli tak porzuc te koordynaty
				break;
			bool statek = walidacja_statku(pHead_ref, i, j + 1, i, j + rodzaj);//sprawdzenie czy statek moze byc ustawiony na planszy
			if (statek == true)//jezeli tak
			{
				licznik++;//zwieksz licznik dostepnych statkow 
				nowe_ustawienie(&ustawienia, j + rodzaj, j + 1, i, i);//zapisz ustawienie do listy
			}
		}
	}
	for (int i = 0;i < 10;i++)//przejscie przez wszystkie koordynaty Y
	{
		for (int j = 10;j > 0;j--)//przejscie przez wszystkie koordynaty X
		{
			bool koordy = walidacja_koordynatow(i + 1, j - rodzaj + 1);//sprawdzenie czy koordynaty statku wykraczaja za plansze
			if (koordy == false)//jezeli tak porzuc te koordynaty
				break;
			bool statek = walidacja_statku(pHead_ref, j, i + 1, j - rodzaj + 1, i + 1);//sprawdzenie czy statek moze byc ustawiony na planszy
			if (statek == true)//jezeli tak
			{
				licznik++;//zwieksz licznik dostepnych statkow
				nowe_ustawienie(&ustawienia, i + 1, i + 1, j - rodzaj + 1, j);//zapisz ustawienie do listy
			}
		}
	}
	int wybor = rand() % licznik;//wylosuj ustawienie
	struct Lista_ustawien* pomocniczy = ustawienia;
	for (int i = 0;i < wybor;i++)//przejdz do tego ustawienia
	{
		pomocniczy = pomocniczy->pNext;
	}
	statek_na_plansze(pHead_ref, pomocniczy->yp, pomocniczy->xp, pomocniczy->yk, pomocniczy->xk);//ustaw statek na planszy
	zapisz_ustawienie_do_pliku(pomocniczy->xp, pomocniczy->yp, pomocniczy->xk, pomocniczy->yk, nazwa);
	usun_ustawienia(&ustawienia);//usun liste ustawien
}
void komputer_dodaj_strzal(struct Komputer_strzelanie** pHead_ref, int x, int y, int kierunek, bool trafienie)
{
	struct Komputer_strzelanie* nowy = (struct Komputer_strzelanie*)malloc(sizeof(struct Komputer_strzelanie));
	nowy->x = x;//przypisanie odpowiednich wartosci nowemu wezlowi listy
	nowy->y = y;
	nowy->kierunek = kierunek;
	nowy->status_strzalu = trafienie;
	nowy->pNext = nowy->pPrev = NULL;//ustawienie wskaznikow pobocznych jako NULL
	if (!(*pHead_ref))//jezeli nie ma glowy
		*pHead_ref = nowy;//nowy staje sie glowa
	else//jezeli jest glowa
	{
		struct Komputer_strzelanie* pomocniczy = *pHead_ref;//zapisanie starej glowy
		*pHead_ref = nowy;//nowy staje sie nowa glowa
		nowy->pNext = pomocniczy;//powiazanie nowej glowy ze stara
		pomocniczy->pPrev = nowy;//powiazanie starej glowy z nowa
	}
}
int komputer_walidacja_ruchu(struct Wspolrzedne_y* pHead, struct Komputer_strzelanie* Strzaly, int x, int y)
{
	while (Strzaly != NULL)//dopoki nie dotarto do konca listy
	{
		if (Strzaly->x == x && Strzaly->y == y)//jezeli byl juz taki ruch
			return 0;//zwroc informaje ze taki ruch juz sie odbyl
		Strzaly = Strzaly->pNext;//przejdz dalej
	}
	while (pHead->y != y)//zejdz na odpowiednia wysokosc
		pHead = pHead->pDown;
	struct Wspolrzedne_x* pomocnicza2 = pHead->pHeadx;//przejscie na koordynaty X
	while (pomocnicza2->x != x)//przejscie do odpowiedniej wartosci X
		pomocnicza2 = pomocnicza2->pNext;
	if (pomocnicza2->status == 2 || pomocnicza2->status == 3 || pomocnicza2->status == 4)//jezeli ruch jest niemozliwy
		return 1;//zwroc informacje ze ruch jest niemozliwy
	else
		return 2;//zwroc informacje ze ruch jest mozliwy
}
void komputer_usun_strzaly(struct Komputer_strzelanie** pHead_ref)
{
	//rekurencyjne usuwanie listy strzalow
	if (*pHead_ref)
	{
		struct Komputer_strzelanie* pomocnicza = *pHead_ref;
		komputer_usun_strzaly(&pomocnicza->pNext);
		free(pomocnicza);
		pomocnicza = NULL;
	}
}
int komputer_strzal(struct Wspolrzedne_y** pHead_ref, int x, int y)
{
	struct Wspolrzedne_y* pomocnicza = *pHead_ref;
	while (pomocnicza->y != y)//zejscie na odpowiednia wysokosc
		pomocnicza = pomocnicza->pDown;
	struct Wspolrzedne_x* pomocnicza2 = pomocnicza->pHeadx;
	while (pomocnicza2->x != x)//przejscie na opdowiedni koordynat X
		pomocnicza2 = pomocnicza2->pNext;
	if (pomocnicza2->status == 1)//jezeli trafiono
	{
		pomocnicza2->status = 2;//zmien status na trafiony
		bool zbicie = walidacja_zbicia(pomocnicza, pomocnicza2);//sprawdz czy zbito
		if (zbicie == false)//jezeli nie
		{
			zapisz_strzal_do_pliku(x, y, 2, "Komputer");
			return 2;//zwroc informacje ze trafiono
		}
		else//jezeli zbito
		{
			zapisz_strzal_do_pliku(x, y, 3, "Komputer");
			zbij(&pomocnicza, &pomocnicza2);//zbij
			return 3;//zwroc informacje ze zbito
		}
	}
	else if (pomocnicza2->status == 0)//jezeli pudlo
	{
		zapisz_strzal_do_pliku(x, y, 4, "Komputer");
		pomocnicza2->status = 4;//zmien status na pudlo
		return 4;//zwroc informacje o pudle
	}
}
int komputer_dalszy_strzal(struct Komputer** Komputer_ref, struct Wspolrzedne_y** Tablica_przeciwnika_ref)
{
	struct Wspolrzedne_y* pomocnicza = *Tablica_przeciwnika_ref;
	struct Komputer* Komputer = *Komputer_ref;
	struct Komputer_strzelanie* ostatni = Komputer->Strzaly;//zapisanie ostatniego strzalu
	int kierunek;
	int x, y;
	if (ostatni->status_strzalu == false)//jezeli ostatni strzal byl pudlem
	{
		//zmien kierunek na odwrotny wzgledem osi X lub osi Y
		if (ostatni->kierunek == 1)
			kierunek = 2;
		else if (ostatni->kierunek == 2)
			kierunek = 1;
		else if (ostatni->kierunek == 3)
			kierunek = 4;
		else
			kierunek = 3;
		while (ostatni->kierunek != 0)
			ostatni = ostatni->pNext;
	}
	else//jezeli trafiono utrzymaj stary kierunek
		kierunek = ostatni->kierunek;
	if (kierunek == 1)//ruch w prawo
	{
		x = ostatni->x + 1;
		y = ostatni->y;
	}
	else if (kierunek == 2)//ruch w lewo
	{
		x = ostatni->x - 1;
		y = ostatni->y;
	}
	else if (kierunek == 3)//ruch w dol
	{
		x = ostatni->x;
		y = ostatni->y - 1;
	}
	else//ruch w gore
	{
		x = ostatni->x;
		y = ostatni->y + 1;
	}
	bool koordy = walidacja_koordynatow(x, y);//sprawdz czy koordynaty sa odpowiednie
	if (koordy == false)//jezeli nie
	{
		komputer_dodaj_strzal(&Komputer->Strzaly, x, y, kierunek, false);//zapisz strzal jako nieprawidlowy
		return 0;
	}
	else//jezeli tak
	{
		int sprawdzenie_strzalu = komputer_walidacja_ruchu(pomocnicza, Komputer->Strzaly, x, y);//sprawdz czy wczesniej strzelano w te miejsce
		if (sprawdzenie_strzalu == 1)//jezeli nie ale ruch jest nieprawidlowy
		{
			komputer_dodaj_strzal(&Komputer->Strzaly, x, y, kierunek, false);//zapisz strzal jako nieprawidlowy
			return 0;
		}
		else if (sprawdzenie_strzalu == 0)//jezeli tak
		{
			komputer_dodaj_strzal(&Komputer->Strzaly, x, y, kierunek, false);//zapisz strzal jako nieprawidlowy
			return 0;
		}
		else if (sprawdzenie_strzalu == 2)//jezeli nie
		{
			int strzal = komputer_strzal(&pomocnicza, x, y);//strzel
			if (strzal == 2)//jezeli trafiono
			{
				komputer_dodaj_strzal(&Komputer->Strzaly, x, y, kierunek, true);//zapisz strzal jako trafiony
				return 2;//zwroc informacje o trafieniu
			}
			else if (strzal == 3)//jezeli zbito
			{
				Komputer->status_strzalu = false;//zresetuj statusy strzalow tak by nastepny strzal byl przy pomocy funkcji komputer_pierwszy_strzal
				Komputer->status_drugiego_strzalu = false;
				komputer_dodaj_strzal(&Komputer->Strzaly, x, y, kierunek, false);//zapisz strzal 
				return 3;//zwroc informacje o zbiciu
			}
			else if (strzal == 4)
			{
				komputer_dodaj_strzal(&Komputer->Strzaly, x, y, kierunek, false);//zapisz strzal jako pudlo
				return 4;//zwroc informacje o pudle
			}
		}
	}
}
int komputer_drugi_strzal(struct Komputer** Komputer_ref, struct Wspolrzedne_y** Tablica_przeciwnika_ref)
{
	srand(time(NULL));
	struct Komputer* Komputer = *Komputer_ref;
	struct Komputer_strzelanie* ostatni = Komputer->Strzaly;//zapamietatnie ostatniego strzalu
	struct Wspolrzedne_y* pomocnicza = *Tablica_przeciwnika_ref;
	if (ostatni->status_strzalu == false)//jezeli ostatni strzal okazal sie pudlem
	{
		while (ostatni->status_strzalu != true)//znajdz ostatni trafiony strzal
			ostatni = ostatni->pNext;
	}
	int x = ostatni->x;//zapamietaj koordynaty ostatniego strzalu
	int y = ostatni->y;
	for (int i = 0;i < 4;i++)//dostepne sa 4 kierunki stad 4 przejscia
	{
		bool kierunek_wali = false;
		int kierunek;
		while (kierunek_wali != true)//dopki kierunek nie bedzie kierunkiem, ktory nie byl uzywany z tego pola
		{
			kierunek = rand() % 4 + 1;//losuj kierunek
			kierunek_wali = komputer_walidacja_kierunku(Komputer->Kierunki, kierunek);//sprawdz kierunek
		}
		int x2, y2;
		if (kierunek == 1)//ruch w prawo
		{
			x2 = x + 1;
			y2 = y;
		}
		else if (kierunek == 2)//ruch w lewo
		{
			x2 = x - 1;
			y2 = y;
		}
		else if (kierunek == 3)//ruch w dol
		{
			x2 = x;
			y2 = y - 1;
		}
		else//ruch w gore
		{
			x2 = x;
			y2 = y + 1;
		}
		bool koordy = walidacja_koordynatow(x2, y2);//sprawdz czy koordynaty sa prawidlowe
		if (koordy == false)//jezeli nie
		{
			komputer_dodaj_kierunek(&Komputer->Kierunki, kierunek);//zapisz kierunek
		}
		else//jezeli tak
		{
			int sprawdzenie_strzalu = komputer_walidacja_ruchu(pomocnicza, Komputer->Strzaly, x2, y2);//sprawdz czy ruch jest prawidlowy
			if (sprawdzenie_strzalu == 2)//jezeli tak
			{
				int strzal = komputer_strzal(&pomocnicza, x2, y2);//strzel
				if (strzal == 2)//jezeli trafiono
				{
					komputer_dodaj_strzal(&Komputer->Strzaly, x2, y2, kierunek, true);//zapisz strzal do listy
					Komputer->status_drugiego_strzalu = true;//zmien status drugiego strzalu tak by nastepnym razem uzyto funkcji komputer_dalszy_strzal
					komputer_usun_kierunki(&Komputer->Kierunki);//usun uzyte kierunki
					return 2;//zwroc informacje o trafieniu
				}
				else if (strzal == 3)//jezeli zbito
				{
					Komputer->status_strzalu = false;//zmien status strzalu tak by nastepnym razem uzyto funckji komputer_pierwszy_strzal
					komputer_dodaj_strzal(&Komputer->Strzaly, x2, y2, kierunek, false);//zapisz strzal do listy
					komputer_usun_kierunki(&Komputer->Kierunki);//usun uzyte kierunki
					return 3;//zwroc informacje o zbiciu
				}
				else if (strzal == 4)//jezeli pudlo
				{
					komputer_dodaj_kierunek(&Komputer->Kierunki, kierunek);//dodaj kierunek do listy
					komputer_dodaj_strzal(&Komputer->Strzaly, x2, y2, kierunek, false);//zapisz strzal do listy
					return 4;//zwroc informacje o pudle
				}
			}
			else if (sprawdzenie_strzalu == 1)//jezeli nie
			{
				komputer_dodaj_kierunek(&Komputer->Kierunki, kierunek);//dodaj kierunek do listy
				komputer_dodaj_strzal(&Komputer->Strzaly, x2, y2, kierunek, false);//dodal strzal do listy
			}
			else//jezeli juz strzelano w te miejsce
				komputer_dodaj_kierunek(&Komputer->Kierunki, kierunek);//zapisz kierunek do listy
		}
	}
}
int komputer_pierwszy_strzal(struct Komputer** Komputer_ref, struct Wspolrzedne_y** Tablica_przeciwnika_ref)
{
	struct Komputer* Komputer = *Komputer_ref;
	struct Wspolrzedne_y* pomocnicza = *Tablica_przeciwnika_ref;
	srand(time(NULL));
	int sprawdzenie_strzalu, x, y;
	do
	{
		x = rand() % 10 + 1;//losowanie koordynatow X
		y = rand() % 10 + 1;//losowanie koordynatow Y
		sprawdzenie_strzalu = komputer_walidacja_ruchu(pomocnicza, Komputer->Strzaly, x, y);//sprawdzenie czy ten strzal zgodny z zasadmi gry
	} while (sprawdzenie_strzalu == 0);

	if (sprawdzenie_strzalu == 2)//jezeli tak
	{
		int strzal = komputer_strzal(&pomocnicza, x, y);//strzel
		if (strzal == 2)//jezeli trafiono
		{
			komputer_dodaj_strzal(&Komputer->Strzaly, x, y, 0, true);//dodaj strzal do listy
			Komputer->status_strzalu = true;//zmien status strzalu tak by nastepnym razem uzyto funkcji komputer_drugi_strzal
			return 2;//zwroc informacje o trafieniu
		}
		else if (strzal == 3)//jezeli zbito
		{
			komputer_dodaj_strzal(&Komputer->Strzaly, x, y, 0, false);//zapisz strzal do listy
			return 3;//zwroc informacje o zbiciu
		}
		else if (strzal == 4)//jezeli pudlo
		{
			komputer_dodaj_strzal(&Komputer->Strzaly, x, y, 0, false);//zapisz strzal do listy
			return 4;//zwroc informacje o pudle
		}
	}
	else if (sprawdzenie_strzalu == 1)//jezeli ruch jest nieprawidlowy
	{
		komputer_dodaj_strzal(&Komputer->Strzaly, x, y, 0, false);//dodaj strzal do listy
	}
	return 0;
}
void komputer_standardowy_zestaw(struct Komputer** Komputer_ref)
{
	//przypisanie komputerowi wszystkich poczatkowych wartosci
	struct Komputer* Komputer = *Komputer_ref;
	Komputer->ilosc_czworek = 1;
	Komputer->ilosc_trojek = 2;
	Komputer->ilosc_dwojek = 3;
	Komputer->ilosc_jedynek = 4;
	Komputer->punkty = 0;
	Komputer->status_drugiego_strzalu = false;
	Komputer->status_strzalu = false;
	Komputer->Strzaly = NULL;
	Komputer->Kierunki = NULL;
}
void usun_komputer(struct Komputer** Komputer_ref)
{
	//usuwanie struktury komputera
	struct Komputer* pomocnicza = *Komputer_ref;
	usun_listy(&pomocnicza->Tablica);//usuwanie planszy komputera
	komputer_usun_strzaly(&pomocnicza->Strzaly);//usuwanie listy strzalow
	komputer_usun_kierunki(&pomocnicza->Kierunki);//usuwanie kierunkow
	free(pomocnicza);
}
//TRYBY GRY
void Gracz_na_Gracza(struct Uzytkownik** Gracz1_ref, struct Uzytkownik** Gracz2_ref)
{
	FILE* plik;
	time_t czas = time(NULL);//pobranie czasu
	char* czas_str = ctime(&czas);//konwersja zmiennej czas na string
	czas_str[strlen(czas_str) - 1] = '\0';//ustawienie ostatniego znaku w stringu na koniec stringa
	plik = fopen("logi.txt", "w+");//otworzenie pliku w trybie nadpisywania
	if (plik)//jezeli otwarto plik
	{
		fprintf(plik, "%s Gra w trybie Gracz na Gracza zostala rozpoczeta.\n", czas_str);
		fclose(plik);
	}
	struct Uzytkownik* Gracz1 = *Gracz1_ref;
	struct Uzytkownik* Gracz2 = *Gracz2_ref;
	struct Wspolrzedne_y* Gracz1_Tab = NULL;
	struct Wspolrzedne_y* Gracz2_Tab = NULL;
	for (int i = 0;i < 10;i++)
	{
		nowy_Y(&Gracz1_Tab, i + 1);//tworzenie planszy graczy
		nowy_Y(&Gracz2_Tab, i + 1);
	}
	Gracz1->Tablica = Gracz1_Tab;//przypisanie graczom swoich planszy
	Gracz2->Tablica = Gracz2_Tab;
	Standardowy_zestaw(&Gracz1);//przypisanie graczom zestawow
	Standardowy_zestaw(&Gracz2);
	char wybor;
	int set = 0;//przysanie uzywanemu zestawowai wartosci 0 tak by kazdy zestaw byl dostepny przy pierwszym otworzeniu pliku
	for (;;)
	{
		system("cls");
		printf("Gracz 1 ustawia statki\n\nCzy chcesz sam ustawic swoje statki?\n\n1.Tak\n\n2.Nie - komputer ustawi statki za mnie\n");
		wybor = _getch();
		switch (wybor)
		{
		case '1'://ustawianie statkow przez gracza
		{
			while (Gracz1->ilosc_czworek != 0 || Gracz1->ilosc_dwojek != 0 || Gracz1->ilosc_jedynek != 0 || Gracz1->ilosc_trojek != 0)
			{
				system("cls");
				printf("Gracz 1 ustawia statki\n\n");
				wyswietl_tablice(Gracz1->Tablica);
				printf("Ilosc Jedynek: %d\n", Gracz1->ilosc_jedynek);
				printf("Ilosc Dwojek: %d\n", Gracz1->ilosc_dwojek);
				printf("Ilosc Trojek: %d\n", Gracz1->ilosc_trojek);
				printf("Ilosc Czworek: %d\n", Gracz1->ilosc_czworek);
				ustaw_statek(&Gracz1, "Gracz 1");
			}
			system("cls");
			printf("Wszystkie statki Gracza 1 zostaly ustawione.\nStatki Gracza 1:\n");
			break;
		}
		case '2'://ustawianie statkow przy pomocy komputera
		{
			set = pobierz_statki_dla_uzytkownika(&Gracz1, "Komputer dla Gracza 1", set);//wczytanie statkow z pliku
			if (Gracz1->ilosc_czworek != 0 || Gracz1->ilosc_trojek != 0 || Gracz1->ilosc_dwojek != 0 || Gracz1->ilosc_jedynek != 0)//jezeli nie wszystkie statki gracza 1 sa na planszy
			{
				//dopoki brakuje statkow ustawiaj je
				while (Gracz1->ilosc_czworek != 0)
				{
					komputer_dostaw_statek(&Gracz1->Tablica, 4, "Komputer dla Gracza 1");
					Gracz1->ilosc_czworek = 0;
				}
				while (Gracz1->ilosc_trojek != 0)
				{
					komputer_dostaw_statek(&Gracz1->Tablica, 3, "Komputer dla Gracza 1");
					Gracz1->ilosc_trojek = Gracz1->ilosc_trojek - 1;
				}
				while (Gracz1->ilosc_dwojek != 0)
				{
					komputer_dostaw_statek(&Gracz1->Tablica, 2, "Komputer dla Gracza 1");
					Gracz1->ilosc_dwojek = Gracz1->ilosc_dwojek - 1;
				}
				while (Gracz1->ilosc_jedynek != 0)
				{
					komputer_dostaw_statek(&Gracz1->Tablica, 1, "Komputer dla Gracza 1");
					Gracz1->ilosc_jedynek = Gracz1->ilosc_jedynek - 1;
				}
			}
			system("cls");
			printf("Statki zostaly ustawione:\n\n");
			break;
		}
		default://wybor opcji nieuwzglednionej w menu
		{
			system("cls");
			printf("Niepoprawny wybor!\nPoprawny Wybor to opcja 1 lub opcja 2!");
			Sleep(3000);
			break;
		}
		}
		if (wybor == '1' || wybor == '2')//wyjdz z menu przy prawidlowym wyborze
			break;
	}
	wyswietl_tablice(Gracz1->Tablica);//wyswietl tablice ze wszystkimi statkami
	Sleep(3000);
	for (;;)
	{
		system("cls");
		printf("Gracz 2 ustawia statki\n\nCzy chcesz sam ustawic swoje statki?\n\n1.Tak\n\n2.Nie - komputer ustawi statki za mnie\n");
		wybor = _getch();
		switch (wybor)
		{
		case '1'://ustawienie statkow przez gracza 1
		{
			while (Gracz2->ilosc_czworek != 0 || Gracz2->ilosc_dwojek != 0 || Gracz2->ilosc_jedynek != 0 || Gracz2->ilosc_trojek != 0)
			{
				system("cls");
				printf("Gracz  ustawia statki\n\n");
				wyswietl_tablice(Gracz2->Tablica);
				printf("Ilosc Jedynek: %d\n", Gracz2->ilosc_jedynek);
				printf("Ilosc Dwojek: %d\n", Gracz2->ilosc_dwojek);
				printf("Ilosc Trojek: %d\n", Gracz2->ilosc_trojek);
				printf("Ilosc Czworek: %d\n", Gracz2->ilosc_czworek);
				ustaw_statek(&Gracz2, "Gracz 2");
			}
			system("cls");
			printf("Wszystkie statki Gracza 2 zostaly ustawione.\nStatki Gracza 2:\n");
			break;
		}
		case '2'://ustawianie statkow przy pomocy komputera
		{
			set = pobierz_statki_dla_uzytkownika(&Gracz2, "Komputer dla Gracza 2", set);//wczytanie statkow z pliku
			if (Gracz2->ilosc_czworek != 0 || Gracz2->ilosc_trojek != 0 || Gracz2->ilosc_dwojek != 0 || Gracz2->ilosc_jedynek != 0)//jezeli nie wszystkie statki gracza 2 sa na planszy
			{
				//dopoki brakuje statkow ustawiaj je
				while (Gracz2->ilosc_czworek != 0)
				{
					komputer_dostaw_statek(&Gracz2->Tablica, 4, "Komputer dla Gracza 2");
					Gracz2->ilosc_czworek = 0;
				}
				while (Gracz2->ilosc_trojek != 0)
				{
					komputer_dostaw_statek(&Gracz2->Tablica, 3, "Komputer dla Gracza 2");
					Gracz2->ilosc_trojek = Gracz2->ilosc_trojek - 1;
				}
				while (Gracz2->ilosc_dwojek != 0)
				{
					komputer_dostaw_statek(&Gracz2->Tablica, 2, "Komputer dla Gracza 2");
					Gracz2->ilosc_dwojek = Gracz2->ilosc_dwojek - 1;
				}
				while (Gracz2->ilosc_jedynek != 0)
				{
					komputer_dostaw_statek(&Gracz2->Tablica, 1, "Komputer dla Gracza 2");
					Gracz2->ilosc_jedynek = Gracz2->ilosc_jedynek - 1;
				}
			}
			system("cls");
			printf("Statki zostaly ustawione:\n\n");
			break;
		}
		default://wybor opcji nieuwzglednionej w menu
		{
			system("cls");
			printf("Niepoprawny wybor!\nPoprawny Wybor to opcja 1 lub opcja 2!");
			Sleep(3000);
			break;
		}
		}
		if (wybor == '1' || wybor == '2')//wyjdz z menu przy prawidlowym wyborze
			break;
	}
	wyswietl_tablice(Gracz2->Tablica);//wyswietl tablice gracza 2
	Sleep(3000);
	for (;;)
	{
		int ruch1 = 0;
		while (ruch1 != 4 && Gracz1->punkty != 20)//dopki gracz nie spudluje lub nie zdobedzie 20 pkt
		{
			system("cls");
			printf("Gracz 1 strzela\n");
			printf("Aktualne punkty: %d\n", Gracz1->punkty);
			wyswietl_tablice_przeciwnika(Gracz2->Tablica);
			ruch1 = strzal(&Gracz2->Tablica, "Gracz 1");//gracz 1 strzela
			if (ruch1 == 2)//jezeli trafil
			{
				Gracz1->punkty = Gracz1->punkty + 1;
				printf("Trafiono w statek!");

			}
			else if (ruch1 == 3)//jezeli zbil
			{
				Gracz1->punkty = Gracz1->punkty + 1;
				printf("Zatopiono statek!");
			}
			else if (ruch1 == 4)//jezeli spudlowal
			{
				system("cls");
				printf("Gracz 1 strzela\n");
				printf("Aktualne punkty: %d\n", Gracz1->punkty);
				wyswietl_tablice_przeciwnika(Gracz2->Tablica);
				printf("Pudlo!");
			}
			else if (ruch1 == 0)//jezeli popelnil nieprawidlowy rych
			{
				printf("Nieprawidlowy ruch!");
			}
			Sleep(3000);
		}
		if (Gracz1->punkty == 20)//jezeli gracz 1 osiagnal 20 pkt 
			break;
		int ruch2 = 0;
		while (ruch2 != 4 && Gracz2->punkty != 20)
		{
			system("cls");
			printf("Gracz 2 strzela\n");
			printf("Aktualne punkty: %d\n", Gracz2->punkty);
			wyswietl_tablice_przeciwnika(Gracz1->Tablica);
			ruch2 = strzal(&Gracz1->Tablica, "Gracz 2");//gracz 2 strzela
			if (ruch2 == 2)//jezeli trafil
			{
				Gracz2->punkty = Gracz2->punkty + 1;
				printf("Trafiono w statek!");

			}
			else if (ruch2 == 3)//jezeli zbil
			{
				Gracz2->punkty = Gracz2->punkty + 1;
				printf("Zatopiono statek!");
			}
			else if (ruch2 == 4)//jezeli spudlowal
			{
				system("cls");
				printf("Gracz 2 strzela\n");
				printf("Aktualne punkty: %d\n", Gracz2->punkty);
				wyswietl_tablice_przeciwnika(Gracz1->Tablica);
				printf("Pudlo!");
			}
			else if (ruch2 == 0)//jezeli popelnil nieprawidlowy ruch
			{
				printf("Niepoprawny ruch!");
			}
			Sleep(3000);
		}
		if (Gracz2->punkty == 20)//jezeli gracz 2 osiagnal 20 pkt
			break;
	}
	system("cls");
	czas = time(NULL);//pobranie czasu
	czas_str = ctime(&czas);//konwersja zmiennej czas na string
	czas_str[strlen(czas_str) - 1] = '\0';//ustawienie ostatniego znaku w stringu na koniec stringa
	if (Gracz1->punkty == 20)//jezeli wygral gracz 1
	{
		printf("Gracz 1 pokonal Gracza 2!");
		printf("\nTablica Gracza 1:\n");
		wyswietl_tablice(Gracz1->Tablica);
		printf("\nTablica Gracza 2:\n");
		wyswietl_tablice(Gracz2->Tablica);
		plik = fopen("logi.txt", "a+");//otwarcie pliku w trybie dopisywania
		if (plik)
		{
			fprintf(plik, "%s Gracz 1 wygral.\n", czas_str);
			fprintf(plik, "%s Gra w trybie Gracz na Gracza zostala zakonczona.\n", czas_str);
			fclose(plik);
		}


	}
	else//jezeli wygral gracz 2 
	{
		printf("Gracz 2 pokonal Gracza 1!");
		printf("\nTablica Gracza 2:\n");
		wyswietl_tablice(Gracz2->Tablica);
		printf("\nTablica Gracza 1:\n");
		wyswietl_tablice(Gracz1->Tablica);
		plik = fopen("logi.txt", "a+");//otwarcie pliku w trybie dopisywania
		if (plik != NULL)
		{
			fprintf(plik, "%s Gracz 2 wygral.\n", czas_str);
			fprintf(plik, "%s Gra w trybie Gracz na Gracza zostala zakonczona.\n", czas_str);
			fclose(plik);
		}

	}
}
void Gracz_na_Komputer(struct Uzytkownik** Gracz_ref, struct Komputer** Komputer_ref)
{
	FILE* plik;
	time_t czas = time(NULL);//pobranie czasu
	char* czas_str = ctime(&czas);//konwersja zmiennej czas na string
	czas_str[strlen(czas_str) - 1] = '\0';//ustawienie ostatniego znaku w stringu na koniec stringa
	plik = fopen("logi.txt", "w+");//otwarcie pliku w trybie nadpisywania
	if (plik)
	{
		fprintf(plik, "%s Gra w trybie Gracz na Komputer zostala rozpoczeta.\n", czas_str);
		fclose(plik);
	}
	struct Uzytkownik* Gracz = *Gracz_ref;
	struct Komputer* Komputer = *Komputer_ref;
	struct Wspolrzedne_y* Gracz_Tab = NULL;
	struct Wspolrzedne_y* Komputer_Tab = NULL;
	for (int i = 0;i < 10;i++)
	{
		nowy_Y(&Gracz_Tab, i + 1);//stworzenie plansz dla gracza i komputera
		nowy_Y(&Komputer_Tab, i + 1);
	}
	Gracz->Tablica = Gracz_Tab;//przypisanie graczowi i komputerowi ich plansz
	Komputer->Tablica = Komputer_Tab;
	Standardowy_zestaw(&Gracz);//przypisanie graczowi i komputerowi ich standardowych zestawow
	komputer_standardowy_zestaw(&Komputer);
	char wybor;
	int set = 0;
	for (;;)
	{
		system("cls");
		printf("Gracz ustawia statki\n\nCzy chcesz sam ustawic swoje statki?\n\n1.Tak\n\n2.Nie - komputer ustawi statki za mnie\n");
		wybor = _getch();
		switch (wybor)
		{
		case '1'://gracz sam ustawia statki
		{
			while (Gracz->ilosc_czworek != 0 || Gracz->ilosc_dwojek != 0 || Gracz->ilosc_jedynek != 0 || Gracz->ilosc_trojek != 0)
			{
				system("cls");
				printf("Gracz ustawia statki\n\n");
				wyswietl_tablice(Gracz->Tablica);
				printf("Ilosc Jedynek: %d\n", Gracz->ilosc_jedynek);
				printf("Ilosc Dwojek: %d\n", Gracz->ilosc_dwojek);
				printf("Ilosc Trojek: %d\n", Gracz->ilosc_trojek);
				printf("Ilosc Czworek: %d\n", Gracz->ilosc_czworek);
				ustaw_statek(&Gracz, "Gracz");
			}
			system("cls");
			printf("Wszystkie statki Gracza zostaly ustawione.\nStatki Gracza :\n");
			break;
		}
		case '2'://komputer ustawia statki za gracza
		{
			set = pobierz_statki_dla_uzytkownika(&Gracz, "Komputer dla Gracza", set);//wczytanie statkow z pliku
			if (Gracz->ilosc_czworek != 0 || Gracz->ilosc_trojek != 0 || Gracz->ilosc_dwojek != 0 || Gracz->ilosc_jedynek != 0)//jezeli nie wszystkie statki gracza sa na planszy
			{
				//dopoki brakuje statkow ustawiaj je
				while (Gracz->ilosc_czworek != 0)
				{
					komputer_dostaw_statek(&Gracz->Tablica, 4, "Komputer dla Gracza");
					Gracz->ilosc_czworek = 0;
				}
				while (Gracz->ilosc_trojek != 0)
				{
					komputer_dostaw_statek(&Gracz->Tablica, 3, "Komputer dla Gracza");
					Gracz->ilosc_trojek = Gracz->ilosc_trojek - 1;
				}
				while (Gracz->ilosc_dwojek != 0)
				{
					komputer_dostaw_statek(&Gracz->Tablica, 2, "Komputer dla Gracza");
					Gracz->ilosc_dwojek = Gracz->ilosc_dwojek - 1;
				}
				while (Gracz->ilosc_jedynek != 0)
				{
					komputer_dostaw_statek(&Gracz->Tablica, 1, "Komputer dla Gracza");
					Gracz->ilosc_jedynek = Gracz->ilosc_jedynek - 1;
				}
			}
			system("cls");
			printf("Statki zostaly ustawione:\n\n");
			break;
		}
		default:
		{
			system("cls");
			printf("Niepoprawny wybor!\nPoprawny Wybor to opcja 1 lub opcja 2!");
			Sleep(3000);
			break;
		}
		}
		if (wybor == '1' || wybor == '2')
			break;
	} 
	wyswietl_tablice(Gracz->Tablica);
	Sleep(3000);
	komputer_pobierz_statki(&Komputer, set);//wczytania statkow z pliku
	if (Komputer->ilosc_czworek != 0 || Komputer->ilosc_trojek != 0 || Komputer->ilosc_dwojek != 0 || Komputer->ilosc_jedynek != 0)//jezeli nie wszystkie statki komputera zostaly ustawione
	{
		//dopoki brakuje statkow ustawiaj je
		while (Komputer->ilosc_czworek != 0)
		{
			komputer_dostaw_statek(&Komputer->Tablica, 4, "Komputer");
			Komputer->ilosc_czworek = 0;
		}
		while (Komputer->ilosc_trojek != 0)
		{
			komputer_dostaw_statek(&Komputer->Tablica, 3, "Komputer");
			Komputer->ilosc_trojek = Komputer->ilosc_trojek - 1;
		}
		while (Komputer->ilosc_dwojek != 0)
		{
			komputer_dostaw_statek(&Komputer->Tablica, 2, "Komputer");
			Komputer->ilosc_dwojek = Komputer->ilosc_dwojek - 1;
		}
		while (Komputer->ilosc_jedynek != 0)
		{
			komputer_dostaw_statek(&Komputer->Tablica, 1, "Komputer");
			Komputer->ilosc_jedynek = Komputer->ilosc_jedynek - 1;
		}
	}
	for (;;)
	{
		int ruch1 = 0;
		while (ruch1 != 4 && Gracz->punkty != 20)//dopki gracz nie spudluje lub nie zdobedzie 20 pkt
		{
			system("cls");
			printf("Gracz strzela\n");
			printf("Aktualne punkty: %d\n", Gracz->punkty);
			wyswietl_tablice_przeciwnika(Komputer->Tablica);
			ruch1 = strzal(&Komputer->Tablica, "Gracz");//uzytkownik strzela
			if (ruch1 == 3)//jezeli zbil
			{
				Gracz->punkty = Gracz->punkty + 1;
				system("cls");
				printf("Gracz strzela\n");
				printf("Aktualne punkty: %d\n", Gracz->punkty);
				wyswietl_tablice_przeciwnika(Komputer->Tablica);
				printf("Zatopiles statek!\n");
				Sleep(3000);
			}
			else if (ruch1 == 2)//jezeli trafil
			{
				Gracz->punkty = Gracz->punkty + 1;
				system("cls");
				printf("Gracz strzela\n");
				printf("Aktualne punkty: %d\n", Gracz->punkty);
				wyswietl_tablice_przeciwnika(Komputer->Tablica);
				printf("Trafiles w statek!\n");
				Sleep(3000);
			}
			else if (ruch1 == 4)//jezeli spudlowal
			{
				system("cls");
				printf("Gracz strzela\n");
				printf("Aktualne punkty: %d\n", Gracz->punkty);
				wyswietl_tablice_przeciwnika(Komputer->Tablica);
				printf("Gracz spudlowal!\n");
				Sleep(3000);
			}
			else if (ruch1 == 0)//jezeli wykonal nieprawidlowy ruch
			{
				printf("Nieprawidlowy ruch!");
				Sleep(3000);
			}
		}
		if (Gracz->punkty == 20)//jezeli gracz zdobyl 20 pkt
			break;
		int ruch2 = 0;
		while (ruch2 != 4 && Komputer->punkty != 20)//dopki komputer nie zdobedzie 20 pkt lub nie spudluje
		{
			system("cls");
			printf("Strzela Komputer\n");
			printf("Aktualne punkty: %d\n", Komputer->punkty);
			wyswietl_tablice(Gracz->Tablica);
			Sleep(3000);
			if (Komputer->status_strzalu == true && Komputer->status_drugiego_strzalu == true)//jezeli komputer moze juz przejsc do dalszego strzalu
			{
				ruch2 = komputer_dalszy_strzal(Komputer_ref, &Gracz->Tablica);
			}
			else if (Komputer->status_strzalu == true && Komputer->status_drugiego_strzalu == false)//jezeli komputer juz moze przejsc do drugiego strzalu
			{
				ruch2 = komputer_drugi_strzal(Komputer_ref, &Gracz->Tablica);
			}
			else if (Komputer->status_strzalu == false && Komputer->status_drugiego_strzalu == false)//jezeli komputer moze tylko przejsc do pierwszego strzalu
			{
				ruch2 = komputer_pierwszy_strzal(Komputer_ref, &Gracz->Tablica);
			}
			if (ruch2 == 3)//jezeli zbil
			{
				Komputer->punkty = Komputer->punkty + 1;
				system("cls");
				printf("Komputer strzela\n");
				printf("Aktualne punkty: %d\n", Komputer->punkty);
				wyswietl_tablice(Gracz->Tablica);
				printf("Komputer zatopil twoj statek!\n");
				Sleep(3000);
			}
			else if (ruch2 == 2)//jezeli trafil
			{
				Komputer->punkty = Komputer->punkty + 1;
				system("cls");
				printf("Komputer strzela\n");
				printf("Aktualne punkty: %d\n", Komputer->punkty);
				wyswietl_tablice(Gracz->Tablica);
				printf("Komputer trafil w twoj statek!\n");
				Sleep(3000);
			}
			else if (ruch2 == 4)//jezeli spudlowal
			{
				system("cls");
				printf("Komputer strzela\n");
				printf("Aktualne punkty: %d\n", Komputer->punkty);
				wyswietl_tablice(Gracz->Tablica);
				printf("Komputer spudlowal!\n");
				Sleep(3000);
			}
		}
		if (Komputer->punkty == 20)//jezeli komputer zdobyl 20 pkt
			break;
	}
	system("cls");
	czas = time(NULL);//pobranie czasu
	czas_str = ctime(&czas);//konwersja zmiennej czas na string
	czas_str[strlen(czas_str) - 1] = '\0';//ustawienie ostatniego znaku w stringu na koniec stringa
	if (Gracz->punkty == 20)//jezeli gracz wygral
	{
		printf("Gracz pokonal Komputer!");
		printf("\nTablica gracza\n");
		wyswietl_tablice(Gracz->Tablica);
		printf("\nTablica Komputera:\n");
		wyswietl_tablice(Komputer->Tablica);
		plik = fopen("logi.txt", "a+");
		if (plik)
		{
			fprintf(plik, "%s Gracz wygral.\n", czas_str);
			fprintf(plik, "%s Gra w trybie Gracz na Komputer zostala zakonczona.\n", czas_str);
			fclose(plik);
		}

	}
	else//jezeli komputer wygral
	{
		printf("Komputer pokonal Gracza!");
		printf("\nTablica Komputera:\n");
		wyswietl_tablice(Komputer->Tablica);
		printf("\nTablica Gracza:\n");
		wyswietl_tablice(Gracz->Tablica);
		plik = fopen("logi.txt", "a+");
		if (plik)
		{
			fprintf(plik, "%s Komputer wygral.\n", czas_str);
			fprintf(plik, "%s w trybie Gracz na Komputer zostala zakonczona.\n", czas_str);
			fclose(plik);
		}

	}
}
void menu()
{
	char wybor;
	for (;;)
	{
		printf("Witam w grze statki autorstwa Mateusza Adamczyka.\n\n");
		printf("MENU:\n\n");
		printf("1. Gracz na Gracza\n");
		printf("2. Gracz na Komputer\n");
		printf("3. Zasady gry\n");
		printf("\nJezeli chcesz wylaczyc gre nacisnij ESC, ale pieskom bedzie wtedy bardzo smutno :(((\n");//granie ma emocjach graczy by trzymac ich w grze - ucze sie od najlepszych
		wybor = _getch();
		switch (wybor)
		{
		case '1'://tryb gracz na gracza
		{
			system("cls");
			struct Uzytkownik* Gracz1 = (struct Uzytkownik*)malloc(sizeof(struct Uzytkownik));
			struct Uzytkownik* Gracz2 = (struct Uzytkownik*)malloc(sizeof(struct Uzytkownik));
			Gracz_na_Gracza(&Gracz1, &Gracz2);
			usun_gracza(&Gracz1);//usuniecie struktury gracza 1
			usun_gracza(&Gracz2);//usuniecie struktury gracza 2
			printf("\n\nNacisnij dowolny przycisk by wroci do menu\n");
			_getch();
			system("cls");
			break;
		}
		case '2'://tryb gracz na komputer
		{
			system("cls");
			struct Uzytkownik* Gracz = (struct Uzytkownik*)malloc(sizeof(struct Uzytkownik));
			struct Komputer* Komputer = (struct Komputer*)malloc(sizeof(struct Komputer));
			Gracz_na_Komputer(&Gracz, &Komputer);
			usun_gracza(&Gracz);//usuwanie struktury gracza
			usun_komputer(&Komputer);//usuwanie struktury komputera
			printf("\n\nNacisnij dowolny przycisk by wroci do menu\n");
			_getch();
			system("cls");
			break;
		}
		case '3'://zasady gry
		{
			system("cls");
			printf("Zasady gry:\n");
			printf("1. Gra odbywa sie na planszy 10 x 10\n");
			printf("2. Gra jest mozliwa w trybie Gracz na Gracza oraz Gracz na Komputer.\n");
			printf("3. Kazdy gracz na starcie gry ustawia zestaw skladajacy sie z: \n");
			printf(" - Jednego statku zajmujacego cztery pola\n ");
			printf("- Dwoch statkow zajmujacych trzy pola\n");
			printf(" - Trzech statkow zajmujacych dwa pola\n");
			printf(" - Czterech statkow zajmujacych jedno pole\n");
			printf("4. Statki nie moga stykac sie ze soba.\n");
			printf("5. Gracz strzela w plansze przeciwnika, dopoki nie spudluje.\n");
			printf("6. Plansza wyswietlana jest przy uzyciu nastepnujacych znakow: \n");
			printf(" .  - oznacza puste pole\n");
			printf(" O  - oznacza pole zajete przez statek\n");
			printf("\033[1;34m");
			printf(" X ");
			printf("\033[0m");
			printf(" - oznacza trafiony statek\n");
			printf("\033[1;31m");
			printf(" X ");
			printf("\033[0m");
			printf(" - oznacza zatopiony statek oraz pola do okola niego\n");
			printf(" X  - oznacza pudlo\n");
			printf("7. Pierwsza osoba, ktora zatopi wszystkie statki przeciwnika - zdobedzie 20 punktow - wygrywa.\n");
			printf("8. Logi z ostatnio rozegranej gry sa dostepne w pliku logi.txt.\n");
			printf("\n\nNacisnij dowolny przycisk by wrocic do menu.");
			_getch();
			system("cls");
			break;
		}
		case 27://wyjscie z gry
		{
			exit(0);
			break;
		}
		default://wybor nie uwzgledniony w menu
		{
			system("cls");
			printf("Takiej opcji nie ma w menu!\n");
			printf("\n\nNacisnij dowolny przycisk by wrocic do menu.");
			_getch();
			system("cls");
			break;
		}
		}
	}
}