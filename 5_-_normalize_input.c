#include "minishell.h" 

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

void	ft_adjust_delimiters(char *s)
{
	char	*end;

	end = s;
	while (ft_isspace(*end))
		end++;
	if (end != s)
		ft_memmove(s, end, ft_strlen(end) + 1);
	while (*s)
	{
		if (*s == '\''  || *s == '"')
			s = ft_strchr(s + 1, *s);
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
