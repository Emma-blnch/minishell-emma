/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:27:38 by handler           #+#    #+#             */
/*   Updated: 2025/02/26 08:46:03 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_dir(char **path, char *cmd, t_shell *data)
{
	struct stat	path_stat;

	stat(*path, &path_stat);
	if (!S_ISREG(path_stat.st_mode))
	{
		print_error2(cmd);
		print_error2(" : Is a directory\n");
		data->exit_code = 126;
		return (false);
	}
	return (true);
}

static bool	cmd_exist(char **path, t_shell *data, char *cmd)
{
	if (!ft_strchr(cmd, '/'))
		*path = find_cmd(data, cmd, data->env);
	else
		absolute_path(path, cmd, data);
	if (!(*path) && data->exit_code == -1)
		free_all(data, NULL, data->exit_code);
	if (!(*path))
	{
		data->exit_code = 127;
		return (false);
	}
	if (access((*path), X_OK))
	{
		perror(*path);
		free((*path));
		(*path) = NULL;
		data->exit_code = 126;
		return (false);
	}
	if (!check_dir(path, cmd, data))
		return (false);
	return (true);
}

static void	redirect_in_out(t_shell *data, t_cmd *cmd, int *pip)
{
	close(pip[0]);
	if (cmd->infile >= 0)
	{
		dup2(cmd->infile, 0);
		close(cmd->infile);
	}
	if (cmd->outfile >= 0)
	{
		dup2(cmd->outfile, 1);
		close(cmd->outfile);
	}
	else if (cmd->next != data->cmd)
		dup2(pip[1], 1);
	close(pip[1]);
}

static void	built(int *pip, t_cmd *cmd, t_shell *data)
{
	close(pip[0]);
	if (cmd->outfile < 0 && cmd->next != data->cmd)
		cmd->outfile = pip[1];
	else
		close(pip[1]);
	launch_builtin(data, cmd);
}

void	child_process(t_shell *data, t_cmd *cmd, int *pip)
{
	char	*path;
	char	**env;

	path = NULL;
	if (cmd->skip_cmd)
		data->exit_code = 1;
	else if (is_builtin(cmd->cmd_param[0]))
		built(pip, cmd, data);
	else if (cmd_exist(&path, data, cmd->cmd_param[0]))
	{
		redirect_in_out(data, cmd, pip);
		env = lst_to_arr(data->env);
		if (!env)
			free_all(data, ERR_MALLOC, EXT_MALLOC);
		rl_clear_history();
		signals2();
		execve(path, cmd->cmd_param, env);
		free(env);
	}
	if (path)
		free(path);
	free_all(data, NULL, data->exit_code);
}
