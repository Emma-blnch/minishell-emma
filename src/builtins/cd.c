/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:19:30 by skassimi          #+#    #+#             */
/*   Updated: 2025/03/06 11:20:43 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_oldpwd(t_shell *data)
{
	t_list	*tmp;
	char	cwd[PATH_MAX];
	char	*oldpwd;

	tmp = data->env;
	if (getcwd(cwd, PATH_MAX) == NULL)
		return ;
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return (error_malloc());
	export2(oldpwd, &data->env);
	free(oldpwd);
}

static void	update_pwd(t_shell *data, char *param)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	update_oldpwd(data);
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		perror(param);
		return ;
	}
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return (error_malloc());
	export2(pwd, &data->env);
	free(pwd);
}

int	cd(t_shell *data, char **params)
{
	int		res;
	char	*path;
	bool	allocated;

	path = NULL;
	allocated = false;
	if (count_arg(params) == 1
		|| (count_arg(params) == 2 && !ft_strncmp(params[1], "~", 2)))
	{
		path = get_elem_env(data->env, "HOME");
		if (!path)
			return (printf("cd: HOME not set\n"), 1);
		allocated = true;
	}
	else if (count_arg(params) == 2)
		path = params[1];
	if (path != NULL)
	{
		res = chdir(path);
		check_res(res, path, data);
		if (allocated)
			free(path);
		return (res);
	}
	return (1);
}
