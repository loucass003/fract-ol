/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 18:01:47 by llelievr          #+#    #+#             */
/*   Updated: 2019/01/08 18:29:29 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	mouse_hook(int button, int x, int y, t_inst *inst)
{
	double	oscale;

	if (button == 5 || button == 4)
	{
		oscale = button == 5 ? 1.1 : 0.9;
		inst->x = x - (x - inst->x) * oscale;
		inst->y = y - (y - inst->y) * oscale;
		inst->scale *= oscale;
		render(inst);
	}
	inst->move = (button == 1);
	return (0);
}

static int	mouse_release(int button, int x, int y, t_inst *inst)
{
	(void)x;
	(void)y;
	inst->move = !(inst->move && button == 1);
	return (0);
}

static int	mousem_hook(int x, int y, t_inst *inst)
{
	const double	div2x = inst->mlx.size.width / 2;
	const double	div2y = inst->mlx.size.height / 2;

	if (!inst->move)
		return (0);
	inst->c = (double)(x - div2x) / inst->mlx.size.width +
		(double)(y - div2y) / inst->mlx.size.height * I;
	render(inst);
	return (0);
}

void		init_mouse_events(t_inst *inst)
{
	mlx_mouse_hook(inst->mlx.win_ptr, mouse_hook, inst);
	mlx_hook(inst->mlx.win_ptr, 5, 6, mouse_release, inst);
	mlx_hook(inst->mlx.win_ptr, 6, 6, mousem_hook, inst);
}
