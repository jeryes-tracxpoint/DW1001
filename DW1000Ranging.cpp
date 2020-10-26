

#include "DW1000Ranging.h"
#include "DW1000Device.h"


typedef unsigned char uchar;

DW1000RangingClass DW1000Ranging;

byte         DW1000RangingClass::_currentAddress[8];
byte         DW1000RangingClass::_currentShortAddress[2];
byte         DW1000RangingClass::_currentXYZPosition[12];
char 		 DW1000RangingClass::_currentXYZPositionChar[6];
int16_t      DW1000RangingClass::_type; // TODO enum??


////////////////////////////////////initCommunication/////////////////////////////////////////////////////////
void DW1000RangingClass::initCommunication(uint8_t myRST, uint8_t mySS, uint8_t myIRQ) {
	
	DW1000.begin(myIRQ, myRST);
	DW1000.select(mySS);
}

////////////////////////////////////configureNetwork/////////////////////////////////////////////////////////
void DW1000RangingClass::configureNetwork(uint16_t deviceAddress, uint16_t networkId, const byte mode[]) {

	DW1000.newConfiguration();
	DW1000.setDefaults();
	DW1000.setDeviceAddress(deviceAddress);
	DW1000.setNetworkId(networkId);
	DW1000.enableMode(mode);
	DW1000.commitConfiguration();
}
///////////////////////////////////generalStart////////////////////////////////////////////////////////////////
void DW1000RangingClass::generalStart() {

		DW1000.attachReceivedHandler(handleReceived);
		DW1000.attachReceiveFailedHandler(handleReceivedFaild);
	
	if(DEBUG) {
		// DEBUG monitoring
		Serial.println("DW1000-arduino");
		// initialize the driver
		
		
		Serial.println("configuration..");
		// DEBUG chip info and registers pretty printed
		char msg[90];
		DW1000.getPrintableDeviceIdentifier(msg);
		Serial.print("Device ID: ");
		Serial.println(msg);
		DW1000.getPrintableExtendedUniqueIdentifier(msg);
		Serial.print("Unique ID: ");
		Serial.print(msg);
		char string[6];
		sprintf(string, "%02X:%02X", _currentShortAddress[0], _currentShortAddress[1]);
		Serial.print(" short: ");
		Serial.println(string);
		
		DW1000.getPrintableNetworkIdAndShortAddress(msg);
		Serial.print("Network ID & Device Address: ");
		Serial.println(msg);
		DW1000.getPrintableDeviceMode(msg);
		Serial.print("Device mode: ");
		Serial.println(msg);
	}
	
			if (_type == ANCHOR)
				receiver();

}


void DW1000RangingClass::receiver(){
	DW1000.newReceive();
	DW1000.setDefaults();
	DW1000.receivePermanently(true);
	DW1000.startReceive();
}


void DW1000RangingClass::startAsTag(char address[], const byte mode[], const bool randomShortAddress) {

	CastToByte(address,_currentAddress);
	DW1000.setEUI(address);
	char msg[90];
	Serial.print("device address: ");
		DW1000.getPrintableExtendedUniqueIdentifier(msg);
	Serial.println(msg);

	if (randomShortAddress) {
		randomSeed(analogRead(0));
		_currentShortAddress[0] = random(0, 256);
		_currentShortAddress[1] = random(0, 256);
	}
	else {
		_currentShortAddress[0] = _currentAddress[0];
		_currentShortAddress[1] = _currentAddress[1];
	}

	DW1000Ranging.configureNetwork(_currentShortAddress[0]*256+_currentShortAddress[1], 0xDECA, mode);
	
	_type = DeviceType::TAG;

	generalStart();
	
	
	Serial.println("### TAG ###");
}


void DW1000RangingClass::startAsAnchor(char address[], const byte mode[], const bool randomShortAddress) {
	
	//save the address
	DW1000.convertToByte(address, _currentAddress);
	char msg[90];
	DW1000.PrintDeviceIdTowByte(msg);
	Serial.print(",Device IDFromCompany: ");
	Serial.println(msg);
	_currentXYZPositionChar[0] = address[6];
	_currentXYZPositionChar[1] = address[7];
	//write the address on the DW1000 chip
	DW1000.setEUI(address);
	Serial.print(",device address: ");
	Serial.println(address);
	//randomShortAddress = false;
	if (randomShortAddress) {
		//we need to define a random short address:
		randomSeed(analogRead(0));
		_currentShortAddress[0] = random(0, 256);
		_currentShortAddress[1] = random(0, 256);
	}
	else {
		// we use first two bytes in addess for short address
		_currentShortAddress[0] = _currentAddress[0];
		_currentShortAddress[1] = _currentAddress[1];
	
	}
	
	DW1000Ranging.configureNetwork(_currentShortAddress[0]*256+_currentShortAddress[1], 0xDECA, mode);
	//defined type as anchor
	_type = ANCHOR;
	generalStart();
	Serial.println("### ANCHOR ###");
}

	




