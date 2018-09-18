/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_vec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrudenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 00:37:15 by arrudenk          #+#    #+#             */
/*   Updated: 2018/03/30 00:37:17 by arrudenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector_math.h>

t_camera new_camera(t_vec3 lower_left_corner, t_vec3 horizontal, t_vec3 vertical, t_vec3 origin) {
	t_camera camera;

	camera.lower_left_corner = lower_left_corner;
	camera.horizontal = horizontal;
	camera.vertical = vertical;
	camera.origin = origin;

	return (camera);
}

t_vec3		new_vec(double x, double y, double z)
{
	t_vec3		v;

	v.x = x;
	v.y = y;
	v.z = z;

	return (v);
}

t_ray		new_ray(t_vec3 v1, t_vec3 v2){
	t_ray ray;

	ray.A = v1;
	ray.B = v2;
	return (ray);
}

t_vec4		vec4(double x, double y, double z, double w)
{
	t_vec4		v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.w = w;
	return (v);
}