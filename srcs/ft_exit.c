/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 18:14:28 by jecarol           #+#    #+#             */
/*   Updated: 2017/06/06 03:30:23 by rlkcmptr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void					ft_freelist(t_args *lst)
{
	t_args				*tmp;

	tmp = lst;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		ft_strdel(&tmp->name);
		free(tmp);
	}
}

void					ft_free_that_shiet(t_args *arglist, t_vals *values,
						t_term *setup)
{
	ft_freelist(arglist);
	setup->attributes.c_lflag |= ICANON;
	setup->attributes.c_lflag |= ECHO;
	tcsetattr(0, 0, &setup->attributes);
	free(setup);
	free(values);
	tputs(tgetstr("ve", NULL), 0, ft_pointchar);
	exit(EXIT_SUCCESS);
}

void					ft_end(t_args *arglist, int buf, t_term *setup,
						t_vals *values)
{
	t_args				*tmp;

	tmp = arglist;
	if (buf == 10)
	{
		while (tmp)
		{
			if (tmp->sel == 1)
			{
				ft_putstr_fd(tmp->name, 1);
				ft_putstr_fd(" ", 1);
				values->result = 1;
			}
			tmp = tmp->next;
		}
		if (values->result == 1)
			ft_putchar('\n');
		ft_free_that_shiet(arglist, values, setup);
	}
	if (buf == 27)
		ft_free_that_shiet(arglist, values, setup);
}
