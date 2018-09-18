/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrudenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 17:30:36 by arrudenk          #+#    #+#             */
/*   Updated: 2018/05/23 17:30:38 by arrudenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector_math.h>

//Sphere - signed - exact
double sdSphere(t_vec3 vec, float s) {
	return (vec_length(vec) - s * s);
}

t_sphere *new_sphere(t_vec3 pos, double radius) {
	t_sphere *s;

	s = malloc(sizeof(t_vec3) + sizeof(double));
	s->radius = radius;
	s->center = pos;
	return (s);
}