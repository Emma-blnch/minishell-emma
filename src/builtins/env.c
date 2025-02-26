/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:20:08 by skassimi          #+#    #+#             */
/*   Updated: 2025/02/26 10:32:05 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	extract_env_as_linked_list(t_shell *shell)
// {
// 	int		index;

// 	index = 0;
// 	while (shell->envp[index])
// 	{
// 		ft_lstadd_back(&shell->env,
// 			ft_lstnew(ft_strdup(shell->envp[index])),ENV);
// 		index++;
// 	}
// }

int	env(t_list *env)
{
	t_list	*temp;

	temp = env;
	if (!temp)
		return (0);
	if (ft_strchr(temp->str, '='))
		printf("%s\n", temp->str);
	temp = temp->next;
	while (temp != env)
	{
		if (ft_strchr(temp->str, '='))
			printf("%s\n", temp->str);
		temp = temp->next;
	}
	return (0);
}
