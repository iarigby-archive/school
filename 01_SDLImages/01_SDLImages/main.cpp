
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

void exitProgram()
{
	SDL_Quit();

	std::cout << "Press any key to continue..." << std::endl;
	std::cin.get();
}

int main( int argc, char* args[] )
{
	atexit( exitProgram );

	//
	// 1. step: ininitalize SDL
	//

	// initialize the graphical subsystem only
	if ( SDL_Init( SDL_INIT_VIDEO ) == -1 )
	{
		// if it fails, signal error and exit
		std::cout << "[SDL_Init]: " << SDL_GetError() << std::endl;
		return 1;
	}
			
	//
	// 2. step: create a window we can draw to
	//

	SDL_Window *win = 0;
    win = SDL_CreateWindow( "Hello SDL!",				// caption of the window
							100,						// the initial X coordinate of the window
							100,						// the initial Y coordinate of the window
							640,						// width of the window's client area
							480,						// height of the window's client area
							SDL_WINDOW_SHOWN);			// display properties

	// should the window creation fail, notify the user
    if (win == 0)
	{
		std::cout << "[SDL_CreateWindow]: " << SDL_GetError() << std::endl;
        return 1;
    }

	//
	// 3. step: create a renderer
	//

    SDL_Renderer *ren = 0;
    ren = SDL_CreateRenderer(	win, // pointer to the window onto which the renderer should draw
								-1,  // the index of the renderer, if -1: the first renderer fitting our needs specified in the last parameter of this function call
									 // a -1 a harmadik paraméterben meghatározott igényeinknek megfelelõ elsõ renderelõt jelenti
								SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);	// we want a HW accelerated, vsync-ed renderer
    if (ren == 0)
	{
        std::cout << "[SDL_CreateRenderer]: " << SDL_GetError() << std::endl;
        return 1;
    }

	//
	// 3. step: load the image file
	//
	SDL_Texture* tex = IMG_LoadTexture( ren, "kep.png" );
	if ( tex == 0 )
	{
        std::cout << "[IMG_LoadTexture]: " << IMG_GetError() << std::endl;
        return 1;
	}


	//
	// 4. step: start the main loop
	// 

	// do we have to quit?
	bool quit = false;
	// the message of the OS
	SDL_Event ev;
	// the X and Y coordinates of the mouse
	Sint32 mouseX = 0, mouseY = 0;



	int image_x = 0;
	int image_y = 0;

	while (!quit)
	{
		// process all pending messages in the application message queue
		while ( SDL_PollEvent(&ev) )
		{
			switch (ev.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				if ( ev.key.keysym.sym == SDLK_ESCAPE )
					quit = true;
				break;
			case SDL_MOUSEMOTION:
				mouseX = ev.motion.x;
				mouseY = ev.motion.y;
				break;
			case SDL_MOUSEBUTTONUP:
				// mouse messages: SDL_BUTTON_LEFT, SDL_BUTTON_MIDDLE, 
				//		SDL_BUTTON_RIGHT, SDL_BUTTON_WHEELUP, SDL_BUTTON_WHEELDOWN
				break;
			}
		}

		// clear the background with white
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderClear(ren);


		// draw the image centered at the mouse cursor
		SDL_Rect cursor_rect;
		SDL_QueryTexture( tex, 0, 0, &cursor_rect.w, &cursor_rect.h );
		
		cursor_rect.x = image_x;
		cursor_rect.y = image_y;

		SDL_RenderCopy( ren,				// which renderer to use
						tex,				// which texture to draw
						0,					// source rect (which part of the texture to draw)
						&cursor_rect );		// target rect

		// display the contents of the backbuffer
		SDL_RenderPresent(ren);
	}



	//
	// 4. step: clean up
	// 

	SDL_DestroyTexture( tex );
	SDL_DestroyRenderer( ren );
	SDL_DestroyWindow( win );

	return 0;
}
