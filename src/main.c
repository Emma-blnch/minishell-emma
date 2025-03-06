/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:50:04 by ahamini           #+#    #+#             */
/*   Updated: 2025/02/27 09:55:38 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_signal_pid;

void	free_all(t_shell *shell, char *err, int ext)
{
	if (shell->cmd)
		free_cmd(&shell->cmd);
	if (shell->token)
		free_token(&shell->token);
	if (shell->env)
		free_list(&shell->env);
	if (shell->pip[0] && shell->pip[0] != -1)
		close(shell->pip[0]);
	if (shell->pip[1] && shell->pip[1] != -1)
		close(shell->pip[1]);
	if (err)
		print_error2(err);
	rl_clear_history();
	if (!access(".heredoc.tmp", F_OK))
		unlink(".heredoc.tmp");
	if (ext != -1)
		exit(ext);
}

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
