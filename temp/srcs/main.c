/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 18:12:10 by jecarol           #+#    #+#             */
/*   Updated: 2017/05/20 00:14:31 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void					ft_errors(int ac)
{
	if (ac == 1)
	{
		ft_putendl_fd("ft_select needs arguments", 2);
		exit(EXIT_FAILURE);
	}
}

int						ft_pointchar(int c)
{
	write(STDIN_FILENO, &c, 1);
	return (0);
}

void					ft_getmax(char **av, t_vals *values)
{
	int					i;

	i = 1;
	while (av[i])
	{
		if (ft_strlen(av[i]) > values->max)
			values->max = ft_strlen(av[i]);
		i++;
	}
}

void					ft_display_loop(char **av, t_term *setup)
{
	char				buf[4];
	int					i;
	int					col_pos;
	int					lin_pos;
	t_vals				*values;

	i = 1;
	col_pos = 0;
	lin_pos = 0;
	(void)setup;
	values = ft_memalloc(sizeof(t_vals));
	ft_getmax(av, values);
	tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_pointchar);
	while (av[i])
	{
		ft_putchar('>');
		ft_putchar(' ');
		ft_putstr(av[i]);
		if ((values->cmp1 = (ft_strlen(av[i]) + 1)) <
		(values->cmp2 = ((values->max))))
			while (values->cmp1 < values->cmp2)
			{
				ft_putchar(' ');
				values->cmp1 += 1;
			}
		if (ft_strlen(av[i]) != values->max)
			ft_putchar(' ');
		ft_putchar('<');
		ft_putchar(' ');
		i++;
		col_pos++;
		tputs(tgoto(tgetstr("cm", NULL), lin_pos, col_pos), 1, ft_pointchar);
		if (col_pos == setup->height)
		{
			lin_pos += values->max + 4;
			col_pos = -1;
		}
	}
	while (42)
	{
		// tputs(tgoto(tgetstr("cm", NULL), 0, i), 1, ft_pointchar);
		read(1, buf, 4);
	}
}

void					ft_init(char *orterm, t_term *setup, char **av)//, t_args *arglist)
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
	setup->height = tgetnum("li");
 	setup->width = tgetnum("co");
	setup->to_sub = setup->width;
	ft_display_loop(av, setup);
}

int						main(int ac, char **av)
{
	char				*orterm;
	t_term				*setup;
	int					i;

	i = 0;
	(void)ac;
	setup = ft_memalloc(sizeof(t_term));
	orterm = getenv("TERM");
	ft_init(orterm, setup, av);
	return (0);
}
