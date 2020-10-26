
#define INACTIVITY_TIME 6000

#ifndef _DW1000Device_H_INCLUDED
#define _DW1000Device_H_INCLUDED

#define good 0

#include "DW1000Time.h"
#include "DW1000Mac.h"

class DW1000Mac;

class DW1000Device;


class DW1000Device {
	
public:
	//Constructor and destructor
	DW1000Device();
	DW1000Device(byte address[], byte shortAddress[]);
	DW1000Device(byte address[], boolean shortOne = false);
	DW1000Device(byte address[], char x[]);
	~DW1000Device();
	
	//setters:
	void setReplyTime(uint16_t replyDelayTimeUs);
	void setAddress(char address[]);
	void setAddress(byte* address);
	void setShortAddress(byte address[]);
	void setXYZPose(byte ValX);
	void setYPose(byte ValY);
	void setZPose(byte ValZ);

	int8_t getInterfaceAddress() { return InterfaceAddressmember; };
	void SetInterfaceAdd(int8_t LocalIntAddress) {InterfaceAddressmember = LocalIntAddress;};

	
	
	void setRange(float range);
	void setRXPower(float power);
	void setFPPower(float power);
	void setQuality(float quality);
	
	void setReplyDelayTime(uint16_t time) { _replyDelayTimeUS = time; }
	
	void setIndex(int8_t index) { _index = index; }
	
	//getters
	uint16_t getReplyTime() { return _replyDelayTimeUS; }
	
	byte* getByteAddress();
	
	int8_t getIndex() { return _index; }
	
	//String getAddress();
	byte* getByteShortAddress();
	uint16_t getShortAddress();
	uint16_t getShortXYZPose();
	byte getXYZPose(){return _ownAddressXYZPose;};
	byte getYPose(){return _ownAddressYPose;};
	byte getZPose(){return _ownAddressZPose;};
	//String getShortAddress();
	
	float getRange();
	float getRXPower();
	float getFPPower();
	float getQuality();
	
	boolean isAddressEqual(DW1000Device* device);
	boolean isShortAddressEqual(DW1000Device* device);
	
	//functions which contains the date: (easier to put as public)
	// timestamps to remember
	DW1000Time timePollSent;
	DW1000Time timePollReceived;
	DW1000Time timePollAckSent;
	DW1000Time timePollAckReceived;
	DW1000Time timeRangeSent;
	DW1000Time timeRangeReceived;
	DW1000Time timeBlinkReceived;
	DW1000Time timeBlinkSent;
	DW1000Time timeSync;
	
	void    noteActivity();
	boolean isInactive();


	static uint8_t efhas ;
	static void updateEfhas();

private:
	//device ID
	byte         _ownAddress[8];
	byte         _shortAddress[2];

	byte 		 _shortXYZPosition[3];
	byte 		 _ownAddressXYZPose;
	byte 		 _ownAddressYPose;
	byte		 _ownAddressZPose;
	
	int32_t      _activity;
	uint16_t     _replyDelayTimeUS;
	int8_t       _index; // not used
	int8_t InterfaceAddressmember;
	int16_t _range;
	int16_t _RXPower;
	int16_t _FPPower;
	int16_t _quality;
	
	void randomShortAddress();
	
};



#endif
