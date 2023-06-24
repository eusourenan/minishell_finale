#include "minishell.h" 

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

int	ft_is_in_set(char c, char const *set)
{
	while (set && *set)
	{
		if (*set++ == c)
			return (1);
	}
	return (0);
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
