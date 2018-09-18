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
#include <float.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 400



double	hit_sphere(const t_vec3 center, double radius, const t_ray ray){
	t_vec3 oc = vec_minus(ray.A, center);
	// dot(B,B) + 2 * dot(B, A-C) + dot(A-C, A-C) - R*R = 0;
	double a = dot_vec(ray.B, ray.B);
	double b = 2.0 * dot_vec(oc, ray.B);
	double c = dot_vec(oc, oc) - radius * radius;
	double discriminant = b*b - 4 * a * c;
	if(discriminant < 0){
		return (-1.0);
	} else{
		return ((-b - sqrt(discriminant)) / (2.0*a));
	}
}

t_vec3 color(const t_ray r, t_list *list) {
	double t;
	t_vec3 unit_direction;
	t_hit_record *rec;
	if (list_hit(r, 0.0, DBL_MAX, &rec, list)) {
		return (vec_mult_scalar(new_vec(rec->normal.x + 1, rec->normal.y + 1, rec->normal.z + 1), 0.5));
	} else {
		unit_direction = unit_vector(r.B);
		t = .5 * (unit_direction.y + 1.0);
		return vec_plus(vec_mult_scalar(new_vec(1.0, 1.0, 1.0), (1.0 - t)), vec_mult_scalar(new_vec(0.5, 0.7, 1.0), t));
	}
}

void	draw_scene(SDL_Renderer *renderer){
	int nx = SCREEN_WIDTH;
	int ny = SCREEN_HEIGHT;

	t_list *list;
	t_list *list2;

	t_sphere *sphere;
	t_sphere *sphere2;

	sphere = new_sphere(new_vec(0, 0, -1), 0.5);
	sphere2 = new_sphere(new_vec(0, -100.5, -1), 100);

	list = ft_lstnew(sphere, sizeof(t_sphere));
	list2 = ft_lstnew(sphere2, sizeof(t_sphere));
	ft_lstadd(&list2, list);

	t_camera camera = new_camera(new_vec(-2, -1, -1),
								 new_vec(4, .0, .0),
								 new_vec(.0, 2, .0),
								 new_vec(.0, .0, .0));

	t_vec3 col;

	for (int j = ny - 1; j >= 0 ; j--) {
		for (int i = 0; i < nx; i++) {
			double u = (double) i / (double) nx;
			double v = (double) j / (double) ny;

			t_ray ray = get_ray(camera, u, v); // ray for current coordinates
/*
			t_vec3 test = new_vec(u, v, 0);
			double testFormulaSphere = sdSphere(test, 0.7);
			printf("%f\n", testFormulaSphere);
			if (testFormulaSphere < 0){
				col = new_vec(1, 0, 0);
			}
			else
			{
				col = new_vec(u, v, 0.5);
			}*/
			/*t_vec3 p = point_at_parameter(ray, 2.0);*/
			col = color(ray, list);
			t_vec3 draw = vec_mult_scalar(col, (int)255.99);

			SDL_SetRenderDrawColor(renderer, draw.x, draw.y, draw.z, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawPoint(renderer, i, j);
		}
	}

}

int main(int argc, char *args[]) {
	(void) argc;
	(void) args;
    SDL_Window *window = NULL;
    SDL_Surface *screenSurface = NULL;
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

    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xA0, 0x06, 0xFF));
    SDL_UpdateWindowSurface(window);

    //SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_Event event;

	draw_scene(renderer);

    SDL_RenderPresent(renderer);

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