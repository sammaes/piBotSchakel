#include "Hoek.h"

using namespace std;

// Destructor
Hoek::~Hoek()
{
}

// constructor
Hoek::Hoek()
{
    setAngle(0);
    setSpeed(0);
    setDirection('l');
    setAfstand(0);
}

void Hoek::BepaalHoek(int Xr,int Yr,int Xb,int Yb,int Beta) // Dit krijgen we binnen
{
    int KwadrantA   = 0;
    int KwadrantB   = 0;
    float Aanliggende = 0;
    float Overstaande = 0;
    int Verschil = 0;
    int Alpha     = 0;

    Aanliggende = abs(Xr - Xb);
    Overstaande = abs(Yr - Yb);

#ifdef DEBUG
    cout<<"Hoek bepalen:"<<endl;
    cout<<"Aanliggende = "<<Aanliggende<<endl;
    cout<<"Overstaande = "<<Overstaande<<endl;
#endif

    // Hoek alpha bepalen
    Alpha = round(((atan(Overstaande/Aanliggende)* 180)/PI));
    //cout<<"Alpha = "<<Alpha<<endl;

    if(Xr < Xb) // Rechterkant cirkel
    {
        if(Yr < Yb) // Vierde kwadrant, Indien Y1 < Y2 ligt de hoek in het eerste kwadrant en moet er niets gebeuren
        {
            KwadrantA   = 1;
        }
        else
        {
            Alpha       = 360 - Alpha;
            KwadrantA   = 4;
        }
    }
    else // Linkerkant cirkel
    {
        if(Yr < Yb) // Tweede kwadrant
        {
            Alpha       = 180 - Alpha;
            KwadrantA   = 2;
        }
        else // Derde kwadrant
        {
            Alpha       = Alpha + 180;
            KwadrantA   = 3;
        }
    }
#ifdef DEBUG
    cout<<"Alpha = "<<Alpha<<endl;
    cout<<"Kwadrant Alpha = "<<KwadrantA<<endl;
#endif

    // Kwadrant voor beta bepalen
    if(Beta >= 0 && Beta <= 90)
    {
        KwadrantB = 1;
    }
    if(Beta >= 91 && Beta <= 180)
    {
        KwadrantB = 2;
    }
    if(Beta >= 181 && Beta <= 270)
    {
        KwadrantB = 3;
    }
    if(Beta >= 270 && Beta <= 360)
    {
        KwadrantB = 4;
    }

    Verschil = Beta - Alpha;

#ifdef DEBUG
    cout<<"Kwadrant Beta = "<<KwadrantB<<endl;
    cout<<"Verschil = "<<Verschil<<endl;
#endif

    if((abs(Verschil) <= 4) || (abs(Verschil) >= 356))
    {
#ifdef DEBUG
        cout<<"Hoek gelijk, stoppen"<<endl;
#endif
        setAngle(0);
    }
    else
    {
        if((Verschil < 0) && (abs(Verschil) > 180)) // De positieve hoek nemen
        {
            Verschil = 360 + Verschil;
        }
        // Dezelfde kwadranten
        if(KwadrantA == KwadrantB)
        {
            if(Verschil < 0)
            {
                //Draai naar links onder hoek van Verschil
#ifdef DEBUG
                cout<<"Draai links, draaihoek = "<<abs(Verschil)<<endl;
#endif
                setAngle(abs(Verschil));
                setDirection('l');
            }
            else
            {
                //Draai naar rechts onder hoek van Verschil
#ifdef DEBUG
                cout<<"Draai rechts, draaihoek = "<<Verschil<<endl;
#endif
                setAngle(Verschil);
                setDirection('r');
            }
        }
        else
        {
            if(Verschil < 0)
            {
                if(abs(Verschil) < 180)
                {
                    //Draai links onder hoek van abs(Verschil)
#ifdef DEBUG
                    cout<<"Draai links, draaihoek = "<<abs(Verschil)<<endl;
#endif
                    setAngle(abs(Verschil));
                    setDirection('l');
                }
                else
                {
                    //Draai rechts onder hoek van Verschil + 360
#ifdef DEBUG
                    cout<<"Draai rechts, draaihoek = "<<Verschil + 360<<endl;
#endif
                    setAngle(Verschil+360);
                    setDirection('r');
                }
            }
            else
            {
                if(Verschil > 180)
                {
                    //Draai links onder hoek van 360 - Verschil
#ifdef DEBUG
                    cout<<"Draai links, draaihoek = "<<360-Verschil<<endl;
#endif
                    setAngle(360-Verschil);
                    setDirection('l');
                }
                else
                {
                    // Draai rechts onder hoek van Verschil
#ifdef DEBUG
                    cout<<"Draai rechts, draaihoek = "<<Verschil<<endl;
#endif
                    setAngle(Verschil);
                    setDirection('r');
                }
            }
        }
    }
}

void Hoek::BepaalAfstand(int Xr,int Yr,int Xb,int Yb)
{
    float Aanliggende = 0;
    float Overstaande = 0;

    Aanliggende = abs(Xr - Xb);
    Overstaande = abs(Yr - Yb);

#ifdef DEBUG
    cout<<"Afstand bepalen:"<<endl;
    cout<<"Aanliggende = "<<Aanliggende<<endl;
    cout<<"Overstaande = "<<Overstaande<<endl;
#endif

    setAfstand(sqrt((Aanliggende*Aanliggende) + (Overstaande*Overstaande)));
#ifdef DEBUG
    cout<<"Afstand = "<<getAfstand()<<endl;
#endif


}

void Hoek::BepaalSnelheid()
{
#ifdef DEBUG
    cout<<"Afstand = "<<getAfstand()<<endl;
#endif
    if(getAfstand() <= 40)
    {
#ifdef DEBUG
        cout<<"Stoppen"<<endl;
#endif
        setSpeed(0);
    }
    else
    {
        if(getAfstand() >= 140)
        {
#ifdef DEBUG
            cout<<"Snelheid = 2"<<endl; //snel rijden
#endif
            setSpeed(MAXSPEED);
        }
        else
        {
#ifdef DEBUG
            cout<<"Snelheid = 1"<<endl; //trager rijden
#endif
            setSpeed(MINSPEED);
        }
    }
}


int Hoek::getAngle()
{
    return i_Angle;
}

char Hoek::getDirection()
{
    return c_Direction;
}

int Hoek::getSpeed()
{
    return i_Speed;
}

int Hoek::getAfstand()
{
    return i_Distance;
}

void Hoek::setAngle(int i_hoek)
{
    i_Angle = i_hoek;
}

void Hoek::setDirection(char c_richting)
{
    c_Direction = c_richting;
}

void Hoek::setSpeed(int i_snelheid)
{
    i_Speed = i_snelheid;
}
void Hoek::setAfstand(int i_Afstand)
{
    i_Distance = i_Afstand;
}

