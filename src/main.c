/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:50:04 by ahamini           #+#    #+#             */
/*   Updated: 2025/02/26 11:37:41 by eblancha         ###   ########.fr       */
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

pid_t	g_signal_pid;

bool	make_env(t_shell *shell)
{
	char	path[PATH_MAX];
	char	*tmp;

	tmp = ft_strdup("OLDPWD");
	if (!tmp || !append(&(shell->env), tmp) || getcwd(path, PATH_MAX) == NULL)
		free_all(shell, ERR_MALLOC, EXT_MALLOC);
	tmp = ft_strjoin("PWD=", path);
	if (!tmp || !append(&(shell->env), tmp))
		free_all(shell, ERR_MALLOC, EXT_MALLOC);
	return (1);
}

int	create_minishell(t_shell *shell, char **env)
{
	t_list	*list;
	int		i;
	char	*tmp;

	if (!(*env))
		return (make_env(shell));
	i = -1;
	list = NULL;
	while (env[++i])
	{
		tmp = ft_strdup(env[i]);
		if (!tmp)
			return (free_list(&list));
		if (!append(&list, tmp))
			return (free_list(&list));
	}
	shell->env = list;
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	shell.env = NULL;
	shell.token = NULL;
	shell.cmd = NULL;
	shell.exit_code = 0;
	shell.pip[0] = -1;
	shell.pip[1] = -1;
	g_signal_pid = 0;
	signals();
	if (!create_minishell(&shell, envp))
		free_all(&shell, ERR_MALLOC, EXT_MALLOC);
	init_readline(&shell);
	free_all(&shell, NULL, -1);
	return (0);
}
