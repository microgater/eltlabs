/* Программа-клиент №1 для иллюстрации работы с программой-сервером */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int msqid; /* IPC дескриптор для очереди сообщений */
	char pathname[] = "9.10_server.c"; /* Имя файла, использующееся для генерации ключа.
	Файл с таким именем должен существовать в текущей директории */
	key_t key; /* IPC ключ */
    int pid = getpid(); /* pid программы */

	/* Ниже следует пользовательская структура для сообщения */
	struct mymsgbuf
	{
		long mtype;
		int msg;
	} mybuf;


	/* Генерируем IPC ключ из имени файла 09-1a.c в текущей директории
	и номера экземпляра очереди сообщений 0. */
	if ((key = ftok(pathname, 0)) < 0)
    {
		printf("Can\'t generate key\n");
		exit(-1);
	}

	/* Пытаемся получить доступ по ключу к очереди сообщений, если она существует,
	или создать ее, если она еще не существует, с правами доступа
	read & write для всех пользователей */
	if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0)
    {
		printf("Can\'t get msqid\n");
		exit(-1);
	}
    
    mybuf.mtype = 1; /* Устанавливаем тип сообщений 1 */
	mybuf.msg = pid; /* Указываем в составе сообщения pid процесса */

	/* Отсылаем сообщение c pid запущенного процесса. В случае ошибки сообщаем об этом. */
	if (msgsnd(msqid, (struct msgbuf *) &mybuf, sizeof(int), 0) < 0)
    {
		printf("Can\'t send message to queue\n");
		exit(-1);
	}
	
	printf("Sent message, pid = %d, ", pid);

	/* Ждем сообщение с типом pid данного процесса */
	if ((msgrcv(msqid, (struct msgbuf *) &mybuf, 0, pid, 0) < 0))
    {
		printf("Can\'t receive message from queue\n");
		exit(-1);
	}

	printf("got message\n");

	return 0;
}