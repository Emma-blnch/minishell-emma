/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:19:50 by skassimi          #+#    #+#             */
/*   Updated: 2025/02/13 08:45:36 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_or_add_env(t_shell *shell, char *var)
{
	t_list	*existing_var;

	existing_var = find_env(shell->env_list, var);
	if (existing_var)
	{
		free(existing_var->content);
		existing_var->content = ft_strdup(var);
		if (!existing_var->content)
			return (-1);
	}
	else
	{
		existing_var = ft_lstnew(ft_strdup(var));
		if (!existing_var || !existing_var->content)
			return (-1);
		ft_lstadd_back(&shell->env_list, existing_var, ENV);
	}
	return (0);
}

int	export(t_shell *shell, char **argv, int fdout)
{
	int		i;
	t_list	*current_env;

	if (fdout < 0)
		return (-1);
	if (!argv[1])
	{
		current_env = shell->env_list;
		while (current_env)
		{
			ft_putstr_fd("export ", fdout);
			ft_putstr_fd((char *)current_env->content, fdout);
			write(fdout, "\n", 1);
			current_env = current_env->next;
		}
		return (0);
	}
	i = 1;
	while (argv[i])
		if (update_or_add_env(shell, argv[i++]) == -1)
			return (-1);
	return (0);
}


