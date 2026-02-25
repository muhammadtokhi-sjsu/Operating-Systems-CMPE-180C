/*******************
 * Muhammad Tokhi  *
 * ID: 019151041   *
 * Project 4       *
 * Signal Handlers *
 * Semester 1 '25  *
 * CMPE 180C       *
 * Juan Gomez      *
 *******************/

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define SLEEP_TIME 2

int flag = 0;

void signal_handler (int sig_int) {

	flag = !flag;

	fprintf(stdout, "flag: %d\n", flag);

	return;

}

void graceful_handler (int sig_int) {

	exit(EXIT_SUCCESS);

}

int main (int argc, char *argv[]) {

	int iteration_count = 0;
	struct sigaction sa;
	struct sigaction sa_user;

	sa.sa_handler = signal_handler;
	sa_user.sa_handler = graceful_handler;


	errno = 0;
	int sigaction_result;

	fprintf(stdout, "PID: %d\n", getpid());

	sigaction_result = sigaction(SIGINT, &sa, NULL);
	
	if (sigaction_result != 0) {
		fprintf(stderr, "Errno: %d\n", errno);
		fprintf(stderr, "Error: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	sigaction_result = sigaction(SIGUSR1, &sa_user, NULL);

	if (sigaction_result != 0) {
		fprintf(stderr, "Errno: %d\n", errno);
		fprintf(stderr, "Error: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	while (1) {

		iteration_count++;

		if (flag == 0) {

			sigaction_result = sigaction(SIGINT, &sa, NULL);
	
			if (sigaction_result != 0) {
				fprintf(stderr, "Errno: %d\n", errno);
				fprintf(stderr, "Error: %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}

			sigaction_result = sigaction(SIGUSR1, &sa_user, NULL);

			if (sigaction_result != 0) {
				fprintf(stderr, "Errno: %d\n", errno);
				fprintf(stderr, "Error: %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}	
		}		


		if (flag == 1) {
			
			fprintf(stdout, "Interation: %d\n", iteration_count);
			
			sigaction_result = sigaction(SIGINT, &sa, NULL);
	
			if (sigaction_result != 0) {
				fprintf(stderr, "Errno: %d\n", errno);
				fprintf(stderr, "Error: %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}

			sigaction_result = sigaction(SIGUSR1, &sa_user, NULL);

			if (sigaction_result != 0) {
				fprintf(stderr, "Errno: %d\n", errno);
				fprintf(stderr, "Error: %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}	
		}

		sleep(SLEEP_TIME);

	}

	exit(EXIT_SUCCESS);

}
