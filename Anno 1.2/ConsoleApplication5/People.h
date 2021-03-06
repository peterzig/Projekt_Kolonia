#ifndef People_h
#define People_h

class People
{
protected:
	int number;					// liczba mieszkancow
	int tax;					// podatek od mieszkanca
	// tutaj dynamiczna tablica z id surowcow pobieranych jako potrzeby

public:
	People(int);
	int getNumber() const;		
	int getTax() const;			// pobiera calkowita kwote podatku jaka placi dana klasa mieszkancow
	void increase(int);			// zwieksza liczbe mieszkancow o podana wartosc
	void setNumber(int);		// ustawia liczbe mieszkancow na konkretna wartosc
	void test() const;
};

#endif