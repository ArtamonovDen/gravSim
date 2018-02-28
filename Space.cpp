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
	//std::cout << "pos: " << A->x << " " << A->y << "v: " << A->vx << " " << A->vy << "a: " << A->ax << " " << A->ay << std::endl;	
	
	/*i = -1*r;
	for ( i; i < r + 1; i++){
		int j = -1*r;
		for ( j; j < r + 1; j++){
			if (i*i + j*j <= r*r )
				spaceScreen.setPixel(A->x+i, A->y+j, 255, 255, 0);
		}
	}*/
	spaceScreen.drawCircle(A->x, A->y, A->radius, 255, 255, 0);
	
	//spaceScreen.setPixel(A->x, A->y,255,255,255);

}

void Space::merge(CelestialObject*A, CelestialObject* B){
	//CHECK MASS AND RADIUS  RATIO!
	//merge A and B. Add B to A
	
	//calculate the momentum
	double M = (A->weight + B->weight);
	double Vx = ((A->weight * A->vx) + (B->weight * B->vx)) / M;
	double Vy = ((A->weight * A->vy) + (B->weight * B->vy)) / M;
	M *= 0.6;

	

	A->weight = M;
	A->ax = 0;
	A->ay = 0;
	A->vx = Vx;
	A->vy = Vy;
	
	
	if (A->radius >= B->radius){
		A->radius += B->radius*0.4;
	}
	else {
		A->radius = B->radius + A->radius*0.4;
	}

	//Megre to A

	//RADIUS!
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
				double a = (G * (*j)->weight) / (r*r) ;

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
				a = 0.1*( (*i)->weight) / (r*r) ;
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
	while (flag){

		somethingHappening();
		spaceScreen.update();
		//function for updating buffer// and there will be spec function for drawing objects
		
		//update for all?



		//int elapsed = SDL_GetTicks();
		//int green = (1 + sin(elapsed*0.001)) * 128;
		//int red = (1 + sin(elapsed*0.002)) * 128;
		//int blue = (1 + sin(elapsed*0.003)) * 128;

		//

		//const particle * const pParticle = swarmA.getParticles();
		//for (int i = 0; i < Swarm::NPARTICLES; i++){
		//	particle prtcl = pParticle[i];

		//	int x = (prtcl.m_x + 1)* Screen::SCREEN_WIDTH/2;
		//	int y = (prtcl.m_y + 1)* Screen::SCREEN_HEIGHT/2;

		//	spaceScreen.setPixel(x, y, red, green, blue);
		//	
		//}
		///*int elapsed =SDL_GetTicks();
		//int green = (1+ sin(elapsed*0.001)) * 128;
		//int red= (1 + sin(elapsed*0.002)) * 128;
		//int blue = (1 + sin(elapsed*0.003)) * 128;

		//std::cout << green << " ";
		//for (int y = 0; y < screen.SCREEN_HEIGHT; y++){
		//	for (int x = 0; x < screen.SCREEN_WIDTH; x++){
		//		screen.setPixel(x, y, red, green, blue);
		//		
		//	}			
		//}*/


		//spaceScreen.update();

		/*if (spaceScreen.processEvents() == 0){
			break;
		}*/
		while (SDL_PollEvent(&event)){
			if (event.type == SDL_MOUSEBUTTONDOWN ){
				std::cout << "New Object" << std::endl;
				int x = event.button.x;
				int y = event.button.y;
				createByButton(900, x, y, 0, 0, 0, 0);
			}

			if (event.type == SDL_QUIT){
				std::cout << "Quit ";
				flag = 0;
				break;
			}
		}
		
		
	}
}
		


	/*static int i = 0;
	SDL_Event event;*/
	//While(SDL_PollEvent(&event)){
	//	/*if (event.type == SDL_){
	//	return 2;
	//	}*/

	//	if (event.type == SDL_QUIT){
	//		return 0;
	//	}
	//	/*	if (event.type == SDL_KEYDOWN){

	//	std::cout << "KD ";
	//	return 0;
	//	}*/
	//	//if (event.type == SDL_MOUSEMOTION){
	//	//	std::cout << "KD ";
	//	//	for (int j = 0; j < 100; j++, i++){
	//	//		if (i<SCREEN_HEIGHT*SCREEN_WIDTH)
	//	//			m_buffer[i] = 0xFF0000FF;
	//	//	}
	//	//	//std::cout << "KD ";

	//	//}

	//	update();
	//}