/**
* @file main.c
* @brief Ovo je glavna datoteka
* @author Marijana Kajtez
* @date 16.05.2021.
* @version 1.0
*/

#include <avr/io.h>
#include <util/delay.h>
#include "../serijska_kom/serijska_kom_drajver.h"
#include "../upravljanje_pinovima/upravljanje_pinovima_drajver.c"
#include "../tajmer0_biblioteka/tajmer0_biblioteka.c"
#include "../util_biblioteka/util_biblioteka.c"

/**
* main - funkcija koja implementiran glavni deo aplikacije
* @return Nema povratnu vrednost
*/
int main()
{
	int16_t duzina;
	int16_t niz[64];
	int16_t str[64];
	int8_t rez;
	// Inicijalizacija
	usartInit(9600);

	// Glavna petlja
	while(1)
	{
		usartPutString("Unesite duzinu niza: \r\n");
		while (!usartAvailable());

		_delay_ms(100);

		duzina = usartParseInt();

		usartPutString("Unesite niz: \r\n");
		PORTB |= 1 << 5; //LED ON
		while (!usartAvailable());
		PORTB &= ~(1 << 5); //LED OFF

		usartGetString(niz);
		Sort(niz, duzina, UP);
		rez = Check(niz, duzina);






		}




 return 0;
}

