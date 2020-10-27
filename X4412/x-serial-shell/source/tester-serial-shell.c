#include <main.h>
#include <readline.h>

enum parse_state_t {
	PS_WHITESPACE,
	PS_TOKEN,
	PS_STRING,
	PS_ESCAPE
};

struct command_t {
	const char * name;
	void (*func)(int argc, char ** argv);
	const char * help;
};

void help(int argc, char ** argv);
void clear(int argc, char ** argv);
void hello(int argc, char ** argv);

struct command_t command_lit[] = {
	{"help", help, " help -- Command help"},
	{"clear", clear," clear -- Clear the screen"},
	{"hello", hello, " hello -- Say hello to system"}
};

void parse_args(char *argstr,char *argc_p,char **argv, char **resid)
{
	char argc = 0;
	char c;
	enum parse_state_t s_state, l_state = PS_WHITESPACE;
	enum parse_state_t n_state = PS_WHITESPACE;

	while ((c = *argstr) != 0)
	{
		if (c == ';' && l_state != PS_STRING && l_state != PS_ESCAPE)
			break;

		if (l_state == PS_ESCAPE)
		{
			n_state = s_state;
		}
		else if (l_state == PS_STRING)
		{
			if (c == '"')
		 	{
				n_state = PS_WHITESPACE;
				*argstr = 0;
			}
		 	else
			{
				n_state = PS_STRING;
			}
		}
	 	else if ((c == ' ') || (c == '\t'))
		{
			*argstr = 0;
			n_state = PS_WHITESPACE;
		}
	 	else if (c == '"')
		{
			n_state = PS_STRING;
			*argstr++ = 0;
			argv[argc++] = argstr;
		}
	 	else if (c == '\\')
		{
			s_state = l_state;
			n_state = PS_ESCAPE;
		}
	 	else
		{
			if (l_state == PS_WHITESPACE)
			{
				argv[argc++] = argstr;
			}
			n_state = PS_TOKEN;
		}

		l_state = n_state;
		argstr++;
	}

	argv[argc] = NULL;
	if (argc_p != NULL)
		*argc_p = argc;

	if (*argstr == ';')
	{
		*argstr++ = '\0';
	}
	*resid = argstr;
}

void exec_command(char * buf)
{
	char argc, *argv[8], *resid;
	int i;
	struct command_t * cmd = 0;

	while(*buf)
 	{
		memset(argv,0,sizeof(argv));
		parse_args(buf, &argc, argv, &resid);
		if(argc > 0)
		{
			if(strcmp("*", argv[0]) == 0)
				break;

			for(i = 0; i < ARRAY_SIZE(command_lit); i++)
			{
				cmd = &command_lit[i];
				if(strncmp(cmd->name,argv[0],strlen(argv[0])) == 0)
					break;
				else
					cmd = 0;
			}
			if(cmd == 0)
			{
				console_print(3, " Could not found \"");
				console_print(3, argv[0]);
				console_print(3, "\" command\r\n");
				console_print(3, " If you want to konw available commands, type 'help'\r\n");
		   	}
			else
			{
				cmd->func(argc,argv);
			}
		}
		buf = resid;
	}
}

/*****************************************************************************/
void help(int argc, char ** argv)
{
	int i;

	switch(argc)
	{
	case 1:
		for(i = 0; i < ARRAY_SIZE(command_lit); i++)
		{
			console_print(3, command_lit[i].help);
			console_print(3, "\r\n");
		}
		break;
	default:
		console_print(3, " Invalid 'help' command: too many arguments\r\n");
		console_print(3, " Usage:\r\n");
		console_print(3, "     help\r\n");
		break;
	}
}

extern s32_t cx, cy;
void clear(int argc, char ** argv)
{
	switch(argc)
	{
	case 1:
		console_print(3, "\033[2J");
		cx = 0;
		cy = 0;
		break;

	default:
		console_print(3, " Invalid 'clear' command: too many arguments\r\n");
		console_print(3, " Usage:\r\n");
		console_print(3, "     clear\r\n");
		break;
	}
}

void hello(int argc, char ** argv)
{
	switch(argc)
	{
	case 1:
		console_print(3, " world\r\n");
		break;

	default:
		console_print(3, " Invalid 'hello' command: too many arguments\r\n");
		console_print(3, " Usage:\r\n");
		console_print(3, "     hello\r\n");
		break;
	}
}

int tester_serial_shell(int argc, char * argv[])
{
	char * p;

	console_print(3, "\033[2J");
	console_print(3, "exynos4412 shell test...\r\n");

	while(1)
	{
		p = readline(3, "--> ");
		exec_command(p);
		free(p);
	}
	return 0;
}
