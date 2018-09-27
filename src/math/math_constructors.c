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

#include <rtv1.h>

t_vec3		vec(double x, double y, double z)
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