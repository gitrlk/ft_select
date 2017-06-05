/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_section.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 17:55:24 by jecarol           #+#    #+#             */
/*   Updated: 2017/06/05 17:56:05 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int						ft_pointchar(int c)
{
	write(STDIN_FILENO, &c, 1);
	return (0);
}

void					ft_getmax(t_args *arglist, t_vals *values)
{
	t_args				*tmp;
	size_t				max;
	int					count;

	max = 0;
	count = 0;
	tmp = arglist;
	while (tmp)
	{
		if (max < tmp->len)
			max = tmp->len;
		count++;
		tmp = tmp->next;
	}
	values->count = count;
	values->max = max;
}

void					ft_padder(t_vals *values, t_term *setup, int checker)
{
	if (values->lin_pos == setup->height)
	{
		if (!checker)
		{
			setup->to_sub_w -= values->max + 3;
			if (setup->to_sub_w < 0 ||
			(setup->to_sub_w < (int)values->max + 3 &&
			values->lin_pos != setup->height))
				setup->fit = 0;
			else
				setup->fit = 1;
		}
		values->col_pos += values->max + 3;
		values->lin_pos = 0;
		values->total = setup->height;
	}
	else
	{
		if (setup->to_sub_w < (int)values->max)
			setup->fit = 0;
		else
			setup->fit = 1;
	}
}

void					ft_fit_checker(int fit)
{
	if (!fit)
	{
		tputs(tgetstr("cl", NULL), 1, ft_pointchar);
		ft_putendl_fd("please enlarge terminal window", 0);
	}
}

void					ft_print(t_args *arglist, t_vals *values, t_term *setup)
{
	t_args				*tmp;
	struct winsize		test;

	tmp = arglist;
	ioctl(0, TIOCGWINSZ, &test);
	setup->width = test.ws_col;
	setup->height = test.ws_row;
	while (tmp)
	{
		if (values->curr == tmp->pos)
			ft_putstr_fd(tgetstr("us", NULL), 0);
		if (tmp->sel == 1)
			ft_putstr_fd(tgetstr("mr", NULL), 0);
		ft_putstr_fd(tmp->name, 0);
		ft_putstr_fd(tgetstr("me", NULL), 0);
		values->lin_pos += 1;
		ft_padder(values, setup, g_checker);
		tputs(tgoto(tgetstr("cm", NULL), values->col_pos, values->lin_pos),
		1, ft_pointchar);
		tmp = tmp->next;
	}
	values->lin_pos = 0;
	ft_fit_checker(setup->fit);
	g_checker = 1;
}
