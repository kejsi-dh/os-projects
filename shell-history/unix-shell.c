#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 80
#define BUFFER_SIZE 50

char history[10][BUFFER_SIZE];
int count = 0;

void used_commands() {
	printf("\nLista e komandave: \n");
	int i, j = 0;
	int history_count = count;

	for(i = 0; i < 10; i++) {
		printf("%d. ", history_count);
		while(history[i][j] != '\n' && history[i][j] != '\0') {
			printf("%c", history[i][j]);
			j++;
		}
		printf("\n");
		j = 0;
		history_count--;
		if(history_count == 0)
			break;
	}
	printf("\n");
}

int commands(char in_buffer[], char *args[], int *flag) {
	int length = read(STDIN_FILENO, in_buffer, MAX_LINE);
	int start = -1;
	int count2 = 0;

	if(length == 0)
		exit(0);
	if(length < 0) {
		printf("Komanda nuk u lexua.\n");
		exit(-1);
	}
	for(int i = 0; i < length; i++) {
		switch(in_buffer[i]) {
			case '':
			case '\t':
				if(start!=-1) {
					args[count2] = &in_buffer[start];
					count2++;
				}
				in_buffer[i] = '\0';
				start = -1;
				break;
			case '\n':
				if(start!=-1){
					args[count2] = &in_buffer[start];
					count2++;
				}
				in_buffer[i] = '\0';
				args[count2] = NULL;
				break;
			default:
				if(start == -1) start = i;
				if(in_buffer[i] == '&') {
					*flag = 1;
					in_buffer[i] = '\0';
				}
		}
	}
	args[count2] = NULL;

	if(strcmp(args[0], "history") == 0) {
		if(count > 0)
			used_commands();
		else
			printf("Asnje komande ne histori.\n");
		return -1;
	}

	else if(args[0][0] - '!' == 0) {
		int x = args[0][1] - '0';
		int z = args[0][2] - '0';
		if(x > count){
			printf("Komanda nuk ekziston ne histori.\n");
			strcpy(in_buffer, "Komande e gabuar");
		}
		else if(z != -48) {
			printf("Komanda nuk ekziston. Jepni nje shifer me te vogel se 9.\n");
			strcpy(in_buffer, "Komande e gabuar");
		}
		else {
			if(x == -15)
				strcpy(in_buffer, history[0]);
			else if(x == 0) {
				printf("Jepni nje komande te sakte.\n");
				strcpy(in_buffer, "Komande e gabuar");
			}
			else if(x >= 1)
				strcpy(in_buffer, history[count-x]);
		}
	}
	for(int i = 9; i > 0; i--)
		strcpy(history[i], history[i-1]);
	strcpy(history[0], in_buffer);
	count++;
	if(count > 10)
		count = 10;
}

int main(void) {
	char in_buffer[MAX_LINE];
	int flag;
	char *args[MAX_LINE/2+1];
	int should_run = 1;
	pid_t, pid, tpid;
	int i;

	while(should_run) {
		flag = 0;
		printf("osh> ");
		fflush(stdout);

		if(-1 != commands(in_buffer, args, &flag)){
			pid = fork();
			if(pid < 0) {
				printf("Fork deshtoi!\n");
				exit(1);
			}
			else if(pid == 0) {
				if(execvp(args[0], args) == -1)
					printf("Error ne ekzekutim te komandes!\n");
			}
			else {
				i++;
				if(flag == 0) {
					i++;
					wait(NULL);
				}
			}
		}
	}
}
