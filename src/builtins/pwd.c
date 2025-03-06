/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:19:40 by skassimi          #+#    #+#             */
/*   Updated: 2025/03/06 09:53:16 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	*cwd;
	char buffer[PATH_MAX];

	cwd = getenv("PWD");
	if (cwd)
	{
		printf("%s\n", cwd);
		return (0);
	}
	if (getcwd(buffer, PATH_MAX))
	{
		printf("%s\n", buffer);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}
