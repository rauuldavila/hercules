#include <stdio.h>
#include <string.h>
#include <signal.h>

void catch_signal(int signal)
{
	printf("You can't catch me!\n");
}

int        main(int argc, char **argv)
{
	signal(SIGINT, catch_signal);
	while (1)
	{
		sleep(10);
		fork();
	}
	return (0);
}
