/* Программа для удаления области разделяемой памяти */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
	int shmid; /* IPC дескриптор для области разделяемой памяти */
	char pathname[] = "8.7_1.c"; /* Имя файла, использующееся для генерации ключа. Файл с таким именем должен существовать в текущей директории */
	key_t key; /* IPC ключ */

	/* Генерируем IPC ключ из имени файла 06-1a.c в текущей директории и номера экземпляра области разделяемой памяти 0 */
	if ((key = ftok(pathname, 0)) < 0)
    {
		printf("Can\'t generate key\n");
		exit(-1);
	}

	/* Пытаемся эксклюзивно создать разделяемую память для сгенерированного ключа, т.е. если для этого ключа она уже существует, то системный вызов вернет отрицательное значение. Размер памяти определяем как размер массива из 3-х целых переменных, права доступа 0666 - чтение и запись разрешены для всех */
	if ((shmid = shmget(key, 3 * sizeof(int), 0666 | IPC_CREAT | IPC_EXCL)) < 0)
    {
		/* В случае возникновения ошибки пытаемся определить: возникла ли она из-за того, что сегмент разделяемой памяти уже существует, или по другой причине */
		if (errno != EEXIST)
        {
			/* Если по другой причине - прекращаем работу */
			printf("Can\'t create shared memory\n");
			exit(-1);
		}
		else
        {
			/* Если из-за того, что разделяемая память уже существует, пытаемся получить ее IPC дескриптор */
			if ((shmid = shmget(key, 3 * sizeof(int), 0)) < 0)
            {
				printf("Can\'t find shared memory\n");
				exit(-1);
			}
		}
	}

    /* Удаляем область разделяемой памяти и завершаем программу */
	if (shmctl(shmid, IPC_RMID, NULL) < 0)
	{
		printf("Can't delete shared memory\n");
		exit(-1);
	}

	return 0;
}