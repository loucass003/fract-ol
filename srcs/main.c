/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 02:35:28 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/22 21:37:43 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		colorize(size_t n, size_t max)
{
	const long double	t = (long double)n / (long double)max;

	return (ft_color_i(ft_color(
		(u_int8_t)(9*(1-t)*t*t*t*255),
		(u_int8_t)(15*(1-t)*(1-t)*t*t*255),
		(u_int8_t)(8.5*(1-t)*(1-t)*(1-t)*t*255)
	)));
}

int		render(t_inst *inst)
{
	t_complex	c;
	size_t		i;

	refresh_img(inst->img);
	for(int y = 0 ; y < inst->mlx.size.height; y++)
	{
		for(int x = 0; x < inst->mlx.size.width; x++)
		{
			c = ((float)(y - inst->pos.y) / ((float)inst->scale * (float)inst->mlx.size.height)) * I + (((float)(x - inst->pos.x) / ((float)inst->scale * (float)inst->mlx.size.width)));
			i = mandelbrot(c, inst->iter);
			if (i == inst->iter)
				put_pixel(inst->img, (t_pixel){ x, y, 0 });
			else
				put_pixel(inst->img, (t_pixel){ x, y, colorize(i, inst->iter) });
		}
	}
	mlx_put_image_to_window(inst->mlx.mlx_ptr, inst->mlx.win_ptr, inst->img->img_ptr, 0, 0);
	return (0);
}

int		close_main(t_inst *inst)
{
	(void)inst;
	return (0);
}

static int	mouse_hook(int button, int x, int y, t_inst *inst)
{
	long double	oscale;
	if (button == 5 || button == 4)
	{
		oscale = button == 5 ? 1.1 : 0.9;
		inst->pos.x = x - (x - inst->pos.x) * oscale;
		inst->pos.y = y - (y - inst->pos.y) * oscale;
		inst->scale *= oscale;
		render(inst);
	}
	return (0);
}


int		main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	t_inst	inst;

	inst.mlx.mlx_ptr = mlx_init();
	inst.mlx.size = (t_size){ 500, 800 };
	inst.mlx.win_ptr = mlx_new_window(inst.mlx.mlx_ptr, inst.mlx.size.width, inst.mlx.size.height, "|| Fract'ol ||");
	if(!(inst.img = new_img(&inst.mlx, inst.mlx.size)))
		return (1);
	inst.pos = (t_vec2){ (float)inst.mlx.size.width / 2, (float)inst.mlx.size.height / 2 };
	inst.scale = 0.25;
	inst.iter = 50;
	put_pixel(inst.img, (t_pixel){ 250, 250, ft_color_i(ft_color(255, 0, 0)) });
	
	mlx_do_key_autorepeaton(inst.mlx.mlx_ptr);
	mlx_hook(inst.mlx.win_ptr, 2, 1, key_event, &inst);
	mlx_hook(inst.mlx.win_ptr, 17, 0, close_main, &inst);
	mlx_mouse_hook(inst.mlx.win_ptr, mouse_hook, &inst);
	render(&inst);
	mlx_loop(inst.mlx.mlx_ptr);
	return (0);
}