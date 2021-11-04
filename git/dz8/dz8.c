#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void parallel(char*, char *, char*, char*); //зпускается при выводе р
void conveyor(char**); //зпускается при выводе c
void print_info(int);

int main(int argc, char **argv) {
	if (argc != 6){
		fprintf(stderr, "Wrong input\n");
		return 1;
	}
	if (!strcmp("p", argv[5])) {
		parallel(argv[1], argv[2], argv[3], argv[4]);
	}
	else if (!strcmp("c", argv[5])) {
		conveyor(argv);
	}
	else {
		printf("Wrong parametr\n");
		return 2;
	}
	return 0;
}

void print_info(int info) {
	if (WIFEXITED(info))
		printf("Process exited with status: %d\n", WEXITSTATUS(info));
	else if (WIFSIGNALED(info))
		printf("Process terminated with signal: %d\n", WTERMSIG(info));
	else if (WIFSTOPPED(info))
		printf("Process stopped with stop-signal: %d\n", WSTOPSIG(info));
}

void parallel(char *prog1, char *arg1, char *prog2, char *arg2) {
	pid_t pid1, pid2;
	int info1, info2;
	if ((pid1 = fork()) == -1){
		fprintf(stderr, "Fork error\n");
		exit(1);
	}
	if (pid1 == 0) {
		execl(prog1, prog1, arg1, NULL);
		exit(2);
	}
	if ((pid2 = fork()) == -1) {
		fprintf(stderr, "Fork error\n");
		exit(1);
	}
	if (pid2 == 0) {
		execl(prog2, prog2, arg2, NULL);
		exit(2);
	}
	wait(&info2);
	wait(&info1);
	print_info(info1);
	print_info(info2);
}

void conveyor(char **argv) {
	pid_t pid;
	int info;
	for (int i = 1; i < 5; i += 2) {
		if ((pid = fork()) == -1) {
			fprintf(stderr, "Error: Failed to calling fork() \n");
			exit(1);
		}
		else if (pid == 0) {
			char* vector_of_args[3] = { argv[i], argv[i + 1], NULL };
			execv(argv[i], vector_of_args);
			exit(2);
		}
		else {
			wait(&info);
			print_info(info);
		}
	}
}