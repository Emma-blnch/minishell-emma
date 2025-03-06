/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:46:58 by ahamini           #+#    #+#             */
/*   Updated: 2025/02/27 09:50:18 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	print_error_token(t_token *token, t_shell *shell)
{
	write(2, "syntax error near unexpected token ", 35);
	write(2, "'", 1);
	if (token->next == shell->token)
		write(2, "newline", 7);
	else
		write(2, token->next->str, ft_strlen(token->next->str));
	write(2, "'\n", 2);
	return (false);
}

bool	print_error2(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	return (true);
}
