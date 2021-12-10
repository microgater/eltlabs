// Лабораторная работа №1
// Задача №3

#include <stdio.h>

int NumBase(char *str, int base)
{
	int num = 0;
	int k = 1;
	int i;
	for (i = 0; *(str + i); i++);
	for (i--; i >= 0; i--)
	{
		int n;
		if (*(str + i) >= '0' && *(str + i) <= '9')
			n = *(str + i) - '0';
		else if (*(str + i) >= 'A' && *(str + i) <= 'F')
			n = *(str + i) - 'A' + 10;
		else
			return -1; // символ не цифра и не A...F
		if (n >= base)
			return -1; // символ не принадлежит символам из этого основания

		num += k * n;
		k *= base;
	}
	return num;
}

int main()
{
	char str1[] = "010";
	char str2[] = "14";
	int mas[2][15]; // массив для вычисленных значений
	int base;
	int equality = 0;

	// Вычисляем запись числа в разных системах счисления
	for (base = 2; base <= 16; base++)
		*(*mas + base - 2) = NumBase(str1, base);
	for (base = 2; base <= 16; base++)
		*(*(mas + 1) + base - 2) = NumBase(str2, base);

	// Находим равные числа
	for (int i = 16; i >= 2; i--)
		if (*(*mas + i - 2) != -1) // пропускаем неверные числа
			for (int j = 16; j >= 2; j--)
			{
				if (*(*mas + i - 2) == *(*(mas + 1) + j - 2)) // если совпало, то выводим
				{
					printf("decimal: %d, base1 = %d, base2 = %d\n", *(*mas + i - 2), i, j);
					equality = 1; // есть правильный ответ
				}
			}

	if (!equality)
		printf("Not equal");

	return 0;
}