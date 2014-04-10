/*
 * Stern.cpp
 *
 *  Created on: Mar 9, 2014
 *      Author: nicolasromanluthold
 */

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

#include "stern.h"
//---------------------------------------------------------------------------
Stern::Stern():	m(0){
	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
	pos[0] = 0;
	pos[1] = 0;
	pos[2] = 0;
}
//---------------------------------------------------------------------------
Stern::~Stern() {

}
//---------------------------------------------------------------------------
Stern::Stern(double mass, double *velocity, double *position):	m(mass){
	v[0] = velocity[0];
	v[1] = velocity[1];
	v[2] = velocity[2];
	pos[0] = position[0];
	pos[1] = position[1];
	pos[2] = position[2];
}
//---------------------------------------------------------------------------
Stern::Stern(const Stern & x) :m(x.m){
	v[0] = x.v[0];
	v[1] = x.v[1];
	v[2] = x.v[2];
	pos[0] = x.pos[0];
	pos[1] = x.pos[1];
	pos[2] = x.pos[2];
}
//---------------------------------------------------------------------------
Stern& Stern::operator =(const Stern &x) {
	m = x.m;
	v[0] = x.v[0];
	v[1] = x.v[1];
	v[2] = x.v[2];
	pos[0] = x.pos[0];
	pos[1] = x.pos[1];
	pos[2] = x.pos[2];

	return *this;
}
//---------------------------------------------------------------------------
Stern Stern::run1s(const Stern* haufen, int AnzSt, int stern) {
	double dt = 60.*60.*24.*360.*5. ;	// Zeitschritt 5 Jahre in sek
	double f[] = {0,0,0}; 	// wirkender Kraftvektor
	double G = 6.67e-11;	// Gravitationskonstante
	double Anz ;			// G*m_i*m_j
	double Dist;			// |x_i-x_j|
	double DistPow;			// |x_i-x_j|^2

	for(int i = 0 ; i < AnzSt ; i++){	// einfluss aller Sterne
		if (i != stern) {				// ausser der aktuelle Stern
			Anz = G*m*haufen[i].m;
			Dist = getDistance(&haufen[i].pos[0]);
			DistPow = pow(Dist, 2);

			// Wirkender Kraftvektor ausrechen
			f[0] -= (Anz*(pos[0]-haufen[i].pos[0]))/(DistPow*Dist);
			f[1] -= (Anz*(pos[1]-haufen[i].pos[1]))/(DistPow*Dist);
			f[2] -= (Anz*(pos[2]-haufen[i].pos[2]))/(DistPow*Dist);
		}
	}
	// Neue Position
	pos[0] += dt*v[0];
	pos[1] += dt*v[1];
	pos[2] += dt*v[2];

	// Richtungs- und Geschwindigkeitseinfluss auf den Stern
	v[0] += dt*f[0]/m;
	v[1] += dt*f[1]/m;
	v[2] += dt*f[2]/m;

	return *this;
}
//---------------------------------------------------------------------------
void Stern::getPosition() {
	std::cout << " x:" << std::setw(10) << pos[0] << "  y:" << std::setw(10) << pos[1] << "  z:" << std::setw(10) << pos[2];
}
//---------------------------------------------------------------------------
double Stern::getDistance(const double* x) {
	return sqrt(pow(pos[0]-x[0], 2) + pow(pos[1]-x[1], 2) + pow(pos[2]-x[2], 2));
}
//---------------------------------------------------------------------------
double Stern::getDistance() {
	return sqrt(pow(pos[0], 2) + pow(pos[1], 2) + pow(pos[2], 2));
}
//---------------------------------------------------------------------------
double Stern::getSpeed() const {
	return sqrt(pow(v[0], 2) +pow(v[1], 2) + pow(v[2], 2));
}
//---------------------------------------------------------------------------
double Stern::getEnergy() const {
	return (pow(getSpeed(), 2)* m * 0.5);
}
//---------------------------------------------------------------------------
