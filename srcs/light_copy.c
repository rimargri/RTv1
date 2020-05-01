/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvernius <cvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 20:36:57 by cvernius          #+#    #+#             */
/*   Updated: 2020/03/17 15:35:32 by cvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float	calculate_intensity(float light_intensity, t_vec3 light_dir, t_intersect intersect, t_vec3 view)
{
	float	intensity;
	t_vec3 light;

	light = vec_normalize(light_dir);
	intensity = 0.0f;
	intensity += calculate_diffuse(light_intensity, light, intersect.normal); // * intersect.s.sphere->material.a.x;
	if (intersect.material.specular >= 0)
		intensity += calculate_reflection(view, light_dir, light_intensity, intersect); // * intersect.s.sphere->material.a.y;
	return (intensity);
}

float	calculate_lightning(t_rtv *r, t_vec3 dir, t_intersect intersect, t_vec3 p)
{
	int		i;
	float	total_intensity;
	t_vec3	light_dir;

	i = 0;
	total_intensity = 0.0f;
	while (i < r->count_lights)
	{
		if (!ft_strcmp(r->light[i].type, POINT))
			light_dir = vec_diff(p, r->light[i].position);
		if (!ft_strcmp(r->light[i].type, DIRECTIONAL))
			light_dir = r->light[i].direction;
		if (!ft_strcmp(r->light[i].type, AMBIENT))
			total_intensity += r->light[i].intensity;
		else
			total_intensity += calculate_intensity(r->light[i].intensity, light_dir, intersect, dir);
		i++;
	}
	if (total_intensity > 1.0f)
		total_intensity = 1.0f;
	return (total_intensity);
}

t_vec3		get_normal_sphere(t_vec3 p, t_vec3 center_sphere)
{
	t_vec3	normal;
	t_vec3	normal_dir;
	
	normal = vec_diff(center_sphere, p);
	normal_dir = vec_normalize(normal);
	return (normal_dir);
}

float		get_light(t_closest_sphere closest, t_vec3 dir, t_rtv *r)
{
	t_intersect intersect;
	t_vec3		reverse_dir;
	float		intensity;
	t_vec3		p;

	intersect.s = closest;
	reverse_dir = mult_vec_const(dir, -1);
	p = vec_add(r->camera, mult_vec_const(dir, closest.dist));
	intersect.normal = get_normal_sphere(p, closest.sphere->center);
	intersect.material = closest.sphere->material;
	// intensity = calculate_lightning(r, dir, normal_dir, closest.sphere->material.specular, p);
	intensity = calculate_lightning(r, reverse_dir, intersect, p);
	return (intensity);
}

t_color	add_light(t_color col, t_closest_sphere closest, t_vec3 dir, t_rtv *r)
{
	float intensity;

	intensity = get_light(closest, dir, r);
	col.r *= intensity;
	col.g *= intensity;
	col.b *= intensity;
	return (col);
}




/*
**************************************************
					escise 
**************************************************
*/

float	calculate_types_light(t_light light, t_ray ray, float specular)
{
	float intensity;

	intensity = 0.0f;
	intensity += calculate_diffuse(light.intensity, light.direction, ray.normal);  // * intersect.s.sphere->material.a.x;
	if (specular >= 0)
		intensity += calculate_reflection(reverse_dir, light, ray, specular);  // * intersect.s.sphere->material.a.y;
	// printf("intensity = %f\n", intensity);
	return (intensity);
}

float	iterate_light(t_rtv *r, float specular)
{
	int		i;
	float	intensity;

	i = 0;
	intensity = 0.0f;
	while (i < r->count_lights)
	{
		if (!ft_strcmp(r->light[i].type, POINT))
			r->light[i].direction = vec_diff(r->ray.p, r->light[i].position);
		if (!ft_strcmp(r->light[i].type, DIRECTIONAL))
			r->light[i].direction = r->light[i].direction;
		if (!ft_strcmp(r->light[i].type, AMBIENT))
			intensity += r->light[i].intensity;
		else
			intensity += calculate_types_light(r->light[i], r->ray, specular);
		i++;
	}
	if (intensity > 1.0f)
		intensity = 1.0f;
	return (intensity);
}

t_color calculate_lightning(t_rtv *r, t_closest_obj closest)
{
	float intensity;

	intensity = 0.0f;
	intensity = iterate_light(r, ((t_sphere *)closest.obj)->material.specular);
	add_light(&((t_sphere *)closest.obj)->material.color, intensity);
	return (((t_sphere *)closest.obj)->material.color);
}

void	add_light(t_color *col, float intensity)
{
	col->r *= intensity;
	col->g *= intensity;
	col->b *= intensity;
}


/**************************/

void	iterate_light(t_rtv *r, t_material material, float *intensity)
{
	int		i;
	t_vec3 light_dir;

	i = 0;
	while (i < r->count_lights)
	{
		// printf("i = %d\nt = %s\n", i, r->light[i].type);
		// printf("r->ray.p = %f %f %f\n", r->ray.p.x, r->ray.p.y, r->ray.p.z);
		if (!ft_strcmp(r->light[i].type, POINT))
			r->light[i].direction = vec_diff(r->ray.p, r->light[i].position);
		if (!ft_strcmp(r->light[i].type, DIRECTIONAL))
			r->light[i].direction = r->light[i].direction;
		if (!ft_strcmp(r->light[i].type, AMBIENT))
			*intensity += r->light[i].intensity;
		else
			calculate_types_light(r, r->light[i], material, intensity);
		i++;
	}
	if (*intensity > 1.0f)
		*intensity = 1.0f;
	// printf("%f\n", *intensity);
}









/*************************************************************/







/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvernius <cvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 20:36:57 by cvernius          #+#    #+#             */
/*   Updated: 2020/03/17 15:35:32 by cvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	calculate_types_light(t_rtv *r, t_light light, t_material material, float *intensity)
{
	calculate_diffuse(light, r->ray.normal, intensity);
	// *intensity *= material.a.x;
	// if (material.specular >= 0)
	// {
	// 	calculate_reflection(r->ray, light, material.specular, intensity);
	// 	*intensity *= material.a.y;
	// }
	// printf("%f\n", *intensity);
	// printf("ray->normal = %f %f %f\n", r->ray.normal);
}

void	iterate_light(t_rtv *r, t_material material, float *intensity)
{
	int		i;

	i = 0;
	while (i < COUNT_LIGHTS)
	{
		if (!ft_strcmp(r->light[i].type, POINT))
		{
			r->light[i].position = mult_vec_const(r->light[i].position, -1);
			r->light[i].direction = vec_diff(r->ray.p, r->light[i].position);
		}
		if (!ft_strcmp(r->light[i].type, DIRECTIONAL))
			r->light[i].direction = r->light[i].direction;
		if (!ft_strcmp(r->light[i].type, AMBIENT))
			*intensity += r->light[i].intensity;
		else
		{
			r->light[i].direction = mult_vec_const(r->light[i].direction, -1);
			calculate_types_light(r, r->light[i], material, intensity);
		}
		i++;
	}
	if (*intensity > 1.0f)
		*intensity = 1.0f;
	// printf("aft %f\n", *intensity);
}

t_color calculate_lightning(t_rtv *r, t_closest_obj closest)
{
	float	intensity;
	t_color	col;

	intensity = 0.0f;
	r->ray.reverse_dir = mult_vec_const(r->ray.dir, -1);
	// r->ray.p = vec_add(r->camera, mult_vec_const(r->ray.dir, closest.dist));
	r->ray.p = vec_add(r->camera, mult_vec_const(r->ray.reverse_dir, closest.dist));
	// printf("%f\n", closest.dist);
	r->ray.normal = get_normal_sphere(r->ray.p, ((t_sphere *)closest.obj)->center);
	// printf("bef %f\n", intensity);
	iterate_light(r, ((t_sphere *)closest.obj)->material, &intensity);
	add_light(((t_sphere *)closest.obj)->material.color, &col, intensity);
	return (col);
}

void	add_light(t_color col, t_color *res_col, float intensity)
{
	res_col->r = col.r * intensity;
	res_col->g = col.g * intensity;
	res_col->b = col.b * intensity;
	// col.r *= intensity;
	// col.g *= intensity;
	// col.b *= intensity;
	// return (res_col);
}
