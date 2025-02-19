/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:47:30 by ahamini           #+#    #+#             */
/*   Updated: 2025/02/19 15:07:40 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_filepath(const char *base, int counter)
{
	char	*counter_str;
	char	*filepath;

	counter_str = ft_itoa(counter);
	if (!counter_str)
		return (NULL);
	filepath = ft_strjoin(base, counter_str);
	free(counter_str);
	return (filepath);
}

char	*generate_heredoc_filepath(t_shell *shell)
{
	char		*base_name;
	char		*heredoc_path;
	int			counter;
	time_t		timestamp;

	timestamp = time(NULL);
	base_name = ft_strjoin(HEREDOC_LOC, ft_itoa((int)timestamp));
	if (!base_name)
		return (set_error(MALLOC_FAIL, shell, "Heredoc"), NULL);
	counter = 0;
	while (counter < 1000)
	{
		heredoc_path = create_filepath(base_name, counter);
		if (!heredoc_path)
			return (free(base_name), set_error(MALLOC_FAIL, shell, "Heredoc"), NULL);
		if (access(heredoc_path, F_OK) != 0)
			return (free(base_name), heredoc_path);
		free(heredoc_path);
		counter++;
	}
	return (free(base_name), set_error(TOO_MANY_HEREDOC, shell, "Impossible de créer un fichier unique"), NULL);
}


void	display_heredoc_prompt(int index)
{
	char	*index_str;
	char	*prompt;

	index_str = ft_itoa(index);
	if (!index_str)
		return ;
	prompt = ft_strjoinfree(index_str, " heredoc> ");
	if (!prompt)
		return ;
	write(STDOUT_FILENO, prompt, ft_strlen(prompt));
	free(prompt);
}

void	read_and_write_heredoc(t_file *file, t_cmd *cmd)
{
	char	*line;

	while (1)
	{
		display_heredoc_prompt(cmd->cmd_index + 1);
		line = get_next_line(STDIN_FILENO);
		if (!line || ft_strncmp(file->delim, line, ft_strlen(file->delim)) == 0)
			break ;
		write(file->fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
}

void	manage_heredoc(t_shell *shell, t_cmd *cmd, t_list *file_node)
{
	t_file	*file;

	file = (t_file *)file_node->content;
	if (file->mode != HEREDOC)
		return ;
	open_file(file, cmd, WRITE);
	if (file->fd < 0)
		return (set_error(READ_ERROR, shell, "Unable to create heredoc"));
	read_and_write_heredoc(file, cmd);
	close(file->fd);
}


void	destroy_heredoc(t_shell *shell, t_list *file_node)
{
	t_file	*file;

	if (catch_error(shell))
		return ;
	file = (t_file *)(file_node)->content;
	if (file->mode != HEREDOC)
		return ;
	unlink(file->path);
}
