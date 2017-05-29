/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 17:57:15 by jecarol           #+#    #+#             */
/*   Updated: 2017/05/29 18:43:48 by jecarol          ###   ########.fr       */
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

void					ft_waddup(void)
{
	ft_putendl("                         ,--,                                ,----,");
    ft_putendl("                      ,---.'|                              ,/   .`|");
	ft_putendl("  .--.--.       ,---,.|   | :       ,---,.  ,----..      ,`   .'  :");
	ft_putendl(" /  /    '.   ,'  .' |:   : |     ,'  .' | /   /  \\    ;    ;     /");
	ft_putendl("|  :  /`. / ,---.'   ||   ' :   ,---.'   ||   :     :.'___,/    ,'");
	ft_putendl(";  |  |--`  |   |   .';   ; '   |   |   .'.   |  ;. /|    :     |");
	ft_putendl("|  :  ;_    :   :  |-,'   | |__ :   :  |-,.   ; /--` ;    |.';  ;");
	ft_putendl(" \\  \\    `. :   |  ;/||   | :.'|:   |  ;/|;   | ;    `----'  |  |");
	ft_putendl("  `----.   \\|   :   .''   :    ;|   :   .'|   : |        '   :  ;");
	ft_putendl("    __\\ \\  ||   |  |-,|   |  ./ |   |  |-,.   | '___     |   |  '");
    ft_putendl(" /  /`--'  /'   :  ;/|;   : ;   '   :  ;/|'   ; : .'|    '   :  |");
	ft_putendl("'--'.     / |   |    \\|   ,/    |   |    \\'   | '/  :    ;   |.'");
  	ft_putendl("  `--'---'  |   :   .''---'     |   :   .'|   :    /     '---'");
  	ft_putendl("            |   | ,'            |   | ,'   \\  \\  .'");
	ft_putendl("            `----'              `----'      `---`");
}

void					ft_print(t_args *arglist, t_vals *values, t_term *setup)
{
	t_args				*tmp;

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
		tputs(tgoto(tgetstr("cm", NULL), values->col_pos, values->lin_pos),
		1, ft_pointchar);
		tmp = tmp->next;
	}
	if (setup->width > 65)
		values->lin_pos = 17;
	else
		values->lin_pos = 0;

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

void					ft_movement(t_args *arglist, int buf, t_term *setup, t_vals *values)
{
	(void)setup;
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
	if (buf == 32)
	{
		ft_toggle_sel(arglist, values);
		if (values->curr == values->count)
			values->curr = 0;
		ft_print(arglist, values, setup);
	}
	if (buf == 10)
	{
		while (arglist)
		{
			if (arglist->sel == 1)
			{
				ft_putstr_fd(arglist->name, 1);
				ft_putstr_fd(" ", 1);
			}
			arglist = arglist->next;
		}
		ft_putchar('\n');
		tputs(tgetstr("ve", NULL), 0, ft_pointchar);
		// tputs(tgetstr("te", NULL), 0, ft_pointchar);
		exit(EXIT_SUCCESS);
	}
}

void					ft_display_loop(t_args	*arglist, t_term *setup)
{
	int					buf;
	int					i;
	t_vals				*values;

	i = 0;
	values = ft_memalloc(sizeof(t_vals));
	values->col_pos = 0;
	if (setup->width > 65)
		values->lin_pos = 17;
	else
		values->lin_pos = 0;
	values->curr = 0;
	ft_getmax(arglist, values);
	tputs(tgetstr("ti", NULL), 0, ft_pointchar);
	tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_pointchar);
	ft_print(arglist, values, setup);
	while (42)
	{
		read(0, &buf, 8);
		tputs(tgetstr("cl", NULL), 1, ft_pointchar);
		values->col_pos = 0;
		ft_movement(arglist, buf, setup, values);
		buf = 0;
	}
}

void					ft_init(char *orterm, t_term *setup, t_args *arglist)
{
	int					retoor;

	if ((retoor = tgetent(NULL, orterm) < 0))
		ft_putendl_fd("error", 2);
	tcgetattr(0, &setup->attributes);
	setup->attributes.c_lflag &= ~ICANON;
	setup->attributes.c_lflag &= ~ECHO;
	tcsetattr(0, TCSADRAIN, &setup->attributes);
	tputs(tgetstr("cl", NULL), 1, ft_pointchar);
	tputs(tgetstr("vi", NULL), 1, ft_pointchar);
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
