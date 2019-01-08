/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 02:35:28 by llelievr          #+#    #+#             */
/*   Updated: 2019/01/08 19:03:03 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				close_main(t_inst *inst)
{
	(void)inst;
	return (0);
}

static void		init(t_inst *i)
{
	i->x = i->mlx.size.width / 2;
	i->y = i->mlx.size.height / 2;
	i->c = i->x / i->mlx.size.width + i->y / i->mlx.size.height * I;
	i->scale = 0.25;
	i->iter = 100;
	i->move = FALSE;
	i->pretty = FALSE;
}

static void		events(t_inst *inst)
{
	mlx_hook(inst->mlx.win_ptr, 17, 0, close_main, inst);
	mlx_expose_hook(inst->mlx.win_ptr, render, inst);
	init_key_events(inst);
	init_mouse_events(inst);
	mlx_loop(inst->mlx.mlx_ptr);
}

int				main(int argc, char **argv)
{
	t_inst	inst;
	int		i;

	inst.selected = NULL;
	i = 0;
	while (argc == 2 && i < 5)
		if (ft_strcmp(g_fractals[i++].name, argv[1]) == 0)
		{
			inst.selected = g_fractals + i - 1;
			break ;
		}
	if (!inst.selected)
		return (write(2, USAGE, sizeof(USAGE) - 1) & 0 + 1);
	inst.mlx.mlx_ptr = mlx_init();
	inst.mlx.size = (t_size){ 800, 800 };
	inst.mlx.win_ptr = mlx_new_window(inst.mlx.mlx_ptr, inst.mlx.size.width,
	inst.mlx.size.height + 50, "|| Fract'ol ||");
	if (!(inst.img = new_img(&inst.mlx, inst.mlx.size)))
		return (1);
	init(&inst);
	events(&inst);
	return (0);
}
