#include "shell.h"
/**
 * main - entry ponint to the shell program.
 * @argc: the length of @av
 * @argv: the list of arguments passed to the program
 * @env: the environment information
 *
 * Return: 0 on success, error code on failure.
 **/
int main(int __attribute__((unused)) argc, char __attribute__((unused)) **argv,
		 char **env)
{
	char *buff, ***commands, **av, **sub;
	size_t n = 0, ac, promptNo = 0, nofcommands;
	int i, atty = -1, stat = 0;

	while (1)
	{
		buff = NULL, av = sub = NULL, commands = NULL, promptNo++;

		if (isatty(STDIN_FILENO) == 1)
		{atty = 1;
			write(STDOUT_FILENO, "$ ", 2);
		}
		/* getting the input and puting it in buff */
		stat = getline(&buff, &n, stdin);
		if (stat == -1)
		{
			if (atty == 1)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
		/* getting the number of commands seperated by newline */
		nofcommands = noftokens(buff, "\n");
		if (nofcommands < 1)
			continue;
		else if (nofcommands == 1)
		{   /* getting the number of arguments */
			ac = noftokens(buff, " \n");
			if (ac < 1)
				continue;
			/* allocating memory for the tokens */
			av = malloc(sizeof(av) * (ac + 1));
			/* filling the data */
			if (getokens(buff, av, " \n") == -1)
			{
				free(av);
				continue;
			}
		}
		else	/* if there are more than 1 command */
		{   /* allocating memory for commands */
			commands = malloc(sizeof(*commands) * nofcommands);
			if (!commands)
				continue;
			/* seperate commands */
			if (getokens(buff, sub, "\n") == -1)
			{
				free(commands);
				continue;
			}
			/* filling the data */
			i = 0;
			while (nofcommands)
			{   getokens(sub[i], commands[i], " \n");
				i++, nofcommands--;
			}
		}
		/* the executeion */
		i = 0;
		if (commands)
		{
			while (commands[i])
			{
				if (execute(commands[i][0], commands[i], env) == -1)
				{
					error(argv[0], promptNo, commands[i][0], "exec");
					return (127);
				}
				i++;
			}
		}
		if (av)
		{
			if (execute(av[0], av, env) == -1)
			{
				error(argv[0], promptNo, av[0], "exec");
				return (127);
			}
		}
	}
	return (0);
}
