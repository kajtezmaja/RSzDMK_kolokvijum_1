/**
 * @file tajmer0_biblioteka.c
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

/// Promenljiva koja skladisti broj milisekundi proteklih od pokretanja aplikacije
volatile unsigned long ms = 0;

/**
 * pinInit - Funkcija koja implementiran inicijalizaciju pina
 * @param port - ulaz tipa unsigned char - Port na kojem je pin koji je potrebno inicijalizovati
 * @param pin - ulaz tipa unsigned char - Pin koji je potrebno inicijalizovati
 * @param direction - ulaz tipa unsigned char - Smer prema kojem je potrebno inicijalizovati pin
 * @return Nema povratnu vrednost
 */
void pinInit(unsigned char port, unsigned char pin, unsigned char direction);

/**
 * timer0DelayMs - Funkcija koja implementira pauzu u broju milisekundi koji je prosledjen
 * kao parametar
 * @param delay_length - ulaz tipa unsigned long - Duzina pauze u milisekundama
 * @return Povratna vrednost je tipa unsigned long i ima vrednost broja milisekundi
 * proteklih od pocetka aplikacije do trenutka izlaska iz funkcije
 */
unsigned long timer0DelayMs(unsigned long delay_length);

/**
 * timer0InteruptInit - Funkcija koja inicijalizuje timer 0 tako da pravi prekide
 * svake milisekunde
 * @return Nema povratnu vrednost
 */
void timer0InteruptInit();

/**
 * calculateHalfPeriod - Funkcija koja izracunava polovinu prosledjene periode
 * @param period - input tipa unsigned long - Duzina periode
 * @return Povratna vrednost je tipa unsigned long i predstavlja polovinu periode
 */
unsigned long calculateHalfPeriod(unsigned long period)	;

/******************************************************************************************/

unsigned long timer0DelayMs(unsigned long delay_length)
{
    unsigned long t0; // Trenutak pocevsi od kog se racuna pauza

    // Implementacija pauze
    t0 = ms;
    while ((ms - t0) < delay_length)
    ;  // Pauza delay_length milisekundi

    return ms;
}

/******************************************************************************************/

void timer0InteruptInit()
{
    // Inicijalizacija tajmera 0 tako da perioda prekida bude 1ms
    TCCR0A = 0x02;
    TCCR0B = 0x03;
    OCR0A = 249;
    TIMSK0 = 0x02;

    // Podesavanje globalne dozvole prekida
    sei();
}

/******************************************************************************************/

/**
 * ISR - prekidna rutina tajmera 0 u modu CTC
 */
ISR(TIMER0_COMPA_vect)
{
    // Inkrementovanje broja milisekundi koje su prosle od pokretanja aplikacije
    ms++;
}

/******************************************************************************************/

unsigned long calculateHalfPeriod(unsigned long period)
{
	return (period/2);
}
