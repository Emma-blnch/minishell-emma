/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:19:57 by skassimi          #+#    #+#             */
/*   Updated: 2025/02/13 08:44:08 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*find_env(t_list *env_list, char *env_name)
{
	size_t	len;
	char	*equal_pos;

	if (!env_list || !env_name)
		return (NULL);
	equal_pos = ft_strchr(env_name, '=');
	len = equal_pos ? (size_t)(equal_pos - env_name) : ft_strlen(env_name);
	while (env_list)
	{
		if (ft_strncmp(env_list->content, env_name, len) == 0
			&& (((char *)env_list->content)[len] == '=' || ((char *)env_list->content)[len] == '\0'))
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}



int	unset(t_shell *shell, char **argv)
{
	int		i;
	t_list	*to_be_unset;

	i = 1;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '=')) // Vérifie si l'argument contient '='
		{
			ft_putstr_fd("unset: ", STDERR_FILENO);
			ft_putstr_fd(argv[i], STDERR_FILENO);
			ft_putstr_fd(": invalid parameter name\n", STDERR_FILENO);
		}
		else
		{
			to_be_unset = find_env(shell->env_list, argv[i]);
			if (to_be_unset)
				ft_lstpop(&shell->env_list, to_be_unset, free);
		}
		i++;
	}
	return (0);
}
