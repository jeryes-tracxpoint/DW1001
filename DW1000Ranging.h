#include "DW1000.h"
#include "DW1000Time.h"
#include "DW1000Device.h" 
#include "DW1000Mac.h"

// messages used in the ranging protocol

#define BLINK 4


#define LEN_DATA 30



//Default Pin for module:
#define DEFAULT_RST_PIN 9
#define DEFAULT_SPI_SS_PIN 10



//sketch type (anchor or tag)
#define TAG 0
#define ANCHOR 1
#define TagSync 2




//debug mode
#ifndef DEBUG
#define DEBUG false
#endif



class DW1000RangingClass {
public:

	static void    initCommunication(uint8_t myRST = DEFAULT_RST_PIN, uint8_t mySS = DEFAULT_SPI_SS_PIN, uint8_t myIRQ = 2);
	static void    configureNetwork(uint16_t deviceAddress, uint16_t networkId, const byte mode[]);
	static void    generalStart();
	static void    startAsAnchor(char address[], const byte mode[], const bool randomShortAddress = false);
	static void    startAsTag(char address[], const byte mode[], const bool randomShortAddress = false);
	static void    receiver();
	static void    handleReceived();
	static void    handleReceivedFaild();
	
private:
	//other devices in the network
	

	static byte         _currentAddress[8];
	static byte         _currentShortAddress[2];
	static byte 		_currentXYZPosition[12];
	static char 		_currentXYZPositionChar[6];

	

	//sketch type (tag or anchor)
	static int16_t          _type; //0 for tag and 1 for anchor

};

extern DW1000RangingClass DW1000Ranging;

