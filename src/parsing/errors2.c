/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:41:42 by ahamini           #+#    #+#             */
/*   Updated: 2025/02/27 09:51:03 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(void)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
}

void	set_error(int err_code, t_shell *shell, char *err_message)
{
	print_error();
	ft_putstr_fd(err_message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	shell->exit_code = err_code;
}

void	set_error_if(int condition, int err_code, t_shell *shell,
	char *err_message)
{
	if (condition)
		set_error(err_code, shell, err_message);
}
