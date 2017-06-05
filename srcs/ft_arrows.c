/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrows.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 17:25:08 by jecarol           #+#    #+#             */
/*   Updated: 2017/06/05 17:31:25 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void					ft_up_down(t_args *arglist, int buf, t_term *setup,
						t_vals *values)
{
	if (buf == 4348699)
	{
		values->curr += 1;
		if (values->curr == values->count)
			values->curr = 0;
		ft_print(arglist, values, setup);
	}
	if (buf == 4283163)
	{
		if (values->curr == 0)
			values->curr = values->count;
		values->curr -= 1;
		ft_print(arglist, values, setup);
	}
}

void					ft_left_right(t_args *arglist, int buf, t_term *setup,
						t_vals *values)
{
	if (buf == 4479771)
	{
		if (values->curr > values->total || values->curr == values->total)
			values->curr = values->curr - values->total;
		ft_print(arglist, values, setup);
	}
	if (buf == 4414235)
	{
		if (values->curr < values->count)
		{
			values->curr = values->curr + values->total;
			if (values->curr == values->count)
				values->curr = values->curr - values->total;
		}
		if (values->curr > values->count)
			values->curr = values->curr - values->total;
		ft_print(arglist, values, setup);
	}
}

void					ft_arrows(t_args *arglist, int buf, t_term *setup,
						t_vals *values)
{
	ft_up_down(arglist, buf, setup, values);
	ft_left_right(arglist, buf, setup, values);
}
