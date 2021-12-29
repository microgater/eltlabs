// Лабораторная работа №4
// Задача №2

/*
Функция получает строку текста и возвращает динамический массив указателей на слова. Каждое слово копируется в отдельный массив в динамической памяти.
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

char** DivideByWords(char* str)
{
	char **ppWord = NULL;
	int i, j, n, pos, numWords;

	// Cчитаем количество слов
	for (pos = 0, numWords = 0; *(str + pos); pos++)
	{
		if (*(str + pos) == ' ')
			numWords++;
	}
	numWords++;

	ppWord = (char**)malloc(sizeof(char*) * (numWords + 1)); // выделяем массив указателей
	*(ppWord + numWords) = NULL; // ограничиваем массив

	
	for (i = 0, pos = 0; i < numWords; i++) // Для каждого слова
	{
		for (j = 0, n = 0; *(str + pos + j) && *(str + pos + j) != ' '; j++) // считаем число букв
			n++;
		
		*(ppWord + i) = (char*)malloc(sizeof(char) * (n + 1)); // выделяем строку под слово
		*(*(ppWord + i) + n) = (char)(long) NULL; // ограничиваем массив

		for (j = 0; j < n; j++) // записываем слово в строку
		{
			*(*(ppWord + i) + j) = *(str + pos);
			pos++;
		}
		pos++;
	}

	return ppWord;
}

int main()
{
	char *str = "The quick brown fox jumps over the lazy dog";
	char **wordArray;
	int i = 0;

	wordArray = DivideByWords(str);

	while (*(wordArray + i) != NULL)
		printf("%s\n", *(wordArray + i++));

	return 0;
}
