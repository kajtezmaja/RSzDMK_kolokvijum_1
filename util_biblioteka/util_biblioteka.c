/**
 * @file util_biblioteka.c
 * @brief
 * @author Marjana Kajtez
 * @date 16.05.2021.
 * @version 1.0
 */
#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>

/// Makro za podesavanje moda niza
#define UP 1
/// Makro za podesavanje moda niza
#define DOWN 0

#define TRUE 1

#define FALSE 0


/**
 * Sort - Funkcija koja sortira niz array duzine array_length na nacin odabran parametrom mode
 * @param array
 * @param array_length
 * @param mode
 * @return Nema povratnu vrednost
 */
void Sort(int16_t *array, int16_t array_length, int8_t mode)
{
	int16_t i = 0, j = 0, tmp;
	for (i = 0; i < array_length; i++)
	{
		for (j = 0; j < array_length - i - 1; j++)
		{
			if(UP){
				if (array[j] > array[j + 1])
				{
					tmp = array[j];
					array[j] = array[j + 1];
					array[j + 1] = tmp;
				}
			} else
			{
				if (array[j] < array[j + 1])
					{
						tmp = array[j];
						array[j] = array[j + 1];
						array[j + 1] = tmp;
				}
			}
		}
	}
}


/**
 * Check - Funkcija koja vrsi proveru da li je uneti niz aritmeticki
 * @param array - niz koji treba proveriti da li je aritmeticki
 * @return Vrednosti TRUE ili FALSE
 */
int8_t Check(int16_t *array, int16_t array_length)
{
	int16_t razlika = array[1] - array[0];
	int16_t i = 0;
	for (i = 0; i < array_length - 1; i++)
	{
		if (array[i + 1] - array[i] != razlika)
		{
			return FALSE;
		}
		i++;
	}
	return TRUE;
}












