/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 20:56:03 by nadesjar          #+#    #+#             */
/*   Updated: 2022/07/13 12:43:21 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	multi_pipes(t_all *all, int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		i;
	int		fd[((argc - 3) * 2) + 1];

	// init_var_b(all, argc, argv, envp);
	if (pipe(fd) == -1)
		free_all(&all);
	pid = fork();
	i = 2;
	while (argv[++i] && i < argc - 1)
	{
		if (pipe(fd) == -1)
			free_all(&all);
		pid = fork();
		if (pid == -1)
			free_all(&all);
		else if (pid == 0)
			child_b(&all, argv, envp, fd);
	}
}


// void	init_var_b(t_all *all, int argc, char **argv, char **envp)
// {
		
// }
