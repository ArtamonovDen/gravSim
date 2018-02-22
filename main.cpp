#include "swarm.h"
#include "particle.h"
#include "Screen.h"

#include "CelestialObject.h"
#include "Space.h"


#include <iostream>

#include <SDL.h>
#include <math.h>
#include<SDL_video.h>

#include <stdlib.h>
#include <time.h>

//# define CHECK(x,text,error_code) if ( x == nullptr){ std::cout << " text error: " << SDL_GetError() << std::endl; SDL_Quit(); return error_code ; }




int main(int argc, char * argv[]){
	srand(time(NULL));

	/*Screen screen;
	if (screen.init() == 0)
		std::cout << "failured init" << std::endl;
*/

	//--------------------

	//CelestialObject(unsigned long int weight, unsigned long int radius,\
	 double x, double y, double ax, double ay, double vx, double vy)
	Space space;
	space.add(1000, 1, 350, 100, 0, 0, 0, 0);

	space.add(100000 ,1, 350, 200, 0,0, 0, 0);

	space.add(1000, 1, 200, 150, 0, 0, 0, 0);

	space.add(1000, 1, 600, 600, 0, 0, 3, 0);
	space.add(100000, 1, 600, 500, 0, 0, -3, 0);

	//space.add(1000, 100, 200, 300, 0, 0, 2, 3);

	space.loop();





	//Swarm swarmA;
	//
	//int r = 0;
	//while (1){

	//	int elapsed = SDL_GetTicks();
	//	int green = (1 + sin(elapsed*0.001)) * 128;
	//	int red = (1 + sin(elapsed*0.002)) * 128;
	//	int blue = (1 + sin(elapsed*0.003)) * 128;

	//	

	//	const particle * const pParticle = swarmA.getParticles();
	//	for (int i = 0; i < Swarm::NPARTICLES; i++){
	//		particle prtcl = pParticle[i];

	//		int x = (prtcl.m_x + 1)* Screen::SCREEN_WIDTH/2;
	//		int y = (prtcl.m_y + 1)* Screen::SCREEN_HEIGHT/2;

	//		screen.setPixel(x, y, red, green, blue);
	//		
	//	}
	//	/*int elapsed =SDL_GetTicks();
	//	int green = (1+ sin(elapsed*0.001)) * 128;
	//	int red= (1 + sin(elapsed*0.002)) * 128;
	//	int blue = (1 + sin(elapsed*0.003)) * 128;

	//	std::cout << green << " ";
	//	for (int y = 0; y < screen.SCREEN_HEIGHT; y++){
	//		for (int x = 0; x < screen.SCREEN_WIDTH; x++){
	//			screen.setPixel(x, y, red, green, blue);
	//			
	//		}			
	//	}*/


	//	screen.update();

	//	if (screen.processEvents() == 0){
	//		break;
	//	}
	//}



	


	return EXIT_SUCCESS;


}