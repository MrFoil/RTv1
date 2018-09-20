/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrudenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:51:40 by arrudenk          #+#    #+#             */
/*   Updated: 2018/05/10 16:51:41 by arrudenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rtv1.h"
#include "vector_math.h"
#include <stdio.h>
#define _XOPEN_SOURCE
#include <stdlib.h>
#include <float.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 400

t_vec3		random_in_unit_sphere();
t_vec3		color(t_ray r, t_list *list);
double		randfrom(double min, double max);
void		draw_scene(SDL_Renderer *renderer);

int main(int argc, char *args[]) {
	(void) argc;
	(void) args;
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;


	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("%s%s\n", "could not initialize sdl2: %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow(
			"hello_sdl2",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN
	);
	if (window == NULL) {
		fprintf(stderr, "could not create window: %s\n", SDL_GetError());
		return 1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

//    screenSurface = SDL_GetWindowSurface(window);
//    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xA0, 0x06, 0xFF));
//    SDL_UpdateWindowSurface(window);

	//SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	SDL_Event event;

	draw_scene(renderer);

	int quit = 0;

	while (!quit) {

		/* Poll for events */
		while (SDL_PollEvent(&event)) {

			switch (event.type) {
				/* Keyboard event */
				/* Pass the event data onto PrintKeyInfo() */
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					printf("KEYUP: %i\n", event.type);
					break;

					/* SDL_QUIT event (window close) */
				case SDL_QUIT:
					quit = 1;
					break;

				default:
					break;
			}

		}

	}

	SDL_Delay(0);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

	t_vec3 color(const t_ray r, t_list *list) {
	double			t;
	t_vec3			unit_direction;
	t_hit_record	*rec;
	t_vec3			target;
	if (list_hit(r, 0.001, DBL_MAX, &rec, list)) {
		/* | rec.point + rec.normal + random_inUnit_sphere() | */
		target = vec_plus(vec_plus(rec->point, rec->normal),random_in_unit_sphere());
		return vec_division_scalar(color(new_ray(rec->point, vec_minus(target, rec->point)), list),0.5);
	} else {
		unit_direction = unit_vector(r.B);
		t = .5 * (unit_direction.y + 1.0);
		return vec_plus(vec_mult_scalar(new_vec(1.0, 1.0, 1.0), (1.0 - t)), vec_mult_scalar(new_vec(0.5, 0.7, 1.0), t));
	}
}

t_vec3	reflect(t_vec3 v, t_vec3 n){
	return vec_minus(v, vec_mult_scalar(n, 2*dot_vec(v, n)));/*|||| v - 2*dot(v, n) * n ||||*/
}

bool	lambertian_scatter(t_ray ray, t_hit_record *record, t_vec3 *attenuation, t_ray *scattered){
	t_vec3	target;

	target = vec_plus(vec_plus(record->point, record->normal),random_in_unit_sphere());
	*scattered = new_ray(record->point, vec_minus(target, record->point));
	*attenuation = record->mat_ptr->material_albedo;
	return (true);
}

bool	metal_scatter(t_ray ray, t_hit_record *record, t_vec3 *attenuation, t_ray *scattered){
	t_vec3 reflected;

	reflected = reflect(unit_vector(ray.B), record->normal);
	*scattered = new_ray(record->point,reflected);
	*attenuation = record->mat_ptr->material_albedo;
	return (dot_vec((*scattered).B, record->normal) > 0);
}


void	draw_scene(SDL_Renderer *renderer){
	int nx = SCREEN_WIDTH;
	int ny = SCREEN_HEIGHT;
	int antialiasingX = 10;

	t_list *list;
	t_list *list2;
	t_list *list3;
	t_list *list4;

	t_sphere *sphere;
	t_sphere *sphere2;
	t_sphere *sphere3;
	t_sphere *sphere4;

	sphere = new_sphere(new_vec(0, 0, -1), 0.5);
	sphere2 = new_sphere(new_vec(0, 100.5, -1), 100);
	sphere3 = new_sphere(new_vec(-1, 0.3, -1.2), 0.3);
	sphere4 = new_sphere(new_vec(1, 0.3, -1.2), 0.3);

	list = ft_lstnew(sphere, sizeof(t_sphere));
	list2 = ft_lstnew(sphere2, sizeof(t_sphere));
	list3 = ft_lstnew(sphere3, sizeof(t_sphere));
	list4 = ft_lstnew(sphere4, sizeof(t_sphere));
	ft_lstadd(&list2, list);
	ft_lstadd(&list3, list->next);
	ft_lstadd(&list4, list->next->next);


	t_camera camera = new_camera(new_vec(-2.0, -1.0, -1.0),/*lower left corner*/
								 new_vec(4.0, 0.0, 0.0),/*horizontal*/
								 new_vec(0.0, 2.0, 0.0),/*vertical*/
								 new_vec(0.0, 0.0, 0));/*origin*/

	t_vec3 col;

	for (int j = ny -1; j >= 0 ; j--) {
		for (int i = 0; i < nx; i++) {
			col = new_vec(0,0,0);
			for (int k = 0; k < antialiasingX ; k++) {
				double u = ((double)i + randfrom(0, 1)) / (double)nx;
				double v = ((double)j + randfrom(0, 1)) / (double)ny;
				t_ray ray = get_ray(camera, u, v); /*ray for current coordinates*/
				/*t_vec3 p = point_at_parameter(ray, 2.0);*/
				col = vec_plus(col,color(ray, list));
			}
			col = vec_division_scalar(col, (double)antialiasingX);
//			t_vec3 test = new_vec(u, v, 0.2);
			col = new_vec(sqrt(col.x), sqrt(col.y), sqrt(col.z));
			t_vec3 draw = vec_mult_scalar(col, (int)255.99);

//			printf("%d\t%d\t%d\n", (int)draw.x, (int)draw.y, (int)draw.z);

			SDL_SetRenderDrawColor(renderer, draw.x, draw.y, draw.z, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawPoint(renderer, i, j);
		}
		SDL_RenderPresent(renderer);
	}

}

double randfrom(double min, double max)
{
	double range = (max - min);
	double div = RAND_MAX / range;
	return min + (rand() / div);
}

t_vec3		random_in_unit_sphere(){
	double random_max;
	double random_min;

	random_max = 0.5;
	random_min = 0.1;
	t_vec3 p;
	do {
		p = vec_minus(vec_mult_scalar(new_vec(randfrom(random_min, random_max), randfrom(random_min, random_max), randfrom(random_min, random_max)),2.0),new_vec(1, 1, 1));
	}while(vec_length(p) >= random_max);
	return p;
}
