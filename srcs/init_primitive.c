/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_primitive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvernius <cvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 22:26:39 by cvernius          #+#    #+#             */
/*   Updated: 2020/03/17 17:51:27 by cvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_cylinder(t_scene *scene)
{
	scene->object = (t_cylinder *)malloc(sizeof(t_cylinder));
	scene->object == NULL ? exit(88) : 0;
	((t_cylinder *)scene->object)->radius = 1.0f;
	((t_cylinder *)scene->object)->offset = (t_vec3){2.0f, 0.0f, -5.0f};
	((t_cylinder *)scene->object)->material.color = float_to_byte(BRIGHT_PURPLE);
	((t_cylinder *)scene->object)->material.specular = 50.0f;
	scene->type = CYLINDER;
}


//cone: a >= b !!
void	init_cone(t_scene *scene)
{
	scene->object = (t_cone *)malloc(sizeof(t_cone));
	scene->object == NULL ? exit(88) : 0;
	// ((t_cone *)scene->object)->offset = (t_vec3){5.0f, 3.0f, -5.0f};
	((t_cone *)scene->object)->offset = (t_vec3){6.0f, 2.0f, 6.324555320336759f};
	// ((t_cone *)scene->object)->c = (t_coefficients){3.0f, 1.0f, -1.0f};
	((t_cone *)scene->object)->material.color = float_to_byte(VINOUS);
	((t_cone *)scene->object)->material.specular = 50.0f;
	scene->type = CONE;
}

void	init_plane_1(t_scene *scene)
{
	scene->object = (t_plane *)malloc(sizeof(t_plane));
	scene->object == NULL ? exit(88) : 0;
	((t_plane *)scene->object)->major_vec = (t_vec3){0.0f, 0.0f, 0.0f};
	((t_plane *)scene->object)->material.color = float_to_byte(VINOUS);
	((t_plane *)scene->object)->material.specular = 50.0f;
	scene->type = PLANE_1;
}

void	init_primitive(t_rtv *r)
{
	int		i;
	t_scene *scene;
	t_scene	*tmp;

	i = 0;
	(COUNT_PRIMITIVE == 0 ? exit(99) : 0);
	while (i < COUNT_PRIMITIVE)
	{
		scene = (t_scene*)malloc(sizeof(t_scene));
		(scene == NULL ? exit(8) : 1);
		// if (i == 1)
		// 	init_sphere(i, scene);
		// if (i == 0)
		// 	init_plane_1(scene);
		// if (i == 1)
		// 	init_plane_2(scene);
		// if (i == 2)
		// 	init_plane_3(scene);
		if (i == 0)
			init_cone(scene);
		// if (i == 0)
		// 	init_cylinder(scene);
		if (i == 0)
			scene->next = NULL;
		else
			scene->next = tmp;
		i++;
		tmp = scene;
	}
	r->scene = scene;
}
