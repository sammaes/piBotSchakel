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
	int XCoordRO1 = 0;
	int YCoordRO1 = 0;
	int XCoordRO2 = 0;
	int YCoordRO2 = 0;
	int Verschil = 0;
	int Alpha = 0;
	int Alpha1 = 0;
	int Alpha2 = 0;
	int VerschilAlpha = 0;
	int Hoek = 0;
	int Verschil1 = 0;
	int Verschil2 = 0;
	float SinusHoek = 0;
	float CosHoek = 0;
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

	cout<<"Kleine Alpha = "<<Alpha<<endl; // Hoek blikje tov oorsprong

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
    // Coordinaten bepalen van de raaklijnen

    VerschilAlpha = abs(Alpha)%90;

    cout<<"Modulus Alpha = "<<VerschilAlpha<<endl;

    cout<<"X Object = "<<Ox<<endl;
	cout<<"Y Object = "<<Oy<<endl;

	if(VerschilAlpha <= 45)
	{
	    SinusHoek   = sin(((VerschilAlpha*PI)/180));
        CosHoek     = cos(((VerschilAlpha*PI)/180));
	}
    else
    {
        SinusHoek   = sin((((90-VerschilAlpha)*PI)/180));
        CosHoek     = cos((((90-VerschilAlpha)*PI)/180));
    }


    cout<<"Sin Hoek = "<<SinusHoek<<endl;
    cout<<"Cos Hoek = "<<CosHoek<<endl;

    Verschil1 = abs(round(TH*SinusHoek));
    Verschil2 = abs(round(TH*CosHoek));

    cout<<"Verschil 1 = "<<Verschil1<<endl;
    cout<<"Verschil 2 = "<<Verschil2<<endl;

    if(Alpha <= 45)
    {
        XCoordRO1 = Ox + Verschil1;
        YCoordRO1 = Oy - Verschil2;
        XCoordRO2 = Ox - Verschil1;
        YCoordRO2 = Oy + Verschil2;
    }
    else if(Alpha <= 90)
    {
        XCoordRO1 = Ox + Verschil2;
        YCoordRO1 = Oy - Verschil1;
        XCoordRO2 = Ox - Verschil2;
        YCoordRO2 = Oy + Verschil1;
    }
    else if(Alpha <= 135)
    {
        XCoordRO1 = Ox + Verschil2;
        YCoordRO1 = Oy + Verschil1;
        XCoordRO2 = Ox - Verschil2;
        YCoordRO2 = Oy - Verschil1;
    }
    else if(Alpha <= 180)
    {
        XCoordRO1 = Ox + Verschil1;
        YCoordRO1 = Oy + Verschil2;
        XCoordRO2 = Ox - Verschil1;
        YCoordRO2 = Oy - Verschil2;
    }
    else if(Alpha <= 225)
    {
        XCoordRO1 = Ox - Verschil1;
        YCoordRO1 = Oy + Verschil2;
        XCoordRO2 = Ox + Verschil1;
        YCoordRO2 = Oy - Verschil2;
    }
    else if(Alpha <= 270)
    {
        XCoordRO1 = Ox - Verschil2;
        YCoordRO1 = Oy + Verschil1;
        XCoordRO2 = Ox + Verschil2;
        YCoordRO2 = Oy - Verschil1;
    }
    else if(Alpha <= 315)
    {
        XCoordRO1 = Ox - Verschil2;
        YCoordRO1 = Oy - Verschil1;
        XCoordRO2 = Ox + Verschil2;
        YCoordRO2 = Oy + Verschil1;
    }
    else
    {
        XCoordRO1 = Ox + Verschil1;
        YCoordRO1 = Oy + Verschil2;
        XCoordRO2 = Ox - Verschil1;
        YCoordRO2 = Oy - Verschil2;
    }

    //================================================================================================
    // Voor obstakel - punt 1

    cout<<"Hoek:\t Kleine hoek voor botsing bepalen:"<<endl;
    cout<<"Hoek:\t XCoord = "<<XCoordRO1<<endl;
	cout<<"Hoek:\t YCoord = "<<YCoordRO1<<endl;

	AanliggendeRO1 = Rx - XCoordRO1;
	OverstaandeRO1 = Ry - YCoordRO1;

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
    cout<<"Hoek:\t Aanliggende 1= "<<AanliggendeRO1<<endl;
	cout<<"Hoek:\t Overstaande 1= "<<OverstaandeRO1<<endl;

    //================================================================================================
    // Voor obstakel - punt 2

    cout<<"Hoek:\t Grote hoek voor botsing bepalen:"<<endl;
    cout<<"Hoek:\t XCoord = "<<XCoordRO2<<endl;
	cout<<"Hoek:\t YCoord = "<<YCoordRO2<<endl;

	AanliggendeRO2 = Rx - XCoordRO2;
	OverstaandeRO2 = Ry - YCoordRO2;

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
    cout<<"Hoek:\t Aanliggende 2= "<<AanliggendeRO2<<endl;
	cout<<"Hoek:\t Overstaande 2= "<<OverstaandeRO2<<endl;

    //================================================================================================
    // Checken of we botsing hebben

    Verschil = Beta - Alpha;

    if((Alpha > Alpha1) && (Alpha < Alpha2))
    {
        cout<<"Botsing!"<<endl;
        if( Verschil < 0)
        {
            Verschil = Verschil - (Alpha1-Alpha);
            richting = 'l';
        }
        else
        {
            Verschil = Verschil - (Alpha-Alpha2);
            richting = 'r';
        }

    }
    else
    {
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

    if ( (abs(Verschil) <= TRESLOW) || (abs(Verschil) >= (360-TRESLOW)) )
    {
        #ifdef DEBUGHOEK
		cout<<"Hoek:\t Hoek gelijk, stoppen"<<endl;
		#endif //DEBUGHOEK
		setAngle(0);
    }
    else
    {
        Hoek = abs(Verschil);
        setAngle(Hoek);             // Draaihoek
    }

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

