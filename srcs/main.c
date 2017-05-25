/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 17:57:15 by jecarol           #+#    #+#             */
/*   Updated: 2017/05/25 21:33:30 by jecarol          ###   ########.fr       */
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

void					ft_print(t_args *arglist, t_vals *values)
{
	t_args				*tmp;

	tmp = arglist;
	while (tmp)
	{
		if (values->curr == tmp->pos)
			ft_putstr("\033[4m");
		ft_putstr(tmp->name);
		if (values->curr == tmp->pos)
			ft_putstr("\033[24m");
		values->lin_pos += 1;
		tputs(tgoto(tgetstr("cm", NULL), values->col_pos, values->lin_pos),
		1, ft_pointchar);
		tmp = tmp->next;
	}
	values->lin_pos = 0;
}

void					ft_movement(t_args *arglist, int buf, t_term *setup, t_vals *values)
{
	(void)setup;
	if (buf == 4348699)
	{
		values->curr += 1;
		if (values->curr == values->count)
			values->curr = 0;
		ft_print(arglist, values);
	}
}

void					ft_display_loop(t_args	*arglist, t_term *setup)
{
	int					buf;
	int					i;
	t_vals				*values;

	i = 0;
	(void)setup;
	values = ft_memalloc(sizeof(t_vals));
	values->col_pos = 0;
	values->lin_pos = 0;
	ft_getmax(arglist, values);
	values->curr = 0;
	tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_pointchar);
	ft_print(arglist, values);
	while (42)
	{
		read(1, &buf, 8);
		tputs(tgetstr("cl", NULL), 1, ft_pointchar);
		values->col_pos = 0;
		ft_movement(arglist, buf, setup, values);
	}
}

void					ft_init(char *orterm, t_term *setup, t_args *arglist)
{
	int					retoor;
	char				buf[4];

	ft_bzero(buf, 4);
	if ((retoor = tgetent(NULL, orterm) < 0))
		ft_putendl_fd("error", 2);
	tcgetattr(1, &setup->attributes);
	setup->attributes.c_lflag &= ~ICANON;
	setup->attributes.c_lflag &= ~ECHO;
	tcsetattr(1, TCSADRAIN, &setup->attributes);
	tputs(tgetstr("cl", NULL), 1, ft_pointchar);
	// tputs(tgetstr("vi", NULL), 1, ft_pointchar);
	setup->height = tgetnum("li");
 	setup->width = tgetnum("co");
	setup->to_sub = setup->width;
	ft_display_loop(arglist, setup);
}

int						main(int ac, char **av)
{
	int					i;
	char				*orterm;
	t_term				*setup;
	t_args				*arglist;

	(void)ac;
	i = 0;
	while (av[++i])
		ft_getargs(&arglist, av[i]);
	setup = ft_memalloc(sizeof(t_term));
	orterm = getenv("TERM");
	ft_init(orterm, setup, arglist);
	return (0);
}
