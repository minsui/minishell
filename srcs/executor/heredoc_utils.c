/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkim2 <mkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 17:00:37 by mkim2             #+#    #+#             */
/*   Updated: 2026/07/24 17:00:45 by mkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	prepare_heredocs(t_cmd *cmds, t_shell *shell)
{
	while (cmds)
	{
		if (cmds->heredoc)
		{
			cmds->heredoc_fd = fill_heredoc_pipe(cmds->infile);
			if (cmds->heredoc_fd == -1)
			{
				if (g_signal == SIGINT)
					shell->exit_status = 130;
				g_signal = 0;
				return (-1);
			}
		}
		cmds = cmds->next;
	}
	return (0);
}

void	close_heredocs(t_cmd *cmds)
{
	while (cmds)
	{
		if (cmds->heredoc && cmds->heredoc_fd >= 0)
		{
			close(cmds->heredoc_fd);
			cmds->heredoc_fd = -1;
		}
		cmds = cmds->next;
	}
}
