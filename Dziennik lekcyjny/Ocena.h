#pragma once
#include <iostream>
#include <Windows.h>
class Ocena
{
	float ocena;
	int rodzaj;
public:	
	Ocena* pNext;
	Ocena();
	Ocena(float, int);
	std::ostream& operator<<(std::ostream&);
	std::string pisemna_ocena(float);
	Ocena& operator=(const Ocena&);
	bool operator>(const Ocena&);
	float operator+=(float);
	bool operator==(int);
	bool operator==(float);
};	

