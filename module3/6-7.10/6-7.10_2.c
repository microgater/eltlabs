/* Задача 6-7.10, программа 2 */

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

	/* Генерируем IPC ключ из имени файла 6-7.10_1.c в текущей директории и номера экземпляра области разделяемой памяти 0 */
	if ((key = ftok(pathname, 0)) < 0)
	{
		printf("Can\'t generate key\n");
		exit(-1);
	}

	/* Пытаемся получить IPC дескриптор разделяемой памяти */
	if ((shmid = shmget(key, 10000*sizeof(char), 0)) < 0)
	{
		printf("Can\'t find shared memory\n");
		exit(-1);
	}

	/* Пытаемся отобразить разделяемую память в адресное пространство текущего процесса. */
	if ((array = shmat(shmid, NULL, 0)) == (char*)-1)
	{
		printf("Can't attach shared memory\n");
		exit(-1);
	}

	/* Выводим на экран сожержимое массива array */
	printf("%s\n", array);

	/* Удаляем разделяемую память из адресного пространства текущего процесса */
	if (shmdt(array) < 0)
	{
		printf("Can't detach shared memory\n");
		exit(-1);
	}

	/* Удаляем разделяемую память и завершаем программу */
	if (shmctl(shmid, IPC_RMID, NULL) < 0)
	{
		printf("Can't delete shared memory\n");
		exit(-1);
	}

	return 0;
}