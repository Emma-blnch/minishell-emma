/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:50:04 by ahamini           #+#    #+#             */
/*   Updated: 2025/02/11 10:50:05 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(int argc, char **argv, char **envp)
// {
// 	t_shell	*shell;
// 	char	*false_argv[2] = {"export", NULL};

// 	shell = create_minishell(envp);
// 	if (argc > 1)
// 	{
// 		export(shell, &argv[1], STDOUT_FILENO);
// 		fprintf(stderr, "export done\n\n");
// 		export(shell, false_argv, STDOUT_FILENO);
// 		unset(shell, &argv[1]);
// 		fprintf(stderr, "unset done\n\n");
// 		export(shell, false_argv, STDOUT_FILENO);
// 	}
// 	return (0);
// }

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = create_minishell(envp);
	if (!shell)
	{
		write(2, "error: minishell creation failed\n", 32);
		return (1);
	}
	init_readline(shell);
	free_minishell(shell);
	return (0);
}
