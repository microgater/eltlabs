// Бабенко В.Ю., РЭ3-91
// Контрольная работа
// Цифровая подпись на основе алгоритма Эль-Гамаля

#define _CRT_SECURE_NO_WARNINGS // отключение предупреждений Visual Studio о небезопасности fscanf
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Greatest common divisor - наибольший общий делитель
// int a, b - числа
int gcd(int a, int b) {
	int c;
	do
	{
		c = a % b;
		a = b;
		b = c;
	} while (c);

	return abs(a);
}

// Быстрое возведение в степень
// a - основание
// b - степень
long long FastPow(long long a, long long b)
{
	if (b == 0)
		return 1;

	if (b % 2 == 0)
		return FastPow(a * a, b / 2);

	return a * FastPow(a, b - 1);
}

// int m - сообщение
// int P, A - общие параметры
// char* lpszFileName - имя файла
void MakeKey(int m, int P, int A, char* lpszFileName)
{
	int a, b; // цифровая подпись сообщения m
	int X; // закрытый ключ
	int Y; // открытый ключ
	int k; // секретное случайное число

	FILE *pf;
	int i;
	int t;
	
	srand((unsigned int)time(0)); // задание seed для генератора случайных чисел

	do
		X = rand()%10;
	while (gcd(X, P - 1) != 1);  // число, взаимно простое к P-1

	Y = FastPow(A, X) % P;

	do
		k = rand()%10;
	while (gcd(k, P - 1) != 1); // число, взаимно простое к P-1

	a = FastPow(A, k) % P;
	
	i = 0;
	do
	{
		b = ((P - 1) * i + m - X * a) / k; // находим b>=0 с помощью расширенного алгоритма Евклида
		t = ((P - 1) * i + m - X * a) % k; // проверяем, чтобы делилось нацело
		i++;
	}
	while (b < 0 || t != 0);
	
	// Проверка, расшифровка сообщения. Должно быть f = m
	// int f = (X * a + k * b) % (P - 1);

	pf = fopen(lpszFileName, "w+");
	if (pf == NULL)
		printf("Error opening file!\n");

	fprintf(pf, "\
m = %d\n\
P = %d\n\
A = %d\n\
Y = %d\n\
a = %d\n\
b = %d", m, P, A, Y, a, b);

	fclose(pf);
}

// int m - сообщение
// int P, A - общие параметры
// char* lpszFileName - имя файла
int VerifyKey(int m, int P, int A, char* lpszFileName)
{
	int a, b; // цифровая подпись сообщения m
	int Y; // открытый ключ

	FILE *pf;

	srand((unsigned int)time(0)); // задание seed для генератора случайных чисел

	pf = fopen("keys.txt", "r");
	if (pf == NULL)
		printf("Error opening file!\n");

	fscanf(pf, "\
m = %*d\n\
P = %*d\n\
A = %*d\n\
Y = %d\n\
a = %d\n\
b = %d", &Y, &a, &b);

	fclose(pf);
	
	int c1 = (FastPow(Y, a)*FastPow(a, b)) % P;
	int c2 = FastPow(A, m) % P;

	if (c1 == c2)
		return 1; // ключи совпадают
	else
		return 0; // ключи не совпадают
}

int main()
{
	int m = 5; // сообщение
	int P = 11, A = 7; // общие параметры

	MakeKey(m, P, A, "keys.txt");
	if (VerifyKey(m, P, A, "keys.txt"))
		printf("Keys are correct.\n");
	else
		printf("Keys aren't correct.\n");

	return 0;
}