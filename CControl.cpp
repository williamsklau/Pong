#include "stdafx.h"
#include "Serial.h"
#include <iostream>
#include <string>

#include "CControl.h"
#include "opencv.hpp"

using namespace std;

CControl::CControl() {
	freq = cv::getTickFrequency();
}
CControl::~CControl(){}

void CControl::init_com(int comport) {
	string com_str = "COM";
	char buff[2];

	// Open comport
	com_str += to_string(comport);
	_com.open(com_str, 115200);
}

bool CControl::get_data(int type, int channel, int& result) {
	char buff;
	string set_rx_str = "";
	int count_space = 0;
	
	_com.flush();
	set_data(type, channel, -1);

	Sleep(10);	// wait for ADC to process
	
	do{
		_com.read(&buff, 1);
		
		if (count_space >= 3)
			set_rx_str += buff;
		
		if (buff == ' ') 
			count_space++;
	}
	while(buff != '\n');
	
	result = stoi(set_rx_str);

	return 0;
}

bool CControl::set_data(int type, int channel, int val) {
	string get_tx_str;

	// NOTE: val = -1 if used by get_data()
	if (val == -1) {
		get_tx_str += "G ";
	}
	else{
		get_tx_str += "S ";
	}
	get_tx_str += to_string(type);
	get_tx_str += " ";
	get_tx_str += to_string(channel);
	if (val != -1) {		// val = -1 if used by get_data()
		get_tx_str += " ";
		get_tx_str += to_string(val);
	}
	get_tx_str += "\n";

	_com.write(get_tx_str.c_str(), get_tx_str.length());

	return 0;
}

void CControl::servo_test() {
	int servo_pos;
	int servo_num = 0;
	int sleep_time = 50;
	
	// Code based on Energia's example code "ServoSweep"
	while (1) {
		for (servo_pos = 1; servo_pos < 180; servo_pos++) {
			set_data(SERVO, servo_num, servo_pos);
			Sleep(sleep_time);
			cout << "SERVO TEST : CH " << servo_num << " POS: " << servo_pos << "\n" << endl;
		}
		Sleep(sleep_time);
		for (servo_pos = 180; servo_pos > 1; servo_pos--) {
			set_data(SERVO, servo_num, servo_pos);
			Sleep(sleep_time);
			cout << "SERVO TEST : CH " << servo_num << " POS: " << servo_pos << "\n" << endl;
		}
		Sleep(sleep_time);

	}
}

void CControl::get_joystick(float& x_joy_val, float& y_joy_val) {
	const float max_resolution = 1023;
	int analog_val1 = 0;
	int analog_val2 = 0;
	int analog_ch1 = 9;
	int	analog_ch2 = 15;

	get_data(ANALOG, analog_ch1, analog_val1);
	get_data(ANALOG, analog_ch2, analog_val2);

	x_joy_val = analog_val2 / max_resolution * 100;
	y_joy_val = analog_val1 / max_resolution * -100 + 100;
}

bool CControl::get_button(int digital_ch) {
	// pushbutton are 32 & 33
	int button_state = 0;

	get_data(DIGITAL, digital_ch, button_state);

	if (button_state == 0) {
		while (button_state == 0) {
			get_data(DIGITAL, digital_ch, button_state);
			Sleep(10);
		}
		return 1;
	}
	else
		return 0;
}

void CControl::digital_test(int channel) {
	int red_led = 39;
	int digital_val = 1;

	while (1) {
		get_data(DIGITAL, channel, digital_val);

		if (digital_val == 0) {
			set_data(DIGITAL, red_led, 1);
		}
		else {
			set_data(DIGITAL, red_led, 0);
		}
		
		Sleep(50);
		cout << "\nDIGITAL TEST: CH" << channel << " = " << digital_val << endl;
	}
}