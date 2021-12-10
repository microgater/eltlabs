// Лабораторная работа №3
// Задача №1

#define _CRT_SECURE_NO_WARNINGS // отключение предупрежедний о небезопасности scanf в visual studio
#include <stdio.h>
#include <malloc.h>

char* dataInput(void)
{
	int row, column;
	int i, j;
	char *pbyte = NULL;
	int *pint;
	double *pdouble;

	printf("Input number of rows: ");
	if (!scanf("%d", &row))
		return NULL;
	printf("Input number of columns: ");
	if (!scanf("%d", &column))
		return NULL;

	if (!(pbyte = (char*)malloc(sizeof(double) * row*column + sizeof(int) * 2))) // выделяем массив байтов
	{
		printf("Malloc error!");
		return NULL;
	}
	pint = (int*)pbyte;
	
	// Заносим размер матрицы в первые два элемента массива
	*pint++ = row; // *pint = row; pint++;
	*pint++ = column;

	pdouble = (double*)pint;

	for (i = 0; i < row; i++)
	{
		printf("Input values of row %d:\n", i + 1);
		for (j = 0; j < column; j++)
			if (!scanf("%lg", pdouble++))
				return NULL;
	}

	return pbyte;
}

void dataOutput(char *pbyte)
{
	int *pint;
	double *pdouble;
	int i, j;
	int row, column;

	pint = (int*)pbyte;
	
	row = *pint++;
	column = *pint++;

	pdouble = (double*)pint;

	printf("\nMatrix:\n");
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < column; j++)
			printf("%10.2f ", *pdouble++);
			printf("\n");
	}
}

int main()
{
	char *byteArr1;

	if (!(byteArr1 = dataInput()))
		return -1;

	dataOutput(byteArr1);

	return 0;
}