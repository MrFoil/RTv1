/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrudenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 18:21:15 by arrudenk          #+#    #+#             */
/*   Updated: 2018/03/29 18:21:16 by arrudenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*TODO: lover_left_corner + u*horizontal + v*vertical - origin*/
t_ray get_ray(t_camera c, double u, double v) {
	t_vec3 a;
	t_vec3 b;

	a = c.origin;
	b = vec_minus(vec_plus(vec_plus(c.lower_left_corner, vec_mult_scalar(c.horizontal, u)),
						vec_mult_scalar(c.vertical, v)), c.origin);
/*	t_vec3 t1 = vec_mult_scalar(c.horizontal, u);
	t_vec3 t2 = vec_mult_scalar(c.vertical, v);
	t_vec3 t3 = vec_plus(c.lower_left_corner, t1);
	t_vec3 t4 = vec_plus(t3, t2);
	t_vec3 t5 = vec_minus(t4, c.origin);*/

	return (new_ray(a, b));
}
