
#ifndef _DW1000_H_INCLUDED
#define _DW1000_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Arduino.h>
#include <SPI.h>
#include "DW1000Constants.h"
#include "DW1000Time.h"
#include "DW1000Mac.h"

class DW1000Class {
public:
	
	static void begin(uint8_t irq, uint8_t rst = 0xff);
	static byte data1[30];
	static uint8_t FillterSyncNumber ;
	static void matheConstantPara(uint8_t FillterSync = 1);
	static DW1000Mac    _globalMac1;
	static float AntenaDelayDevice1 ;
	static float getAntenaDelayDevice1(){return AntenaDelayDevice1;};
	
	static void select(uint8_t ss);
	
	static void mask();
	static void Unmask();
	static void clearDBLBuff();

	static void reselect(uint8_t ss);
	
	static void end();
	
	static void enableDebounceClock();

	static void enableLedBlinking();

	static void setGPIOMode(uint8_t msgp, uint8_t mode);

        static void deepSleep();

		static void WakeUpViaSS();

	static void reset();
	
	/** 
	Resets the currently selected DW1000 chip programmatically (via corresponding commands).
	*/
	static void softReset();
	
	static void getPrintableDeviceIdentifier(char msgBuffer[]);
	
	static void getPrintableExtendedUniqueIdentifier(char msgBuffer[]);

	static void PrintDeviceIdTowByte(char msgBuffer[]);
	
	static void getPrintableNetworkIdAndShortAddress(char msgBuffer[]);
	
	static void getPrintableDeviceMode(char msgBuffer[]);
	
	static void setNetworkId(uint16_t val);

	static void setPositionXYZ(uint16_t val);
	
	static void setDeviceAddress(uint16_t val);
	// TODO MAC and filters
	
	static void setEUI(char eui[]);
	static void setEUI(byte eui[]);
	

	static void setReceiverAutoReenable(boolean val);
	
	static void setInterruptPolarity(boolean val);
	
	static void suppressFrameCheck(boolean val);
	
	static void setDataRate(byte rate);
	
	static void setPulseFrequency(byte freq);
	static byte getPulseFrequency();
	static void setPreambleLength(byte prealen);
	static void setChannel(byte channel);
	static void setPreambleCode(byte preacode);
	static void useSmartPower(boolean smartPower);
	
	/* transmit and receive configuration. */
	static DW1000Time   setDelay(const DW1000Time& delay);
	static void         receivePermanently(boolean val);
	static void         setData(byte data[], uint16_t n);
	static void         setData(const String& data);
	static void         getData(byte data[], uint16_t n);
	static void         getData(String& data);
	static uint16_t     getDataLength();
	static void         getTransmitTimestamp(DW1000Time& time);
	static void         getReceiveTimestamp(DW1000Time& time);
	static void         getSystemTimestamp(DW1000Time& time);
	static void         getTransmitTimestamp(byte data[]);
	static void         getReceiveTimestamp(byte data[]);
	static void         getSystemTimestamp(byte data[]);
	
	/* receive quality information. */
	static float getReceivePower();
	static float getFirstPathPower();
	static float getReceiveQuality();
	static float getPeakPathIndx();
	
	/* interrupt management. */
	static void interruptOnSent(boolean val);
	static void interruptOnReceived(boolean val);
	static void interruptOnReceiveFailed(boolean val);
	static void interruptOnReceiveTimeout(boolean val);
	static void interruptOnReceiveTimestampAvailable(boolean val);
	static void interruptOnAutomaticAcknowledgeTrigger(boolean val);
	
	/* callback handler management. */
	static void attachErrorHandler(void (* handleError)(void)) {
		_handleError = handleError;
	}
	
	static void attachSentHandler(void (* handleSent)(void)) {
		_handleSent = handleSent;
	}
	
	static void attachReceivedHandler(void (* handleReceived)(void)) {
		_handleReceived = handleReceived;
	}
	
	static void attachReceiveFailedHandler(void (* handleReceiveFailed)(void)) {
		_handleReceiveFailed = handleReceiveFailed;
	}
	
	static void attachReceiveTimeoutHandler(void (* handleReceiveTimeout)(void)) {
		_handleReceiveTimeout = handleReceiveTimeout;
	}
	
	static void attachReceiveTimestampAvailableHandler(void (* handleReceiveTimestampAvailable)(void)) {
		_handleReceiveTimestampAvailable = handleReceiveTimestampAvailable;
	}
	
	/* device state management. */
	// idle state
	static void idle();
	static bool IsIdleDone ;
	
	// general configuration state
	static void newConfiguration();
	static void commitConfiguration();
	
	// reception state
	static void newReceive();
	static void startReceive();
	
	// transmission state
	static void newTransmit();
	static void startTransmit();
	static void SetDeviceMode(uint8_t CurMode);

	static void enableMode(const byte mode[]);
	
	// use RX/TX specific and general default settings
	static void setDefaults();
	
	/* debug pretty print registers. */
	static void getPrettyBytes(byte cmd, uint16_t offset, char msgBuffer[], uint16_t n);
	static void getPrettyBytes(byte data[], char msgBuffer[], uint16_t n);
	
	//convert from char to 4 bits (hexadecimal)
	static uint8_t nibbleFromChar(char c);
	static void convertToByte(char string[], byte* eui_byte);
	
	// host-initiated reading of temperature and battery voltage
	static void getTempAndVbat(float& temp, float& vbat);
	
	// transmission/reception bit rate
	static constexpr byte TRX_RATE_110KBPS  = 0x00;
	static constexpr byte TRX_RATE_850KBPS  = 0x01;
	static constexpr byte TRX_RATE_6800KBPS = 0x02;
	
	// transmission pulse frequency
	// 0x00 is 4MHZ, but receiver in DW1000 does not support it (!??)
	static constexpr byte TX_PULSE_FREQ_16MHZ = 0x01;
	static constexpr byte TX_PULSE_FREQ_64MHZ = 0x02;
	
	// preamble length (PE + TXPSR bits)
	static constexpr byte TX_PREAMBLE_LEN_64   = 0x01;
	static constexpr byte TX_PREAMBLE_LEN_128  = 0x05;
	static constexpr byte TX_PREAMBLE_LEN_256  = 0x09;
	static constexpr byte TX_PREAMBLE_LEN_512  = 0x0D;
	static constexpr byte TX_PREAMBLE_LEN_1024 = 0x02;
	static constexpr byte TX_PREAMBLE_LEN_1536 = 0x06;
	static constexpr byte TX_PREAMBLE_LEN_2048 = 0x0A;
	static constexpr byte TX_PREAMBLE_LEN_4096 = 0x03;
	
	// PAC size. */
	static constexpr byte PAC_SIZE_8  = 8;
	static constexpr byte PAC_SIZE_16 = 16;
	static constexpr byte PAC_SIZE_32 = 32;
	static constexpr byte PAC_SIZE_64 = 64;
	
	/* channel of operation. */
	static constexpr byte CHANNEL_1 = 1;
	static constexpr byte CHANNEL_2 = 2;
	static constexpr byte CHANNEL_3 = 3;
	static constexpr byte CHANNEL_4 = 4;
	static constexpr byte CHANNEL_5 = 5;
	static constexpr byte CHANNEL_7 = 7;
	
	/* preamble codes. */
	static constexpr byte PREAMBLE_CODE_16MHZ_1  = 1;
	static constexpr byte PREAMBLE_CODE_16MHZ_2  = 2;
	static constexpr byte PREAMBLE_CODE_16MHZ_3  = 3;
	static constexpr byte PREAMBLE_CODE_16MHZ_4  = 4;
	static constexpr byte PREAMBLE_CODE_16MHZ_5  = 5;
	static constexpr byte PREAMBLE_CODE_16MHZ_6  = 6;
	static constexpr byte PREAMBLE_CODE_16MHZ_7  = 7;
	static constexpr byte PREAMBLE_CODE_16MHZ_8  = 8;
	static constexpr byte PREAMBLE_CODE_64MHZ_9  = 9;
	static constexpr byte PREAMBLE_CODE_64MHZ_10 = 10;
	static constexpr byte PREAMBLE_CODE_64MHZ_11 = 11;
	static constexpr byte PREAMBLE_CODE_64MHZ_12 = 12;
	static constexpr byte PREAMBLE_CODE_64MHZ_17 = 17;
	static constexpr byte PREAMBLE_CODE_64MHZ_18 = 18;
	static constexpr byte PREAMBLE_CODE_64MHZ_19 = 19;
	static constexpr byte PREAMBLE_CODE_64MHZ_20 = 20;
	
	/* frame length settings. */
	static constexpr byte FRAME_LENGTH_NORMAL   = 0x00;
	static constexpr byte FRAME_LENGTH_EXTENDED = 0x03;
	
	/* pre-defined modes of operation (3 bytes for data rate, pulse frequency and 
	preamble length). */
	static constexpr byte MODE_LONGDATA_RANGE_LOWPOWER[] = {TRX_RATE_110KBPS, TX_PULSE_FREQ_16MHZ, TX_PREAMBLE_LEN_2048};
	static constexpr byte MODE_SHORTDATA_FAST_LOWPOWER[] = {TRX_RATE_6800KBPS, TX_PULSE_FREQ_16MHZ, TX_PREAMBLE_LEN_128};
	static constexpr byte MODE_LONGDATA_FAST_LOWPOWER[]  = {TRX_RATE_6800KBPS, TX_PULSE_FREQ_16MHZ, TX_PREAMBLE_LEN_1024};
	static constexpr byte MODE_SHORTDATA_FAST_ACCURACY[] = {TRX_RATE_6800KBPS, TX_PULSE_FREQ_64MHZ, TX_PREAMBLE_LEN_128};
	static constexpr byte MODE_LONGDATA_FAST_ACCURACY[]  = {TRX_RATE_6800KBPS, TX_PULSE_FREQ_64MHZ, TX_PREAMBLE_LEN_1024};
	static constexpr byte MODE_LONGDATA_RANGE_ACCURACY[] = {TRX_RATE_110KBPS, TX_PULSE_FREQ_64MHZ, TX_PREAMBLE_LEN_2048};
	
	byte getModeDevice(int indx);
	

//private:
	/* chip select, reset and interrupt pins. */
	static uint8_t _ss;
	static uint8_t _rst;
	static uint8_t _irq;
	
	/* callbacks. */
	static void (* _handleError)(void);
	static void (* _handleSent)(void);
	static void (* _handleReceived)(void);
	static void (* _handleReceiveFailed)(void);
	static void (* _handleReceiveTimeout)(void);
	static void (* _handleReceiveTimestampAvailable)(void);
	
	/* register caches. */
	static byte _syscfg[LEN_SYS_CFG];
	static byte _sysctrl[LEN_SYS_CTRL];
	static byte _sysstatus[LEN_SYS_STATUS];
	static byte _txfctrl[LEN_TX_FCTRL];
	static byte _sysmask[LEN_SYS_MASK];
	static byte _chanctrl[LEN_CHAN_CTRL];
	
	/* device status monitoring */
	static byte _vmeas3v3;
	static byte _tmeas23C;

	/* PAN and short address. */
	static byte _networkAndAddress[LEN_PANADR];
	static byte _PositionXYZ[3];
	
	/* internal helper that guide tuning the chip. */
	static boolean    _smartPower;
	static byte       _extendedFrameLength;
	static byte       _preambleCode;
	static byte       _channel;
	static byte       _preambleLength;
	static byte       _pulseFrequency;
	static byte       _dataRate;
	static byte       _pacSize;
	static DW1000Time _antennaDelay;
	
	/* internal helper to remember how to properly act. */
	static boolean _permanentReceive;
	static boolean _frameCheck;
	
	// whether RX or TX is active
	static uint8_t _deviceMode;

	// whether debounce clock is active
	static boolean _debounceClockEnabled;

	static boolean _enableRcvFaild;

	/* Arduino interrupt handler */
	static void handleInterrupt();
	
	/* Allow MAC frame filtering . */
	// TODO auto-acknowledge
	static void setFrameFilter(boolean val);
	static void setFrameFilterBehaveCoordinator(boolean val);
	static void setFrameFilterAllowBeacon(boolean val);
	//data type is used in the FC_1 0x41
	static void setFrameFilterAllowData(boolean val);
	static void setFrameFilterAllowAcknowledgement(boolean val);
	static void setFrameFilterAllowMAC(boolean val);
	//Reserved is used for the Blink message
	static void setFrameFilterAllowReserved(boolean val);
	
	// note: not sure if going to be implemented for now
	static void setDoubleBuffering(boolean val);
	// TODO is implemented, but needs testing
	static void useExtendedFrameLength(boolean val);
	// TODO is implemented, but needs testing
	static void waitForResponse(boolean val);
	
	/* tuning according to mode. */
	static void tune();
	
	/* device status flags */
	static boolean isReceiveTimestampAvailable();
	static boolean isTransmitDone();
	static boolean isReceiveDone();
	static boolean isReceiveFailed();
	static boolean isReceiveTimeout();
	static boolean isClockProblem();
	
	/* interrupt state handling */
	static void clearInterrupts();
	static void clearAllStatus();
	static void clearReceiveStatus();
	static void clearReceiveTimestampAvailableStatus();
	static void clearTransmitStatus();
	
	/* internal helper to read/write system registers. */
	static void readSystemEventStatusRegister();
	static void readSystemConfigurationRegister();
	static void writeSystemConfigurationRegister();
	static void readNetworkIdAndDeviceAddress();
	static void writeNetworkIdAndDeviceAddress();
	static void readSystemEventMaskRegister();
	static void writeSystemEventMaskRegister();
	static void readChannelControlRegister();
	static void writeChannelControlRegister();
	static void readTransmitFrameControlRegister();
	static void writeTransmitFrameControlRegister();
	
	/* clock management. */
	static void enableClock(byte clock);
	
	/* LDE micro-code management. */
	static void manageLDE();
	
	/* timestamp correction. */
	static void correctTimestamp(DW1000Time& timestamp);
	
	/* reading and writing bytes from and to DW1000 module. */
	static void readBytes(byte cmd, uint16_t offset, byte data[], uint16_t n);
	static void readBytesOTP(uint16_t address, byte data[]);
	static void WriteBytesOTP(uint16_t address, byte data[]);
	static void writeByte(byte cmd, uint16_t offset, byte data);
	static void writeBytes(byte cmd, uint16_t offset, byte data[], uint16_t n);
	static void readLEDPPINDX(uint16_t address, byte data[]);

	static void getLEdPPIndx(byte PPIndx);
	
	/* writing numeric values to bytes. */
	static void writeValueToBytes(byte data[], int32_t val, uint16_t n);
	
	/* internal helper for bit operations on multi-bytes. */
	static boolean getBit(byte data[], uint16_t n, uint16_t bit);
	static void    setBit(byte data[], uint16_t n, uint16_t bit, boolean val);
	
	/* Register is 6 bit, 7 = write, 6 = sub-adressing, 5-0 = register value
	 * Total header with sub-adressing can be 15 bit. */
	static const byte WRITE      = 0x80; // regular write
	static const byte WRITE_SUB  = 0xC0; // write with sub address
	static const byte READ       = 0x00; // regular read
	static const byte READ_SUB   = 0x40; // read with sub address
	static const byte RW_SUB_EXT = 0x80; // R/W with sub address extension
	
	/* clocks available. */
	static const byte AUTO_CLOCK = 0x00;
	static const byte XTI_CLOCK  = 0x01;
	static const byte PLL_CLOCK  = 0x02;
	
	/* SPI configs. */
	static const SPISettings _fastSPI;
	static const SPISettings _slowSPI;
	static const SPISettings* _currentSPI;
	
	/* range bias tables (500/900 MHz band, 16/64 MHz PRF), -61 to -95 dBm. */
	static const byte BIAS_500_16_ZERO = 10;
	static const byte BIAS_500_64_ZERO = 8;
	static const byte BIAS_900_16_ZERO = 7;
	static const byte BIAS_900_64_ZERO = 7;
	
	// range bias tables (500 MHz in [mm] and 900 MHz in [2mm] - to fit into bytes)
	static constexpr byte BIAS_500_16[] = {198, 187, 179, 163, 143, 127, 109, 84, 59, 31, 0, 36, 65, 84, 97, 106, 110, 112};
	static constexpr byte BIAS_500_64[] = {110, 105, 100, 93, 82, 69, 51, 27, 0, 21, 35, 42, 49, 62, 71, 76, 81, 86};
	static constexpr byte BIAS_900_16[] = {137, 122, 105, 88, 69, 47, 25, 0, 21, 48, 79, 105, 127, 147, 160, 169, 178, 197};
	static constexpr byte BIAS_900_64[] = {147, 133, 117, 99, 75, 50, 29, 0, 24, 45, 63, 76, 87, 98, 116, 122, 132, 142};

	static void PrintANchorRCVData();

	
};

extern DW1000Class DW1000;

#endif
