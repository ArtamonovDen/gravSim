#include "Space.h"
#include "particle.h"
#include "swarm.h"

#include <SDL.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
Space::Space()
{

}


Space::~Space()
{
	for (auto &i : objects){
		delete i;
	}
}

void Space::createByButton(unsigned long int weight, int x, int y, double ax, double ay, double vx, double vy){
	add(weight, weight / 300 + 2, x, y, ax, ay, vx, vy);
	std::cout << "New object created: " << x << ", " << y << std::endl;

}


void Space::add(unsigned long int weight, unsigned long int radius, double x, double y, double ax, double ay, double vx, double vy){
	CelestialObject* newObj = new CelestialObject( weight,  radius,  x,  y,  ax,  ay,  vx,  vy);
	objects.push_back(newObj);
}

void Space::add(int N){

	for (int i = 0; i < N; i++){
		CelestialObject* newObj = new CelestialObject;
		newObj->x = rand() % Screen::SCREEN_WIDTH;
		newObj->y = rand() % Screen::SCREEN_WIDTH;
		objects.push_back(newObj);
	
	}
}

double Space::getDistance(CelestialObject* A, CelestialObject* B){
	return sqrt(pow((A->x - B->x), 2) + pow((A->y - B->y), 2));

}

bool Space::is_collapse(CelestialObject* A, CelestialObject* B, double r){

	return  (r <= (A->radius + B->radius));
}


void Space::udpateObject(CelestialObject* A){

	spaceScreen.drawCircle(A->x, A->y, A->radius, 0, 0, 0);

	A->vx += A->ax * dt;
	A->vy += A->ay * dt;

	A->x += A->vx*dt;
	A->y += A->vy*dt;

	//spaceScreen.drawCircle(A->x, A->y, A->radius, 255, 255, 0);
	spaceScreen.drawCircle(A->x, A->y, A->radius, A->red, A->green, A->blue);

}

void Space::merge(CelestialObject*A, CelestialObject* B){
	//CHECK RADIUS  RATIO!
	//merge A and B. Add B to A
	
	//calculate the momentum
	double M = (A->weight + B->weight);
	double Vx = ((A->weight * A->vx) + (B->weight * B->vx)) /(100* M);
	double Vy = ((A->weight * A->vy) + (B->weight * B->vy)) /(100* M);
	M *= 0.6;

	A->weight = M;
	A->ax = 0;
	A->ay = 0;
	A->vx = Vx;
	A->vy = Vy;	
	
	if (A->radius >= B->radius){
		A->radius += B->radius*0.4;
	}
	else {//"replace" A and B
		std::swap(A->x, B->x);
		std::swap(A->y, B->y);
		A->radius = B->radius + A->radius*0.4;
	}

}


void Space::somethingHappening(){

	std::vector<CelestialObject*>::iterator i = objects.begin();
	for (i; i != objects.end();){
		std::vector<CelestialObject*>::iterator j = i + 1;
		for (j; j != objects.end();){

			double r = getDistance(*i, *j);

			if (!is_collapse(*i, *j, r)){
				//compute alpha (between r-line and OX)
				double sinAlpha = abs((*i)->y - (*j)->y) / r;
				double cosAlpha = abs((*i)->x - (*j)->x) / r;

				int sign_ax = 1, sign_ay = 1;
				//FOR I
				double a = (G* (*j)->weight) / (r*r) ;

				if ((*i)->x < (*j)->x)
					sign_ax = 1;
				else
					sign_ax = -1;

				if ((*i)->y < (*j)->y)
					sign_ay = 1;
				else sign_ay = -1;

				double ax = sign_ax*a*cosAlpha;
				double ay = sign_ay*a*sinAlpha;

				(*i)->ax += ax;
				(*i)->ay += ay;


				//FOR J
				a = (G* (*i)->weight) / (r*r) ;
				sign_ax *= -1;
				sign_ay *= -1;
				 ax = sign_ax*a*cosAlpha;
				 ay = sign_ay*a*sinAlpha;

				(*j)->ax += ax;
				(*j)->ay += ay;

				++j;
			}
			else{
				//drop j and add everything to i -> merge()
				merge(*i, *j);
				spaceScreen.drawCircle((*j)->x, (*j)->y, (*j)->radius, 0, 0, 0);
				CelestialObject* temp_j;
				temp_j = (*j);
				j = objects.erase(j);
				delete temp_j;
			}	
		}
		++i;
	}


	for (auto& r : objects)
		udpateObject(r);		
	
}


void Space::loop(){

	srand(time(NULL));

	if (spaceScreen.init() == 0)
		std::cout << "failured init" << std::endl;


	//--------------------


	Swarm swarmA;
	SDL_Event  event;

	int flag = 1;
	int mouse_button_left = 0;//0-not clicked/ 1 - clicked
	int x = 0, y = 0;
	int _vx = 0, _vy = 0;
	while (flag){
		

		somethingHappening();
		spaceScreen.update();

		//EVENTS HENDLA
		if (SDL_PollEvent(&event)){

			switch (event.type)
			{
			

			case (SDL_MOUSEBUTTONDOWN) :
				if (event.button.button == SDL_BUTTON_LEFT){
					//std::cout << "New Object" << std::endl;
					x = event.button.x;
					y = event.button.y;
					//createByButton(900, x, y, 0, 0, 0, 0);
					spaceScreen.setPixel(x, y, 255, 255, 255);
					mouse_button_left = 1;
				}
				break;
			
			case(SDL_MOUSEBUTTONUP) :
				mouse_button_left = 0; 
				 std::cout << event.button.x << " " << event.button.y << std::endl;
				 _vx = -0.1*(event.button.x - x);
				  _vy = -0.1*(event.button.y - y);
				 createByButton(900, x, y,0,0, _vx, _vy);
				
				break;

			//case(SDL_MOUSEMOTION) :
			//	if (mouse_button_left == 1)
			//	{
			//		/*int x = event.motion.x;
			//		int y = event.motion.x;
			//		std::cout << x << ' ' << y << std::endl;*/
			//	}
			//		//std::cout << "sss" << std::endl;
			//		

			//	break;


			case(SDL_KEYDOWN):
				switch (event.key.keysym.sym)
				{
				case(SDLK_ESCAPE) :
					std::cout << "Quit ";
					flag = 0;
					break;
				case(SDLK_i) :
					std::cout << "The number of objects: " << objects.size() << std::endl;
					break;
				default:
					break;
				}
				break;



			case(SDL_QUIT) :
				std::cout << "Quit ";
				flag = 0;
				break;
			
			default:
				break;
			}
			
			//if (event.type == SDL_MOUSEBUTTONDOWN ){
			//	if (event.button.button == SDL_BUTTON_LEFT){
			//		//std::cout << "New Object" << std::endl;
			//		int x = event.button.x;
			//		int y = event.button.y;
			//		createByButton(900, x, y, 0, 0, 0, 0);
			//	} 			
			//	
			//}
			//if (event.type == SDL_MOUSEBUTTONUP){
			//	if (event.button.clicks == 2){
			//		std::cout << "sss" << std::endl;
			//	}
			//}

			//if (event.type == SDL_QUIT){
			//	std::cout << "Quit ";
			//	flag = 0;
			//	break;
			//}
		}
		
		
	}
}