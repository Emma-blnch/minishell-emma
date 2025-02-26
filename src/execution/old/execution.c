/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:47:21 by ahamini           #+#    #+#             */
/*   Updated: 2025/02/24 11:13:00 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	exec_with_process(t_shell *shell, t_cmd *cmd)
{
	if (cmd->exit_code)
		return (cmd->exit_code);
	if (create_process_or_pipe(shell, &cmd->fork_pid, false) != 0)
		return (FORK_ERROR);
	if (cmd->fork_pid == 0)
	{
		redirect_for_cmd(shell, cmd);
		if (cmd->exit_code)
			exit(cmd->exit_code);
		get_cmd_path(shell, cmd);
		if (!cmd->cmd_path)
			exit(cmd->exit_code);
		command_into_array(cmd);
		if (!cmd->argv)
			exit(cmd->exit_code);
		execve(cmd->cmd_path, cmd->argv, shell->env);
		exit(CANT_EXECUTE_CMD);
	}
	waitpid(cmd->fork_pid, &cmd->exit_code, 0);
	return (cmd->exit_code);
}

int	exec_with_builtin(t_shell *shell, t_cmd *cmd, bool piped)
{
	command_into_array(cmd);
	if (!cmd->argv)
		return (cmd->exit_code);
	redirect_for_cmd(shell, cmd);
	if (cmd->exit_code)
		return (cmd->exit_code);
	exec_builtin(shell, cmd);
	reset_std(shell, piped);
	return (cmd->exit_code);
}

int	exec_one_cmd(t_shell *shell, t_tree *tree, bool piped)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)tree->content;
	if (!cmd->arg_list || cmd->exit_code)
	{
		redirect_for_cmd(shell, cmd);
		reset_std(shell, piped);
	}
	else if (is_builtin(cmd))
		exec_with_builtin(shell, cmd, piped);
	else
		exec_with_process(shell, cmd);
	return (cmd->exit_code);
}

int exec_pipe(t_shell *shell, t_tree *tree)
{
    int pipe_fd[2];
    int fork_pid[2];
    int exit_code;

    if (create_process_or_pipe(shell, pipe_fd, true) != 0)
        return (PIPE_ERROR);
    if (create_process_or_pipe(shell, &fork_pid[0], false) != 0)
        return (FORK_ERROR);
    if (fork_pid[0] == 0)
        connect_pipes_and_exec(shell, tree->left, pipe_fd, WRITE);
    else
    {
        if (create_process_or_pipe(shell, &fork_pid[1], false) != 0)
            return (FORK_ERROR);
        if (fork_pid[1] == 0)
            connect_pipes_and_exec(shell, tree->right, pipe_fd, READ);
        else
        {
            close_pipe(pipe_fd);
            waitpid(fork_pid[0], &exit_code, 0);
            waitpid(fork_pid[1], &exit_code, 0);
            return exit_code;
        }
    }
    return (PIPE_ERROR);
}*/


int	exec_tree(t_shell *shell)
{
	t_cmd	*tmp;
	int		*pip;

	pip = shell->pip;
	tmp = shell->cmd;
	printf("cmd_param:%s\n", tmp->cmd_param[0]);
	if (tmp && tmp->skip_cmd == false && tmp->next == tmp && tmp->cmd_param[0] \
		&& is_builtin(tmp->cmd_param[0]))
		return (launch_builtin(shell, tmp));
	if (pipe(pip) == -1)
		return (false);
	/*if (shell->type == AST_PIPE)
	{
		//printf("hello pipe\n");
		return (exec_pipe(shell));
	}
	return (exec_one_cmd(shell));*/
	return (true);
}
