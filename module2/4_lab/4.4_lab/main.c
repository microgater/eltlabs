// Лабораторная работа №4
// Задача №4

/*
4. Функция находит в строке фрагменты, симметричные относительно центрального символа, длиной 7 и более символов (например, "abcdcba") и возвращает динамический массив указателей на копии таких фрагментов.
*/

#define _CRT_SECURE_NO_WARNINGS // отключение предупрежедний о небезопасности scanf в visual studio
#include <stdio.h>
#include <stdlib.h>

// Функция находит в строке фрагменты, симметричные относительно центрального символа, длиной 7 и более символов
// и возвращает динамический массив указателей на копии таких.
char** FindSymmetricalParts(char* str)
{
	char **ppSym;
	int symParts = 0; // количество повторяющихся фрагментов
	int symLength = 0; // длина повторяющегося фрагмента
	int i, j, k;

	// Считаем количество повторяющихся фрагментов в строке
	for (i = 3; *(str + i) != 0; i++) // начинаем с 4 центрального символа и пока не дойдем до конца строки
	{
		symLength = 1; // центральный символ уже есть
		for (j = 1; j - i <= 0 && (str + i + j) != 0; j++) // не выходим за пределы строки
		{
			if (*(str + i - j) == *(str + i + j))
				symLength += 2;
			else
				break;
		}
		if (symLength >= 7)
			symParts++;
	}

	// Выделяем память под массив указателей на начала строк.
	// Последний элемент массива - нуль для обозначения конца массива.
	if (!(ppSym = (char**)malloc(sizeof(char*) * (symParts + 1))))
	{
		printf("Pointer malloc error!");
		return NULL;
	}
	
	for (k = 0, i = 3; k < symParts; k++, i++)
	{
		for (; *(str + i) != 0; i++)
		{
			symLength = 1;
			for (j = 1; j - i <= 0 && (str + i + j) != 0; j++)
			{
				if (*(str + i - j) == *(str + i + j))
					symLength += 2;
				else
					break;
			}
			if (symLength >= 7)
				break;
		}

		// Под каждую симметричную строку выделяем новый объем памяти
		// и записываем указатель на строку в массив указателей.
		if (!(*(ppSym + k) = (char*)malloc(sizeof(char) * (symLength + 1))))
		{
			printf("String malloc error!");
			return NULL;
		}
		// Копируем симметричные части в отдельные строки
		for (j = -i; j <= (symLength - 1) / 2; j++)
		{
			*(*(ppSym + k) + (symLength - 1) / 2 + j) = *(str + i + j);
		}
		*(*(ppSym + k) + (symLength - 1) / 2 + j) = 0; // обозначаем конец строки
	}
	*(ppSym + k) = 0; // указываем конец массива указателей

	return ppSym;
}

int main()
{
	char str[] = "abcdcbaqwertytrewqzxcvbvcxz";
	char **ppSymmetry;

	ppSymmetry = FindSymmetricalParts(str);
	if (*ppSymmetry)
	{
		printf("Symmetrical parts:\n");
		// Выводим строки пока не дойдем до нулевого указателя
		for (int i = 0; *(ppSymmetry + i) != 0; i++)
			printf("%s\n", *(ppSymmetry + i));
	}
	else
		printf("There is no symmetrical parts.\n");

	return 0;
}
