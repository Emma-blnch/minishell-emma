/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:01:57 by ahamini           #+#    #+#             */
/*   Updated: 2025/02/27 09:51:38 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quoting_choice(bool *d_quote, bool *s_quote, int *index, char c)
{
	if ((c == '\'' || c == '"') && !*s_quote && !*d_quote)
	{
		if (c == '\'' && !*d_quote)
			*s_quote = true;
		else if (c == '"' && !*s_quote)
			*d_quote = true;
		if (index)
			++(*index);
	}
	else if ((c == '\'' || c == '"'))
	{
		if (c == '\'' && !*d_quote && *s_quote)
			*s_quote = false;
		else if (c == '"' && !*s_quote && *d_quote)
			*d_quote = false;
		if (index)
			++(*index);
	}
}

int	open_quote(t_shell *shell, char *input)
{
	bool	double_quote;
	bool	simple_quote;
	int		i;

	i = 0;
	double_quote = false;
	simple_quote = false;
	while (input && input[i])
	{
		quoting_choice(&double_quote, &simple_quote, &i, input[i]);
		if (input[i] && input[i] != '\'' && input[i] != '"')
			++i;
	}
	if (double_quote || simple_quote)
	{
		print_error2("err : open quote\n");
		shell->exit_code = 2;
		return (1);
	}
	return (0);
}
