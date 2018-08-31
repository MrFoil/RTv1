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

t_mat4		new_mat4(void)
{
    t_mat4 m;

    m.x_axis = vec4(1, 0, 0, 0);
    m.y_axis = vec4(0, 1, 0, 0);
    m.z_axis = vec4(0, 0, 1, 0);
    m.w_axis = vec4(0, 0, 0, 1);
    return (m);
}
