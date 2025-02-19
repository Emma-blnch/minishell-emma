/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readability.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:47:46 by ahamini           #+#    #+#             */
/*   Updated: 2025/02/19 16:06:04 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int create_process_or_pipe(t_shell *shell, int *fd, bool is_pipe)
{
    int result;

    if (is_pipe)
    {
        result = pipe(fd);
        if (result != 0)
            return (set_error(PIPE_ERROR, shell, "Failed to pipe"), PIPE_ERROR);
    }
    else
    {
        *fd = fork();
        if (*fd == -1)
            return (set_error(FORK_ERROR, shell, "Failed to fork"), FORK_ERROR);
    }
    return (0);
}

void	close_pipe(int *pipe_fd)
{
	close(pipe_fd[READ]);
	close(pipe_fd[WRITE]);
}

void	reset_std(t_shell *shell, bool piped)
{
	if (piped)
		return ;
	dup2(shell->std_in, 0);
	dup2(shell->std_out, 1);
}

