/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:52:05 by ema_blnch         #+#    #+#             */
/*   Updated: 2025/02/27 09:52:24 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigtstp(int code)
{
	(void)code;
	if (g_signal_pid > 0)
	{
		printf("\n[Minishell] Processus suspendu : %d\n", g_signal_pid);
		kill(g_signal_pid, SIGSTOP);
		clear_rl_line();
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		clear_rl_line();
		printf("\n[Minishell] Ignore CTRL+Z\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signals2(void)
{
	signal(SIGQUIT, SIG_DFL);
}
