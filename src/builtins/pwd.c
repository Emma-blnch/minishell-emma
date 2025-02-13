/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:19:40 by skassimi          #+#    #+#             */
/*   Updated: 2025/02/13 09:01:18 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(int fdout)
{
	char	*cwd;

	if (fdout < 0)
		return (-1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("pwd"), -1);
	ft_putstr_fd(cwd, fdout);
	write(fdout, "\n", 1);
	free(cwd);
	return (0);
}

