/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 17:57:15 by jecarol           #+#    #+#             */
/*   Updated: 2017/06/05 18:17:40 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void					ft_signals(void)
{
	signal(SIGTSTP, ft_sigstp);
	signal(SIGCONT, ft_sigcont);
	signal(SIGINT, ft_sigint);
	signal(SIGWINCH, ft_resize);
	signal(SIGKILL, ft_sigint);
	signal(SIGTERM, ft_sigint);
	signal(SIGSEGV, ft_segvwtf);
}

int						main(int ac, char **av)
{
	int					i;
	char				*orterm;
	t_term				*setup;
	t_args				*arglist;

	i = 0;
	if (ac == 1)
	{
		(ft_putendl_fd("ft_select: usage : ./ft_select [arguments...]", 2));
		exit(EXIT_FAILURE);
	}
	while (av[++i])
		ft_getargs(&arglist, av[i]);
	setup = ft_memalloc(sizeof(t_term));
	if (!(orterm = getenv("TERM")))
	{
		ft_putendl_fd("error : no TERM variable set", 2);
		exit(EXIT_FAILURE);
	}
	ft_init(orterm, setup, arglist);
	return (0);
}
