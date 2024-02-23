#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "buffer.h"

int main(int argc, char *argv[]) {
	if (argc!=4) {
		fprintf(stderr, "Pedorimi: <executable> sleepSecond numProducer numConsumer\n");
		return 0;
	}
	
	unsigned int sleepSecond = atoi (argv[1]);
	size_t numProducer = atoi(argv[2]), numConsumer = atoi(argv[3]);
	
	init_buffer();
	
	pthread_t *producers = malloc(numProducer * sizeof(pthread_t));
	int *producer_id = malloc(numProducer * sizeof(pthread_t));
	
	for(size_t i = 0; i != numProducer; i++) {
		producer_id[i] = i + 1;
		pthread_create(&producers[i], NULL, producer, &producer_id[i]);
	}
	
	pthread_t *consumers = malloc(numConsumer * sizeof(pthread_t));
	int *consumer_id = malloc(numConsumer * sizeof(pthread_t));
	
	for(size_t i = 0; i != numConsumer; i++) {
		consumer_id[i] = i + 1;
		pthread_create(&consumers[i], NULL, consumer, &consumer_id[i]);
	}
	
	printf("Fli per %u sekond(a) para exit.\n", sleepSecond);
	sleep(sleepSecond);
	
	for(size_t i = 0; i != numProducer; i++) {
		pthread_cancel(producers[i]);
		pthread_join(producers[i], NULL);
	}
	
	sleep (3);
	
	for(size_t i=0; i!=numConsumer; i++) {
		pthread_cancel (consumers [i]);
		pthread_join(producers[i], NULL);
	}
	
	free (producers);
	free(producer_id);
	free (consumers);
	free (consumer_id);
	
	destroy_buffer();
	return 0;
}
