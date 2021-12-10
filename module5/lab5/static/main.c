#include <stdio.h>

// Объявляем внешние функции
extern int mod(int a, int b);
extern int idiv(double a, int b);

int main()
{
	int a = 11, b = 5;

	printf("mod(%d, %d) = %d\n", a, b, mod(a, b));
	printf("idiv(%d, %d) = %d\n", a, b, idiv(a, b));

	return 0;
}
