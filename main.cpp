/*
 * main.cpp
 *
 *  Changed on: 13.03.2014
 *      Author: Cojones und Flvio (Hauptsächlich Cojones)
 */

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <fstream>
//----------------
#include "stern.h"
//---------------------------------------------------------------------------
#define anzahlSterne 1000 	// anzahl sterne in unser System
int fileCount = -1;			// global um fileerstellung zu erleichtern
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
void initStern(Stern *s);   			// sternenhaufen initialisieren
void simNsteps(Stern *s, int steps);  	// N schritte simulieren
double getAverageRadius(Stern *s);		// TODO
double getAveraveEnergy(Stern *s);
void saveAllStars(Stern *s);
void saveAllRadius(Stern *s);

//=============== Main ======================================================
int main()
{
  char choice = '0';
  int inputValue;
   Stern  *sternhaufen = new Stern[anzahlSterne];
  // Stern sternhaufen[anzahlSterne];   // Sternenhaufen
  initStern(&sternhaufen[0]);

  // Programmmenu
  while(choice != 'q' && choice != 'Q'){
    cout << "================================================================================" << endl;
    cout << "Enter next command (for help 'h'): ";
    cin >> choice;
    cout << endl;

    switch(choice){
    case 'h':     // help menu
      cout << "Print 1 position:                'p' " << endl;
      cout << "Print all position:              'P' " << endl;
      cout << "Simulate 1 step:                 's' " << endl;
      cout << "Simulate n steps:                'S' " << endl;
      cout << "Export 1 star:                   'e' " << endl; 	// -> TODO soll ein fiel generieren mit den Pos der dernen
      cout << "Export all stars:                'E' " << endl;	// -|
      cout << "Export pos.trace of a star:      't' " << endl;	// TODO soll ein file mit den Pos bewegungen eiens sternes ausgeben
      cout << "Get intermediate star radius:    'r' " << endl;	// TODO soll mittlerer abstand aller sternen zum mittelpunkt ausgeben
      cout << "Get all radiuses                 'R' " << endl;
      cout << "Get potential energy of system:  'y' " << endl;	// TODO soll anhand der geschw. und Massen die potentielle energei des haufens ausgeben
      cout << "Exit program:                    'q' " << endl;
      break;

    case 'p':     // 1 possition ausgeben
      cout << "Enter star number: ";
      cin >> inputValue;
      cout << "Star number " << inputValue << " has the coordinates: ";
      sternhaufen[inputValue-1].getPosition();
      cout << endl;
      break;

    case 'P':     // alle possitinen ausgeben
		for(int x=0 ; x<anzahlSterne ; x++){
			cout << "Coordinates of star number " << setw(5) << x+1 << " is: ";
			sternhaufen[x].getPosition();
			cout << endl;

		}
		break;

    case 's':     // simulieren
      simNsteps(&sternhaufen[0], 1);
      break;

    case 'S':
      cout << "Enter numbers of Simulations: ";
      cin >> inputValue;
      simNsteps(&sternhaufen[0], inputValue);
      break;

    case 'e':
    	break;

    case 'E':
    	saveAllStars(&sternhaufen[0]);
    	cout << "Data has been saved" << endl;
      break;

    case 'R':
    	saveAllRadius(&sternhaufen[0]);
    	cout << "Data has been saved" << endl;
      break;

    case 'q':
    case 'Q':
      cout << "Closing program" << endl;
      break;

    default:
      cout << "invalid command" << endl;
      break;
    }
  }
  cout << "Program closed" << endl;
}
//=============== Unterprogramme ============================================
void initStern(Stern *s) {
  double m;
  double v[3];
  double pos[3];
  double gesch = 20;
  double impuls[3] = {0,0,0};
  double buff;

  int ZahlenBereich = 10000;

  for (int i = 1 ; i < anzahlSterne ; i++){
    // Anfangsgeschwindigkeiten
    v[0] = ((rand()%ZahlenBereich)+1)/gesch;
    v[1] = ((rand()%ZahlenBereich)+1)/gesch;
    v[2] = ((rand()%ZahlenBereich)+1)/gesch;

    // Anfangspotitionen
    pos[0] = ((ZahlenBereich/2) - ((rand()%ZahlenBereich)+1))*1e15;
    pos[1] = ((ZahlenBereich/2) - ((rand()%ZahlenBereich)+1))*1e15;
    pos[2] = ((ZahlenBereich/2) - ((rand()%ZahlenBereich)+1))*1e15;

    // Masse des Sternes
    m = ((rand()%100)+50)*1e25;

    // Stern dem "Haufen" zufü[gen
    s[i] = Stern(m, &v[0], &pos[0]);
  }
  // Impuls des Kugelsterns auf 0 setzten
  for (int i = 0 ; i < anzahlSterne ; i++){
	m = s[i].getMass();
	impuls[0] += s[i].getSpeedX() * m;
	impuls[1] += s[i].getSpeedY() * m;
	impuls[2] += s[i].getSpeedZ() * m;
  }

  impuls[0] /= anzahlSterne;
  impuls[1] /= anzahlSterne;
  impuls[2] /= anzahlSterne;

  for (int i = 0 ; i < anzahlSterne ; i++){
	m = s[i].getMass();
	buff = s[i].getSpeedX() - impuls[0]/m;
	s[i].setSpeedX(buff);
	buff = s[i].getSpeedY() - impuls[1]/m;
	s[i].setSpeedY(buff);
	buff = s[i].getSpeedZ() - impuls[2]/m;
	s[i].setSpeedZ(buff);
  }

  // "Schwarzes Loch" -------------------------------------------
  // Anfangsgeschwindigkeiten
  v[0] = 0;
  v[1] = 0;
  v[2] = 0;

  // Anfangspotitionen
  pos[0] = 0;
  pos[1] = 0;
  pos[2] = 0;

  // Masse des Sternes
  m = 1e35;

  // Stern dem "Haufen" zuf�gen
  s[0] = Stern(m, &v[0], &pos[0]);
}
//---------------------------------------------------------------------------
void simNsteps(Stern *s, int steps){
	int prozent = anzahlSterne / 100;
	int progress = 0;
	int starToMonitor = 5;	// choose the Star to trace
	bool h1 = 0;  			// hilfsvariabel
	bool h2 = 0;			// 0 = don't show progress, 1 = show progress
	int h3 = 0;				// Hilfsvariable zum jeden h4'te messung zu protokolieren
	int h4 = 1000;			// ^
	int h5 = 0;				// Hilfsvariable um daten zu öffnen
	int h6 = 10000;			// ^
	char buffer[1024];
	ofstream data;

	for(int j=0 ; j<steps ; j++){
		#pragma omp parallel for num_threads(32) // parallelisierung
		for(int i=1 ; i< anzahlSterne ; i++) {
			// rechnen
			s[i].run1s(s, anzahlSterne, i);

			// prozent anzeige des Fortschritts TODO der "balken" wird erst am schluss angezeigt
			// edit flavio: flush wurde eingefügt
			/* if (h2){
				if(progress == (i/prozent) && h1 == 0){
					switch(progress) {
					case 0:   cout << "--" << flush;  break;
					case 5:   cout << "--" << flush;  break;
					case 10:  cout << "--" << flush;  break;
					case 15:  cout << "--" << flush;  break;
					case 20:  cout << "--" << flush;  break;
					case 25:  cout << "--" << flush;  break;
					case 30:  cout << "--" << flush;  break;
					case 35:  cout << "--" << flush;  break;
					case 40:  cout << "--" << flush;  break;
					case 45:  cout << "--" << flush;  break;
					case 50:  cout << "50%" << flush; break;
					case 55:  cout << "--" << flush;  break;
					case 60:  cout << "--" << flush;  break;
					case 65:  cout << "--" << flush;  break;
					case 70:  cout << "--" << flush;  break;
					case 75:  cout << "--" << flush;  break;
					case 80:  cout << "--" << flush;  break;
					case 85:  cout << "--" << flush;  break;
					case 90:  cout << "--" << flush;  break;
					case 95:  cout << "--" << flush;  break;
					case 99:  cout << "--" << endl << flush; break;
					default:  break;
					}
					h1 = 1;
				}else{
					if(progress != (i/prozent)){
						progress = i/prozent;
						h1 = 0;
					}
				}
			}*/
		}

		if (h5 == 0){
			fileCount++;
			snprintf(buffer, sizeof(buffer), "Data%09d.csv", fileCount);

			data.open(buffer);
			data << "x,y,z,r,e" << endl;
		}

		if (h3 == (h4-1)){
			// consolen feedback
			cout << "Round number " << j+1 << endl;
			// write Possition into Data.csv
			data << s[starToMonitor].getCordX() << "," << s[starToMonitor].getCordY() << "," << s[starToMonitor].getCordZ() << ",";
			data << getAverageRadius(s) << ",";
			data << getAveraveEnergy(s) << endl;
			h3 = 0;
		}else{
			h3++;
		}

		if (h5 == (h6-1)){
			data.close();	// close Document Data*.csv
			h5 = 0;

			// Daten Speichern Radius und Positionen von allen
			saveAllRadius(s);
			saveAllStars(s);
		}else{
			h5++;
		}
	}
	if (h5 != 0){
		data.close();	// close Document Data*.csv

		// Daten Speichern Radius und Positionen von allen
		saveAllRadius(s);
		saveAllStars(s);
	}
	cout << "Simulation for " << steps << " round/s finished" << endl;
}
//---------------------------------------------------------------------------
double getAverageRadius(Stern* s) {
	double radius = 0;

	for(int i=0 ; i<anzahlSterne ; i++){
		radius += s[i].getDistance();
	}
	return radius/anzahlSterne;
}
//---------------------------------------------------------------------------
double getAveraveEnergy(Stern* s) {
	double energy = 0;

	for(int i=0 ; i<anzahlSterne ; i++){
		energy += s[i].getEnergy();
	}
	return energy/anzahlSterne;
}
//---------------------------------------------------------------------------

void saveAllStars(Stern* s) {
	char buffer[1024];
	snprintf(buffer, sizeof(buffer), "Pos%09d.csv", fileCount);

	ofstream data;
	data.open(buffer);
	data << "x,y,z" << endl;

	for(int x=0 ; x<anzahlSterne ; x++){
		data << s[x].getCordX() << "," << s[x].getCordY() << "," << s[x].getCordZ() << endl;
	}
	data.close();
}


//---------------------------------------------------------------------------
void saveAllRadius(Stern* s) {
	char buffer[1024];
	snprintf(buffer, sizeof(buffer), "Rad%09d.csv", fileCount);

	ofstream data;
	data.open(buffer);
	data << "r" << endl;

	double radius;
	for(int x=0 ; x<anzahlSterne ; x++){
		radius = s[x].getDistance();
		if (radius <= 1e30)	{data << radius << endl;}
	}
	data.close();
}
//---------------------------------------------------------------------------
