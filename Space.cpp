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


void Space::add(unsigned long int weight, unsigned long int radius, double x, double y, double ax, double ay, double vx, double vy){
	CelestialObject* newObj = new CelestialObject( weight,  radius,  x,  y,  ax,  ay,  vx,  vy);
	objects.push_back(newObj);
}

double Space::getDistance(CelestialObject* A, CelestialObject* B){
	return sqrt(pow((A->x - B->x), 2) + pow((A->y - B->y), 2));

}

bool Space::is_collapse(CelestialObject* A, CelestialObject* B, double r){

	return  (r <= (A->radius + B->radius));
}


void Space::udpateObject(CelestialObject* A, double sinAlpha, double cosAlpha, double a, int sign_ax, int sign_ay){

	double ax = sign_ax*a*cosAlpha;
	double ay = sign_ay*a*sinAlpha;

	A->ax += ax;
	A->ay += ay;

	A->vx += A->ax * dt;
	A->vy += A->ay * dt;

	A->x += A->vx*dt;
	A->y += A->vy*dt;

	std::cout << "pos: " << A->x << " " << A->y << "v: " << A->vx << " " << A->vy << "a: " << A->ax << " " << A->ay << std::endl;
	spaceScreen.setPixel(A->x, A->y,255,255,255);
}


void Space::somethingHappening(){
	int N = objects.size();

	std::vector<CelestialObject*>::iterator i = objects.begin();
	for (i; i != objects.end();){
		std::vector<CelestialObject*>::iterator j = i+1;
		for (j; j != objects.end();){

			double r = getDistance(*i, *j);

			if (!is_collapse(*i, *j, r)){

				//compute alpha (between r-line and OX)
				double sinAlpha = abs((*i)->y - (*j)->y) / r;
				double cosAlpha = abs((*i)->x - (*j)->x) / r;

				int sign_ax = 1, sign_ay = 1;
				//FOR I
				double a = G * (*j)->weight / r*r;

				if ((*i)->x < (*j)->x)
					sign_ax = 1;
				if ((*i)->y < (*j)->y)
					sign_ay = 1;


				udpateObject(*i, sinAlpha, cosAlpha, a, sign_ax, sign_ay);

				//FOR J
				a = G * (*i)->weight / r*r;
				sign_ax *= -1;
				sign_ay *= -1;
				udpateObject(*j, sinAlpha, cosAlpha, a, sign_ax, sign_ay);

				//t+=dt //maybe for some reasones
				++j;
			}
			else{
				//For now, just destro'em. Fistly j, then break and then i

				//Firstly do it just for j. Means i destroys j
				//CelestialObject* temp_i;
				CelestialObject* temp_j;
				//temp_i = (*i);
				temp_j = (*j);
				j = objects.erase(j);
				delete temp_j;//?

			}
			//Changes in buffer means objects changes  his x,y in buf
			//update()??
			
		}
		++i;
	}

	//for (int i = 0; i < N; i++){
	//	for (int j = i; j < N; j++){

	//		double r = getDistance(objects[i], objects[j]);

	//		if (!is_collapse(objects[i], objects[j], r)){

	//			//compute alpha (between r-line and OX)
	//			double sinAlpha = abs(objects[i]->y - objects[j]->y) / r;
	//			double cosAlpha = abs(objects[i]->x - objects[j]->x) / r;

	//			int sign_ax = 1 , sign_ay = 1;
	//			//FOR I
	//			double a = G * objects[j]->weight / r*r;

	//			if (objects[i]->x < objects[j]->x)
	//				sign_ax = -1;
	//			if (objects[i]->y < objects[j]->y)
	//				sign_ay = -1;


	//			udpateObject(objects[i],  sinAlpha,  cosAlpha,  a, sign_ax, sign_ay);

	//			//FOR J
	//			 a = G * objects[i]->weight / r*r;
	//			 sign_ax *= -1;
	//			 sign_ay *= -1;
	//			 udpateObject(objects[j], sinAlpha, cosAlpha, a, sign_ax, sign_ay);

	//			//t+=dt //maybe for some reasones

	//		}
	//		else{
	//			//For now, just destro'em
	//			//Erase it from vector and field
	//			//obj * temp;
	//			//temp = (*it_creat);
	//			//if ((*it_creat)->marked_f_death)
	//			//	field[temp->getLoc().first][temp->getLoc().second] = nullptr;

	//			//it_creat = creatures.erase(it_creat);
	//			//delete temp;//?

	//		}
	//		






	//	}
	//}



}


void Space::loop(){

	srand(time(NULL));

	if (spaceScreen.init() == 0)
	std::cout << "failured init" << std::endl;
	

	//--------------------
	





	Swarm swarmA;
	
	while (1){

		somethingHappening();
		spaceScreen.update();
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

		if (spaceScreen.processEvents() == 0){
			break;
		}
	}
		
}