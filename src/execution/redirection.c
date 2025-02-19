/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:46:20 by ahamini           #+#    #+#             */
/*   Updated: 2025/02/19 15:11:50 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(t_file *file, t_cmd *cmd, int mode)
{
	int	flags;

	if (mode == READ)
		flags = O_RDONLY;
	else if (mode == WRITE)
		flags = O_WRONLY | O_TRUNC | O_CREAT;
	else if (mode == APPEND)
		flags = O_RDWR | O_APPEND | O_CREAT;
	file->fd = open(file->path, flags, 0666);
	if (file->fd == -1)
	{
		set_cmd_error(OPEN_ERROR, cmd, "Error while opening file");
		return (-1);
	}
	return (file->fd);
}

void    get_input_fd(t_shell *shell, t_cmd *cmd)
{
    t_file  *file;

    if (cmd->infiles == NULL)
    {
        (cmd->fd_in = STDIN_FILENO);
        return ;
    }
    file = (t_file *)cmd->infiles->content;
    if (file->mode == HEREDOC)
        manage_heredoc(shell, cmd, cmd->infiles);
    else
    {
        if (access(file->path, F_OK) == -1)
            return (set_cmd_error(NO_FILE, cmd, "Input file not found"));
        if (access(file->path, R_OK) == -1)
            return (set_cmd_error(READ_ERROR, cmd, "Permission denied for input file"));
        cmd->fd_in = open(file->path, O_RDONLY);
        if (cmd->fd_in == -1)
            return (set_cmd_error(OPEN_ERROR, cmd, "Failed to open input file"));
    }
}

void    get_output_fd(t_cmd *cmd)
{
    t_file  *file;

    if (cmd->outfiles == NULL)
    {
        (cmd->fd_out = STDOUT_FILENO);
        return ;
    }
    file = (t_file *)cmd->outfiles->content;
    if (access(file->path, F_OK) == 0 && access(file->path, W_OK) == -1)
        return (set_cmd_error(READ_ERROR, cmd, "Write permission denied on output file"));
    int flags = O_WRONLY | O_CREAT | O_TRUNC;
    cmd->fd_out = open(file->path, flags, 0644);
    if (cmd->fd_out == -1)
        return (set_cmd_error(OPEN_ERROR, cmd, "Failed to open output file"));
}


int	connect_pipes_and_exec(t_shell *shell, t_tree *tree, int pipe_fd[2], int mode)
{
	int	exit_code;

	if (mode == WRITE)
	{
		close(pipe_fd[READ]);
		dup2(pipe_fd[WRITE], STDOUT_FILENO);
		close(pipe_fd[WRITE]);
	}
	if (mode == READ)
	{
		close(pipe_fd[WRITE]);
		dup2(pipe_fd[READ], STDIN_FILENO);
		close(pipe_fd[READ]);
	}
	exit_code = exec_tree(shell, tree, true);
	exit (exit_code);
}

void    redirect_for_cmd(t_shell *shell, t_cmd *cmd)
{
    if (catch_error(shell))
        return ;
    get_input_fd(shell, cmd);
    get_output_fd(cmd);
    if (cmd->exit_code)
        return ;
    if (cmd->fd_in != STDIN_FILENO && dup2(cmd->fd_in, STDIN_FILENO) == -1)
    {
        set_cmd_error(DUP_ERROR, cmd, "Error redirecting input");
        return ;
    }
    if (cmd->fd_out != STDOUT_FILENO && dup2(cmd->fd_out, STDOUT_FILENO) == -1)
    {
        set_cmd_error(DUP_ERROR, cmd, "Error redirecting output");
        return ;
    }
}
