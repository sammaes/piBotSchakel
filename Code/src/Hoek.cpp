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

void Hoek::BepaalHoek(int Xr,int Yr,int Xb,int Yb,int Beta)
{
	this->BepaalHoek(Xr,Yr,0,0,Xb,Yb,Beta);
}

void Hoek::BepaalHoek(int Rx, int Ry, int Ox, int Oy, int Bx, int By, int Beta) // Dit krijgen we binnen
{
	int AanliggendeRB = 0;
	int OverstaandeRB = 0;
	int AanliggendeRO1 = 0;
	int OverstaandeRO1 = 0;
	int AanliggendeRO2 = 0;
	int OverstaandeRO2 = 0;
	int Verschil = 0;
	int Alpha = 0;
	int Alpha1 = 0;
	int Alpha2 = 0;
	int Hoek = 0;
	char richting = 'l';
	int TH = 80; // Straal cirkel

    // Voor robot
	AanliggendeRB = Rx - Bx;
	OverstaandeRB = Ry - By;

    cout<<"Hoek:\t Hoek bepalen tussen x-as en blik:"<<endl;
    cout<<"Hoek:\t Aanliggende = "<<AanliggendeRB<<endl;
	cout<<"Hoek:\t Overstaande = "<<OverstaandeRB<<endl;

	// Hoek alpha bepalen
	Alpha = round(((atan((float)OverstaandeRB/(float)AanliggendeRB) * 180) / PI));

    if(AanliggendeRB > 0)
    {
        Alpha += 180;
    }
    else if((AanliggendeRB < 0) && (OverstaandeRB > 0))
    {
        Alpha += 360;
    }
    cout<<"Berekende hoek Alpha = "<<Alpha<<endl; // Hoek blikje tov oorsprong

    //================================================================================================
    // Voor obstakel - punt 1

    if(((Alpha >= 45) && (Alpha < 135)) || ((Alpha >= 225) && (Alpha < 315)))
    {
        AanliggendeRO1 = Rx - (Ox + TH);
        OverstaandeRO1 = Ry - Oy;
    }
    else
    {
        AanliggendeRO1 = Rx - Ox;
        OverstaandeRO1 = Ry - (Oy + TH);
    }

    cout<<"Hoek:\t Kleine hoek voor botsing bepalen:"<<endl;
    cout<<"Hoek:\t Aanliggende = "<<AanliggendeRO1<<endl;
	cout<<"Hoek:\t Overstaande = "<<OverstaandeRO1<<endl;

	// Hoek alpha bepalen
	Alpha1 = round(((atan((float)OverstaandeRO1/(float)AanliggendeRO1) * 180) / PI));

    if(AanliggendeRO1 > 0)
    {
        Alpha1 += 180;
    }
    else if((AanliggendeRO1 < 0) && (OverstaandeRO1 > 0))
    {
        Alpha1 += 360;
    }
    cout<<"Berekende hoek Alpha 1= "<<Alpha1<<endl; // Hoek punt 1 obstakel

    //================================================================================================
    // Voor obstakel - punt 2
    if(((Alpha >= 45) && (Alpha < 135)) || ((Alpha >= 225) && (Alpha < 315)))
    {
        AanliggendeRO2 = Rx - (Ox - TH);
        OverstaandeRO2 = Ry - Oy;
    }
    else
    {
        AanliggendeRO2 = Rx - Ox;
        OverstaandeRO2 = Ry - (Oy - TH);
    }

    cout<<"Hoek:\t Grote hoek voor botsing bepalen:"<<endl;
    cout<<"Hoek:\t Aanliggende = "<<AanliggendeRO2<<endl;
	cout<<"Hoek:\t Overstaande = "<<OverstaandeRO2<<endl;

	// Hoek alpha bepalen
	Alpha2 = round(((atan((float)OverstaandeRO2/(float)AanliggendeRO2) * 180) / PI));

    if(AanliggendeRO2 > 0)
    {
        Alpha2 += 180;
    }
    else if((AanliggendeRO2 < 0) && (OverstaandeRO2 > 0))
    {
        Alpha2 += 360;
    }
    cout<<"Berekende hoek Alpha 2 = "<<Alpha2<<endl; // Hoek punt 2 obstakel

    //================================================================================================
    // Checken of we botsing hebben

    if((Alpha < Alpha1) && (Alpha > Alpha2))
    {
        cout<<"Botsing!"<<endl;
        if(Beta > Alpha)
        {
            Verschil = ((floor(Alpha1/90) + 1) * 90) - Beta;
            richting = 'l';
            cout<<"Verschil met Alpha 1"<<endl;
            cout<<"Draaien naar:"<<((floor(Alpha1/90) + 1) * 90)<<endl;
        }
        else
        {
            Verschil = ((floor(Alpha1/90) + 1)) - Beta;
            richting = 'r';
            cout<<"Verschil met Alpha 2"<<endl;
            cout<<"Draaien naar:"<<((floor(Alpha1/90) + 1))<<endl;
        }
    }
    else
    {
        Verschil = Beta - Alpha;
        if (Verschil < 0)
        {
            richting = 'l';
        }
        else
        {
            richting = 'r';
        }
    }
    cout<<"Verschil = "<<Verschil<<endl;

    //================================================================================================
    // Richting bepalen

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
	setAngle(Hoek);             // Draaihoek
    setDirection(richting);
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

