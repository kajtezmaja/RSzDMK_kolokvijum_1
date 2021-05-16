/**
 * @file upravljanje_pinovima_drajver.c
 * @brief Aplikacija koja implementira podesavanje smera i vrednosti pina
 * @author Marjana Kajtez
 * @date 16.05.2021.
 * @version 1.0
 */
#include <avr/io.h>
#include <avr/interrupt.h>

/// Makro za podesavanje visoke vrednosti signala na pinu
#define HIGH 1
/// Makro za podesavanje niske vrednosti signala na pinu
#define LOW 0

/// Makro za podesavanje izlaznog smera pina
#define OUTPUT 1
/// Makro za podesavanje ulaznog smera pina
#define INPUT 0

/// Makro za selektovanje porta B
#define PORT_B 0
/// Makro za selektovanje porta C
#define PORT_C 1
/// Makro za selektovanje porta D
#define PORT_D 2

/// Makro za selektovanje pina na koji je povezana dioda
#define DIODE_PIN 5

/// Makro za podesavanje periode u brzom rezimu treptanja
#define FAST 200
/// Makro za podesavanje periode u sporom rezimu treptanja
#define SLOW 1000

/// Makro za podesavanje broja brzih treptaja
#define FAST_REPETITIONS 15
/// Makro za podesavanje broja sporih treptaja
#define SLOW_REPETITIONS 3

/**
 * pinPulsing - Funkcija koja implementira num_of_repetitions perioda podizanja i spustanja vrednosti na pinu
 * odgovarajucom brzinom
 * @param port - ulaz tipa unsigned char - Port na kojem je potrebno implementirati funkcionalnost
 * @param pin - ulaz tipa unsigned char - Pin na kojem je potrebno implementirati funkcionalnost
 * @param period - ulaz tipa unsigned long - Perioda promene vrednosti na pinu
 * @param num_of_repetitions - ulaz tipa unsigned char - Broj perioda koje je potrebno implementirati
 * @return Nema povratnu vrednost
 */
void pinPulsing(unsigned char port, unsigned char pin, unsigned long period, unsigned char num_of_repetitions);

/**
 * pinPulse - Funkcija koja implementiran podizanje i spustanje vrednosti na pinu
 * odgovarajucom brzinom
 * @param port - ulaz tipa unsigned char - Port na kojem je potrebno implementirati funkcionalnost
 * @param pin - ulaz tipa unsigned char - Pin na kojem je potrebno implementirati funkcionalnost
 * @param period - ulaz tipa unsigned long - Perioda promene vrednosti na pinu
 * @return Nema povratnu vrednost
 */
void pinPulse(unsigned char port, unsigned char pin, unsigned long period);

/**
 * pinSetValue - Funkcija koja postavlja vrednost na pinu
 * @param port - ulaz tipa unsigned char - Port na kojem je pin ciju vrednost potrebno postaviti
 * @param pin - ulaz tipa unsigned char - Pin ciju je vrednost potrebno postaviti
 * @param value - ulaz tipa unsigned char - Vrednost koju je potrebno postaviti na pin
 * @return Nema povratnu vrednost
 */
void pinSetValue(unsigned char port, unsigned char pin, unsigned char value);

/**
 * pinInit - Funkcija koja implementiran inicijalizaciju pina
 * @param port - ulaz tipa unsigned char - Port na kojem je pin koji je potrebno inicijalizovati
 * @param pin - ulaz tipa unsigned char - Pin koji je potrebno inicijalizovati
 * @param direction - ulaz tipa unsigned char - Smer prema kojem je potrebno inicijalizovati pin
 * @return Nema povratnu vrednost
 */
void pinInit(unsigned char port, unsigned char pin, unsigned char direction);


/******************************************************************************************/

void pinPulsing(unsigned char port, unsigned char pin, unsigned long period, unsigned char num_of_repetitions)
{
	unsigned char i;

	// Implementacija num_of_repetitions perioda
	for (i = 0; i < num_of_repetitions; i++)
		pinPulse(port, pin, period);
}

/******************************************************************************************/

void pinPulse(unsigned char port, unsigned char pin, unsigned long period)
{
    // Poluperioda u kojoj pin ima visoku vrednost
    pinSetValue(port, pin, HIGH);
    timer0DelayMs(calculateHalfPeriod(period));

    // Poluperioda u kojoj pin ima nisku vrednost
    pinSetValue(port, pin, LOW);
    timer0DelayMs(calculateHalfPeriod(period));
}

/******************************************************************************************/

void pinSetValue(unsigned char port, unsigned char pin, unsigned char value)
{
    // Postavljanje vrednosti pina
    switch(port)
    {
    case PORT_B:
        if (value == HIGH)
            PORTB |= 1 << pin;
        else
            PORTB &= ~(1 << pin);
        break;
    case PORT_C:
        if (value == HIGH)
            PORTC |= 1 << pin;
        else
            PORTC &= ~(1 << pin);
        break;
    case PORT_D:
        if (value == HIGH)
            PORTD |= 1 << pin;
        else
            PORTD &= ~(1 << pin);
        break;
    default:
        break;
    }
}

/******************************************************************************************/

void pinInit(unsigned char port, unsigned char pin, unsigned char direction)
{
    // Inicijalizacija smera pina
    switch (port)
    {
    case PORT_B:
        if (direction == OUTPUT)
            DDRB |= 1 << pin;
        else
            DDRB &= ~(1 << pin);
        break;
    case PORT_C:
        if (direction == OUTPUT)
            DDRC |= 1 << pin;
        else
            DDRC &= ~(1 << pin);
        break;
    case PORT_D:
        if (direction == OUTPUT)
            DDRD |= 1 << pin;
        else
            DDRD &= ~(1 << pin);
        break;
    default:
        break;
    }

}

