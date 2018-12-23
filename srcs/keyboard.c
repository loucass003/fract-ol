/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 17:00:41 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/22 20:07:35 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		key_event(int k, t_inst *inst)
{
	(void)inst;
	if (k == KEY_ESC)
		exit(0);
	if (k == KEY_A || k == KEY_D)
		inst->pos.x += 100 / inst->scale * (k == KEY_D ? -1 : 1);
	if (k == KEY_W || k == KEY_S)
		inst->pos.y += 100 / inst->scale * (k == KEY_S ? -1 : 1);
	if (k == KEY_PAGE_D || k == KEY_PAGE_U)
		inst->iter += (k == KEY_PAGE_D ? -4 : 4);

	ft_putnbr(k);
	ft_putendl("");
	render(inst);
	return (0);
}