/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvernius <cvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 20:10:56 by cvernius          #+#    #+#             */
/*   Updated: 2020/03/16 18:57:41 by cvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H
#include "rtv1.h"
#include "structs.h"

// /*
// ** *********************************** **
// ** *********************************** **
// **                 mlx                 **
// ** *********************************** **
// ** *********************************** **
// */

// t_mlx		init_mlx(void);
// int			key_press(int k, t_rtv *r);
// int			close_hook(void *param);
// void		check_hooks_loops(t_rtv *r);
// int			draw_all_hook(t_rtv *r);

/*
** *********************************** **
** *********************************** **
**                 sdl       		   **
** *********************************** **
** *********************************** **
*/

t_sdl		init_sdl(void);
void		destroy_sdl(t_sdl sdl);
void		clear_window_sdl(t_sdl sdl);
void		put_pixel(SDL_Renderer *ren, int x, int y, t_color col);

/*
** *********************************** **
** *********************************** **
**               sphere       		   **
** *********************************** **
** *********************************** **
*/

void		render_sphere(t_rtv *rtv);
int 		intersect_ray_sphere(t_vec3 camera, t_vec3 dir, t_sphere sphere, float *sphere_dist);
t_color		cast_ray(t_vec3 camera, t_vec3 dir, t_rtv *r);

/*
** *********************************** **
** *********************************** **
**               color       		   **
** *********************************** **
** *********************************** **
*/

int			get_color(t_color color);

/*
** *********************************** **
** *********************************** **
**          quadratic_equation         **
** *********************************** **
** *********************************** **
*/

float		calculate_quadratic_equation(t_vec3 length_cam_center, t_vec3 dir, float r, float *t1, float *t2);
float		calc_discriminant(float a, float b, float c);
float		calc_b(t_vec3 length_cam_center, t_vec3 dir);
float		calc_a(t_vec3 dir);
float		calc_c(t_vec3 length_cam_center, float r);

/*
** *********************************** **
** *********************************** **
**               init_rtv     		   **
** *********************************** **
** *********************************** **
*/

t_vec3		init_camera(void);
t_viewport	init_viewport(void);
t_sphere	*init_sphere(t_rtv *r);
t_light		*init_light(t_rtv *r);

/*
** *********************************** **
** *********************************** **
**              lightning     		   **
** *********************************** **
** *********************************** **
*/

float		calculate_lightning(t_rtv *r, t_vec3 dir, t_vec3 vec_n);
t_color		add_light(t_color col, float count_lights);

#endif