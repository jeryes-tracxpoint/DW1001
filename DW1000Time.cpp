#include "DW1000Time.h"

/**
 * Initiates DW1000Time with 0
 */
DW1000Time::DW1000Time() {
	_timestamp = 0;
}

DW1000Time::DW1000Time(int64_t time) {
	setTimestamp(time);
}


DW1000Time::DW1000Time(byte data[]) {
	setTimestamp(data);
}


DW1000Time::DW1000Time(const DW1000Time& copy) {
	setTimestamp(copy);
}


DW1000Time::DW1000Time(float timeUs) {
	setTime(timeUs);
}

DW1000Time::DW1000Time(int32_t value, float factorUs) {
	setTime(value, factorUs);
}

DW1000Time::~DW1000Time() {}

void DW1000Time::setTimestamp(int64_t value) {
	_timestamp = value;
}

void DW1000Time::setTimestamp(byte data[]) {
	_timestamp = 0;
	for(uint8_t i = 0; i < LENGTH_TIMESTAMP; i++) {
		_timestamp |= ((int64_t)data[i] << (i*8));
	}
}

void DW1000Time::setTimestamp(const DW1000Time& copy) {
	_timestamp = copy.getTimestamp();
}


void DW1000Time::setTime(float timeUs) {
	_timestamp = (int64_t)(timeUs*TIME_RES_INV);
}

void DW1000Time::setTime(int32_t value, float factorUs) {
;
	setTime(value*factorUs);
}

int64_t DW1000Time::getTimestamp() const {
	return _timestamp;
}


void DW1000Time::getTimestamp(byte data[]) const {
	memset(data, 0, LENGTH_TIMESTAMP);
	for(uint8_t i = 0; i < LENGTH_TIMESTAMP; i++) {
		data[i] = (byte)((_timestamp >> (i*8)) & 0xFF);
	}
}


float DW1000Time::getAsFloat() const {
	return getAsMicroSeconds();
}

float DW1000Time::getAsMicroSeconds() const {
	return (_timestamp%TIME_OVERFLOW)*TIME_RES;
}


float DW1000Time::getAsMeters() const {
	return (_timestamp%TIME_OVERFLOW)*DISTANCE_OF_RADIO;
}

DW1000Time& DW1000Time::wrap() {
	if(_timestamp < 0) {
		_timestamp += TIME_OVERFLOW;
	}
	return *this;
}

bool DW1000Time::isValidTimestamp() {
	return (0 <= _timestamp && _timestamp <= TIME_MAX);
}

// assign
DW1000Time& DW1000Time::operator=(const DW1000Time& assign) {
	if(this == &assign) {
		return *this;
	}
	_timestamp = assign.getTimestamp();
	return *this;
}

// add
DW1000Time& DW1000Time::operator+=(const DW1000Time& add) {
	_timestamp += add.getTimestamp();
	return *this;
}

DW1000Time DW1000Time::operator+(const DW1000Time& add) const {
	return DW1000Time(*this) += add;
}

// subtract
DW1000Time& DW1000Time::operator-=(const DW1000Time& sub) {
	_timestamp -= sub.getTimestamp();
	return *this;
}

DW1000Time DW1000Time::operator-(const DW1000Time& sub) const {
	return DW1000Time(*this) -= sub;
}

// multiply
DW1000Time& DW1000Time::operator*=(float factor) {
	//float tsValue = (float)_timestamp*factor;
	//_timestamp = (int64_t)tsValue;
	_timestamp *= factor;
	return *this;
}

DW1000Time DW1000Time::operator*(float factor) const {
	return DW1000Time(*this) *= factor;
}

DW1000Time& DW1000Time::operator*=(const DW1000Time& factor) {
	_timestamp *= factor.getTimestamp();
	return *this;
}

DW1000Time DW1000Time::operator*(const DW1000Time& factor) const {
	return DW1000Time(*this) *= factor;
}

// divide
DW1000Time& DW1000Time::operator/=(float factor) {
	//_timestamp *= (1.0f/factor);
	_timestamp /= factor;
	return *this;
}

DW1000Time DW1000Time::operator/(float factor) const {
	return DW1000Time(*this) /= factor;
}

DW1000Time& DW1000Time::operator/=(const DW1000Time& factor) {
	_timestamp /= factor.getTimestamp();
	return *this;
}

DW1000Time DW1000Time::operator/(const DW1000Time& factor) const {
	return DW1000Time(*this) /= factor;
}

// compare
boolean DW1000Time::operator==(const DW1000Time& cmp) const {
	return _timestamp == cmp.getTimestamp();
}

boolean DW1000Time::operator!=(const DW1000Time& cmp) const {
	//return !(*this == cmp); // seems not as intended
	return _timestamp != cmp.getTimestamp();
}

#ifdef DW1000TIME_H_PRINTABLE

void DW1000Time::print() {
	Serial.print(*this);
	//Serial.println();
}

size_t DW1000Time::printTo(Print& p) const {
	int64_t       number  = _timestamp;
	unsigned char buf[21];
	uint8_t       i       = 0;
	uint8_t       printed = 0;
	// printf for arduino avr do not support int64, so we have to calculate
	if(number == 0) {
		p.print((char)'0');
		return 1;
	}
	if(number < 0) {
		p.print((char)'-');
		number = -number; // make positive
		printed++;
	}
	while(number > 0) {
		int64_t q = number/10;
		buf[i++] = number-q*10;
		number = q;
	}
	printed += i;
	for(; i > 0; i--)
		p.print((char)(buf[i-1] < 10 ? '0'+buf[i-1] : 'A'+buf[i-1]-10));
	
	return printed;
}
#endif // DW1000Time_H_PRINTABLE
