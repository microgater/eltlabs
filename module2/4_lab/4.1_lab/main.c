// Лабораторная работа №4
// Задача №1

/*
Функция получает линейный массив целых, находит в нем последовательности подряд возрастающих значений и возвращает их в динамическом массиве указателей на линейные массивы (аналог двумерного массива). В каждом из линейных динамических массивов содержится копия возрастающей последовательности, начиная с индекса 1, а под индексом 0 содержится его длина. Невозрастающие значения включаются в отдельный массив, добавляемый в конец (или начало) массива указателей.
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define N 100 // размер массива

// return = | размер n | &возраст.посл-ность 1 | &возраст.посл-ность 2 | ... | &возраст.посл-ность n | невозраст.значения |
// посл-ность = | размер m | число 1| число 2 | ... | число m |
int** FindSequences(int* mas, int masSize)
{
	int inc_counter = 0, // счетчик чисел в возрастающей последовательности
		normal_counter = 0, // счетчик обычных чисел
		inc_size = 0, // размер массива для возарастающих последовательностей
		i, j, k;
	int **ppSeq = NULL;

	// Считаем количество поседовательностей
	for (i = 1; i < masSize; i++)
	{
		if (*(mas + i - 1) + 1 == *(mas + i)) // найдено число возрастающей последовательности
			inc_counter++;
		else
			if (inc_counter > 0) // найден конец последовательности
			{
				inc_size++;
				inc_counter = 0;
			}
			else // найдено обычное число
			{
				normal_counter++;
			}
	}
	if (inc_counter)
	{
		inc_size++;
		normal_counter--;
		inc_counter = 0;
	}

	if(!(ppSeq = (int**)malloc(sizeof(int*) * (inc_size + 2)))) // выделяем память под массив указателей
	{
		printf("Malloc error!");
		return NULL;
	}

	if (!(*ppSeq = (int*)malloc(sizeof(int) * (inc_size + 2)))) // выделяем память под размер
	{
		printf("Malloc error!");
		return NULL;
	}
	**ppSeq = inc_size; // первая ячейка массива указателей - его размер

	// последняя ячейка массива указателей - указатель на массив обычных чисел
	if(!(*(ppSeq + inc_size + 1) = (int*)malloc(sizeof(int) * (normal_counter + 1)))) // выделяем память под массив обычных чисел;
	{
		printf("Malloc error!");
		return NULL;
	}


	**(ppSeq + inc_size + 1) = normal_counter + 1; // вносим размер последовательности обычных чисел
	normal_counter = 1;

	// Заносим возрастающие последовательности в массивы
	for (i = 1, j = 1; i < masSize; i++)
	{
		if (*(mas + i - 1) + 1 == *(mas + i)) // найдено число возрастающей последовательности
		{
			inc_counter++;
		}
		else
			if (inc_counter > 0) // найден конец последовательности
			{
				if(!(*(ppSeq + j) = (int*)malloc(sizeof(int) * (inc_counter + 2)))) // выделяем память под j-ую возрастающую последовательность
				{
					printf("Malloc error!");
					return NULL;
				}
				**(ppSeq + j) = inc_counter + 1; // вносим размер последовательности
				for (k = 0; k <= inc_counter; k++)
					*(*(ppSeq + j) + k + 1) = *(mas + i - inc_counter + k - 1);
				inc_counter = 0;
				j++;
			}
			else // найдено обычное число
			{
				*(*(ppSeq + inc_size + 1) + normal_counter++) = *(mas + i - 1);
			}
	}

	if (inc_counter)
	{
		if (!(*(ppSeq + j) = (int*)malloc(sizeof(int) * (inc_counter + 2)))) // выделяем память под j-ую возрастающую последовательность
		{
			printf("Malloc error!");
			return NULL;
		}
		**(ppSeq + j) = inc_counter + 1; // вносим размер последовательности
		for (k = 0; k <= inc_counter; k++)
			*(*(ppSeq + j) + k + 1) = *(mas + i - inc_counter + k - 1);
	}
	else
		*(*(ppSeq + inc_size + 1) + normal_counter++) = *(mas + i - 1);

	return ppSeq;
}

int main()
{
	int mas [N] = {
		91, 61, 68, 50, 63, 47, 12, 34, 52, 80,
		 1,  2, 42, 28, 18, 29, 33, 76, 72, 36,
		44, 96, 87, 45, 79,  6, 99, 25,  5, 70,
		1,  2,  3,  4,  75, 49, 19, 43, 57, 81,
		54,  9, 86, 69, 64, 98, 14, 62, 73, 78,
		22, 23, 24, 25, 26, 41, 94, 16, 46, 13,
		78, 79, 80, 56, 57, 58, 59, 60, 61, 62,
		88, 38, 40, 30, 32, 23, 74, 95, 17,  3,
		83, 77,  2, 93, 48, 59,  7, 20, 92, 27,
		67, 82, 22,  8, 53, 11, 66, 37, 20, 22};
	int **pMas;
	int i, j;

	pMas = FindSequences(mas, N);

	printf("Increasing sequences:\n");
	for (i = 1; i <= **pMas; i++)
	{
		for (j = 1; j <= **(pMas + i); j++)
			printf("%d ", *(*(pMas + i) + j));
		printf("\n");
	}
	printf("\nOther numbers:\n");
	for (j = 1; j <= **(pMas + i); j++)
		printf("%d ", *(*(pMas + i) + j));
	printf("\n");
		
	return 0;
}
