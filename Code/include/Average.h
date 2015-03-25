#ifndef AVERAGE_H
#define AVERAGE_H

#include 				"debug.h"
#include 				"Positie.h"

#define DEBUGAVERAGE

#define NUMSAMPLES 8	//average voorlopig van de laatste 8 samples

/* Implementatie op basis van een statisch gedefinieerde array
 * ipv linked list aangezien de grootte van de array op voorhand
 * wordt vastgezet
 */

class Average
{
    public:
                        Average();

        int		        getNuberSamp();

        Positie         getAverage();
        void	        calcAverage();
        Positie         getCalcAverage();
        Positie 		getCalcAverage(Positie val);
        void            addInputVal(Positie val);

        void 			print();

    private:
        Positie     	averagebuffer[NUMSAMPLES];
        Positie			average;
        int				currentIndex;
};

#endif // AVERAGE_H
