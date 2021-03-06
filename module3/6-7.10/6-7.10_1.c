/* Задача 6-7.10, программа 1 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
	char *array; /* Указатель на разделяемую память */
	int shmid; /* IPC дескриптор для области разделяемой памяти */
	char pathname[] = "6-7.10_1.c"; /* Имя файла, использующееся для генерации ключа. Файл с таким именем должен существовать в текущей директории */
	key_t key; /* IPC ключ */
	FILE *pf; /* Указатель на файл */
	int i; /* Счетчик */

	/* Генерируем IPC ключ из имени файла 6-7.10_1.c в текущей директории и номера экземпляра области разделяемой памяти 0 */
	if ((key = ftok(pathname, 0)) < 0)
	{
		printf("Can\'t generate key\n");
		exit(-1);
	}

	/* Пытаемся эксклюзивно создать разделяемую память для сгенерированного ключа, т.е. если для этого ключа она уже существует системный вызов вернет отрицательное значение. Размер памяти определяем как размер массива из 3-х целых переменных, права доступа 0666 - чтение и запись разрешены для всех */
	if ((shmid = shmget(key, 10000 * sizeof(char), 0666 | IPC_CREAT | IPC_EXCL)) < 0)
	{
		/* В случае возникновения ошибки пытаемся определить: возникла ли она из-за того, что сегмент разделяемой памяти уже существует или по другой причине */
		if (errno != EEXIST)
		{
			/* Если по другой причине - прекращаем работу */
			printf("Can\'t create shared memory\n");
			exit(-1);
		}
		else
		{
			/* Если из-за того, что разделяемая память уже существует - прекращаем работу */
				printf("Shared memory is already is exist!\n");
				exit(-1);
		}
	}
	
	/* Пытаемся отобразить разделяемую память в адресное пространство текущего процесса. */
	if ((array = shmat(shmid, NULL, 0)) == (char*)-1)
	{
		printf("Can't attach shared memory\n");
		exit(-1);
	}

	/* Открываем файл */
	pf = fopen("6-7.10_1.c", "r");
	if (pf == NULL)
		printf("Error opening file!\n");

	/* Читаем по одному символу из файла в массив array, пока не закончится файл */
	for (i = 0; !feof(pf); i++)
		fscanf(pf, "%c", array + i);
	
	/* Обозначаем конец строки */
	array[i+1] = '\0';

	/* Закрываем файл */
	fclose(pf);

	/* Удаляем разделяемую память из адресного пространства текущего процесса и завершаем программу */
	if (shmdt(array) < 0)
	{
		printf("Can't detach shared memory\n");
		exit(-1);
	}

	return 0;
}