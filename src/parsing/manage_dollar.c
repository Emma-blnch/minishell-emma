/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:15:25 by ahamini           #+#    #+#             */
/*   Updated: 2025/02/25 16:13:46 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	in_env(t_shell *shell, char *line, int size, char **str)
{
	char	*tmp;
	char	*key;
	char	*value;

	key = get_dollar_word(line, size);
	value = get_elem_env(shell->env, key);
	if (!value)
		value = ft_strdup("");
	if (key)
		free(key);
	tmp = ft_strjoin(*str, value);
	if (value)
		free(value);
	free(*str);
	if (!tmp)
		return (0);
	*str = tmp;
	return (1);
}

static int	dollar_point_interrogation(t_shell *shell, char **str)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_itoa(shell->exit_code);
	if (!tmp)
		return (0);
	tmp2 = ft_strjoin(*str, tmp);
	free(tmp);
	free(*str);
	if (!tmp2)
		return (0);
	*str = tmp2;
	return (1);
}

int	add_dollar(char *line, int *index, char **str, t_shell *shell)
{
	int		ctrl;
	int		n;

	n = *index;
	ctrl = exist_in_env(line, index, shell);
	if (ctrl == 1)
		return (in_env(shell, &line[n], *index - n, str));
	else if (ctrl == 2)
	{
		(*index) += 2;
		return (dollar_point_interrogation(shell, str));
	}
	else
	{
		// ++(*index);
		// while (line[*index] && \
		// 	(ft_isalnum(line[*index]) || line[*index] == '_'))
		// 	++(*index);
		return (1);
	}
}

int	add_char(char *c, char **str, t_shell *shell, int *index)
{
	char	char_to_str[2];
	char	*tmp2;
	int		i;

	i = 0;
	if (c[i] == '$' && !shell->squote && exist_in_env(c, &i, shell))
		return (1);
	char_to_str[0] = *c;
	char_to_str[1] = '\0';
	(*index)++;
	tmp2 = ft_strjoin(*str, char_to_str);
	free(*str);
	if (!tmp2)
		return (0);
	*str = tmp2;
	return (1);
}

int	replace_dollar(char **line, t_shell *shell)
{
	bool	dquote;
	int		i;
	char	*str;

	i = 0;
	dquote = false;
	shell->squote = false;
	str = ft_strdup("");
	while ((*line)[i])
	{
		quoting_choice(&dquote, &shell->squote, NULL, (*line)[i]);
		if ((*line)[i] && (*line)[i + 1] && (*line)[i] == '$' && \
			((*line)[i + 1] != '\'' && (*line)[i + 1] != '"') && \
			(ft_isalpha((*line)[i + 1]) || (*line)[i + 1] == '?' || \
			(*line)[i + 1] == '_') && !shell->squote && \
			!add_dollar((*line), &i, &str, shell))
			return (0);
		if ((*line)[i] && !add_char(&(*line)[i], &str, shell, &i))
			return (0);
	}
	free(*line);
	*line = str;
	return (1);
}