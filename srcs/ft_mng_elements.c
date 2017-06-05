/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mng_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 18:01:41 by jecarol           #+#    #+#             */
/*   Updated: 2017/06/05 18:18:53 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void					ft_update_pos(t_args *arglist, t_vals *values)
{
	t_args				*tmp;
	int					pos;

	pos = 0;
	tmp = arglist;
	if (!tmp)
		return ;
	while (tmp)
	{
		tmp->pos = pos;
		pos++;
		tmp = tmp->next;
	}
	values->count -= 1;
}

void					ft_end_backspace(t_term *setup,
						t_vals *values)
{
	free(setup);
	free(values);
	tputs(tgetstr("ve", NULL), 0, ft_pointchar);
	exit(EXIT_SUCCESS);
}

void					ft_del_first(t_args *todel, t_args **arglist,
						t_args **tmp, t_vals *values)
{
	todel = *arglist;
	*arglist = (*arglist)->next;
	ft_strdel(&todel->name);
	free(todel);
	*tmp = *arglist;
	ft_update_pos(*arglist, values);
}

void					ft_del_any(t_args *todel, t_args **arglist,
						t_args **tmp, t_vals *values)
{
	(*tmp)->next = (*tmp)->next->next;
	ft_strdel(&todel->name);
	free(todel);
	ft_update_pos(*arglist, values);
	if (values->count == values->curr)
		values->curr = 0;
}

void					ft_del_elem(t_args **arglist, int buf, t_term *setup,
						t_vals *values)
{
	t_args				*tmp;
	t_args				*todel;

	if (buf == 127 || buf == 2117294875)
	{
		tmp = *arglist;
		while (tmp)
		{
			todel = tmp->next;
			if (values->curr == 0 && tmp->pos == 0)
				ft_del_first(todel, arglist, &tmp, values);
			else if (todel && todel->pos == values->curr)
				ft_del_any(todel, arglist, &tmp, values);
			if (*arglist == NULL)
				ft_end_backspace(setup, values);
			tmp = tmp->next;
		}
		ft_print(*arglist, values, setup);
	}
}
