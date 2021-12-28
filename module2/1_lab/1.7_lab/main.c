// Лабораторная работа №1
// Задача №7

/*
7. Найти во входной строке самую внутреннюю пару скобок {...} и переписать в выходную строку содержащиеся между ними символы. Во входной строке фрагмент удаляется. Повторять этот процесс, пока во входной строке не останется скобок, остаток также переписать в выходную строку.
*/

#include <stdio.h>

void modifyStr(char *str, char *strOut)
{
	int bracketCount, bracketCountMax = 1;
	int i = 0, iMax, j = 0, delta = 0;

	while(bracketCountMax)
	{ 
		bracketCount = 0;
		bracketCountMax = 0;
		delta = 0;
		for (i = 0; *(str + i); i++)
		{
			switch (*(str + i))
			{
			case '{':
				bracketCount++;
				if (bracketCount > bracketCountMax)
				{
					bracketCountMax = bracketCount;
					iMax = i;
				}
				break;
			case '}':
				bracketCount--;
				break;
			}
		}
		if (bracketCountMax == 0)
			break;
		for (i = iMax + 1; *(str + i) != '}'; i++)
		{
			*(strOut + j++) = *(str + i);
			delta++;
		}
		for (i = iMax; *(str + i); i++)
		{
			*(str + i) = *(str + i + delta + 2);
		}
	}
	for (i = 0; *(str + i); i++)
		*(strOut + j++) = *(str + i);
	*(strOut + j) = '\0';
}

int main()
{
	char str[] = "aaa{bbb{ccc}ddd}eee{f{gg{hh}ii}}";
	char strOut[100];

	modifyStr(str, strOut);
	printf("%s\n", str);
	printf("%s", strOut);

	return 0;
}
