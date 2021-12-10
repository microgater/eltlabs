/* Программа-сервер для иллюстрации работы с сообщениями от разных клиентов */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

#define LAST_MESSAGE 0 /* Тип сообщения для прекращения работы */

int main()
{
	int msqid; /* IPC дескриптор для очереди сообщений */
	char pathname[] = "9.10_server.c"; /* Имя файла, использующееся для генерации ключа.
	Файл с таким именем должен существовать в текущей директории */
	key_t key; /* IPC ключ */
    int len; /* Длина информативной части сообщения */
	long i;

	/* Ниже следует пользовательская структура для сообщения */
	struct mymsgbuf
	{
		long mtype;
		int msg;
	} mybuf;

	/* Генерируем IPC ключ из имени файла 09-1a.c в текущей директории
	и номера экземпляра очереди сообщений 0 */
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

	while (1)
    {
		/* В бесконечном цикле принимаем сообщения конкретного типа в порядке FIFO, пока не поступит сообщение выключения с типом LAST_MESSAGE */
		if (len = (msgrcv(msqid, (struct msgbuf *) &mybuf, sizeof(int), 1, 0) < 0))
        {
			printf("Can\'t receive message from queue\n");
			exit(-1);
		}

        printf("Got message from process with pid = %d, ", mybuf.msg);
		for (i = 0; i < 500000000L; i++); /* Имитируем длительную обработку сообщения */
		printf("sent message\n");
        mybuf.mtype = mybuf.msg; /* Устанавливаем тип сообщений pid */

	    /* Отсылаем сообщение c pid запущенного процесса. В случае ошибки сообщаем об этом. */
	    if (msgsnd(msqid, (struct msgbuf *) &mybuf, 0, 0) < 0)
        {
	        printf("Can\'t send message to queue\n");
	        exit(-1);
	    }
	}

	return 0;
}