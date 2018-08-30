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
#include <vector_math.h>
#include <stdio.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


int main(int argc, char *args[]) {
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

    int nx = 640;
    int ny = 480;

    for (int j = ny - 1; j >= 0 ; j--) {
        for (int i = 0; i < nx; i++) {
            t_vec3 color = new_vec((double) i / (double) nx, (double) j / (double) ny, 0.7);

            t_vec3 draw = color.mult_scalar(color, (int)255.99);

            SDL_SetRenderDrawColor(renderer, draw.x, draw.y, draw.z, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawPoint(renderer, i, j);
        }
	}

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