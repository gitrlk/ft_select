/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 18:08:26 by jecarol           #+#    #+#             */
/*   Updated: 2017/06/05 18:20:17 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int						ft_buf_checker(int buf)
{
	if (buf == 4348699 || buf == 4283163 || buf == 4479771 || buf == 4414235 ||
	buf == 32 || buf == 10 || buf == 27 || buf == 127 || buf == 2117294875)
		return (1);
	else
		return (0);
}

void					ft_events(t_args **arglist, int buf, t_term *setup,
						t_vals *values)
{
	if (setup->fit)
	{
		tputs(tgetstr("cl", NULL), 1, ft_pointchar);
		ft_arrows(*arglist, buf, setup, values);
		ft_select_elem(*arglist, buf, setup, values);
		ft_del_elem(arglist, buf, setup, values);
	}
	ft_end(*arglist, buf, setup, values);
}

void					ft_setup_for_loop(t_args *arglist, t_term *setup,
						t_vals *values)
{
	g_args = arglist;
	g_vals = values;
	g_term = setup;
	ft_set_term();
	ft_print(arglist, values, setup);
	ft_signals();
}

void					ft_display_loop(t_args *arglist, t_term *setup)
{
	int					buf;
	int					i;
	t_vals				*values;

	i = 0;
	buf = 0;
	g_checker = 0;
	values = ft_memalloc(sizeof(t_vals));
	ft_set_values(values, arglist);
	tcgetattr(0, &setup->attributes);
	setup->attributes.c_lflag &= ~ICANON;
	setup->attributes.c_lflag &= ~ECHO;
	tcsetattr(0, TCSADRAIN, &setup->attributes);
	tputs(tgetstr("ti", NULL), 0, ft_pointchar);
	tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_pointchar);
	ft_setup_for_loop(arglist, setup, values);
	while (42)
	{
		read(0, &buf, 8);
		values->col_pos = 0;
		if (ft_buf_checker(buf))
			ft_events(&arglist, buf, setup, values);
		buf = 0;
	}
}

void					ft_init(char *orterm, t_term *setup, t_args *arglist)
{
	int					retoor;

	if ((retoor = tgetent(NULL, orterm) < 0))
	{
		ft_putendl_fd("error", 2);
		ft_freelist(arglist);
		free(setup);
		exit(EXIT_FAILURE);
	}
	tcgetattr(0, &setup->attributes);
	setup->attributes.c_lflag &= ~ICANON;
	setup->attributes.c_lflag &= ~ECHO;
	tcsetattr(0, TCSADRAIN, &setup->attributes);
	tputs(tgetstr("cl", NULL), 1, ft_pointchar);
	tputs(tgetstr("vi", NULL), 1, ft_pointchar);
	setup->height = tgetnum("li");
	setup->width = tgetnum("co");
	setup->to_sub_w = setup->width;
	setup->to_sub_h = setup->height;
	setup->fit = 1;
	ft_display_loop(arglist, setup);
}
