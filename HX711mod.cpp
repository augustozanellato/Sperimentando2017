#include <Arduino.h>
#include "HX711mod.h"

#if ARDUINO_VERSION <= 106
	// "yield" is not implemented as noop in older Arduino Core releases, so let's define it.
	// See also: https://stackoverflow.com/questions/34497758/what-is-the-secret-of-the-arduino-yieldfunction/34498165#34498165
	void yield(void) {};
#endif

#ifdef ESP8266
  void espyield(){
    yield();
    ESP.wdtFeed();
  }
#endif

#ifndef ESP8266
  void espyield(){};
#endif

HX711::HX711(byte dout, byte pd_sck, byte gain) {
	begin(dout, pd_sck, gain);
}

HX711::HX711() {
}

HX711::~HX711() {
}

void HX711::begin(byte dout, byte pd_sck, byte gain) {
	PD_SCK = pd_sck;
	DOUT = dout;
	espyield();
	pinMode(PD_SCK, OUTPUT);
	pinMode(DOUT, INPUT);
	espyield();
	set_gain(gain);
}

bool HX711::is_ready() {
	espyield();
	return digitalRead(DOUT) == LOW;
}

void HX711::set_gain(byte gain) {
	switch (gain) {
		case 128:		// channel A, gain factor 128
			GAIN = 1;
			break;
		case 64:		// channel A, gain factor 64
			GAIN = 3;
			break;
		case 32:		// channel B, gain factor 32
			GAIN = 2;
			break;
	}
	espyield();
	digitalWrite(PD_SCK, LOW);
	espyield();
	read();
}

long HX711::read() {
	// wait for the chip to become ready
	while (!is_ready()) {
		// Will do nothing on Arduino but prevent resets of ESP8266 (Watchdog Issue)
		espyield();
	}

	unsigned long value = 0;
	uint8_t data[3] = { 0 };
	uint8_t filler = 0x00;

	// pulse the clock pin 24 times to read the data
	data[2] = shiftIn(DOUT, PD_SCK, MSBFIRST);
	espyield();
	data[1] = shiftIn(DOUT, PD_SCK, MSBFIRST);
	espyield();
	data[0] = shiftIn(DOUT, PD_SCK, MSBFIRST);
	espyield();

	// set the channel and the gain factor for the next reading using the clock pin
	for (unsigned int i = 0; i < GAIN; i++) {
		digitalWrite(PD_SCK, HIGH);
		digitalWrite(PD_SCK, LOW);
		espyield();
	}

	// Replicate the most significant bit to pad out a 32-bit signed integer
	if (data[2] & 0x80) {
		filler = 0xFF;
	} else {
		filler = 0x00;
	}

	// Construct a 32-bit signed integer
	value = ( static_cast<unsigned long>(filler) << 24
			| static_cast<unsigned long>(data[2]) << 16
			| static_cast<unsigned long>(data[1]) << 8
			| static_cast<unsigned long>(data[0]) );
	espyield();
	return static_cast<long>(value);
}

long HX711::read_average(byte times) {
	long sum = 0;
	espyield();
	for (byte i = 0; i < times; i++) {
		sum += read();
		espyield();
	}
	espyield();
	return sum / times;
}

double HX711::get_value(byte times) {
	espyield();
	return read_average(times) - OFFSET;
}

float HX711::get_units(byte times) {
	espyield();
	return get_value(times) / SCALE;
}

void HX711::tare(byte times) {
	espyield();
	double sum = read_average(times);
	espyield();
	set_offset(sum);
}

void HX711::set_scale(float scale) {
	espyield();
	SCALE = scale;
}

float HX711::get_scale() {
	espyield();
	return SCALE;
}

void HX711::set_offset(long offset) {
	espyield();
	OFFSET = offset;
}

long HX711::get_offset() {
	espyield();
	return OFFSET;
}

void HX711::power_down() {
	espyield();
	digitalWrite(PD_SCK, LOW);
	digitalWrite(PD_SCK, HIGH);
}

void HX711::power_up() {
	espyield();
	digitalWrite(PD_SCK, LOW);
}
