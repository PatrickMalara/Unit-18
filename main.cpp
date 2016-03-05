//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <iostream>

//These are the dimensions of the window, they are constant 
//because we don't want them to change.
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The window we'll be rendering to
SDL_Window* window = NULL;

//The surface contained by the window
SDL_Surface* screenSurface = NULL;
//This is the image of our super detailed MIDI Pad Player
SDL_Surface *image = NULL;

//The sound effects that will be used
Mix_Chunk *gsckick1 = NULL;
Mix_Chunk *gscsnr5 = NULL;
Mix_Chunk *scclap35 = NULL;
Mix_Chunk *fhh = NULL;
Mix_Chunk *backRound = NULL;
Mix_Chunk *snap = NULL;
Mix_Chunk *kick10 = NULL;

//The boolean flag to check if the application is running or active,
//we turn this off when we attempt to close the application by setting the value
//to false;
bool isRunning = true;

bool Init()
{
	//This function's job is to Initialize all of the SDL subsystems as well as SDL

	//SDL is initialized
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) //Video an Sound
		std::cout << "Trouble Initializing SDL: " << SDL_GetError() << std::endl;

	//Create window
	window = SDL_CreateWindow("Super Duper High Octane DJ Simulator 2016 | Ultimate Extreme Sound Excellence Edition",
							  SDL_WINDOWPOS_CENTERED,
							  SDL_WINDOWPOS_CENTERED,
							  SCREEN_WIDTH,
							  SCREEN_HEIGHT,
							  SDL_WINDOW_SHOWN);
	//Init the ability to use Png images
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
		std::cout << "Error Initializing, IMG_INIT: " << IMG_GetError() << std::endl;
	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "Error Initializing, Opening Audio: " << Mix_GetError() << std::endl;
	else
		screenSurface = SDL_GetWindowSurface(window);//Apply the screenSurface on the window
	
	// load the MIDI PAD image "Pad.png" into image
	image = IMG_Load("Pad.png");
	if (!image)
		std::cout << "Error loading, IMG_INIT: " << IMG_GetError() << std::endl;

	//Load sound effects
	gsckick1 = Mix_LoadWAV("KS - Sample Kit 1/KS-fkick 1.wav");
	if (gsckick1 == NULL)
		std::cout << "Cannot Load Kick1: " << Mix_GetError() << std::endl;
	gscsnr5 = Mix_LoadWAV("KS - Sample Kit 1/KS-msnare16.wav");
	if (gscsnr5 == NULL)
		std::cout << "Cannot Load Snare1: " << Mix_GetError() << std::endl;
	scclap35 = Mix_LoadWAV("Sounds/6Claps/clap 05.wav");
	if (scclap35 == NULL)
		std::cout << "Cannot Load Clap1: " << Mix_GetError() << std::endl;
	fhh = Mix_LoadWAV("Sounds/25Percs/percussion 01.wav");
	if (fhh == NULL)
		std::cout << "Cannot Load Perc1: " << Mix_GetError() << std::endl;
	snap = Mix_LoadWAV("Sounds/5Snaps/snap 07.wav");
	if (snap == NULL)
		std::cout << "Cannot Load Snap1: " << Mix_GetError() << std::endl;
	backRound = Mix_LoadWAV("Sounds/25Percs/percussion 04.wav");
	if (backRound == NULL)
		std::cout << "Cannot Load BackGround Noise thingy: " << Mix_GetError() << std::endl;
	kick10 = Mix_LoadWAV("Sounds/38Kicks/kick 10.wav");
	if (kick10 == NULL)
		std::cout << "Cannot Load Kick2: " << Mix_GetError() << std::endl;
	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "Failed to Init SDL_MIXER: " << Mix_GetError() << std::endl;
	//Initialize window
	if (window == NULL)
		std::cout << "Erro creating window: " << SDL_GetError() << std::endl;

	return true;
}

void run() //The Loop
{
	//Event handler
	SDL_Event e;

	while (isRunning)//This is the Game Loop
	{
		//Handles Input events
		while (SDL_PollEvent(&e) != 0)
		{
			//The Exit Button Is Hit
			if (e.type == SDL_QUIT)
				isRunning = false;
			//Keyboard Presses
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_p://When P is pressed
					Mix_PlayChannel(-1, gsckick1, 0);
					break;
				case SDLK_o:
					Mix_PlayChannel(-1, gscsnr5, 0);
					break;
				case SDLK_l:
					Mix_PlayChannel(-1, fhh, 0);
					break;
				case SDLK_k:
					Mix_PlayChannel(-1, scclap35, 0);
					break;
				case SDLK_a:
					Mix_PlayChannel(-1, backRound, 0);
					break;
				case SDLK_i:
					Mix_PlayChannel(-1, snap, 0);
					break;
				case SDLK_j:
					Mix_PlayChannel(-1, kick10, 0);
					break;
				default:
					break;
				}
			}
		}

		//Get window surface
		screenSurface = SDL_GetWindowSurface(window);

		//Fill the surface white
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

		//Apply the PNG image
		SDL_BlitSurface(image, NULL, screenSurface, NULL);

		//Update the surface
		SDL_UpdateWindowSurface(window);
	}
}

//Close all of the SDL subsystems loaded
void deallocate()
{
	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	//Freeing all the Sound Chunks
	Mix_FreeChunk(gsckick1);
	Mix_FreeChunk(gscsnr5);
	Mix_FreeChunk(scclap35);
	Mix_FreeChunk(fhh);
	Mix_FreeChunk(backRound);
	Mix_FreeChunk(snap);
	Mix_FreeChunk(kick10);

	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

//We need to have these arguments so that SDL can work on multiple platforms
int main(int argc, char* args[])
{
	//Call Init() to Initialize SDL and all the SDL Subsystems
	if (!Init())
		std::cout << "There was a problem with Initializing SDL" << std::endl;
	else//run the main Loop
		run();

	return 0;
}
