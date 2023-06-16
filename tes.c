#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
//#include "minishell.h"

void	ft_putendl_fd(char *s, int fd)
{
	while (*s)
		write(1, s++, 1);
	write(fd, "\n", 1);
}

void	sigsig(int signal)
{
	puts("Raluca");
}

int main(int a, char **c, char **e)
{
	/*printf("You don't have\n\n\n\n\n\n space, bro! (っ˘̩╭╮˘̩)っ\n");
	ft_putendl_fd("You don't have space, bro! (っ˘̩╭╮˘̩)っ", 2);*/
	/*int	teste;
	int	fd = fork();

	if (fd == 0)
	{
		exit (1);
	}
	wait(&teste);
	//wait(NULL);
	printf("%d\n", teste);
	printf("%d\n", WEXITSTATUS(teste));*/
	/* fork();
	printf("%10245846d minishel: , dude! ¯\\_(ツ)_/¯ o(><)o (×_×) (ᗒᗣᗕ)՞ (」°ロ°)」( Ｔ▽Ｔ) \n", 2);
	write(1, "oi", 2);
	exit(0); */
	unsigned char str[4];

	str[0] = 0b00000000;
	str[1] = 2;//0b00000010;
	str[2] = 'Y';//0b01011001;
	str[3] = 144;//0b10010000;
	//00000000
	//00000010
	//01011001
	//10010000
	/*int	teste = 0;
	teste = teste | (str[0] << 24);
	teste = teste | (str[1] << 16);
	teste = teste | (str[2] << 8);
	teste = teste | str[3];
	printf("%d\n", teste);*/
	signal(SIGINT, sigsig);
	int	teste = 0;
	while (teste < 3)
	{
		sleep(1);
		teste++;
	}
	printf("Cabô\n");
}
