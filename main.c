
#include "minishell.h"

void	free_matrix(char **matrix);
int	print_error(char *command, char *error, int exit_status);

void	principal(int signal, siginfo_t *info, void *context)
{
	ft_putendl_fd("", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)info;
	(void)signal;
	(void)context;
}

void	segunda_principal(int signal, siginfo_t *info, void *context)
{
	ft_putendl_fd("Entrei aqui 2222", 1);
	//printf("O que recebi foi %d\n", );
	(void)info;
	(void)signal;
	(void)context;
}

void	kk(int s)
{
	s++;
	dup2(1, 1);
	dup2(0, 0);
}

void	init_signals()
{
	/***
	 * Tratar sigPIPE (basta ignorar e ser feliz) 
	 * Reinan lindão <3!
	 */

	struct sigaction	sa;
	struct sigaction	sb;
	struct sigaction	sc;
	

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sa.sa_sigaction = principal;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);


	sigemptyset(&sb.sa_mask);
	sigaddset(&sb.sa_mask, SIGQUIT);
	sb.sa_flags = 0;
	sb.sa_sigaction = segunda_principal;
	sigaction(SIGQUIT, &sb, NULL);

	//sigaction(SIGPIPE, &(struct sigaction){SIG_IGN}, NULL);
	sigemptyset(&sc.sa_mask);
	sigaddset(&sc.sa_mask, SIGPIPE);
	sc.sa_flags = SA_SIGINFO;
	sc.sa_handler = kk;
	sigaction(SIGPIPE, &sc, NULL);
}

int	ft_env(char **command, int input_fd, int output_fd, t_env *env)
{
	if (!command)
		return 0;
	if (command[1] != NULL)
	{
		ft_putstr_fd("YOU JUST HAVE ONE JOB! Read The F*@# PDF!!!", 2);
		ft_putendl_fd("⸨◣_◢⸩", 2);
		ft_putstr_fd("He explicit says that we DON'T have to implement ", 2);
		ft_putstr_fd("env with some options or arguments. Respect that!", 2);
		ft_putendl_fd("\nGODAMIT!!!┌∩┐(◣_◢)┌∩┐\n\n"\
		"Have a nice day! (｡^‿^｡) ٩(◕‿◕)۶", 2);
		return (2);
	}
	while (env)
	{
		if (ft_strchr(env->var, '='))
			ft_putendl_fd(env->var, output_fd);
		env = env->next;
	}
	return (0);
	(void)input_fd;
}
/*
int ft_pwd(char **command, int input_fd, int output_fd, t_env *env)
{
	char	*pwd;

	if (!command)
	{
		return (12);
	}
	pwd = getcwd(0, 0);
	if (!pwd)
	{
		//somenthing to indicate error
		ft_putendl_fd("Buffer is NULL.", 2);
		return (ENOMEM);
	}
	/ * if (ft_strlen(pwd) > 4096)
		ft_putendl_fd("File name id too long!", 2); * /
	ft_putendl_fd(pwd, output_fd);
	free(pwd);
	return (0);
	(void)(env);
}
*/
int	ft_echo(char **command, int input_fd, int output_fd, t_env *env)
{
	char	*line_feed;

	if (!command)
		return (ENOMEM);
	line_feed = command[1];
	if (line_feed && *line_feed == '-')
		line_feed++;
	while (line_feed && *line_feed && *line_feed == 'n')
		line_feed++;
	if (line_feed && !*line_feed && line_feed > command[1] + 1)
		line_feed = NULL;
	else
		line_feed = (char *)1;
	command = command + 1 + (command[1][0] == '-' && line_feed != NULL);
	while (*command)
	{
		ft_putstr_fd(*command++, output_fd);
		if (*command)
			ft_putstr_fd(" ", output_fd);
	}
	if (line_feed)
		write(output_fd, "\n", 1);
	return (0);
	(void)env;
	(void)input_fd;
}


long	ft_atoll(char *s)
{
	long	numb;
	int		sign;

	if (!s)
		return (0);
	numb = 0;
	while (ft_isspace(*s))
		s++;
	sign = (*s == '+' || ft_isdigit(*s)) - (*s == '-');
	s += (*s == '+' || *s == '-');
	while (ft_isdigit(*s))
		numb = numb * 10 + *s++ - '0';
	return (numb * sign);
}

int	numb_fits_max_long(char *numb_begin, int sign)
{
	int		index;
	char	*big_long;

	if (sign == 1)
		big_long = "9223372036854775807";
	else
		big_long = "9223372036854775808";
	// Percorrer os números que são iguais {while(big_long[index] == numb_begin[index]) index++;}
	// Verificar se não estou no index 0 if (numb_begin[index] > big_long[index]) return 0
	// Checar se o dígito atual é maior do que o limite permitido àquele dígito -- se sim, return (0)
	index = 0;
	while (big_long[index] && numb_begin[index] == big_long[index])
		index++;
	if (big_long[index] && numb_begin[index] > big_long[index])
		return (0);
	return (1);
}

int	is_valid_number(char *s)
{
	char	*numb_begin;
	int		len;
	int		sign;

	if (!s)
		return (1);
	while (ft_isspace(*s))
		s++;
	len = 0;
	sign = (*s == '+' || ft_isdigit(*s)) - (*s == '-');
	s += (*s == '+' || *s == '-');
	while (*s == '0')
		s++;
	numb_begin = s;
	while (ft_isdigit(*s))
	{
		if (++len > 19)
			return (0);
		s++;
	}
	while (*s == ' ' || *s == '\t')
		s++;
	if (len == 19 && numb_fits_max_long(numb_begin, sign) == 0)
		return (0);
	return (!*s);
}
/*
int	ft_exit(char **command, int input_fd, int output_fd, t_env *env)
{
	long	num;

	if (!command || !command[1])
	{
		num = 0;
//		free_matrix((void **)command);
//		exit(0);
	}
	else if (command[2] != NULL)
		return (print_error(command[0], "Too many arguments", 1));
	else if (is_valid_number(command[1]))
	{
		num = ft_atoll(command[1]);
//		free_matrix((void **)command);
//		exit(num);
	}
	else
	{
		// Invalid number
		num = 2;
	}
	free_matrix(command);
	ft_close(input_fd);
	ft_close(output_fd);
	exit(num);
}
*/
void	*set_builtin(char **command)
{
	if (!command || !*command || !**command)
		return (NULL);
	if (!ft_strncmp(command[0], "echo", 5))
		return (ft_echo);
	/*if (!ft_strncmp(command[0], "cd", 3))
		return (ft_cd);
	if (!ft_strncmp(command[0], "pwd", 4))
		return (ft_pwd);
	/ * if (!ft_strncmp(command[0], "export", 7))
		return (ft_export);
	if (!ft_strncmp(command[0], "unset", 6))
		return (ft_unset); */
	if (!ft_strncmp(command[0], "env", 4))
		return (ft_env);
	/*if (!ft_strncmp(command[0], "exit", 5))
		return (ft_exit);*/
	return (NULL); // Is not a builtin command
}

void	free_matrix(char **matrix)
{
	int	index;

	if (matrix)
	{
		index = 0;
		while (matrix[index])
			free(matrix[index++]);
		free(matrix);
	}
}

void	ft_dup2(int new, int old)
{
	if (new != old)
	{
		dup2(new, old);
		close(new);
	}
}

void	ft_close(int fd, int check)
{
	if (fd < 0)
		return ;
	if (fd != check)
		close(fd);
}

void	find_comment(char *input)
{
	char	*start;

	start = input;
	while (input && *input)
	{
		if (*input == '\'' || *input == '"')
			input = ft_strchr(input + 1, *input);
		if (input && *input == '#')
			if (input == start || ft_isspace(input[-1]))
			{
				*input = 0;
				return ;
			}
		if (input)
			input++;
	}
}

int	ft_is_only_spaces(char *input)
{
	if (input == NULL)
		return (1);
	while(*input)
	{
		if (ft_isspace(*input) == 1)
			input++;
		else
			return (0);
	}
	return (1);
}

void	ft_adjust_delimiters(char *s)
{
	char	*end;

	if (!s)
		return ;
	end = s;
	while (ft_isspace(*end))
		end++;
	if (end != s)
		ft_memmove(s, end, ft_strlen(end) + 1);
	while (*s)
	{
		if (ft_isspace(*s))
		{
			end = s + 1;
			while (ft_isspace(*end))
				end++;
			if (!*end)
				*s = 0;
			else
				*s = ' ';
			if (s + 1 != end)
				ft_memmove(s + 1, end, ft_strlen(end) + 1);
		}
		s++;
	}
}

int	ft_has_invalid_pipe(char *input)
{
	if (input == NULL)
		return (1);
	if (input && *input == '|')
		return (1);
	while (input && *input)
	{
		if (*input == '\'' || *input == '"')
			input = ft_strchr(input + 1, *input);
		if (input && *input == '|')
		{
			input++;
			if (!*input || (*input && input[1] == '|'))
				return (1);
		}
		else if (input)
			input++;
	}
	return (0);
}

int	has_unclosed_quotes(char *input)
{
	if (input == NULL)
		return (1);
	while (*input != '\0')
	{
		if (*input == '\'')
		{
			input = ft_strchr(input + 1, '\'');
			if (input == NULL)
				return (1);
		}
		else if (*input == '"')
		{
			input = ft_strchr(input + 1, '"');
			if (input == NULL)
				return (1);
		}
		input++;
	}
	return (0);
}

int	ft_is_in_set(char c, char const *set)
{
	while (set && *set)
	{
		if (*set++ == c)
			return (1);
	}
	return (0);
}

int	has_redirect_error(char *input)
{
	if (input == NULL)
		return (1);
	while (*input)
	{
		if (*input == '\'' || *input == '"')
			input = ft_strchr(input + 1, *input);
		if (*input == '<' || *input == '>')
		{
			input++;
			if (*input == '<' || *input == '>')
			{
				if (*input != input[-1])
					return (1);
				input++;
			}
			if (!*input || ft_is_in_set(*input, "<>|") || \
				ft_is_in_set(input[1], "<>|"))
				return (1);
		}
		input++;
	}
	return (0);
}

int	has_input_error(char *input)
{
	if (!input)
		return (1);
	find_comment(input);
	ft_adjust_delimiters(input);
	if (ft_is_only_spaces(input))
		return (1);
	if (ft_has_invalid_pipe(input))
		return (1);
	if (has_unclosed_quotes(input))
		return (1);
	if (has_redirect_error(input))
		return (1);
	return (0);
}

char	*ft_readline(char *text)
{
	char	*bkp;
	char	*line;

	bkp = "> ";
	line = malloc(ft_strlen(text) + 3);
	if (!line)
		return (readline(bkp));
	ft_strlcpy(line, text, ft_strlen(text) + 1);
	ft_strlcpy(line + ft_strlen(line), bkp, 3);
	bkp = readline(line);
	free(line);
	return (bkp);
}

void	pre_split(char *input)
{
	if (!input || !*input)
		return ;
	while (*input)
	{
		if (*input == '"' || *input == '\'')
			input = ft_strchr(input + 1, *input);
		if (*input == ' ')
			*input = -1;
		input++;
	}
}

int number_of_redirects(char *str)
{
	int		i;
	int		count;
	char	*quote_address;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote_address = ft_strchr(&str[i + 1], str[i]);
			if (!quote_address)
				return (-1);
			i += quote_address - &str[i];
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			count++;
			if (str[i] == str[i + 1])
				i++;
		}
		i++;
	}
	return (count);
}

char	*redirect(char *str)
{
	char	*start;
	char	*newstr;
	char	*new_aux;

	start = str;
	newstr = ft_calloc(1, ft_strlen(str) + number_of_redirects(str) + 1);
	if (!newstr)
		return (NULL);
	new_aux = newstr;
	while(*str != '\0')
	{
		if (*str == '\'' || *str == '"')
		{
			ft_strlcpy(newstr, str, ft_strchr(str + 1, *str) - str + 1);
			str += ft_strlen(newstr);
			newstr += ft_strlen(newstr);
		}
		else if (*str == '<' || *str == '>')
			if (str > start && ((str[-1] != ' ' && str[1] == *str) || \
				(str[-1] != *str)))
				*newstr++ = ' ';
		*newstr++ = *str++;
	}
	free(start);
	return (new_aux);
}

char	*put_minus_five_after_redirects(char *str)
{
	char	*start;
	char	*newstr;
	char	*new_aux;

	start = str;
	newstr = ft_calloc(1, ft_strlen(str) + number_of_redirects(str) + 1);
	if (!newstr)
		return (NULL);
	new_aux = newstr;
	while(*str)
	{
		if (*str == '\'' || *str == '"')
		{
			ft_strlcpy(newstr, str, ft_strchr(str + 1, *str) - str + 2);
			str += ft_strlen(newstr) - 1;
			newstr += ft_strlen(newstr) - 1;
		}
		*newstr = *str;
		if (str > start && (((str[-1] == '<' || str[-1] == '>') && \
		(*str != '<' && *str != '>') && (*str != ' ' || *str++ == ' '))))
			*newstr++ = -5;
		*newstr++ = *str++;
	}
	free(start);
	return (new_aux);
}

int	count_pipes(char *input)
{
	int	pipes;

	if (input == NULL)
		return (0);
	pipes = 0;
	while (*input != '\0')
	{
		if (*input == '\'' || *input == '"')
			input = ft_strchr(input + 1, *input);
		input++;
		if (*input == '|')
			pipes++;
	}
	return (pipes);
}

char	**insert_command(char *input, char **commands)
{
	int		line;
	char	*start;

	start = input;
	line = 0;
	while (*input)
	{
		if (*input == '\'' || *input == '"')
			input = ft_strchr(input + 1, *input);
		input++;
		if (*input == '|' || *input == '\0')
		{
			commands[line] = ft_substr(start, 0, input - start);
			if (commands[line] == NULL)
			{
				free_matrix(commands);
				return (NULL);
			}
			line++;
			if (*input)
				start = input + 1;
		}
	}
	commands[line] = NULL;
	return (commands);
}

char	**split_commands(char *input)
{
	char	**commands;
	int		line;

	if (input == NULL)
		return (NULL);
	line = 0;
	commands = (char **) malloc ((count_pipes(input) + 2) * sizeof(char*));
	if (commands == NULL)
		return (NULL);
	commands = insert_command(input, commands);
	if (!commands)
		return (NULL);
	return (commands);
}

int	check_file_path_access(char *path, int permission)
{
	struct stat path_stat;

    stat(path, &path_stat);
	if (access(path, F_OK))
		return (127); // No such file/directory
	if (access(path, permission))
		return (126); // Permission denied
	if (S_ISDIR(path_stat.st_mode))
		return (125); // Is a directory
	return (0); // File com execution
}

int	set_envp_and_execute(char **command, t_env *env)
{
	char	**envp;

	envp = list_to_pointer(env);
	if (!envp)
		return (12);
	execve(command[0], command, envp);
	free_matrix(envp);
	return (2);
}

int	print_error(char *command, char *error, int exit_status)
{
	printf("minishel: %s : %s, dude!\n", command, error);
	return (exit_status);
}

int	print_file_error(char *path, int code)
{
	if (code == 125)
		return (print_error(path, "Is a directory", 126));
	if (code == 126)
		return (print_error(path, "Permission denied", 126));
	if (code == 127)
		return (print_error(path, "No such file/directory", 127));
	return (0);
}


char	*find_var(char *input)
{
	char	*start;

	start = input;
	while (input && *input)
	{
		if (-*input > 0 && *input == -1)
			while (*(++input) != -1)
				;
		else if (-*input > 0 && *input == -2)
		{
			while (*++input != -2)
				if (*input == '$' &&\
				(ft_isalpha(input[1]) || input[1] == '_' || input[1] == '?'))
					return (input + 1);
		}
		else if (*input == '$'
			&& (ft_isalpha(input[1]) || input[1] == '_' || input[1] == '?'))
			if (start + 3 > input || input[-2] != '<' || input[-3] != '<')
				return (input + 1);
		if (input)
			input++;
	}
	return (NULL);
}

char	*get_var_name(char *start)
{
	char	*name;
	char	*end;

	if (!start)
		return (NULL);
	end = start;
	if (*end == '?')
		end++;
	else if (ft_isalpha(*end) || *end == '_')
		while (ft_isalnum(*end) || *end == '_')
			end++;
	name = ft_substr(start, 0, end - start);
	if (!name)
		return (NULL);
	return (name);
}

char	*get_value_of_var(char *var, t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->var, var, ft_strlen(var) + 1) == '=')
			return (env->var + ft_strlen(var) + 2);
		env = env->next;
	}
	return (NULL);
}

char	*expand_variables(char *input, t_env *env)
{
	char	*var_start;
	char	*var_name;
	char	*value;
	char	*temp;

	var_start = find_var(input);
	if (!var_start)
		return (input);
	var_name = get_var_name(var_start);
	if (!var_name)
		return (input);
	value = get_value_of_var(var_name, env);
	temp = malloc(var_start - input + (!value) +\
		ft_strlen(value) + (ft_strlen(var_start) - ft_strlen(var_name)));
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, input, var_start - input);
	ft_strlcpy(temp + ft_strlen(temp), value, ft_strlen(value) + 1);
	ft_strlcpy(temp + ft_strlen(temp), var_start + ft_strlen(var_name), \
			ft_strlen(var_start + ft_strlen(var_name)) + 1);
	free(input);
	free(var_name);
	input = temp;
	return (expand_variables(input, env));
}


void	get_redirects(char **command, t_redirects *redirect)
{
	char	**temp;
	t_env	*aux;

	if (!command)
		return ;
	while (*command)
	{
		if(**command == '>' || **command == '<')
		{
			aux = new_node(*command);
			if (!aux)
			{
				free_list(&redirect->redirects);
				return ;
			}
			add_back(&redirect->redirects, aux);
			temp = command - 1;
			free(*command);
			while (*++temp)
				*temp = *(temp + 1);
		}
		else
			command++;
	}
}

int	has_quotes(char *s)
{
	while (s && *s)
	{
		if (*s == '\'' || *s == '"')
			return (1);
		s++;
	}
	return (0);
}


int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void execute_heredoc(int fd, int expandble, char *key, t_env *env)
{
	char *input;
	while (1)
	{
		input = readline("heredoc > ");
		if (!input)
			return;
		if (ft_strcmp(key, input) == 0)
			return;
		if (expandble == 1)
			input = expand_variables(input, env);
		ft_putendl_fd(input, fd);
	}
}

void	set_heredoc(t_redirects *redirect, t_env *env)
{
	t_env	*aux;
	int		pipes[2];
	int		quotemarks;

	aux = redirect->redirects;
	while (aux)
	{
		if (*aux->var == '<' && aux->var[1] == '<')
		{
			pipe(pipes);
			quotemarks = has_quotes(aux->var); // tem aspas
			execute_heredoc(pipes[1], !quotemarks, aux->var + 3, env);
			if (redirect->fd_heredoc != -1)
				close(redirect->fd_heredoc);
			redirect->fd_heredoc = dup(pipes[0]);
			close(pipes[0]);
			close(pipes[1]);
		}
		aux = aux->next;
	}
}

void	set_fds(t_redirects *redirect)
{
	t_env	*aux;

	aux = redirect->redirects;
	while (aux)
	{
		// Fazer expansão de variáveis para fd (detectar)
		if (*aux->var == '<' && aux->var[1] != '<')
		{
			if (redirect->fd_input != 0 && redirect->fd_input != redirect->fd_heredoc)
				close(redirect->fd_input);
			if (!aux->var[2])
				return ; // Ambiguous redirect
			redirect->fd_input = open(aux->var + 2, O_RDONLY);
			if (redirect->fd_input == -1)
				return;
		}
		else if (*aux->var == '<' && aux->var[1] == '<')
		{
			if (redirect->fd_input != 0 && redirect->fd_input != redirect->fd_heredoc)
				close(redirect->fd_input);
			redirect->fd_input = redirect->fd_heredoc; // Quando aparecer um heredoc, apenas trocar o fd de input
		}
		else if (*aux->var == '>' && aux->var[1] == '>')
		{
			if (redirect->fd_output != 1)
				close(redirect->fd_output);
			if (!aux->var[3])
				return ; // Ambiguous redirect
			redirect->fd_output = open(aux->var + 3, O_CREAT | O_APPEND | O_WRONLY, 0644);
			if (redirect->fd_output == -1)
				return ;
		}
		else if (*aux->var == '>' && aux->var[1] != '>')
		{
			if (redirect->fd_output != 1)
				close(redirect->fd_output);
			if (!aux->var[2])
				return ; // Ambiguous redirect
			redirect->fd_output = open(aux->var + 2, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (redirect->fd_output == -1)
				return ;
		}
		aux = aux->next;
	}
}

char	*join_path(char *path_init, char *path_end)
{
	char	*path;

	if (!path_init && !path_end)
		return (NULL);
	path = malloc(ft_strlen(path_init) + ft_strlen(path_end) + 2);
	if (!path)
		return (NULL);
	ft_strlcpy(path, path_init, ft_strlen(path_init) + 1);
	ft_strlcpy(path + ft_strlen(path), "/", 2);
	ft_strlcpy(path + ft_strlen(path), path_end, ft_strlen(path_end) + 1);
	return (path);
}

int	set_path(char **command, t_env *env)
{
	char	**paths;
	char	*path_var;
	int		index;

	path_var = get_value_of_var("PATH", env);
	paths = ft_split(path_var, ':');
	if (path_var && !paths)
		return (12);
	index = -1;
	while (paths && paths[++index])
	{
		path_var = join_path(paths[index], *command);
		if (!path_var || access(path_var, 0) == 0)
			break;
		free(path_var);
	}
	index = (paths[index] != NULL);
	free_matrix(paths);
	if (!path_var)
		return (12);
	if (!index)
		return (0);
	free(*command);
	*command = path_var;
	return (0);
}

int	execute_external_command
(char **cmd, t_env *env, int exit_status, t_redirects red)
{
	int		pid;

	pid = fork();
	init_signals();
	if (pid == 0)
	{
		ft_dup2(red.fd_input, STDIN_FILENO);
		ft_dup2(red.fd_output, STDOUT_FILENO);
		if (!ft_strchr(*cmd, '/'))
			pid = set_path(cmd, env);
		if (*cmd && pid != 12)
		{
			pid = check_file_path_access(cmd[0], X_OK);
			if (pid == 0)
				pid = set_envp_and_execute(cmd, env);
			else if (!ft_strchr(*cmd, '/'))
				printf("%s: command not found ¯\\_(ツ)_/¯\n", *cmd);
			else
				pid = print_file_error(*cmd, pid);
		}
		free_matrix(cmd);
		free_list(&env);
		exit(pid + (pid == 125));
	}
	wait(&exit_status);
	return (WEXITSTATUS(exit_status));
}

int get_read_write_fds(char **command, t_env *env, t_redirects *redir)
{
	redir->redirects = NULL;
	redir->fd_heredoc = -1;
	redir->fd_input = 0;
	redir->fd_output = 1;
	get_redirects(command, redir);
	set_heredoc(redir, env);
	set_fds(redir);
	free_list(&redir->redirects);
	if (redir->fd_input == -1 || redir->fd_output == -1)
	{
		if (redir->fd_input > 0)
			close(redir->fd_input);
		if (redir->fd_output > 1)
			close(redir->fd_output);
		if (redir->fd_heredoc > -1)
			close(redir->fd_heredoc);
		return (-1);
	}
	if (redir->fd_input != redir->fd_heredoc && redir->fd_heredoc > -1)
		close(redir->fd_heredoc);
	return (0);
}

int	get_index(char c, char *s)
{
	int	index = 0;

	while(s && s[index])
	{
		if (c == s[index])
			return (index);
		index++;
	}
	return (-1);
}

void	ft_modify_quotemarks_to_remove(char *input, char *set)
{
	char	quote;
	int		index;

	while (input && *input)
	{
		if (ft_is_in_set(*input, set))
		{
			quote = *input;
			index = get_index(quote, set);
			if (index != -1)
				*input = (-index) - 1;
			input = ft_strchr(input, quote);
			index = get_index(quote, set);
			if (index != -1)
				*input = (-index) - 1;
		}
		input++;
	}
}

void	ft_removing_modified_quotemarks(char *input, char *set)
{
	while (input && *input)
	{
		if (-*input > 0 && -(*input) <= (int)ft_strlen(set))
			ft_memmove(input, input + 1, ft_strlen(input));
		else if (*input)
			input++;
	}
}


int	ft_check_before_tilde(char *input, char *start)
{
	if (!input || input == start)
		return (0);
	if (input < start)
		return (1);
	if (*input == '=')
	{
		if (ft_isalpha(*start) || *start == '_')
		{
			start++;
			while (ft_isalnum(*start) || *start == '_')
				start++;
		}
		else
			return (0);
		if (start == input)
			return (1);
	}
	return (0);
}

int	ft_check_after_tilde(char *input)
{
	if (!input)
		return (0);
	if (!*input)
		return (1);
	if (*input == '/' || *input == ':')
		return (1);
	return (0);
}

char	*make_string(char *start, char *tilde_position, t_env *env)
{
	char	*string;
	char	*expansion;

	expansion = get_value_of_var("HOME", env);
	if (!expansion)
		return (start);
	string = malloc(tilde_position - start + ft_strlen(expansion) + 
				ft_strlen(tilde_position) + 1);
	if (!string)
		return (start);
	ft_strlcpy(string, start, tilde_position - start + 1);
	ft_strlcpy(string + ft_strlen(string), expansion, 
				ft_strlen(expansion) + 1);
	ft_strlcpy(string + ft_strlen(string), tilde_position + 1, 
				ft_strlen(tilde_position));
	free(start);
	free(expansion);
	return (string);
}

char	*tilde_expansion(char *input, t_env *env)
{
	char	*current;

	if (!input)
		return (NULL);
	current = input;
	while (*current)
	{
		if (*current == '\'' || *current == '"')
			current = ft_strchr(current + 1, *current);
		if (*current == '~')
		{
			if (ft_check_before_tilde(&current[-1], input)
				&& ft_check_after_tilde(&current[1]))
				return (make_string(input, current, env));
			else
				break;
		}
		current++;
	}
	return (input);
}

char	*make_expansions_and_remove_quotes(char *input, t_env *env)
{
	char	*temp;

	if (input)
	{
		input = tilde_expansion(input, env);
		ft_modify_quotemarks_to_remove(input, "'\"");
		temp = input;
		input = expand_variables(input, env); 
		if (!input)
		{
			free(temp);
			return (NULL);
		}
		ft_removing_modified_quotemarks(input, "'\"");
	}
	return (input);
}

int	execute_one_command(char **command, t_env *env, int exit_s)
{
	char		**splitted;
	int			(*builtin)(char **, int, int, t_env *);
	t_redirects	redirect;

	*command = make_expansions_and_remove_quotes(*command, env);
	if (!*command)
		return (12);
	pre_split(*command);
	splitted = ft_split(*command, -1);
	if (!splitted)
		return (12);
	free_matrix(command);
	if (get_read_write_fds(splitted, env, &redirect) == -1)
	{
		free_matrix(splitted);
		return (2);
	}
	builtin = set_builtin(splitted);
	if (builtin != NULL)
		exit_s = builtin(splitted, redirect.fd_input, redirect.fd_output, env);
	else
		exit_s = execute_external_command(splitted, env, exit_s, redirect);
	free_matrix(splitted);
	ft_close(redirect.fd_input, STDIN_FILENO);
	ft_close(redirect.fd_output, STDOUT_FILENO);
	return (exit_s);
}

int	count_commands(char **cmd)
{
	int	count;

	count = 0;
	if (!cmd)
		return (0);
	while (cmd[count])
		count++;
	return (count);
}

int	prepare_multiple_commands(char **commands, t_env *env, int exit_status)
{
	int	pipes[2];
	int	bkp_input;
	int	*fork_pids;
	int	index;
	int	command_index;
	char	**copy;

	bkp_input = 0;
	index = 0;
	command_index = 0;
	fork_pids = ft_calloc(count_commands(commands) + 1, sizeof(int));
	while (commands[command_index])
	{
		if (commands[1])
			pipe(pipes);
		fork_pids[index] = fork();
		init_signals();
		if (fork_pids[index++] == 0)
		{
			free(fork_pids);
			if (bkp_input)
				ft_dup2(bkp_input, STDIN_FILENO);
			close(pipes[0]);
			if (commands[1])
				ft_dup2(pipes[1], STDOUT_FILENO);
			copy = split_commands(commands[command_index]);
			free_matrix(commands);
			exit_status = execute_one_command(copy, env, exit_status);
			free_list(&env);
			exit(exit_status);
		}
		ft_close(bkp_input, STDIN_FILENO);
		bkp_input = dup(pipes[0]);
		close(pipes[0]);
		close(pipes[1]);
		command_index++;
	}
	close(bkp_input);
	index = -1;
	while (fork_pids[++index])
		waitpid(fork_pids[index], &exit_status, 0);	
	return (WEXITSTATUS(exit_status));
}

int		do_the_hard_work(char *input, t_env *env, int exit_status)
{
	char	**commands;

	input = redirect(input);
	if (!input)
		return (0);
	input = put_minus_five_after_redirects(input);
	if (!input)
		return (0);
	/** heredocs (Fazer com que eles abram, sejam inseridos numa lista 
	 * encadeada)
	 * Salvar o delimitador do heredoc e o fd (transformar int em string);
	 * Quando for a hora de executar, buscar o fd com base no heredoc
	 * 
	 **/
	commands = split_commands(input);
	if (!commands)
		return (0);
	free(input);
	if (commands[1])
		exit_status = prepare_multiple_commands(commands, env, exit_status);
	else
		exit_status = execute_one_command(commands, env, exit_status), commands = NULL;
	//free_matrix(commands);
	free(commands);
	return (exit_status);
}

int	minishell(t_env *env) // restam 4 linhas
{
	char	*input;
	char	*cwd;
	int		exit_status;

	input = NULL;
	init_signals();
	exit_status = 0;
	while (1)
	{
		cwd = getcwd(NULL, 0);
		input = ft_readline(cwd);
		free(cwd);
		if (has_input_error(input))
		{
			if (!input)
				break;
			ft_putendl_fd("Do you really know how to type a command?"\
			" ヽ( `д´*)ノ", 2);
			free(input);
			continue ;
		}
		exit_status = do_the_hard_work(input, env, exit_status);
	}
	free_list(&env);
	ft_putendl_fd("exit", 1);
	return (exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*list;

	if (argc > 1 || argv[1])
	{
		ft_putendl_fd("EXECUTE ME PROPERLY, YOU ASSHOLE!!! ┗|｀O′|┛", 2);
		return (2);
	}
	list = pointer_to_list(envp);
	if (!list)
	{
		ft_putendl_fd("You don't have space, bro! (っ˘̩╭╮˘̩)っ", 2);
		return (ENOMEM);
	}
	return (minishell(list));
}