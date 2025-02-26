/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:49:13 by ahamini           #+#    #+#             */
/*   Updated: 2025/02/26 10:22:55 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	print_token(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp->next != token)
	{
		printf("Type : %d, [%s]\n", tmp->type, tmp->str);
		tmp = tmp->next;
	}
	printf("Type : %d, [%s]\n",  tmp->type, tmp->str);
}*/

bool pipe_error(t_shell *shell)
{
    t_token *tmp;
    t_token *prev_tmp = NULL;  // Ajout d'une variable pour vérifier si on entre dans un cycle

    // Vérifie si la liste des tokens est vide
    if (!shell->token)
    {
        write(2, "Error: No tokens found\n", 23);
        return (false);
    }

    tmp = shell->token;
    while (tmp)
    {
        // Débogage pour afficher l'adresse du token et de son prochain
        printf("Token address: %p, Next address: %p\n", (void *)tmp, (void *)tmp->next);

        // Vérifie si on est déjà passé par ce token (cycle)
        if (tmp == prev_tmp)
        {
            write(2, "Error: Detected a cycle in the token list\n", 41);
            break;  // Sortir de la boucle si un cycle est détecté
        }

        // Vérifie si tmp->next existe avant d'accéder à tmp->next->type
        if (tmp->type == PIPE && tmp->next && tmp->next->type == PIPE)
        {
            // Affiche une erreur si deux pipes consécutifs sont trouvés
            write(2, "Error: Invalid pipe usage (consecutive pipes)\n", 46);
            shell->exit_code = 2;
            free_token(&shell->token);
            return (false);
        }

        prev_tmp = tmp;  // Garde une trace du token précédent
        tmp = tmp->next; // Avance au token suivant
    }
	return (true);
}


bool	operator_error(t_shell *shell)
{
	// printf("hello\n");
	if (shell->token && shell->token->prev->type == PIPE)
	{
		write(2, "Error: Unclosed pipe\n", 21);
		shell->exit_code = 2;
		free_token(&shell->token);
		return (false);
	}
	if (shell->token && shell->token->prev->type == APPEND)
	{
		write(2, "Error: Unclosed append\n", 21);
		shell->exit_code = 2;
		free_token(&shell->token);
		return (false);
	}
	if (shell->token && shell->token->prev->type == HEREDOC)
	{
		write(2, "Error: Unclosed heredoc\n", 21);
		shell->exit_code = 2;
		free_token(&shell->token);
		return (false);
	}
	if (shell->token && shell->token->prev->type == INPUT)
	{
		write(2, "Error: Unclosed input\n", 21);
		shell->exit_code = 2;
		free_token(&shell->token);
		return (false);
	}
	if (shell->token && shell->token->prev->type == TRUNC)
	{
		write(2, "Error: Unclosed trunc\n", 21);
		shell->exit_code = 2;
		free_token(&shell->token);
		return (false);
	}
	return (true);
}

bool	check_pipe(t_shell *shell)
{
	if (shell->token->type == PIPE)
	{
		write(2, "syntax error near unexpected token '|'\n", 39);
		free_token(&shell->token);
		free_cmd(&shell->cmd);
		return (false);
	}
	return (true);
}

bool	empty_input(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (i == (int)ft_strlen(line))
	{
		free(line);
		return (true);
	}
	return (false);
}

bool	parse_cmd(t_shell *shell, char *input)
{
	if (open_quote(shell, input))
	{
		free(input);
		return (false);
	}
	if (!replace_dollar(&input, shell) || !create_list_token(&shell->token, input))
	{
		free(input);
		free_all(shell, ERR_MALLOC, EXT_MALLOC);
	}
	free(input);
	// print_token(shell->token);
	// printf("hello1\n");
	//if (!pipe_error(shell))
	//	return (false);
	if (!operator_error(shell))
		return (false);
	if (!shell->token || !create_list_cmd(shell))
	{
		free_token(&shell->token);
		free_cmd(&shell->cmd);
		return (false);
	}
	return (check_pipe(shell));
}

int	init_readline(t_shell *shell)
{
	char		*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			free_all(shell, "exit\n", shell->exit_code);
		if (empty_input(input))
			continue;
		add_history(input);
		if (!parse_cmd(shell, input))
			continue;
		if (!exec(shell))
			free_all(shell, ERR_PIPE, EXT_PIPE);
		free_cmd(&shell->cmd);
		free_token(&shell->token);
		g_signal_pid = 0;
	}
	rl_clear_history();
	free_all(shell, NULL, -1);
	return (0);
}
