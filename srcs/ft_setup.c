/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 18:11:50 by jecarol           #+#    #+#             */
/*   Updated: 2017/06/05 18:19:36 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_args					*ft_addarg(char *av)
{
	t_args				*tmp;
	static int			pos = 0;

	if (!(tmp = ft_memalloc(sizeof(t_args))))
		return (NULL);
	tmp->next = NULL;
	if (!av)
		tmp->name = NULL;
	else
	{
		tmp->name = ft_strdup(av);
		tmp->len = ft_strlen(av);
		tmp->pos = pos;
		tmp->sel = 0;
		pos++;
	}
	return (tmp);
}

void					ft_getargs(t_args **arglist, char *av)
{
	t_args				*tmp;

	tmp = *arglist;
	if (!tmp)
		*arglist = ft_addarg(av);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_addarg(av);
	}
}

void					ft_set_values(t_vals *values, t_args *arglist)
{
	values->col_pos = 0;
	values->result = 0;
	values->lin_pos = 0;
	values->curr = 0;
	ft_getmax(arglist, values);
}

void					ft_set_term(void)
{
	tputs(tgetstr("cl", NULL), 1, ft_pointchar);
	tputs(tgetstr("vi", NULL), 1, ft_pointchar);
	g_term->height = tgetnum("li");
	g_term->width = tgetnum("co");
	g_term->to_sub_w = g_term->width;
	g_term->to_sub_h = g_term->height;
	g_term->fit = 1;
	tcgetattr(0, &g_term->attributes);
	g_term->attributes.c_lflag &= ~ICANON;
	g_term->attributes.c_lflag &= ~ECHO;
	tcsetattr(0, TCSADRAIN, &g_term->attributes);
}
