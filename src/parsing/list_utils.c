/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:53:26 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/02/27 10:01:42 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	len_list(t_list *list)
{
	t_list	*tmp;
	size_t	i;

	if ((list))
	{
		tmp = list;
		i = 1;
		while (tmp->next != list)
		{
			++i;
			tmp = tmp->next;
		}
		return (i);
	}
	return (0);
}

char	**lst_to_arr(t_list *env)
{
	t_list	*lst;
	char	**dest;
	int		i;

	dest = NULL;
	i = 0;
	lst = env;
	dest = (char **)malloc(sizeof(char *) * (len_list(lst) + 1));
	if (!dest)
		return (NULL);
	dest[i] = (lst->str);
	lst = lst->next;
	i++;
	while (lst != env)
	{
		dest[i] = (lst->str);
		lst = lst->next;
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

static bool	operator_error2(t_shell *shell)
{
	if (shell->token && shell->token->prev->type == HEREDOC)
	{
		write(2, "Error: Unclosed heredoc\n", 21);
		shell->exit_code = 2;
		free_token(&shell->token);
		return (false);
	}
	if (shell->token && shell->token->prev->type == INPUT)
	{
		write(2, "Error: Unclosed input\n", 21);
		shell->exit_code = 2;
		free_token(&shell->token);
		return (false);
	}
	if (shell->token && shell->token->prev->type == TRUNC)
	{
		write(2, "Error: Unclosed trunc\n", 21);
		shell->exit_code = 2;
		free_token(&shell->token);
		return (false);
	}
	return (true);
}

bool	operator_error(t_shell *shell)
{
	if (shell->token && shell->token->prev->type == PIPE)
	{
		write(2, "Error: Unclosed pipe\n", 21);
		shell->exit_code = 2;
		free_token(&shell->token);
		return (false);
	}
	if (shell->token && shell->token->prev->type == APPEND)
	{
		write(2, "Error: Unclosed append\n", 21);
		shell->exit_code = 2;
		free_token(&shell->token);
		return (false);
	}
	operator_error2(shell);
	return (true);
}
