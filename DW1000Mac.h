#define FC_1 0x41
#define FC_1_BLINK 0xC5
#define FC_2 0x8C
#define FC_2_SHORT 0x88

#define PAN_ID_1 0xCA
#define PAN_ID_2 0xDE

#define SHORT_MAC_LEN 9
#define LONG_MAC_LEN 15


#ifndef _DW1000MAC_H_INCLUDED
#define _DW1000MAC_H_INCLUDED

#include <Arduino.h>
#include "DW1000Device.h" 

class DW1000Device;

class DW1000Mac {
public:
	//Constructor and destructor
	DW1000Mac(DW1000Device* parent);
	DW1000Mac();
	~DW1000Mac();
	
	
	//setters
	void setDestinationAddress(byte* destinationAddress);
	void setDestinationAddressShort(byte* shortDestinationAddress);
	void setSourceAddress(byte* sourceAddress);
	void setSourceAddressShort(byte* shortSourceAddress);
	
	
	void generateBlinkFrame(byte frame[], byte sourceAddress[], byte sourceShortAddress[]);
	
	void generateShortMACFrame(byte frame[], byte sourceShortAddress[], byte destinationShortAddress[]);

	void generateLongMACFrame(byte frame[], byte sourceShortAddress[], byte destinationAddress[]);
	
	void decodeBlinkFrame(byte frame[], byte address[], byte shortAddress[]);
	void decodeShortMACFrame(byte frame[], byte address[]);
	void decodeLongMACFrame(byte frame[], byte address[], byte addressXYZ[]);
	
	void incrementSeqNumber();


private:
	uint8_t _seqNumber = 0;
	void reverseArray(byte to[], byte from[], int16_t size);
	
};


#endif

