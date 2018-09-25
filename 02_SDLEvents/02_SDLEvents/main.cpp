#include <SDL.h>
#include <iostream>

void exitProgram()
{
	std::cout << "Press any key to exit..." << std::endl;
	std::cin.get();
}

int main( int argc, char* args[] )
{
	//
	// 1.: initilize the video subsystem of SDL
	//

	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		std::cout << "[SDL launch]" << SDL_GetError() << std::endl;
		return 1;
	}

	//
	// 2.: create a window with SDL
	//

	SDL_Window *win = 0;	// identifier (!) of the window to be created
	win = SDL_CreateWindow("Hello SDL!",				// caption of the window
		100,						// initial X
		100,						//	   and Y coordinates (wrt. desktop)
		640,						// width
		480,						// height (both in pixels)
		SDL_WINDOW_SHOWN);			// creation flags

	if (win == 0)
	{
		std::cout << "[Window] " << SDL_GetError() << std::endl;
		return 1;
	}

	//
	// 3.: create a renderer for the window. The renderer can be used to draw on the window
	//

	SDL_Renderer *ren = 0; // the identifier of the renderer
	ren = SDL_CreateRenderer(win, // the window onto which the renderer draws
							-1,  // select the first supported renderer that...
							SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);	// ...satisfies these conditions

	if (ren == 0)
	{
		std::cout << "[Renderer]: " << SDL_GetError() << std::endl;
		return 1;
	}

	//
	// 4.: The Loop
	// 

	bool quit = false;
	SDL_Event ev;
	Sint32 mouseX = 0, mouseY = 0;

	bool redColor = true;

	while (!quit)
	{
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
				// buttons: SDL_BUTTON_LEFT, SDL_BUTTON_MIDDLE, 
				//		SDL_BUTTON_RIGHT, SDL_BUTTON_WHEELUP, SDL_BUTTON_WHEELDOWN
				// ev.button.button
				break;
			}
		}

		// clear the screen with white
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		//SDL_RenderClear(ren);

		// draw a green line
		SDL_SetRenderDrawColor(	ren, 0, 255, 0,	 255);	
		SDL_RenderDrawLine(	ren, 0, 0, mouseX, mouseY);
		
		SDL_SetRenderDrawColor(	ren, 255, 0, 0,	 255);	
		// and a red rectangle
		SDL_Rect cursor_rect;
		cursor_rect.x = mouseX - 20/2;
		cursor_rect.y = mouseY - 20/2;
		cursor_rect.w = 20;
		cursor_rect.h = 20;

		SDL_SetRenderDrawColor( ren, 255, 0, 0, 255 );
		SDL_RenderFillRect( ren, &cursor_rect);

		// present the current frame
		SDL_RenderPresent(ren);
	}



	//
	// 5. exit
	// 

	SDL_DestroyRenderer( ren );
	SDL_DestroyWindow( win );

	SDL_Quit();

	return 0;
}
