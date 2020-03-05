/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvernius <cvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 20:29:49 by cvernius          #+#    #+#             */
/*   Updated: 2020/03/05 19:48:37 by cvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec2 intersect_ray_sphere(t_vec3 camera, t_vec3 *D, t_sphere *sphere)
{
	t_vec2 res;
	t_vec3 C;
	double R;
	t_vec3 *Cam_C;
	double k1;
	double k2;
	double k3;
	double discriminant;
	t_vec2 t;

	C = sphere->center;
	R = sphere->radius;
	Cam_C = vec_diff(&camera, &C);
	k1 = dot_product(D, D);
	k2 = 2 * dot_product(Cam_C, D);
	k3 = dot_product(Cam_C, Cam_C) - R * R;
	discriminant = k2 * k2 - 4 * k1 * k3;
	if (discriminant < 0)
	{
		res = (t_vec2){0, 0};
		return (res);
	}
	t.x = (- k2 + sqrt(discriminant)) / (2 * k1);
	t.y = (- k2 - sqrt(discriminant)) / (2 * k1);
	return (t);
}

/*
** trace_ray - вычисляет пересечение луча с каждой сферой, и возвращает цвет сферы
** в ближайшей точке пересечения, которая находится в требуемом интервале t
*/ 

t_color		trace_ray(t_vec3 camera, t_vec3 *D, double t_min, t_sphere *sphere)
{
	//?? double t1, t2;
	t_sphere *closest_sphere;
	t_vec2 t;
	double closest_t;
	t_color c;
	int i = 0;

	// closest_t = t_max;
	closest_t = t_max;
	closest_sphere = (t_sphere*)(malloc(sizeof(t_sphere)));
	// while (i < 2)
	// {
		t = intersect_ray_sphere(camera, D, sphere);
		if ((t.x >= t_min && t.x <= t_max) && t.x < closest_t)
		{
			closest_t = t.x;
			closest_sphere = sphere;
		}
		if ((t.y >= t_min && t.y <= t_max) && t.y < closest_t)
		{
			closest_t = t.y;
			closest_sphere = sphere;
		}
		i++;
	// }
	if (closest_sphere == NULL)
	{
		c = (t_color){255, 255, 255};
		return (c);
	}
	return (closest_sphere->color);
}