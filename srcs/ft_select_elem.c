/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 18:16:23 by jecarol           #+#    #+#             */
/*   Updated: 2017/06/05 18:16:30 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void					ft_toggle_sel(t_args *arglist, t_vals *values)
{
	t_args				*tmp;

	tmp = arglist;
	while (tmp)
	{
		if (tmp->pos == values->curr && tmp->sel == 0)
			tmp->sel = 1;
		else if (tmp->pos == values->curr && tmp->sel == 1)
			tmp->sel = 0;
		tmp = tmp->next;
	}
	values->curr += 1;
}

void					ft_select_elem(t_args *arglist, int buf, t_term *setup,
						t_vals *values)
{
	if (buf == 32)
	{
		ft_toggle_sel(arglist, values);
		if (values->curr == values->count)
			values->curr = 0;
		ft_print(arglist, values, setup);
	}
}
