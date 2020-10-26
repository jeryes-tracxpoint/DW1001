#include "DW1000Device.h"
#include "DW1000.h"




uint8_t  DW1000Device::efhas = 8;
static  uint16_t efhas2 = 20;


//Constructor and destructor
DW1000Device::DW1000Device() {
	randomShortAddress();
	
}


void DW1000Device::updateEfhas(){
	efhas =10;
	efhas2 = 25;
}
DW1000Device::DW1000Device(byte deviceAddress[], boolean shortOne) {
	
	if(!shortOne) {
		//we have a 8 bytes address
		setAddress(deviceAddress);
		randomShortAddress();
	}
	else {
		//we have a short address (2 bytes)
		setShortAddress(deviceAddress);
		
	//	setXYZPose(currentXYZPositionChar);
	}
}
DW1000Device::DW1000Device(byte deviceAddress[],char x[]) {
		setShortAddress(deviceAddress);
	//	Serial.print("sdasda= ");Serial.println(x);
		//setXYZPose(x);
}

DW1000Device::DW1000Device(byte deviceAddress[], byte shortAddress[]) {
	//we have a 8 bytes address
	setAddress(deviceAddress);
	//we set the 2 bytes address
	setShortAddress(shortAddress);
}

DW1000Device::~DW1000Device() {
}

//setters:
void DW1000Device::setReplyTime(uint16_t replyDelayTimeUs) { _replyDelayTimeUS = replyDelayTimeUs; }

void DW1000Device::setAddress(char deviceAddress[]) { DW1000.convertToByte(deviceAddress, _ownAddress); }

void DW1000Device::setAddress(byte* deviceAddress) {
	memcpy(_ownAddress, deviceAddress, 8);
}

void DW1000Device::setShortAddress(byte deviceAddress[]) {
	memcpy(_shortAddress, deviceAddress, 2);
}

void DW1000Device::setXYZPose(byte valX) { 
	 _ownAddressXYZPose = valX; 
	
}

void DW1000Device::setYPose(byte ValY) { 
	 _ownAddressYPose = ValY; 
	
}
void DW1000Device::setZPose(byte ValZ) { 
	 _ownAddressZPose = ValZ; 
	
}



void DW1000Device::setRange(float range) { _range = round(range*100); }

void DW1000Device::setRXPower(float RXPower) { _RXPower = round(RXPower*100); }

void DW1000Device::setFPPower(float FPPower) { _FPPower = round(FPPower*100); }

void DW1000Device::setQuality(float quality) { _quality = round(quality*100); }






byte* DW1000Device::getByteAddress() {
	return _ownAddress;
}


byte* DW1000Device::getByteShortAddress() {
	
	return _shortAddress;
}



uint16_t DW1000Device::getShortAddress() {
	return _shortAddress[1]*256+_shortAddress[0];
}

uint16_t DW1000Device::getShortXYZPose() {
	return _shortXYZPosition[1]*256+_shortXYZPosition[0];
}

boolean DW1000Device::isAddressEqual(DW1000Device* device) {
	return memcmp(this->getByteAddress(), device->getByteAddress(), 8) == 0;
}

boolean DW1000Device::isShortAddressEqual(DW1000Device* device) {
	return memcmp(this->getByteShortAddress(), device->getByteShortAddress(), 2) == 0;
}


float DW1000Device::getRange() { return float(_range)/100.0f; }

float DW1000Device::getRXPower() { return float(_RXPower)/100.0f; }

float DW1000Device::getFPPower() { return float(_FPPower)/100.0f; }

float DW1000Device::getQuality() { return float(_quality)/100.0f; }


void DW1000Device::randomShortAddress() {
	_shortAddress[0] = random(0, 256);
	_shortAddress[1] = random(0, 256);
}

void DW1000Device::noteActivity() {
	_activity = millis();
}


boolean DW1000Device::isInactive() {
	//One second of inactivity
	if(millis()-_activity > INACTIVITY_TIME) {
		_activity = millis();
		return true;
	}
	return false;
}
