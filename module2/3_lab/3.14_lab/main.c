// Лабораторная работа №3
// Задача №14

#define _CRT_SECURE_NO_WARNINGS // отключение предупрежедний о небезопасности scanf в visual studio
#include <stdio.h>

int dataInput(char *pbyte)
{
	int row, column;
	int i, j; // x, y
	double value;
	int *pNonZeroAmount;
	int *pint;
	double *pdouble;

	printf("Input number of rows: ");
	if (!scanf("%d", &row))
		return -1;
	printf("Input number of columns: ");
	if (!scanf("%d", &column))
		return -1;

	pint = (int*)pbyte;

	// Заносим размер матрицы в первые два элемента массива
	*pint++ = row; // *pint = row; pint++;
	*pint++ = column;
	pNonZeroAmount = pint++;

	for (i = 0; i < row; i++)
	{
		printf("Input values of row %d:\n", i + 1);
		for (j = 0; j < column; j++)
		{
			if (!scanf("%lg", &value))
				return -1;
			if (value)
			{
				++*pNonZeroAmount; // (*pNonZeroAmount)++;

				*pint++ = i; // x
				*pint++ = j; // y
				pdouble = (double*)pint;
				*pdouble++ = value; // value
				pint = (int*)pdouble;
			}
		}
	}
	return 0;
}

void dataOutput(char *pbyte)
{
	int *pint;
	double *pdouble;
	int i, j;
	int row, column;
	int nonZeroAmount;

	pint = (int*)pbyte;

	row = *pint++;
	column = *pint++;
	nonZeroAmount = *pint++;

	pdouble = (double*)pint;

	printf("\nMatrix:\n");
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < column; j++)
		{
			if (nonZeroAmount-- && i == *pint && j == *(pint+1))
			{
				pint += 2;
				pdouble = (double*)pint;
				printf("%10.3f ", *pdouble++);
				pint = (int*)pdouble;
			}
			else
				printf("%10.2f ", (double)0);
		}
		printf("\n");
	}
}

int main()
{
	char byteArr1[1001];

	if (dataInput(byteArr1))
		return -1;
	dataOutput(byteArr1);

	return 0;
}