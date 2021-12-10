/* Лабораторная работа №1
   Защита

Написать 4 функции для работы с массивами через указатели:
1. Обращение к элементу массива
2. Присваивание значения элементу массива
3. Удаление (зануление)
4. Длина
*/

#include <stdio.h>

#define GetLength(mas) sizeof mas / sizeof *mas

int GetElement(int *mas, int elem)
{
	return *(mas + elem);
}

void AssignValue(int *mas, int elem, int value)
{
	*(mas + elem) = value;
}

void DeleteElem(int *mas, int elem)
{
	*(mas + elem) = 0;
}

//int GetLength(int *mas)
//{
//	/*int i, length = 0;
//	for (i = 0; *(mas + i); i++)
//		length++;
//
//	return length;*/
//	return (int)(sizeof(mas) / sizeof(*mas));
//}

int main()
{
	//char mas1[] = "12345";
	int mas2[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int i;

	printf("%d\n", GetElement(mas2, 4));

	AssignValue(mas2, 5, 2);
	for (i = 0; i < 10; i++)
		printf("%d ", *(mas2 + i));
	printf("\n");

	DeleteElem(mas2, 6);
	for (i = 0; i < 10; i++)
		printf("%d ", *(mas2 + i));
	printf("\n");

	printf("%d", GetLength(mas2));

	return 0;
}