/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:46:35 by ahamini           #+#    #+#             */
/*   Updated: 2025/02/13 11:58:41 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmd *cmd)
{
	char	*argv0;
	t_list	*arg = cmd->arg_list;

	while (arg)
	{
		printf("arg: %s\n", (char *)arg->content);  // Affiche chaque argument
        arg = arg->next;
	}
	if (!cmd || !cmd->arg_list)
		return (0);
	argv0 = (char *)cmd->arg_list->content;
	if (ft_strcmp(argv0, "cd") == 0)
		return (1);
	//printf("arg: %s\n", argv0);
	if (ft_strcmp(argv0, "echo") == 0)
		return (1);
	if (ft_strcmp(argv0, "env") == 0)
		return (1);
	if (ft_strcmp(argv0, "export") == 0)
		return (1);
	if (ft_strcmp(argv0, "unset") == 0)
		return (1);
	if (ft_strcmp(argv0, "pwd") == 0)
		return (1);
	if (ft_strcmp(argv0, "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_shell *shell, t_cmd *cmd)
{
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (cd(shell, cmd->argv[1]));
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (echo(cmd->argv, cmd->fd_out));
	if (ft_strcmp(cmd->argv[0], "env") == 0)
            return (env(shell, cmd->fd_out));
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (export(shell, cmd->argv, cmd->fd_out));
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (unset(shell, cmd->argv));
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (pwd(cmd->fd_out));
	else
		exit_shell(shell, cmd->argv);
	return (1);
}
