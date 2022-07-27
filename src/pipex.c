/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:28:23 by nadesjar          #+#    #+#             */
/*   Updated: 2022/07/27 04:24:10 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	check_entry(t_all *all, char **argv)
{
	if (open(argv[1], O_RDONLY, 0644) == -1
		|| open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644) == -1)
	{
		perror("Error, wrong open");
		free(all->fd);
		free(all->pid);
		free(all->pipe);
		exit (0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_all	all;
	int		exit_code;

	if (argc < 5)
		return (0);
	init_var(&all, argc);
	check_entry(&all, argv);
	if (argc == 5)
	{
		exit_code = pipex(&all, argv, envp);
	}
	else
	{
		perror("Error, Wrong argument number");
		free(all.fd);
		free(all.pid);
		free(all.pipe);
		exit (0);
	}
	free(all.pid);
	free(all.pipe);
	free(all.fd);
	return (exit_code);
}

char	*div_cmd(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	ret = ft_calloc(sizeof(char), i + 1);
	if (!str || !ret)
	{
		perror("Error, wrong alloc <div_cmd>");
		free(str);
		return (NULL);
	}
	i = -1;
	while (str[++i] != ' ' && str[i] != '\0')
		ret[i] = str[i];
	return (ret);
}

char	*init_path(t_all *all, char *argv, char **envp)
{
	char	*str;
	char	*ret;
	char	*cmd;

	cmd = ft_calloc(sizeof(char), ft_strlen(argv) + 1);
	if (!cmd)
	{
		perror("Error, wrong alloc <init_path>");
		free(cmd);
		exit(0);
	}
	if (access(argv, F_OK | X_OK) == 0)
	{
		cmd = ft_strdup(argv);
		return (cmd);
	}
	str = div_cmd(argv);
	cmd = ft_strdup(str);
	ret = check_path(all, cmd, envp);
	free(cmd);
	return (ret);
}
