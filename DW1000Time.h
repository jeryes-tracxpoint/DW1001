#ifndef DW1000TIME_H
#define DW1000TIME_H
#include <Arduino.h>

#include <stdint.h>
#include <inttypes.h>
#include "DW1000CompileOptions.h"
#include "deprecated.h"
#include "require_cpp11.h"

#if DW1000TIME_H_PRINTABLE

class DW1000Time : public Printable {
#else
class DW1000Time {
	//Serial.print("not Printable");
#endif // DW1000Time_H_PRINTABLE
public:
	
	static constexpr float TIME_RES     = 0.000015650040064103f;
	static constexpr float TIME_RES_INV = 63897.6f;
	
	static constexpr float DISTANCE_OF_RADIO     = 0.0046917639786159f;
	static constexpr float DISTANCE_OF_RADIO_INV = 213.139451293f;
	
	static constexpr uint8_t LENGTH_TIMESTAMP = 5;
	
	static constexpr int64_t TIME_OVERFLOW = 0x10000000000; //1099511627776LL
	static constexpr int64_t TIME_MAX      = 0xffffffffff;

	static constexpr float SECONDS      = 1e6;
	static constexpr float MILLISECONDS = 1e3;
	static constexpr float MICROSECONDS = 1;
	static constexpr float NANOSECONDS  = 1e-3;
	
	// constructor
	DW1000Time();
	DW1000Time(int64_t time);
	DW1000Time(byte data[]);
	DW1000Time(const DW1000Time& copy);
	DW1000Time(float timeUs);
	DW1000Time(int32_t value, float factorUs);
	~DW1000Time();
	
	// setter
	// dw1000 timestamp, increase of +1 approx approx. 15.65ps real time
	void setTimestamp(int64_t value);
	void setTimestamp(byte data[]);
	void setTimestamp(const DW1000Time& copy);
	
	// real time in us
	void setTime(float timeUs);
	void setTime(int32_t value, float factorUs);
	
	// getter
	int64_t getTimestamp() const;
	void    getTimestamp(byte data[]) const;
	
	DEPRECATED_MSG("use getAsMicroSeconds()")
	float getAsFloat() const;
	// getter, convert the timestamp to usual units
	float getAsMicroSeconds() const;
	float getAsMeters() const;
	
	DW1000Time& wrap();
	
	// self test
	bool isValidTimestamp();
	
	// assign
	DW1000Time& operator=(const DW1000Time& assign);
	// add
	DW1000Time& operator+=(const DW1000Time& add);
	DW1000Time operator+(const DW1000Time& add) const;
	// subtract
	DW1000Time& operator-=(const DW1000Time& sub);
	DW1000Time operator-(const DW1000Time& sub) const;
	// multiply
	DW1000Time& operator*=(float factor);
	DW1000Time operator*(float factor) const;
	// no accuracy lost
	DW1000Time& operator*=(const DW1000Time& factor);
	DW1000Time operator*(const DW1000Time& factor) const;
	// divide
	DW1000Time& operator/=(float factor);
	DW1000Time operator/(float factor) const;
	// no accuracy lost
	DW1000Time& operator/=(const DW1000Time& factor);
	DW1000Time operator/(const DW1000Time& factor) const;
	// compare
	boolean operator==(const DW1000Time& cmp) const;
	boolean operator!=(const DW1000Time& cmp) const;

#ifdef DW1000TIME_H_PRINTABLE

	DEPRECATED_MSG("use Serial.print(object)")
	void print();

	size_t printTo(Print& p) const;
#endif // DW1000Time_H_PRINTABLE
	
private:

	int64_t _timestamp = 0;
};

#endif // DW1000Time_H
