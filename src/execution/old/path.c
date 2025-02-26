/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:47:39 by ahamini           #+#    #+#             */
/*   Updated: 2025/02/24 11:21:26 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Sets the command's table env to NULL
Extract path from env if env exists
Splits it into an array of possible path
Loads it into the command table */
int	extract_paths(t_shell *shell)
{
	char	*path;
	int		index;

	path = NULL;
	shell->paths = NULL;
	index = 0;
	while (shell->envp[index])
	{
		if (ft_strncmp(shell->envp[index], "PATH=", 5) == 0)
		{
			path = ft_substr(shell->envp[index], 5,
					ft_strlen(shell->envp[index]));
			if (!path)
			{
				set_error_if(!path, MALLOC_FAIL, shell,
					"Failed to allocate for path");
				ft_free_tab(shell->envp);
				return (-1);
			}
			shell->paths = ft_split(path, ':');
			if (!shell->paths)
			{
				set_error_if(!shell->paths, MALLOC_FAIL, shell,
					"Failed to split path variable");
				ft_free_tab(shell->paths);
				return (-1);
			}
			free(path);
			return (0);
		}
		index++;
	}
	return (0);
}

/*int	is_a_directory(char *path)
{
	int	fd;

	fd = open(path, __O_DIRECTORY);
	if (fd < 0)
		return (0);
	close (fd);
	return (1);
}

void	check_cmd(t_cmd *cmd)
{
	if (cmd->cmd_path == NULL)
		return (set_cmd_error(CANT_FIND_CMD, cmd, "Command not found"));
	if (is_a_directory(cmd->cmd_path))
		return (set_cmd_error(CANT_EXECUTE_CMD, cmd, "Command is a directory"));
	if (access(cmd->cmd_path, X_OK) != 0)
		return (set_cmd_error(CANT_EXECUTE_CMD, cmd, "Command cannot be executed"));
}

void	find_accessible_path(t_shell *shell, t_cmd *cmd)
{
	char	*tested_path;
	size_t	i;

	i = 0;
	while (shell->paths[i])
	{
		tested_path = ft_strjoin(shell->paths[i++], cmd->cmd_path);
		if (!tested_path)
			return (set_cmd_error(MALLOC_FAIL, cmd, "Failed to allocate path"));
		if (access(tested_path, F_OK | R_OK) == 0)
		{
			cmd->cmd_path = tested_path;
			return ;
		}
		free(tested_path);
	}
	cmd->cmd_path = NULL;
}

void	get_cmd_path(t_shell *shell, t_cmd *cmd)
{
	if (ft_strchr(cmd->arg_list->content, '/'))
		cmd->cmd_path = ft_strdup(cmd->arg_list->content);
	else
		cmd->cmd_path = ft_strjoin("/", cmd->arg_list->content);
	
	if (!cmd->cmd_path)
		return (set_cmd_error(MALLOC_FAIL, cmd, "Failed to allocate path"));
	
	if (access(cmd->cmd_path, F_OK) == 0)
		return (check_cmd(cmd));
	
	if (!shell->paths)
		return (set_cmd_error(CANT_FIND_CMD, cmd, "No PATH variable found"));

	find_accessible_path(shell, cmd);
	check_cmd(cmd);
}*/


