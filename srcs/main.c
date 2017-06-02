/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 17:57:15 by jecarol           #+#    #+#             */
/*   Updated: 2017/06/01 20:12:47 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void			ft_freelist(t_args *lst)
{
	t_args		*tmp;

	tmp = lst;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		ft_strdel(&tmp->name);
		free(tmp);
	}
}

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

void					ft_waddup_more(void)
{
	ft_putstr_fd("                         ", 0);
	ft_putendl_fd(",--,                                ,----,", 0);
    ft_putstr_fd("                      ", 0);
	ft_putendl_fd(",---.'|                              ,/   .`|", 0);
	ft_putstr_fd("  .--.--.       ,---,.|   | :       ", 0);
	ft_putendl_fd(",---,.  ,----..      ,`   .'  :", 0);
	ft_putstr_fd(" /  /    '.   ,'  .' |:   : |     ", 0);
	ft_putendl_fd(",'  .' | /   /  \\    ;    ;     /", 0);
	ft_putstr_fd("|  :  /`. / ,---.'   ||   ' :   ", 0);
	ft_putendl_fd(",---.'   ||   :     :.'___,/    ,'", 0);
	ft_putstr_fd(";  |  |--`  |   |   .';   ; '   ", 0);
	ft_putendl_fd("|   |   .'.   |  ;. /|    :     |", 0);
	ft_putstr_fd("|  :  ;_    :   :  |-,'   | |__ :   ", 0);
	ft_putendl_fd(":  |-,.   ; /--` ;    |.';  ;", 0);
	ft_putstr_fd(" \\  \\    `. :   |  ;/||   | :.'|", 0);
}

void					ft_waddup(void)
{
	ft_waddup_more();
	ft_putendl_fd(":   |  ;/|;   | ;    `----'  |  |", 0);
	ft_putstr_fd("  `----.   \\|   :   .''   :    ", 0);
	ft_putendl_fd(";|   :   .'|   : |        '   :  ;", 0);
	ft_putstr_fd("    __\\ \\  ||   |  |-,|   |  ", 0);
	ft_putendl_fd("./ |   |  |-,.   | '___     |   |  '", 0);
    ft_putstr_fd(" /  /`--'  /'   :  ;/|;   : ;   '   :  ", 0);
	ft_putendl_fd(";/|'   ; : .'|    '   :  |", 0);
	ft_putstr_fd("'--'.     / |   |    \\|   ,/    ", 0);
	ft_putendl_fd("|   |    \\'   | '/  :    ;   |.'", 0);
  	ft_putstr_fd("  `--'---'  |   :   .''---'     ", 0);
	ft_putendl_fd("|   :   .'|   :    /     '---'", 0);
  	ft_putendl_fd("            |   | ,'            |   | ,'   \\  \\  .'", 0);
	ft_putendl_fd("            `----'              `----'      `---`", 0);
}

void					ft_padd_waddup(t_vals *values, t_term *setup, int checker)
{
	values->col_pos += values->max + 3;
	values->lin_pos = 17;
	values->total = setup->height - 17;
	if (!checker)
	{
		setup->to_sub_w -= values->col_pos;
		if (setup->to_sub_w < 0 || setup->to_sub_w < values->col_pos + 3)
			setup->fit = 0;
		else
			setup->fit = 1;
	}
}

void					ft_padder(t_vals *values, t_term *setup, int checker)
{
	if (values->lin_pos == setup->height && setup->width > 65)
		ft_padd_waddup(values, setup, checker);
	else if (values->lin_pos == setup->height)
	{
		values->col_pos += values->max + 3;
		values->lin_pos = 0;
		values->total = setup->height;
		if (!checker)
		{
			setup->to_sub_w -= values->col_pos;
			if (setup->to_sub_w < 0 || setup->to_sub_w < values->col_pos + 3)
				setup->fit = 0;
			else
				setup->fit = 1;
		}
	}
}

void					ft_print_more(t_term *setup, t_vals *values)
{
	if (setup->width > 65)
		values->lin_pos = 17;
	else
		values->lin_pos = 0;
}

void					ft_print(t_args *arglist, t_vals *values, t_term *setup)
{
	t_args				*tmp;
	static int			checker = 0;

	tmp = arglist;
	if (setup->width > 65)
	{
		ft_waddup();
		tputs(tgoto(tgetstr("cm", NULL), 0, 17), 1, ft_pointchar);
	}
	while (tmp)
	{
		if (values->curr == tmp->pos)
			ft_putstr_fd(tgetstr("us", NULL), 0);
		if (tmp->sel == 1)
			ft_putstr_fd(tgetstr("mr", NULL), 0);
		ft_putstr_fd(tmp->name, 0);
		ft_putstr_fd(tgetstr("me", NULL), 0);
		values->lin_pos += 1;
		ft_padder(values, setup, checker);
		tputs(tgoto(tgetstr("cm", NULL), values->col_pos, values->lin_pos),
		1, ft_pointchar);
		tmp = tmp->next;
	}
	ft_print_more(setup, values);
	checker = 1;
}

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

void					ft_free_that_shiet(t_args *arglist, t_vals *values, t_term *setup)
{
	ft_freelist(arglist);
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
	if (buf == 27)
		ft_free_that_shiet(arglist, values, setup);
	}
}

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

void					ft_set_values(t_vals *values, t_args *arglist,
						t_term *setup)
{
	values->col_pos = 0;
	values->result = 0;
	if (setup->width > 65)
		values->lin_pos = 17;
	else
		values->lin_pos = 0;
	values->curr = 0;
	ft_getmax(arglist, values);
}

void					ft_display_loop(t_args	*arglist, t_term *setup)
{
	int					buf;
	int					i;
	t_vals				*values;

	i = 0;
	buf = 0;
	values = ft_memalloc(sizeof(t_vals));
	ft_set_values(values, arglist, setup);
	tputs(tgetstr("ti", NULL), 0, ft_pointchar);
	tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_pointchar);
	ft_print(arglist, values, setup);
	if (!setup->fit)
	{
		tputs(tgetstr("cl", NULL), 1, ft_pointchar);
		ft_putendl_fd("please enlarge terminal window", 0);
	}
	while (42)
	{
		read(0, &buf, 8);
		values->col_pos = 0;
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

int						main(int ac, char **av)
{
	int					i;
	char				*orterm;
	t_term				*setup;
	t_args				*arglist;

	i = 0;
	if (ac == 1)
	{
		(ft_putendl_fd("ft_select: usage : ./ft_select [arguments...]", 2));
		exit(EXIT_FAILURE);
	}
	while (av[++i])
		ft_getargs(&arglist, av[i]);
	setup = ft_memalloc(sizeof(t_term));
	if (!(orterm = getenv("TERM")))
	{
		ft_putendl_fd("error : no TERM variable set", 2);
		exit(EXIT_FAILURE);
	}
	ft_init(orterm, setup, arglist);
	return (0);
}
