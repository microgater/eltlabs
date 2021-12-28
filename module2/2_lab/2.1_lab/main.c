// Лабораторная работа №2
// Задание 1

/*
Определить структурированный тип и набор  функций для работы с таблицей записей, реализованной в массиве структур. В перечень функций входят:
* ввод записи таблицы с клавиатуры;
* загрузка и сохранение  таблицы в текстовом файле;
* просмотр таблицы;
* сортировка таблицы в порядке возрастания заданного поля;
* поиск в таблице элемента с заданным значением поля или с наиболее близким к нему по значению;
* удаление записи;
* изменение (редактирование) записи;
* вычисление с проверкой и использованием всех записей по заданному условию и формуле (например, общая сумма на всех счетах).

 Перечень полей структурированной переменной:
1. Фамилия, номер счета, сумма на счете, дата последнего изменения.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N 100 // число элементов в массиве
// #define MasAccountLength(mas) sizeof mas / sizeof (struct account)

struct date
{
	int day;
	int month;
	int year;
};

struct account
{
	char name[21]; // фамилия
	int accNumber; // номер счета
	double money;  // сумма на счете
	struct date lastChange; // дата последнего изменения
};

// Ввод записи таблицы с клавиатуры
// struct account *person - адрес начала массива структур person
int AddRecord(struct account *person)
{
	int i;
	for (i = 0; (person + i)->accNumber > 0; i++)
		if (i >= N)
			return -1;

	printf("Input person name: ");
	if (!scanf("%s", (person + i)->name))
		return -1;

	printf("Input accNumber: ");
	if (!scanf("%d", &(person + i)->accNumber))
		return -1;

	printf("Input money: ");
	if (!scanf("%lg", &(person + i)->money))
		return -1;

	printf("Input date of last change (DD.MM.YYYY): ");
	if (scanf("%2d.%2d.%4d", &(person + i)->lastChange.day, &(person + i)->lastChange.month, &(person + i)->lastChange.year) < 3)
		return -1;
	
	return 0;
}

// Загрузка таблицы из текстового файла
// struct account *person - адрес начала массива структур person
// int masLength - длина массива
// char *lpszFileName - указатель на строку с именем файла
int LoadTable(struct account *person, int masLength, char *lpszFileName)
{
	int i;
	FILE *pf;
	char str[100];

	pf = fopen(lpszFileName, "r");
	if (pf == NULL)
	{
		printf("Error opening table file!\n");
		return -2;
	}

	fgets(str, 100, pf);
	if (strcmp(str, "Table file\n"))
	{
		printf("This is not table file!\n");
		return -1;
	}
	fgets(str, 100, pf);
	fgets(str, 100, pf);
	fgets(str, 100, pf);

	for (i = 0; i < masLength && !feof(pf); i++)
		fscanf(pf, "|%*3d| %20s | %18d | %16lg |  %2d.%2d.%4d |\n",
		(person + i)->name, &(person + i)->accNumber, &(person + i)->money, &(person + i)->lastChange.day, &(person + i)->lastChange.month, &(person + i)->lastChange.year);

	fclose(pf);

	return 0; // read OK
}

// Сохранение таблицы в текстовом файле
// struct account *person - адрес начала массива структур person
// int masLength - длина массива
// char *lpszFileName - указатель на строку с именем файла
int SaveTable(struct account *person, int masLength, char *lpszFileName)
{
	int i;
	FILE *pf;

	pf = fopen(lpszFileName, "w+");
	if (pf == NULL)
	{
		printf("Error writing table file!\n");
		return -1;
	}

	fprintf(pf, "Table file\n\
----------------------------------------------------------------------------------\n\
| # |         Name         |   Account number   |       Money      | Last change |\n\
----------------------------------------------------------------------------------\n");
	for (i = 0; i < masLength && (person + i)->accNumber > 0; i++)
		fprintf(pf, "|%3d| %20s | %18d | %16.2f |  %02d.%02d.%4d |\n",
			i + 1, (person + i)->name, (person + i)->accNumber, (person + i)->money, (person + i)->lastChange.day, (person + i)->lastChange.month, (person + i)->lastChange.year);

	fclose(pf);

	return 0; // save OK
}

// Просмотр таблицы
// struct account *person - адрес начала массива структур person
// int masLength - длина массива
void ShowTable(struct account *person, int masLength)
{
	int i;
	printf("\
----------------------------------------------------------------------------------\n\
| # |         Name         |   Account number   |       Money      | Last change |\n\
----------------------------------------------------------------------------------\n");
	for (i = 0; i < masLength && (person + i)->accNumber > 0; i++)
		printf("|%3d| %20s | %18d | %16.2f |  %02d.%02d.%4d |\n",
			i + 1, (person + i)->name, (person + i)->accNumber, (person + i)->money, (person + i)->lastChange.day, (person + i)->lastChange.month, (person + i)->lastChange.year);
	printf("----------------------------------------------------------------------------------\n");
}

// Сортировка таблицы в порядке возрастания заданного поля
// struct account *person - адрес начала массива структур person
// int masLength - длина массива
// int field - поле, по которому производится сортировка:
// 1 - по номеру счета, 2 - по сумме на счету
void SortTable(struct account *person, int masLength, int field)
{
	int i, flag;
	struct account temp;
	switch (field)
	{
	case 1: // by account number
		// Внешний цикл. Выполняется, пока производятся перестановки пар. 
		do
		{
			flag = 0; // Сбрасываем влаг, сигнализирующий о наличии перестановок. 
			for (i = 0; i < masLength - 1 && (person + i + 1)->accNumber > 0; i++)
			{
				if ((person + i)->accNumber > (person + i + 1)->accNumber)
				{
					// Меняем элементы в паре местами.
					temp = *(person + i);
					*(person + i) = *(person + i + 1);
					*(person + i + 1) = temp;
					flag = 1;	 // Устанавливаем флаг.
				}
			}
		} while (flag);
		break;
	case 2: // by money
		do
		{
			flag = 0; // Сбрасываем влаг, сигнализирующий о наличии перестановок. 
			for (i = 0; i < masLength - 1 && (person + i + 1)->accNumber > 0; i++)
			{
				if ((person + i)->money > (person + i + 1)->money)
				{
					// Меняем элементы в паре местами.
					temp = *(person + i);
					*(person + i) = *(person + i + 1);
					*(person + i + 1) = temp;
					flag = 1;	 // Устанавливаем флаг.
				}
			}
		} while (flag);
		break;
	}
}

// Поиск в таблице элемента с заданным значением поля или с наиболее близким к нему по значению
// struct account *person - адрес начала массива структур person
// int masLength - длина массива
// int field - поле, по которому производится поиск:
// 1 - по номеру счета, 2 - по сумме на счету
int FindElement(struct account *person, int masLength, int field, double value)
{
	int i, found;
	double delta = 0;
	switch (field)
	{
	case 1: // account number
		for (i = 0; i < masLength && (person + i)->accNumber > 0; i++)
			if (abs((person + i)->accNumber - (int)value) < delta)
			{
				delta = abs((person + i)->accNumber - (int)value);
				found = i;
			}
		break;
	case 2: // money
		for (i = 0; i < masLength && (person + i)->accNumber > 0; i++)
			if (fabs((person + i)->money - value) < delta)
			{
				delta = fabs((person + i)->money - value);
				found = i;
			}
		break;
	default:
		return -1;
	}

	return found;
}

// Удаление записи
// struct account *person - адрес начала массива структур person
// int masLength - длина массива
// int i - номер записи для удаления
int DeleteRecord(struct account *person, int masLength, int i)
{
	if (i <= 0 || i > masLength)
	{
		printf("Wrong record number!\n");
		return -1;
	}
	for (; i <= masLength && (person + i)->accNumber > 0; i++)
	{
		strcpy((person + i - 1)->name, (person + i)->name);
		(person + i - 1)->accNumber = (person + i)->accNumber;
		(person + i - 1)->money = (person + i)->money;
		(person + i - 1)->lastChange.day = (person + i)->lastChange.day;
		(person + i - 1)->lastChange.month = (person + i)->lastChange.month;
		(person + i - 1)->lastChange.year = (person + i)->lastChange.year;
	}
	if (i < masLength)
		(person + i - 1)->accNumber = 0;

	return 0;
}

// Изменение (редактирование) записи
// struct account *person - адрес начала массива структур person
// int masLength - длина массива
// int i - номер записи для редактирования
int EditRecord(struct account *person, int masLength, int i)
{
	i--;
	if (i < 0 || i >= masLength || (person + i)->accNumber <= 0)
	{
		printf("Wrong record number!\n");
		return -1;
	}

	int option;

	printf("Person name: %s\nInput 1 to edit.\n", (person + i)->name);
	scanf("%d", &option);
	if (option == 1)
		if (!scanf("%20s", (person + i)->name))
			return -1;

	printf("accNumber: %d\nInput 1 to edit.\n", (person + i)->accNumber);
	scanf("%d", &option);
	if (option == 1)
		if (!scanf("%18d", &(person + i)->accNumber))
			return -1;

	printf("Money: %.2f\nInput 1 to edit.\n", (person + i)->money);
	scanf("%d", &option);
	if (option == 1)
		if (!scanf("%16lg", &(person + i)->money))
			return -1;

	printf("Date of last change (DD.MM.YYYY): %02d.%02d.%4d\nInput 1 to edit.\n", (person + i)->lastChange.day, (person + i)->lastChange.month, (person + i)->lastChange.year);
	scanf("%d", &option);
	if (option == 1)
		if (scanf("%2d.%2d.%4d", &(person + i)->lastChange.day, &(person + i)->lastChange.month, &(person + i)->lastChange.year) < 3)
			return -1;

	return 0;
}

// Вычисление общей суммы на всех счетах
// struct account *person - адрес начала массива структур person
// int masLength - длина массива
double SumAllMoney(struct account *person, int masLength)
{
	int i;
	double sum = 0;

	for (i = 0; i < masLength && (person + i)->accNumber > 0; i++)
		sum += (person + i)->money;

	return sum;
}

int main()
{
	struct account person[N] = { 0 };
	int option = -1;
	double value;
	int i;

	while (option)
	{
		printf("\n\
Choose option:\n\
1) Add new record\n\
2) Load table from file\n\
3) Save table to file\n\
4) Show table\n\
5) Sort table\n\
6) Find element\n\
7) Delete record\n\
8) Edit record\n\
9) Calculate all money\n\
0) Exit\n");

		if (!scanf("%d", &option))
			scanf("%*c"); // защита от зацикливания
		else
		switch (option)
		{
		case 1:
			if (AddRecord(person))
				printf("Error!\n");
			break;
		case 2:
			LoadTable(person, N, "Table_file.txt");
			break;
		case 3:
			SaveTable(person, N, "Table_file.txt");
			break;
		case 4:
			ShowTable(person, N);
			break;
		case 5:
			printf("\
Sort:\n\
1) By account number\n\
2) By money\n");
			scanf("%d", &option);
			SortTable(person, N, option);
			break;
		case 6:
			printf("\
Find:\n\
1) account number\n\
2) money\n");
			scanf("%d", &option);
			printf("Input value: ");
			scanf("%16lg", &value);
			i = FindElement(person, N, option, value);
			if (i >= 0)
				printf("|%3d| %20s | %18d | %16.2f |  %02d.%02d.%4d |\n",
					i + 1, (person + i)->name, (person + i)->accNumber, (person + i)->money, (person + i)->lastChange.day, (person + i)->lastChange.month, (person + i)->lastChange.year);
			else
				printf("Error!\n");
			break;
		case 7:
			printf("Choose record: ");
			scanf("%d", &i);
			DeleteRecord(person, N, i);
			break;
		case 8:
			printf("Choose record: ");
			scanf("%d", &i);
			EditRecord(person, N, i);
			break;
		case 9:
			printf("Sum: %.2f\n", SumAllMoney(person, N));
			break;
		case 0:
			break;
		default:
			printf("No option was picked.\n");
			//option = -1;
		}
	}

	return 0;
}
