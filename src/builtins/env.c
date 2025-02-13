/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:20:08 by skassimi          #+#    #+#             */
/*   Updated: 2025/02/13 10:55:41 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extract_env_as_linked_list(t_shell *shell)
{
	int		index;

	index = 0;
	while (shell->env[index])
	{
		ft_lstadd_back(&shell->env_list,
			ft_lstnew(ft_strdup(shell->env[index])),ENV);
		index++;
	}
}

int	env(t_shell *shell, int fdout)
{
	t_list	*current;

	current = shell->env_list;
	while (current != NULL)
	{
		ft_putstr_fd((char *)current->content, fdout);
		write(fdout, "\n", 1);
		current = current->next;
	}
	return (0);
}
