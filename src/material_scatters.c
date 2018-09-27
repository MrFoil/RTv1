//
// Created by artem.rudencko on 9/25/2018.
//

#include "rtv1.h"

t_material	new_material(float reflect, t_vec3 albedo, char *type)
{
	t_material	material;

	material.albedo = albedo;
	material.ref_index = reflect;

	if (ft_strcmp(type, "metal") == 0)
		material.scatter = &metal_scatter;
	else if (ft_strcmp(type, "lambertian") == 0)
		material.scatter = &lambertian_scatter;
	else if (ft_strcmp(type, "dielectric") == 0)
		material.scatter = &dielectric_scatter;

	return (material);
}

bool	refract(t_vec3 v, t_vec3 n, float ni_over_nt, t_vec3 *refracted)
{
	t_vec3	uv;
	float	dt;
	float	discriminant;

	uv = unit_vector(v);
	dt = dot_vec(uv, n);
	discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);
	if (discriminant > 0)
	{
		*refracted = vec_mult_scalar(vec_minus(uv,vec_mult_scalar(n, dt)), ni_over_nt);
		uv = vec_mult_scalar(n, sqrt(discriminant));
		*refracted = vec_minus(*refracted, uv);
		return (true);
	}
	else
		return (false);
}

float	schlick(float cosine, float ref_idx)
{
	float	r0;

	r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0*r0;
	return (r0 + (1 - r0) * pow((1 - cosine), 5));
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

bool	dielectric_scatter(t_ray ray, t_hit_record *record, t_vec3 *attenuation, t_ray *scattered)
{
	t_vec3	outward_normal;
	t_vec3	reflected;
	float	ni_over_nt;
	t_vec3	refracted;
	float	cosine;
	float	reflect_prob;

	reflected = vec_reflect(ray.B, record->normal);
	*attenuation = vec(1.0, 1.0, 1.0);
	if (dot_vec(ray.B, record->normal) > 0)
	{
		outward_normal = vec_mult_scalar(record->normal, -1);
		ni_over_nt = record->mat_ptr->ref_index;
		cosine = ni_over_nt * dot_vec(ray.B, record->normal) / vec_length(ray.B);
	}
	else
	{
		outward_normal = record->normal;
		ni_over_nt = 1.0 / record->mat_ptr->ref_index;
		cosine = (dot_vec(ray.B, record->normal) * -1) / vec_length(ray.B);

	}
	if (refract(ray.B, outward_normal, ni_over_nt, &refracted))
	{
		*scattered = new_ray(record->point, refracted);
		reflect_prob = schlick(cosine, record->mat_ptr->ref_index);
	}
	else
	{
		*scattered = new_ray(record->point, reflected);
		reflect_prob = 1.0;
	}
	if (randfrom(0, 1) < reflect_prob)
		*scattered = new_ray(record->point, reflected);
	else
		*scattered = new_ray(record->point, refracted);
	return (true);
}