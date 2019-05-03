#include <SDL.h>
#include <iostream>
#include <string>

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int main(int argc, char **argv)
{
	//initiate SDL with the subsystems you want to use ie SDL_INIT_VIDEO
	//we're initaliasing all of them (sound, input, video etc)
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "SDL Fail initialised!!!\n";
		return -1; //failed, dont continue rest of main code
	}
	else
	{
		cout << "SDL initialised success!!!\n";
	}

	//create window, params are: window title, window pos x, pos y, width, height, window flags
	window = SDL_CreateWindow("5796_Tai_Game", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN );/*| SDL_WINDOW_FULLSCREEN*/

	if (window != NULL){
		cout << "Window created succes!" << endl;
	}
	else
	{
		cout << "Failed to create window!" << endl;
		return -1;
	}

	//create renderer to help draw stuff to the screen
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer != NULL)
	{
		cout << "Renderer created!" << endl;
	}
	else
	{
		cout << "Renderer FAILED!" << endl;
		return -1;
	}
	//set drawing colour for the renderer, numbers are: RGBA(alpha, transparency). All values between 0-255
	SDL_SetRenderDrawColor(renderer, 0, 228, 255, 255);
	//clear screen with current draw colour
	SDL_RenderClear(renderer);
	//TODO draw stuff to renderer here, like game images, colours, ui whatever
	//set drawing colour to BABY BLUE
	//SDL_SetRenderDrawColor(renderer, 0, 228, 255, 255);
	//make a SDL_Rect, to describe a rectangle x,y,w,h
	//SDL_Rect rect = { 100, 50, 600, 240 };

	//render rectangle to screen (renderer and a rectangle for positioning)
	//SDL_RenderFillRect(renderer, &rect);
	//then
	//get renderer to output to the window
	SDL_RenderPresent(renderer);
	//SDL_Delay pauses game for x many milliseconds
	SDL_Delay(5000); //5000ms = 5secs

	//clean up renderer and window properly (aka clean up dynamic memory)
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	//shut down subsystems and cleanup any setup it did earlier in sdl_init
	SDL_Quit();

	system("pause");

	return 0;
}
