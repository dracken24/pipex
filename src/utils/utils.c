/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:16:54 by nadesjar          #+#    #+#             */
/*   Updated: 2022/07/22 21:16:36 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	child(t_all *all, char **argv, char **envp, int *fd)
{
	char	**options;
	char	*cmd_path;
	int		error;
	
	cmd_path = init_path(all, argv[all->ct.ii], envp);
	
 	options = ft_split(argv[all->ct.ii], ' ');
	int i = -1;
	while (options[++i])
		ft_printf("Options: %s\n", options[i]);
	
	if (all->ct.test == 0)
	{
		dup2(all->fd_child, STDIN_FILENO);
		dup2(fd[all->ct.turn + 1], STDOUT_FILENO);
		close(fd[0]);
		dprintf(2, "IN: Child  Out: %d  Close: 0\n", all->ct.turn + 1);
		dprintf(2, "1_ct.turn: %d\n", all->ct.turn);
		dprintf(2, "1_ct.ii: %d\n", all->ct.ii);
	}
	else if(all->ct.test == all->argc - 4)
	{
		dup2(fd[all->ct.turn], STDIN_FILENO);
		dup2(all->fd_dady, STDOUT_FILENO);
		close(fd[all->ct.turn + 1]);
		dprintf(2, "IN: %d  Out: Dady  Close: %d\n", all->ct.turn, all->ct.turn + 2);
		dprintf(2, "3_ct.turn: %d\n", all->ct.turn);
		dprintf(2, "1_ct.ii: %d\n", all->ct.ii);
	}
	else
	{
		dup2(fd[all->ct.turn], STDIN_FILENO);
		dup2(fd[all->ct.turn + 3], STDOUT_FILENO);
		close(fd[all->ct.turn + 2]);
		dprintf(2, "IN: %d  Out: %d  Close: %d\n", all->ct.turn, all->ct.turn + 3, all->ct.turn +2);
		dprintf(2, "2_ct.turn: %d\n", all->ct.turn);
		dprintf(2, "1_ct.ii: %d\n", all->ct.ii);
	}

	dprintf(2, "RE: \n\n");
	
	error = execve(cmd_path, options, envp);
	if (error == -1)
	{
		free_ptr(options);
		free_all(all);
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
		free(all->fd);
		free(all->pid);
		free(all->pipe);
		exit(-1);
	}
	all->argc = argc;
	all->ct.turn = 0;
	all->ct.test = 0;
	all->ct.rec = 0;
	all->nbr_cmd = argc - 3;
	all->ct.ii = 2;
}

int pipex(t_all *all, char**argv, char **envp)
{
    // int ret;
    int i;
    
    if (pipe(all->fd) == -1)
	{
		free(all->fd);
		free_all(all);
	}
	all->fd_child = open(argv[1], O_RDONLY, 0644);
	all->fd_dady = open(argv[all->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!all->fd_child && !all->fd_dady)
	{
		exit(-1);
	}
	i = -1;
	while (++i < all->argc -3)
	{
		all->pid[i] = fork();
		if (all->pid[i] == -1)
			free_all(all);
		if (all->pid[i] == 0)
			child(all, argv, envp, all->fd);
		
		usleep(1000);
		if (i >= 1)
			all->ct.turn += 2;
		all->ct.ii++;
		all->ct.test++;
	}
	// ret = dady(all);
	close(all->fd_child);
	close(all->fd_dady);
	free_all(all);
    return (0);
}
