#ifndef DEBUG_H_
#define DEBUG_H_


	#define DEBUG /* Debug van alle klasses */

	#ifdef DEBUG
		/* Niet aankomen */
		#define DEBUGSERVER
		#define DEBUGSERIALPORT
		#define DEBUGROBOTCOMMAND
		#define DEBUGROBOT
		#define DEBUGPOSITIE
		#define DEBUGHOEK
		#define DEBUGDESTINATION
	#else
		/* Hier aan en uit zetten door in commentaar te zetten wat niet nodig is */
		#define DEBUGSERVER
		#define DEBUGSERIALPORT
		#define DEBUGROBOTCOMMAND
		#define DEBUGROBOT
		#define DEBUGPOSITIE
		#define DEBUGHOEK
		#define DEBUGDESTINATION
	#endif //DEBUG
#endif // DEBUG_H_
