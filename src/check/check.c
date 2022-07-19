/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 20:44:21 by nadesjar          #+#    #+#             */
/*   Updated: 2022/07/13 16:18:34 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

char	*check_path(t_all *all, char *cmd, char **envp)
{
	char	**paths;
	char	*cmd_path;

	cmd_path = NULL;
	all->ct.i = -1;
	while (envp[++all->ct.i])
	{
		all->envp_path = ft_strnstr(envp[all->ct.i], "PATH=", 5);
		if (all->envp_path)
		{
			find_path(all);
			break ;
		}
	}
	paths = ft_calloc(sizeof(paths), ft_strlen(all->envp_path + 1));
	cmd_path = find_good_path(paths, cmd_path, cmd, all);
	free(paths);
	return (cmd_path);
}

char	*find_path(t_all *all)
{
	char	*tmp;

	all->len.len = ft_strlen(all->envp_path);
	tmp = ft_calloc(sizeof(tmp), all->len.len + 1);
	if (!tmp)
	{
		free(tmp);
		exit(0);
	}
	tmp = ft_substr(all->envp_path, 5, all->len.len);
	all->len.len = ft_strlen(tmp);
	all->envp_path = ft_substr(tmp, 0, all->len.len);
	free(tmp);
	return (all->envp_path);
}

char	*find_good_path(char **paths, char *cmd_path, char *cmd, t_all *all)
{
	if (!paths)
		free_all(all);
	paths = ft_split(all->envp_path, ':');
	all->ct.i = -1;
	while (paths[++all->ct.i])
		paths[all->ct.i] = ft_strjoin(paths[all->ct.i], "/");
	all->ct.i = -1;
	while (paths[++all->ct.i])
	{
		cmd_path = ft_strjoin(paths[all->ct.i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			free(paths);
			return (cmd_path);
		}
		free(cmd_path);
	}
	return (NULL);
}

void	free_all(t_all *all)
{
	(void)all;
	// free(all->cmd_path1);
	// free(all->cmd_path2);
	// free(all->envp_path);
	// free_ptr(all->cmd);
	exit(-1);
}
