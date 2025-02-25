/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:19:30 by skassimi          #+#    #+#             */
/*   Updated: 2025/02/25 16:39:05 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_arg(char **params)
{
	int	count;

	count = 0;
	while (params[count])
		count++;
	return (count);
}

static void	error_malloc(void)
{
	print_error2(ERR_MALLOC);
	return ;
}

static void	update_oldpwd(t_shell *shell)
{
	t_list	*tmp;
	char	*test;
	int		len;

	tmp = shell->env;
	test = NULL;
	len = len_list(tmp);
	while (len--)
	{
		if (ft_strncmp(tmp->str, "PWD=", 3) == 0)
			test = tmp->str;
		tmp = tmp->next;
	}
	if (!test)
		export2("OLDPWD", &shell->env);
	if (test)
	{
		test = ft_strjoin("OLD", test);
		if (!test)
			return (error_malloc());
		export(&test, &shell->env);
	}
	free(test);
}

static void	update_pwd(t_shell *shell, char *param)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	update_oldpwd(shell);
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		perror(param);
		return ;
	}
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return (error_malloc());
	export(&pwd, &shell->env);
	free(pwd);
}

int	handle_cd_sign(t_shell *shell, char **params)
{
	char	*path;
	
	if (count_arg(params) == 1 || (count_arg(params) == 2 && !ft_strncmp(params[1], "~", 2)))
    {
        path = get_elem_env(shell->env, "HOME");
        if (!path)
        {
            printf("cd: HOME not set\n");
            return (1);
        }
    }
    else if (count_arg(params) == 2 && !ft_strncmp(params[1], "-", 2))
    {
        path = get_elem_env(shell->env, "OLDPWD");
        if (!path)
        {
            printf("cd: OLDPWD not set\n");
            return (1);
        }
        printf("%s\n", path);
    }
	return (0);
}

int	cd(t_shell *shell, char **params)
{
	int	res;
	char	*path;

	handle_cd_sign(&shell, &params);
	if (count_arg(params) == 2)
	{
		res = chdir(params[1]);
		if (res == 0)
			update_pwd(shell, params[1]);
		if (res == -1)
			res *= -1;
		if (res == 1)
			perror(params[1]);
		return (res);
	}
	return (1);
}
