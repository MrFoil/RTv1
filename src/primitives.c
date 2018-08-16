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
float sdSphere(t_vec4 vec, float s)
{
return (dot_vec4(vec, vec) - s);//or s * s
}

