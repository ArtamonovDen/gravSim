#include "swarm.h"
#include "particle.h"

#include <iostream>

#include <SDL.h>
#include <math.h>
#include<SDL_video.h>

#include <stdlib.h>
#include <time.h>

//# define CHECK(x,text,error_code) if ( x == nullptr){ std::cout << " text error: " << SDL_GetError() << std::endl; SDL_Quit(); return error_code ; }

class Screen{
public:

	const static int  SCREEN_WIDTH = 800;
	const static int  SCREEN_HEIGHT = 600;
private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Texture * m_texture;
	uint32_t* m_buffer; 
public:
	Screen():
		m_window(nullptr), m_renderer(nullptr), m_buffer(nullptr){}

	int init(){
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
			std::cout << "SDL isn't init! Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
			return 0;
		}

		m_window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (m_window == nullptr)
		{
			std::cout << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return 0;
		}
		//CHECK(window, SDL_CreateWindow, 2);

		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
		if (m_renderer == nullptr)
		{
			std::cout << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return 0;
		}

		//CHECK(renderer, SDL_CreateRender, 3);

		m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888/*1Byte for 1px*/,
			SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
		if (m_texture == nullptr)
		{
			std::cout << "SDL_CreateTexture error: " << SDL_GetError() << std::endl;
			SDL_DestroyRenderer(m_renderer);
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return 0;
		}
		//CHECK(texture, SDL_CreateTesture, 4);

		m_buffer = new uint32_t[SCREEN_WIDTH*SCREEN_HEIGHT];//Buffer to deal with pixels in de window
		//4 Byte for every element
		memset(m_buffer, 0/*255*/, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(uint32_t));//Init every pix with 255 
		//0xFF or 255-white; 0-black

		//-------------------------------------------------
		//m_buffer[30000] = 0xFFFFFFFF; //FF for byte, 4*2
		

		SDL_UpdateTexture(m_texture, nullptr, m_buffer, SCREEN_WIDTH*sizeof(uint32_t));
		SDL_RenderClear(m_renderer);
		SDL_RenderCopy(m_renderer, m_texture, nullptr, nullptr);
		SDL_RenderPresent(m_renderer);
		return 1;
	}

	void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue){

		if ((x < 0) || (x >= SCREEN_WIDTH) || (y < 0) || (y>=SCREEN_HEIGHT))
			return;

		uint32_t color = 0;

		color += red;
		color <<= 8;
		color += green;
		color <<= 8;
		color += blue;
		color <<= 8;
		color += 0xFF;

		m_buffer[(y * SCREEN_WIDTH) + x] = color;
	}

	bool processEvents(){
		static int i = 0;
		SDL_Event event;
		while (SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT){
				return 0;
			}
			//if (event.type == SDL_KEYDOWN){
			//	
			//	std::cout << "KD ";
			//}
			//if (event.type == SDL_MOUSEMOTION){
			//	std::cout << "KD ";
			//	for (int j = 0; j < 100; j++, i++){
			//		if (i<SCREEN_HEIGHT*SCREEN_WIDTH)
			//			m_buffer[i] = 0xFF0000FF;
			//	}
			//	//std::cout << "KD ";

			//}

			update();
		}
		return 1;
	}

	void update(){
		SDL_UpdateTexture(m_texture, nullptr, m_buffer, SCREEN_WIDTH*sizeof(uint32_t));
		SDL_RenderClear(m_renderer);
		SDL_RenderCopy(m_renderer, m_texture, nullptr, nullptr);
		SDL_RenderPresent(m_renderer);
	}

	void close(){

		std::cin.get();
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyTexture(m_texture);
		SDL_DestroyWindow(m_window);
		SDL_Quit();

		delete[] m_buffer;
	}




};


int main(int argc, char * argv[]){

	srand(time(NULL));

	Screen screen;
	if (screen.init() == 0)
		std::cout << "failured init" << std::endl;


	swarm swarmA;
	
	int r = 0;
	while (1){

		int elapsed = SDL_GetTicks();
		int green = (1 + sin(elapsed*0.001)) * 128;
		int red = (1 + sin(elapsed*0.002)) * 128;
		int blue = (1 + sin(elapsed*0.003)) * 128;

		

		const particle * const pParticle = swarmA.getParticles();
		for (int i = 0; i < swarm::NPARTICLES; i++){
			particle prtcl = pParticle[i];

			int x = (prtcl.m_x + 1)* Screen::SCREEN_WIDTH/2;
			int y = (prtcl.m_y + 1)* Screen::SCREEN_HEIGHT/2;

			screen.setPixel(x, y, red, green, blue);
			
		}
		/*int elapsed =SDL_GetTicks();
		int green = (1+ sin(elapsed*0.001)) * 128;
		int red= (1 + sin(elapsed*0.002)) * 128;
		int blue = (1 + sin(elapsed*0.003)) * 128;

		std::cout << green << " ";
		for (int y = 0; y < screen.SCREEN_HEIGHT; y++){
			for (int x = 0; x < screen.SCREEN_WIDTH; x++){
				screen.setPixel(x, y, red, green, blue);
				
			}			
		}*/


		screen.update();

		if (screen.processEvents() == 0){
			break;
		}
	}






	return EXIT_SUCCESS;


}