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
#include <stdio.h>
#define _XOPEN_SOURCE
#include <stdlib.h>
#include <float.h>

void		draw_scene(SDL_Renderer *renderer);

int		main(int argc, char *args[]) {
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
			WIDTH, HEIGHT,
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

t_vec3	color_by_material(const t_ray r, t_list *list, int depth)
{
	double			t;
	t_vec3			unit_direction;
	t_hit_record	*rec;
	t_vec3			attenuation;
	t_ray			scattered;

	if (list_hit(r, 0.001, DBL_MAX, &rec, list))
	{
		if (depth < 50 && rec->mat_ptr->scatter(r, rec, &attenuation, &scattered))
		{
			/*|(attenuation * color(scattered, list, depth+1))|*/
			return vec_mult(attenuation, color_by_material(scattered, list, depth + 1));
		}
		else
		{
			return (vec(0, 0, 0));
		}
	} else {
		unit_direction = unit_vector(r.B);
		t = .5 * (unit_direction.y + 1.0);
		return vec_plus(vec_mult_scalar(vec(1.0, 1.0, 1.0), (1.0 - t)), vec_mult_scalar(vec(0.5, 0.7, 1.0), t));
	}
}

void	add_sphere_to_world(t_sphere *sphere, t_list **world)
{
	if (!*world)
		*world = ft_lstnew(sphere, sizeof(t_sphere));
	else
		ft_lstadd_end(world, ft_lstnew(sphere, sizeof(t_sphere)));
}

void	draw_scene(SDL_Renderer *renderer){
	int			nx;
	int			ny;
	t_camera	camera;
	int			antialiasingX;
	t_list		*world;

	world = NULL;

	ny = HEIGHT;
	nx = WIDTH;
	antialiasingX = 1;
	camera = new_camera(vec(0, 0, 2), vec(0, 0, -1), vec(0, 1, 0), 90, (float)nx / (float)ny);
	float R = cos(M_PI/4);

	add_sphere_to_world(new_sphere(vec(0, 0, -1), 0.5, new_material(0, vec(0.1, 0.2, 0.5), "lambertian")), &world);
	add_sphere_to_world(new_sphere(vec(0, -100.5, -1), 100, new_material(0, vec(0.8, 0.8, 1), "metal")), &world);
	add_sphere_to_world(new_sphere(vec(1, 0, -1), 0.5, new_material(0, vec(1, 0.4, 0.6), "metal")), &world);
	add_sphere_to_world(new_sphere(vec(2, 0, -1), 0.5, new_material(0, vec(0.85, 0.26, 1), "lambertian")), &world);
	add_sphere_to_world(new_sphere(vec(-1, 0, -1), 0.5, new_material(1.5, vec(1, 0.5, 0.9), "dielectric")), &world);
	add_sphere_to_world(new_sphere(vec(-1, 0, -1), -0.45, new_material(1.5, vec(0, 0, 0), "dielectric")), &world);



	t_vec3 col;

	for (int j = ny -1; j >= 0 ; j--) {
		for (int i = 0; i < nx; i++) {
			col = vec(0, 0, 0);
			for (int k = 0; k < antialiasingX ; k++) {
				double u = ((double)i + randfrom(0, 1)) / (double)nx;
				double v = ((double)j + randfrom(0, 1)) / (double)ny;
				t_ray ray = get_ray(camera, u, v); /*ray for current coordinates*/
				col = vec_plus(col,color_by_material(ray, world, 0));
			}
			col = vec_division_scalar(col, (double)antialiasingX);
			col = vec(sqrt(col.x), sqrt(col.y), sqrt(col.z));
			t_vec3 draw = vec_mult_scalar(col, 255.99);

			SDL_SetRenderDrawColor(renderer, (Uint8)draw.x, (Uint8)draw.y, (Uint8)draw.z, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawPoint(renderer, i, j);
		}
		SDL_RenderPresent(renderer);
	}

}
