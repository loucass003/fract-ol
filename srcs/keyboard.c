/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 17:00:41 by llelievr          #+#    #+#             */
/*   Updated: 2019/01/08 19:15:10 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		key_event(int k, t_inst *inst)
{
	int		i;

	if (k == KEY_ESC)
		exit(0);
	if (k == KEY_A || k == KEY_D)
		inst->x += 1 / inst->scale * (k == KEY_D ? -1 : 1);
	if (k == KEY_W || k == KEY_S)
		inst->y += 1 / inst->scale * (k == KEY_S ? -1 : 1);
	if (k == KEY_PAGE_D || k == KEY_PAGE_U)
		inst->iter += (k == KEY_PAGE_D ? -4 : 4);
	if (k == KEY_C)
		inst->pretty = !inst->pretty;
	i = -1;
	while (++i < 5)
		if (g_fractals[i].key == k)
		{
			inst->selected = g_fractals + i;
			break ;
		}
	render(inst);
	return (0);
}

void			init_key_events(t_inst *inst)
{
	mlx_do_key_autorepeaton(inst->mlx.mlx_ptr);
	mlx_hook(inst->mlx.win_ptr, 2, 1, key_event, inst);
}
