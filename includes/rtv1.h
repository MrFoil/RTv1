/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrudenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:54:50 by arrudenk          #+#    #+#             */
/*   Updated: 2018/05/10 16:54:51 by arrudenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include "vector_math.h"
# include <SDL.h>
# include <SDL2/SDL.h>
# include <math.h>
# include "libft.h"

# define WIDTH 1280
# define HEIGHT 720

typedef struct	s_material t_material;
typedef struct	s_ray t_ray;
typedef struct	s_hit_record t_hit_record;
typedef struct s_sphere t_sphere;

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

typedef struct s_camera {
	t_vec3 lower_left_corner;
	t_vec3 horizontal;
	t_vec3 vertical;
	t_vec3 origin;
} t_camera;

typedef struct	s_ray
{
	struct s_vec3	A;
	struct s_vec3	B;
}				t_ray;

typedef struct	s_hit_record
{
	double				t;
	t_vec3				point;
	t_vec3				normal;
	struct s_material	*mat_ptr;
}			t_hit_record;

typedef struct	s_material
{
	t_vec3	albedo;
	float	ref_index;
	bool	(*scatter)(t_ray ray, t_hit_record *record, t_vec3 *attenuation, t_ray *scattered);
}				t_material;

typedef struct s_sphere {
	t_vec3		center;
	double		radius;
	t_material	material;

}			t_sphere;

t_ray			new_ray(t_vec3 v1, t_vec3 v2);
t_camera		new_camera(t_vec3 lookfrom, t_vec3 lookat, t_vec3 vup, float vfov, float aspect);
t_sphere		*new_sphere(t_vec3 pos, double radius, t_material material);

bool			sphere_hit(t_ray ray, double t_min, double t_max, t_hit_record *rec, t_sphere *s);
double			randfrom(double min, double max);
t_vec3			point_at_parameter(t_ray r, double t);
t_ray			get_ray(t_camera c, double u, double v);
bool			list_hit(t_ray ray, double d_min, double d_max, t_hit_record *rec, t_list *list);
t_vec3			random_point_in_unit_sphere();
t_material		new_material(float reflect, t_vec3 albedo, char *type);
bool			lambertian_scatter(t_ray ray, t_hit_record *record, t_vec3 *attenuation, t_ray *scattered);
bool			metal_scatter(t_ray ray, t_hit_record *record, t_vec3 *attenuation, t_ray *scattered);
bool			dielectric_scatter(t_ray ray, t_hit_record *record, t_vec3 *attenuation, t_ray *scattered);

void			ft_lstadd_end(t_list **alst, t_list *new);

#endif
