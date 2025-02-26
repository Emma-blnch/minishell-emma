/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:00:25 by reldnah           #+#    #+#             */
/*   Updated: 2025/02/26 08:49:27 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_builtin(int save_stdout, t_shell *data, t_cmd *cmd)
{
	if (!ft_strncmp("echo", cmd->cmd_param[0], INT_MAX))
		data->exit_code = echo(cmd->cmd_param);
	else if (!ft_strncmp("cd", cmd->cmd_param[0], INT_MAX))
		data->exit_code = cd(data, cmd->cmd_param);
	else if (!ft_strncmp("pwd", cmd->cmd_param[0], INT_MAX))
		data->exit_code = pwd();
	else if (!ft_strncmp("export", cmd->cmd_param[0], INT_MAX))
		data->exit_code = export(cmd->cmd_param, &data->env);
	else if (!ft_strncmp("unset", cmd->cmd_param[0], INT_MAX))
		data->exit_code = ft_unset(cmd->cmd_param, &data->env);
	else if (!ft_strncmp("env", cmd->cmd_param[0], INT_MAX))
		data->exit_code = env(data->env);
	else if (!ft_strncmp("exit", cmd->cmd_param[0], INT_MAX))
	{
		if (cmd->outfile >= 0)
		{
			dup2(save_stdout, 1);
			close(save_stdout);
		}
		ft_exit(data, cmd->cmd_param);
	}
}

bool	launch_builtin(t_shell *data, t_cmd *cmd)
{
	int	save_stdout;

	save_stdout = -1;
	if (cmd->outfile >= 0)
	{
		save_stdout = dup(1);
		dup2(cmd->outfile, 1);
	}
	exec_builtin(save_stdout, data, cmd);
	if (cmd->outfile >= 0)
	{
		dup2(save_stdout, 1);
		close (save_stdout);
	}
	return (true);
}
