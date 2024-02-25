#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 4
#define INIT_FILE "resources.txt"

int available[NUMBER_OF_RESOURCES];
int max[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

int is_leq(int *a, int *b, int n) {
	for(int i = 0; i !=n ; i++) {
		if(a[i] > b[i])
			return 0;
	}
	return 1;
}

int is_safe() {
	int work [NUMBER_OF_RESOURCES], finish [NUMBER_OF_CUSTOMERS];
	memcpy(work, available, NUMBER_OF_RESOURCES * sizeof(int));
	memset (finish, 0, NUMBER_OF_CUSTOMERS * sizeof(int));
	for(int round = 0; round != NUMBER_OF_CUSTOMERS; round++) {
		int flag = 0;
		for(int i = 0; i != NUMBER_OF_CUSTOMERS; i++) {
			if(finish[i] == 0 && is_leq(need[i], work, NUMBER_OF_RESOURCES)) {
				flag = 1;
				finish[i] = 1;
				for(int j = 0; j != NUMBER_OF_RESOURCES; j++)
					work[j] += allocation[i][j];
				break;
			}
		}
		
		if (!flag)
			return 0;
	}
	return 1;
}

int request_resources(int customer, int request[NUMBER_OF_RESOURCES]) {
	if (customer < 0 || customer >= NUMBER_OF_CUSTOMERS) {
		printf("Klient jo i vlefshem: %d\n", customer);
		return -1;
	}
	
	int error = 0;
	for(int i = 0; i != NUMBER_OF_RESOURCES; i++) {
		if(request[i] < 0 || request[i] > need[customer][i]) {
			printf("Numer jo i vlefshem burimesh: \
				<klient: %d, burime: %d, need: %d, per kerkim: %d>\n", \
				customer, i, need [customer][i], request[i]);
			error = -1;
		}
		if(request[i] > available[i]) {
			printf("Burime te pamjaftueshme: \
				<klient: %d, burime: %d, available: %d, per kerkim: %d>\n", \
				customer, i, available[i], request[i]);
			error = -2;
		}
		if(error != 0) {
			while(i--) {
				available[i] += request[i];
				allocation[customer][i] -= request[i];
				need[customer][i] += request[i];
			}
			return error;
		}
		available[i] -= request[i];
		allocation[customer][i] += request[i];
		need [customer][i] -= request[i];
	}
	
	if(!is_safe()) {
		printf("Gjendje e pasigurt pas kerkeses!\n");
		for(int i = 0; i != NUMBER_OF_RESOURCES; i++) {
			available[i] += request[i];
			allocation[customer][i] -= request[i];
			need[customer][i] += request[i];
		}
		return -3;
	}
	return 0;
}

int release_resources(int customer, int release[NUMBER_OF_CUSTOMERS]) {
	if(customer < 0 || customer >= NUMBER_OF_CUSTOMERS) {
		printf("Klient jo i vlefshem: %d\n", customer);
		return -1;
	}
	for(int i = 0; i != NUMBER_OF_RESOURCES; i++) {
		if(release[i] < 0 || release[i] > allocation[customer][i]) {
			printf("Numer i pavlefshem burimesh: \
				<klient: %d, burime: %d, per tu alokuar: %d, per tu leshuar: %d>\n", \
				customer, i, allocation[customer][i], release[i]);
			while(i--) {
				allocation[customer][i-1] += release [i-1];
				available[i] -= release [i];
			}
			return -1;
		}
		allocation[customer][i] -= release[i];
		available[i] += release[i];
	}
	return 0;
}

void display_resources() {
	printf("======\n");
	printf("Burime te lira:\n");
	for(int i = 0; i != NUMBER_OF_RESOURCES; i++)
		printf("%d: ", available[i]);
	printf("\n\n");
	printf("Numri max i burimeve per cdo klient:\n");
	for(int customer = 0; customer != NUMBER_OF_CUSTOMERS; customer++) {
		printf("%d: ", customer);
		for(int r=0; r != NUMBER_OF_RESOURCES; r++)
			printf("%d ", max[customer][r]);
		printf("\n");
	}
	printf("\n");
	printf("Burime te alokuara per cdo klient:\n");
	for(int customer = 0; customer != NUMBER_OF_CUSTOMERS; customer++){
		printf("%d: ", customer);
		for(int r = 0; r != NUMBER_OF_RESOURCES; r++)
			printf("%d", allocation[customer][r]);
		printf("\n");
	}
	printf("\n");
	printf ("Burimet e nevojshme per cdo klient:\n");
	for(int customer = 0; customer != NUMBER_OF_CUSTOMERS; customer++) {
		printf("%d: ", customer);
		for(int r = 0; r != NUMBER_OF_RESOURCES; r++)
			printf("%d ", need [customer][r]);
		printf("\n");
	}
	printf("======\n");
}

int init(int argc, char *argv[], const char *resources_file) {
	if (argc != 1 + NUMBER_OF_RESOURCES) {
		printf("Numer i gabuar parametrash!\n");
		return -1;
	}
	
	for(int i = 0; i != NUMBER_OF_RESOURCES; i++)
		available[i] = atoi(argv[i+1]);
	
	FILE *f = fopen(resources_file, "r");
	if (f == NULL) {
		printf("Skedari %s nuk mund te hapet!\n", resources_file);
		return -2;
	}
	
	for(int c = 0; c != NUMBER_OF_CUSTOMERS; c++) {
		for(int r = 0; r != NUMBER_OF_RESOURCES; r++) {
			fscanf (f, "%d", &max[c][r]);
			need[c][r] = max[c][r];
		}
	}
	fclose(f);
	return 0;
}


int main(int argc, char *argv[]){
	if (init(argc, argv, INIT_FILE) != 0){ 
		display_usage(); 
		return 0;
	}
	
	char op[5];
	printf(">");
	
	while(scanf("%s", op) == 1) {
		if(strcmp(op, "REQ") == 0)
			request_wrapper();
		else if(strcmp(op, "REL") == 0)
			release_wrapper();
		else if(strcmp(op, "DIS") == 0)
			display_resources();
		else
			display_usage();
		printf(">");
	}
	return 0;
}
