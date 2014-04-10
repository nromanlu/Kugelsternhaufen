/*
 * Stern.h
 *
 *  Created on: Mar 9, 2014
 *      Author: nicolasromanluthold
 */

#ifndef STERN_H_
#define STERN_H_

class Stern {
public:
	Stern();				// Default-Constructor
	virtual ~Stern();		// Default-Destructor
	Stern(double mass, double *velocity, double *position);		// Constructor
	Stern(const Stern & x);                                     // Copy-Constructor
	Stern & operator= (const Stern & x);                        // "=" Operator
	Stern run1s(const Stern *haufen, int AnzSt, int stern);     // 1 step
    // Getters and Setters --------------------------------------------------------
	void getPosition();
	double getDistance(const double *x);	//gibt Distanz zum Stern x
	double getDistance();					//gibt Distanz zum Koordinaten Ursprung
	double getMass() const {return m;}
	double getCordX() const {return pos[0];}
	double getCordY() const {return pos[1];}
	double getCordZ() const {return pos[2];}
	double getSpeed() const;
	double getSpeedX() const {return v[0];}
	double getSpeedY() const {return v[1];}
	double getSpeedZ() const {return v[2];}
	void setSpeedX(double v) {this->v[0] = v;}
	void setSpeedY(double v) {this->v[1] = v;}
	void setSpeedZ(double v) {this->v[2] = v;}
	double getEnergy() const;

private:
	double m;			// Masse in kg
	double v[3];		// Geschwindigkeit in m/s
	double pos[3];		// Positon in m
};

#endif /* STERN_H_ */
