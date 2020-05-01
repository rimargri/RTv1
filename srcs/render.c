/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvernius <cvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 16:00:15 by cvernius          #+#    #+#             */
/*   Updated: 2020/03/17 17:45:45 by cvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void ray_normalize(t_ray *ray)
{
	ray->dir = (t_vec3){0.0f, 0.0f, 0.0f};
	ray->normal = (t_vec3){0.0f, 0.0f, 0.0f};
	ray->p = (t_vec3){0.0f, 0.0f, 0.0f};
	ray->reverse_dir = (t_vec3){0.0f, 0.0f, 0.0f};
}

void render(t_rtv *r)
{
	t_ivec2	iter;
	t_vec2 	coord;
	t_color col;

	iter = (t_ivec2){0, 0};
	coord = (t_vec2){0.0f, 0.0f};
	while (iter.y < WIN_H)
	{
		iter.x = 0;
		while (iter.x < WIN_W)
		{
			coord.x = (2 * (iter.x + 0.5) / (float)WIN_W - 1) * tan(FOV / 2.0) * WIN_W / (float)WIN_H;
            coord.y = (2 * (iter.y + 0.5) / (float)WIN_H - 1) * tan(FOV / 2.0);
			ray_normalize(&r->ray);
			r->ray.dir = vec_normalize((t_vec3){coord.x, coord.y, -1});
			col = trace_ray(r);
			col = byte_to_float(col);
			put_pixel(r->sdl.renderer, iter.x, iter.y, col);
			iter.x++;
		}
		iter.y++;
	}
}