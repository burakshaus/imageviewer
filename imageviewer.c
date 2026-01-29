#include<stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
int main(int argc, char* argv[]){
	if(argc<2){
		printf("Usage: %s <image_path>\n", argv[0]);
return 1;
	}

	if (SDL_Init(SDL_INIT_VIDEO)<0){
		printf("SDL could not initialize ! SDL_Error: %s\n",SDL_GetError());
		return 1;

	}

	SDL_Window* window = SDL_CreateWindow("C Image Viewer", SDL_WINDIWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,800,600,SDL_WINDIW_SHOWN | SDL_WINDIW_RESIZABLE);

	SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	SDL_Texture* texture = IMG_LoadTexture(renderer, argv[1]);
	if(!texture){
prinf("Could not load image! Error:%s\n",IMG_GetError());
return 1;
	int quit = 0;
	SDL_Event e;
	while(!quit){
	while(SDL_PollEvent(&e) != o){
	if (e.type == SDL_QUIT){
quit = 1;
	}
	SDL_RenderClear(renderer);
	SQL_RenderCopy(renderer,texture,NULL,NULL);
	SDL_RenderPresent(renderer);

	}

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();

	}
	}

return 0;
}
