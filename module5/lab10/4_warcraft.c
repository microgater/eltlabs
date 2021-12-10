//--- 4_warcraft.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

#define N_UNITS 5

int minerals = 43;
int unit_performance = 3;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *unit(void *unit_in_work) {
	sleep(rand()%5); // путь в шахту

    pthread_mutex_lock(&lock);
    if (minerals) {
        if (minerals > unit_performance) {
            minerals -= unit_performance; // добыча минералов
            printf("Unit %d grabbed %d minerals. Minerals left: %d\n", *((int*)unit_in_work), unit_performance, minerals);
        } else {
            printf("Unit %d grabbed %d minerals. No minerals left.\n", *((int*)unit_in_work), minerals);
            minerals = 0;
        }
    }
    pthread_mutex_unlock(&lock);
    
	sleep(rand()%7); // путь из шахты
    *((int*)unit_in_work) = 0; // юнит завершил работу

    return NULL;
}

int main(int argc, char **argv) {
	int i, err, unit_id[N_UNITS];
	pthread_t tid_unit[N_UNITS];

    srand(time(NULL));

    printf("Starting minerals mining. Estimating minerals: %d\n", minerals);

    // Отправляем всех юнитов в шахту
	for (i = 0; i < N_UNITS; i++) {
        unit_id[i] = i+1;
        printf("Sending unit %d.\n", i+1);
		err = pthread_create(&tid_unit[i], NULL, unit, &unit_id[i]);
        if (err) {
			printf("reating %d thread failure!\n", i);
		    return EXIT_FAILURE;
        }
	}

	// По прибытии юнита отправляем его обратно в шахту, если шахта не пуста
	while (minerals) {
        if (i >= N_UNITS)
            i = 0;

        if (!unit_id[i]) {
            pthread_join(tid_unit[i], NULL);
            if (err) {
			    printf("Joining thread %d failure!\n", i);
		        return EXIT_FAILURE;
            }
            printf("Unit %d arrived.\n", i+1);
            unit_id[i] = i+1;
            printf("Sending unit %d.\n", i+1);
            err = pthread_create(&tid_unit[i], NULL, unit, &unit_id[i]);
            if (err) {
			    printf("Creating %d thread failure!\n", i);
			    return EXIT_FAILURE;
            }
        }

        i++;
	}
	
    printf("Mining finished. Waiting for all units to arrive.\n");
    // Ждем прибытия всех юнитов
    for (i = 0; i < N_UNITS; i++) {
        pthread_join(tid_unit[i], NULL);
	}
    printf("All units arrived. %d minerals left.\n", minerals);

	return EXIT_SUCCESS;
}