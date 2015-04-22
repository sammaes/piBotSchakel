#include "Hoek.h"

using namespace std;

// Destructor
Hoek::~Hoek() {
}

// constructor
Hoek::Hoek() {
	setAngle(0);
	setSpeed(0);
	setDirection('l');
	setAfstand(0);
}

void Hoek::BepaalHoek(int Xr, int Yr, int Xb, int Yb, int Beta) // Dit krijgen we binnen
{
	int Aanliggende = 0;
	int Overstaande = 0;
	int Verschil = 0;
	int Alpha = 0;
	int Hoek = 0;
	char richting = 'l';

	Aanliggende = Xr - Xb;
	Overstaande = Yr - Yb;

    cout<<"Hoek:\t Hoek bepalen:"<<endl;
    cout<<"Hoek:\t Aanliggende = "<<Aanliggende<<endl;
	cout<<"Hoek:\t Overstaande = "<<Overstaande<<endl;

	// Hoek alpha bepalen
	Alpha = round(((atan((float)Overstaande/(float)Aanliggende) * 180) / PI));

    if(Aanliggende > 0)
    {
        Alpha += 180;
    }
    else if((Aanliggende < 0) && (Overstaande > 0))
    {
        Alpha += 360;
    }
    cout<<"Berekende hoek = "<<Alpha<<endl;

    Verschil = Beta - Alpha;
    cout<<"Verschil = "<<Verschil<<endl;

    if (Verschil < 0)
    {
        richting = 'l';
    }
    else
    {
        richting = 'r';
    }

    Verschil = abs(Verschil);

    if (Verschil > 180) // De positieve hoek nemen
    {
		Verschil = 360 - Verschil;
		if (richting == 'l')
		{
		    richting = 'r';
		}
		else
		{
		    richting = 'l';
		}
	}
	Hoek = abs(Verschil);
	setAngle(Hoek);
    setDirection(richting);

	#ifdef DEBUGHOEK
		cout<<"Hoek:\t Alpha = "<<Alpha<<endl;
		cout<<"Hoek:\t Kwadrant Alpha = "<<KwadrantA<<endl;
	#endif // DEBUGHOEK

	if ( (abs(Verschil) <= TRESLOW) || (abs(Verschil) >= (360-TRESLOW)) ) {
		#ifdef DEBUGHOEK
			cout<<"Hoek:\t Hoek gelijk, stoppen"<<endl;
		#endif //DEBUGHOEK
		setAngle(0);
	}
}

void Hoek::BepaalAfstand(int Xr, int Yr, int Xb, int Yb) {
	float Aanliggende = 0;
	float Overstaande = 0;

	Aanliggende = abs(Xr - Xb);
	Overstaande = abs(Yr - Yb);

	#ifdef DEBUGHOEK
		cout<<"Hoek:\t Afstand bepalen:"<<endl;
		cout<<"Hoek:\t Aanliggende = "<<Aanliggende<<endl;
		cout<<"Hoek:\t Overstaande = "<<Overstaande<<endl;
	#endif //DEBUGHOEK

	setAfstand(sqrt((Aanliggende * Aanliggende) + (Overstaande * Overstaande)));
	#ifdef DEBUGHOEK
		cout<<"Hoek:\t Afstand = "<<getAfstand()<<endl;
	#endif //DEBUGHOEK

}

// TODO: Wordt dit nog gebruikt?
void Hoek::BepaalSnelheid() {
	#ifdef DEBUGHOEK
		cout<<"Hoek:\t Afstand = "<<getAfstand()<<endl;
	#endif //DEBUGHOEK
	if (getAfstand() <= 40) {
		#ifdef DEBUGHOEK
			cout<<"Hoek:\t Stoppen"<<endl;
		#endif //DEBUGHOEK
		setSpeed(0);
	} else {
		if (getAfstand() >= 140) {
			#ifdef DEBUGHOEK
				cout<<"Hoek:\t Snelheid = 2"<<endl; //snel rijden
			#endif //DEBUGHOEK
			setSpeed (MAXSPEED);
		} else {
			#ifdef DEBUGHOEK
				cout<<"Hoek:\t Snelheid = 1"<<endl; //trager rijden
			#endif //DEBUGHOEK
			setSpeed (MINSPEED);
		}
	}
}

int Hoek::getAngle() {
	return i_Angle;
}

char Hoek::getDirection() {
	return c_Direction;
}

int Hoek::getSpeed() {
	return i_Speed;
}

int Hoek::getAfstand() {
	return i_Distance;
}

void Hoek::setAngle(int i_hoek) {
	i_Angle = i_hoek;
}

void Hoek::setDirection(char c_richting) {
	c_Direction = c_richting;
}

void Hoek::setSpeed(int i_snelheid) {
	i_Speed = i_snelheid;
}

void Hoek::setAfstand(int i_Afstand) {
	i_Distance = i_Afstand;
}

