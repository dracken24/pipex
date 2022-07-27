/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:16:54 by nadesjar          #+#    #+#             */
/*   Updated: 2022/07/27 03:58:14 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	child(t_all *all, char **argv, char **envp, int *fd)
{
	char	**options;
	char	*cmd_path;
	int		error;

	cmd_path = init_path(all, argv[all->ct.ii], envp);
	if (!cmd_path)
		free_all(all, "Error, cmd_path <child>");
	ft_printf("PATH: %s\n", cmd_path);
	options = ft_split(argv[all->ct.ii], ' ');
	if (all->ct.child == 0)
	{
		dup2(all->fd_child, STDIN_FILENO);
		dup2(fd[all->ct.turn + 1], STDOUT_FILENO);
		close(fd[0]);
	}
	else
	{
		dup2(fd[all->ct.turn], STDIN_FILENO);
		dup2(all->fd_dady, STDOUT_FILENO);
		close(fd[all->ct.turn + 1]);
	}
	error = execve(cmd_path, options, envp);
	if (error == -1)
	{
		free_ptr(options);
		free_all(all, "Error, error <child>");
	}
	free_ptr(options);
}

void	init_var(t_all *all, int argc)
{
	all->pipe = ft_calloc(sizeof(int), argc - 3);
	all->pid = ft_calloc(sizeof(pid_t), argc - 2);
	all->fd = ft_calloc(sizeof(int), 5);
	if (!all->fd || !all->pid || !all->pipe)
	{
		perror("Error, alloc <init_var>");
		free(all->fd);
		free(all->pid);
		free(all->pipe);
		exit(0);
	}
	all->argc = argc;
	all->ct.turn = 0;
	all->ct.child = 0;
	all->nbr_cmd = argc - 3;
	all->ct.ii = 2;
	all->ct.i_path = 0;
}

int	pipex(t_all *all, char**argv, char **envp)
{
	int	i;

	all->fd_child = open(argv[1], O_RDONLY, 0644);
	all->fd_dady = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipe(all->fd) == -1)
		free_all(all, "Error, pipe <pipex>");
	i = -1;
	while (++i < all->argc -3)
	{
		all->pid[i] = fork();
		if (all->pid[i] == -1)
			free_all(all, "Error, fork <pipex>");
		if (all->pid[i] == 0)
			child(all, argv, envp, all->fd);
		usleep(1000);
		if (i >= 1)
			all->ct.turn += 2;
		all->ct.ii++;
		all->ct.child++;
	}
	free_all(all, "good");
	return (0);
}
