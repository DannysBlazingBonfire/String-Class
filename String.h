#pragma once
#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <cassert>

class String
{
public:
	//Default konstruktor
	String();
	//Copy konstruktor
	String(const String& rhs);
	//cstr avslutas med '\0'
	String(const char* cstr);
	//Destruktor. Avallokera heap-minne.
	~String();
	//Copy assignment operator
	String& operator=(const String& rhs);
	//indexerar utan range check
	char& operator[](size_t i);
	//indexerar utan range check
	const char& operator[](size_t i) const;
	//Hur många tecken i strängen
	size_t size() const;
	//Hur mycket plats finns det
	size_t capacity() const;
	//lägger till ett tecken sist
	void push_back(char c);
	//debug print function
	void print() const;
	//(För testning) Ger en pekare till arrayen som innehåller
	//strängen, ej avslutad med '\0'.
	const char* data() const;
	//Out-of-class definition
	friend bool operator==(const String& lhs,
		const String& rhs);
	//Out-of-class definition
	friend bool operator!=(const String& lhs,
		const String& rhs);

	friend std::ostream& operator<<(std::ostream& out, 
		const String& rhs);

	//String literal - pekare
	char* cstrPtr;
	size_t strSize;
	size_t strcapacity;

private:
	void Invariant();
};

#endif