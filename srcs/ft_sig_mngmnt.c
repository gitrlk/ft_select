/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sig_mngmnt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 17:43:37 by jecarol           #+#    #+#             */
/*   Updated: 2017/06/06 03:32:36 by rlkcmptr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void					ft_resize(int i)
{
	struct winsize		testplus;

	(void)i;
	tputs(tgetstr("cl", NULL), 1, ft_pointchar);
	ioctl(0, TIOCGWINSZ, &testplus);
	g_term->width = testplus.ws_col;
	g_term->height = testplus.ws_row;
	g_term->to_sub_w = g_term->width;
	g_term->to_sub_h = g_term->height;
	g_checker = 0;
	ft_set_values(g_vals, g_args);
	ft_print(g_args, g_vals, g_term);
}

void					ft_sigint(int i)
{
	(void)i;
	ft_freelist(g_args);
	free(g_term);
	free(g_vals);
	tputs(tgetstr("ve", NULL), 0, ft_pointchar);
	tputs(tgetstr("cl", NULL), 1, ft_pointchar);
	tputs(tgetstr("te", NULL), 0, ft_pointchar);
	g_term->attributes.c_lflag |= ICANON;
	g_term->attributes.c_lflag |= ECHO;
	tcsetattr(0, 0, &g_term->attributes);
	exit(EXIT_SUCCESS);
}

void					ft_sigstp(int i)
{
	(void)i;
	tputs(tgetstr("cl", NULL), 1, ft_pointchar);
	tputs(tgetstr("ve", NULL), 0, ft_pointchar);
	tputs(tgetstr("te", NULL), 0, ft_pointchar);
	tcsetattr(0, TCSANOW, &g_term->attributes);
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, "\032");
}

void					ft_sigcont(int i)
{
	(void)i;
	signal(SIGTSTP, &ft_sigstp);
	ft_set_term();
	ft_set_values(g_vals, g_args);
	ft_print(g_args, g_vals, g_term);
}

void					ft_segvwtf(int i)
{
	(void)i;
	tputs(tgetstr("cl", NULL), 1, ft_pointchar);
	tputs(tgetstr("ve", NULL), 0, ft_pointchar);
	tputs(tgetstr("te", NULL), 0, ft_pointchar);
	tcsetattr(0, TCSANOW, &g_term->attributes);
	ft_putendl_fd("IMPOSSIBRUU", 2);
	exit(EXIT_FAILURE);
}
