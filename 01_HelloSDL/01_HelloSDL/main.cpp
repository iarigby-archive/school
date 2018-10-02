#include <SDL.h>
#include <iostream>

void exitProgram()
{
	std::cout << "Press any key to exit..." << std::endl;
	std::cin.get();
}

int main( int argc, char* args[] )
{
	atexit( exitProgram );

	//
	// 1.: initilize the video subsystem of SDL
	//

	if ( SDL_Init( SDL_INIT_VIDEO ) == -1 )
	{
		std::cout << "[SDL launch]" << SDL_GetError() << std::endl;
		return 1;
	}
	
	//
	// 2.: create a window with SDL
	//

	SDL_Window *win = 0;	// identifier (!) of the window to be created
    win = SDL_CreateWindow( "Hello SDL!",				// caption of the window
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
    ren = SDL_CreateRenderer(	win, // the window onto which the renderer draws
								-1,  // select the first supported renderer that...
								SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);	// ...satisfies these conditions

	if (ren == 0)
	{
        std::cout << "[Renderer]: " << SDL_GetError() << std::endl;
        return 1;
    }

	//
	// 4.: draw something
	//
	
	

	// set the current drawcolor ...
	SDL_SetRenderDrawColor(	ren,	// of this renderer
							0,		// red,
							0,		// green,
							0,		// blue,
							255);	// and alpha of the new color (all 1 byte, i.e. in the range of [0,255]
	SDL_RenderClear(ren); // clear the entire client area of the window associated with the renderer 'ren' with the current drawcolor

	SDL_RenderPresent(ren);

	SDL_Delay(2000);
	// change color: SDL_SetRenderDrawColor

	// clear screen: SDL_RenderClear

	// drawing line with: SDL_RenderDrawLine

	// switching buffers: SDL_RenderPresent

	// waiting for n milliseconds: SDL_Delay(n)

	//
	// 5.: Draw a letter H
	//



	//
	// 6.: change the color of the screen every 2 seconds: red then green then blue
	//


	//
	// 7.: cleanup
	// 

	SDL_DestroyRenderer( ren );
	SDL_DestroyWindow( win );

	SDL_Quit();

	return 0;
}
