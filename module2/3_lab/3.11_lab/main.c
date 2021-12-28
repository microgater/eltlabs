// Лабораторная работа №3
// Задача №11

/*
Упаковка переменных различного типа в заданном формате

Разработать две функции, одна из которых вводит с клавиатуры набор данных в произвольной последовательности и размещает в памяти в заданном формате. Другая функция читает  эти  данные  и выводит на экран. Программа запрашивает и размещает в памяти несколько наборов данных при помощи первой функции, а затем читает их и выводит на экран при помощи второй. Размещение данных производить в выделенном массиве байтов с  контролем  его переполнения.


11. В начале области памяти размещается форматная строка. Выражение "%nnnd", где nnn - целое - определяет массив из nnn целых чисел, "%d" - одно целое число, "%nnnf" - массив из nnn вещественных чисел, "%f" - одно вещественное число. Сразу же вслед за строкой размещается последовательность целых, вещественных и их массивов в соответствии с заданным форматом.
*/

#define _CRT_SECURE_NO_WARNINGS // отключение предупрежедний о небезопасности scanf в visual studio
#include <stdio.h>
#include <malloc.h>

void* dataInput()
{
	int numberOfElements;
	int numType;
	char *formatStr = 0;
	int *pint;
	double *pdouble;
	int i;

	printf("Choose number type:\n\
1) integer\n\
2) float\n");
	if (!scanf("%d", &numType))
		return NULL;
	printf("Input number of elements: ");
	if (!scanf("%d", &numberOfElements))
		return NULL;

	switch (numType)
	{
	case 1: // integer
		if (numberOfElements == 1)
		{
			if (!(formatStr = (char*)malloc(sizeof(char) * 3 + sizeof(int)))) // выделяем место
			{
				printf("Malloc error!\n");
				return NULL;
			}
			sprintf(formatStr, "%%d");
			pint = (int*)(formatStr + 3);
			printf("Input integer number: ");
			if (!scanf("%d", pint))
				return NULL;
		} else if (numberOfElements > 0 && numberOfElements < 1000)
		{
			if (!(formatStr = (char*)malloc(sizeof(char) * 6 + sizeof(int) * numberOfElements*numType))) // выделяем место
			{
				printf("Malloc error!\n");
				return NULL;
			}
			sprintf(formatStr, "%%%03dd", numberOfElements);
			pint = (int*)(formatStr + 6);
			printf("Input integer numbers:\n");
			for (i = 0; i < numberOfElements; i++)
				if (!scanf("%d", pint++))
					return NULL;
		}
		else
		{
			printf("Wrong number of elements!");
			return NULL; // ошибка
		}
		break;

	case 2: // float
		if (numberOfElements == 1)
		{
			if (!(formatStr = (char*)malloc(sizeof(char) * 3 + sizeof(double)))) // выделяем место
			{
				printf("Malloc error!\n");
				return NULL;
			}
			sprintf(formatStr, "%%f");
			pdouble = (double*)(formatStr + 3);
			printf("Input float point number: ");
			if (!scanf("%lg", pdouble))
				return NULL;
		}
		else if (numberOfElements > 0 && numberOfElements < 1000)
		{
			if (!(formatStr = (char*)malloc(sizeof(char) * 6 + sizeof(double) * numberOfElements*numType))) // выделяем место
			{
				printf("Malloc error!\n");
				return NULL;
			}
			sprintf(formatStr, "%%%03df", numberOfElements);
			pdouble = (double*)(formatStr + 6);
			printf("Input float point numbers:\n");
			for (i = 0; i < numberOfElements; i++)
				if (!scanf("%lg", pdouble++))
					return NULL;
		}
		else
		{
			printf("Wrong number of elements!");
			return NULL; // ошибка
		}
		break;

	default:
		printf("Wrong number type!");
		return NULL; // ошибка
	}

	return formatStr;
}

int dataOutput(void *format)
{
	int numberOfElements = 0;
	char *formatStr;
	int *pint;
	double *pdouble;
	int i;

	formatStr = (char*)format;
	if (*formatStr != '%')
	{
		printf("It's not a format string!");
		return -1;
	}
	if (*(formatStr + 1) >= '0' && *(formatStr + 1) <= '9')
	{
		for (i = 3; i > 0; i--)
			numberOfElements += (int)(*(formatStr + i) - '0');
		if (*(formatStr + 4) == 'd')
		{
			pint = (int*)(formatStr + 6);
			for (i = 0; i < numberOfElements; i++)
				printf("%d\n", *(pint + i));
		}
		else if (*(formatStr + 4) == 'f')
		{
			pdouble = (double*)(formatStr + 6);
			for (i = 0; i < numberOfElements; i++)
				printf("%.2f\n", *(pdouble + i));
		}
		else
			return -2;
	}
	else if (*(formatStr + 1) == 'd')
	{
		pint = (int*)(formatStr + 3);
		printf("%d\n", *pint);
	}
	else if (*(formatStr + 1) == 'f')
	{
		pdouble = (double*)(formatStr + 3);
		printf("%.2f\n", *pdouble);
	}
	else
		return -2;

	return 0;
}

int main()
{
	void *format;
	if (!(format = dataInput()))
		return -1;

	printf("\nOutput:\n");
	if (dataOutput(format))
		return -1;

	return 0;
}
