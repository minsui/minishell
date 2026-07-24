/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkim2 <mkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 21:25:49 by mkim2             #+#    #+#             */
/*   Updated: 2026/07/24 17:15:59 by mkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_number(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	parse_code(char *s, unsigned char *code)
{
	unsigned long long	n;
	int					i;
	int					neg;

	i = 0;
	neg = (s[i] == '-');
	if (s[i] == '+' || s[i] == '-')
		i++;
	n = 0;
	while (s[i])
	{
		if (n > 922337203685477580ULL)
			return (0);
		n = n * 10 + (s[i] - '0');
		i++;
	}
	if (n > 9223372036854775807ULL + neg)
		return (0);
	*code = (unsigned char)n;
	if (neg)
		*code = (unsigned char)(256 - *code);
	return (1);
}

static void	exit_error(char *arg)
{
	ft_putstr("minishell: exit: ", 2);
	ft_putstr(arg, 2);
	ft_putstr(": numeric argument required\n", 2);
}

int	builtin_exit(char **argv, t_shell *shell)
{
	unsigned char	code;

	ft_putstr("exit\n", 1);
	if (!argv[1])
	{
		code = (unsigned char)shell->exit_status;
		shell_cleanup(shell);
		exit(code);
	}
	if (!is_valid_number(argv[1]) || !parse_code(argv[1], &code))
	{
		exit_error(argv[1]);
		shell_cleanup(shell);
		exit(2);
	}
	if (argv[2])
	{
		ft_putstr("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	shell_cleanup(shell);
	exit(code);
}
