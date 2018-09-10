/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrudenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 16:16:46 by arrudenk          #+#    #+#             */
/*   Updated: 2018/05/23 16:16:47 by arrudenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector_math.h>

t_vec3 normalize_vec3(t_vec3 v) {
    t_vec3 r;
    double l;

    l = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    r.x = v.x / l;
    r.y = v.y / l;
    r.z = v.z / l;
    return (r);
}

t_vec3 cross_vec3(t_vec3 v1, t_vec3 v2) {
    t_vec3 r;

    r.x = v1.y * v2.z - v2.y * v1.z;
    r.y = v1.x * v2.z - v2.x * v1.z;
    r.z = v1.x * v2.y - v2.x * v1.y;
    return (r);
}

t_vec3 subtract_vec3(t_vec3 v1, t_vec3 v2) {
    t_vec3 r;

    r.x = v1.x - v2.x;
    r.y = v1.y - v2.y;
    r.z = v1.z - v2.z;
    return (r);
}

double dot_vec(t_vec3 v1, t_vec3 v2) {
    double r;

    r = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    return (r);
}

float         vec_length(t_vec3 vec)
{
    return (float)sqrt(dot_vec(vec, vec));
}

t_vec3      vec_division_scalar(t_vec3 vec, double scalar)
{
	if (scalar == 0)
		return vec;
	t_vec3 v;
    v.x = vec.x / scalar;
    v.y = vec.y / scalar;
    v.z = vec.z / scalar;

    return (v);
}

t_vec3      vec_mult_scalar(t_vec3 vec, double scalar)
{
    t_vec3 v;

	v.x = vec.x * scalar;
	v.y = vec.y * scalar;
	v.z = vec.z * scalar;

	return (v);
}

t_vec3      vec_plus(t_vec3 vec1, t_vec3 vec2){
    t_vec3 vec;

    vec.x = vec1.x + vec2.x;
    vec.y = vec1.y + vec2.y;
    vec.z = vec1.z + vec2.z;

    return (vec);
}

t_vec3      vec_minus(t_vec3 vec1, t_vec3 vec2){
    t_vec3 vec;

    vec.x = vec1.x - vec2.x;
    vec.y = vec1.y - vec2.y;
    vec.z = vec1.z - vec2.z;

    return (vec);
}

t_vec3      vec_mult(t_vec3 vec1, t_vec3 vec2){
    t_vec3 vec;

    vec.x = vec1.x * vec2.x;
    vec.y = vec1.y * vec2.y;
    vec.z = vec1.z * vec2.z;

    return (vec);
}


/*
 * we do not divide by zero
 * Ugly but usfull
 * */
t_vec3      vec_division(t_vec3 vec1, t_vec3 vec2){
    t_vec3 vec;

    vec.x = vec1.x != 0 && vec2.x != 0 ? vec1.x / vec2.x : vec1.x != 0 ? vec1.x : vec2.x;
    vec.y = vec1.y != 0 && vec2.y != 0 ? vec1.y / vec2.y : vec1.y != 0 ? vec1.y : vec2.y;
    vec.z = vec1.z != 0 && vec2.z != 0 ? vec1.z / vec2.z : vec1.z != 0 ? vec1.z : vec2.z;

    return (vec);
}

t_vec3      unit_vector(t_vec3 v){
    return (vec_division_scalar(v, vec_length(v)));
}