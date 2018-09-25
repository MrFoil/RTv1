//
// Created by artem.rudencko on 9/25/2018.
//

#include "rtv1.h"

t_material	new_material(t_vec3 albedo, char *type)
{
	t_material	material;

	material.albedo = albedo;

	if (ft_strcmp(type, "metal") == 0)
		material.scatter = &metal_scatter;
	else if (ft_strcmp(type, "lambertian") == 0)
		material.scatter = &lambertian_scatter;

	return (material);
}

bool	lambertian_scatter(t_ray ray, t_hit_record *record, t_vec3 *attenuation, t_ray *scattered)
{
	t_vec3	target;

	target = vec_plus(vec_plus(record->point, record->normal), random_point_in_unit_sphere());
	*scattered = new_ray(record->point, vec_minus(target, record->point));
	*attenuation = record->mat_ptr->albedo;
	return (true);
}

bool	metal_scatter(t_ray ray, t_hit_record *record, t_vec3 *attenuation, t_ray *scattered){
	t_vec3 reflected;

	reflected = vec_reflect(unit_vector(ray.B), record->normal);
	*scattered = new_ray(record->point,reflected);
	*attenuation = record->mat_ptr->albedo;
	return (dot_vec((*scattered).B, record->normal) > 0);
}