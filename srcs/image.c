/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 00:36:51 by llelievr          #+#    #+#             */
/*   Updated: 2019/01/08 16:57:10 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_img			*new_img(t_mlx *mlx, t_size size)
{
	t_img	*img;

	if (!(img = (t_img *)malloc(sizeof(t_img))))
		return (NULL);
	img->img_ptr = mlx_new_image(mlx->mlx_ptr, size.width, size.height);
	img->img_buf = mlx_get_data_addr(img->img_ptr, &img->s_pixel, &img->s_line,
		&img->endian);
	img->size = size;
	return (img);
}

t_img			*clear_img(t_img *img)
{
	if (img->img_buf)
		ft_bzero(img->img_buf, (img->size.width * img->size.height * 4));
	return (img);
}

void			destroy_img(t_mlx *inst, t_img *img)
{
	if (!img)
		return ;
	mlx_destroy_image(inst->mlx_ptr, img->img_ptr);
	ft_memdel((void **)&img);
}

t_bool			put_pixel(t_img *img, t_pixel p)
{
	ft_memmove(img->img_buf + (p.y * img->s_line) + (p.x * 4), &p.color, 4);
	return (TRUE);
}
