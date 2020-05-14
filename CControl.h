#pragma once

#include "Serial.h"

/**
*
* @brief Sends and recieves serial communication through the comport. Also includes various hardware tests.
*
* Tests avaliable include reading analog channels, servo sweep, detecting button activation, and reading digital channels.
*
* @author William Lau
*
*/
class CControl {
private:
	Serial _com; ///< Object for serial communication
	int last_button_state = 1; ///< used by get_button() to check a negative falling edge
	double start_t, freq, elapsed_t;
	enum { DIGITAL = 0, ANALOG = 1, SERVO = 2 }; ///< Type of signal sent enumeration
public:
	CControl(); ///< Constructor
	~CControl(); ///< Deconstructor
	
/** @brief Initiates and opens requested comport
*
* @param comport The numerical value of requested comport to open
* @return nothing to return
*/
void init_com(int comport);

/** @brief Sends a 'get' request via function set_data(). Recieves Tx string, concatanate data, and returns data by pass-by-reference
*
* @param type Analog(=0), Digital(=1), or Servo(=2) 
* @param channel Channel number on microcontroller to get data from. 
* @param result Data returned by microcontroller
* @return 0 on successful execution of function
*/
bool get_data(int type, int channel, int& result);

/** @brief Sends a 'get' or 'set' request on serial comport.
*
* @param type Analog(=0), Digital(=1), or Servo(=2) 
* @param channel Channel number to set data. 
* @param val Data to be pushed into channel. 
* @return 0 on successful execution of function
*/
bool set_data(int type, int channel, int val);

/** @brief Sweeps the servo motor from 1 to 180 and back
*
* @param none
* @return nothing to return
*/
void servo_test();

/** @brief returns value of analog channel 9 & 15 (joystick x,y) on uController
*
* @param x_joy_val Raw value received from x axis of joystick. Between 0-1023
* @param y_joy_val Raw value received from y axis of joystick. Between 0-1023
* @return nothing to return
*/
void get_joystick(float& x_joy_val, float& y_joy_val);

/** @brief Checks if button is pressed at time of check. returns a 0 if unpressed and 1 if pressed
*
* @param digital_ch Channel of digital input.
* @return 0 if button was not pressed on channel.
* @return 1 if button was pressed on channel.
*/
bool get_button(int digital_ch);

/** @brief Enables editing the data variables for a particular student.
*
* @param int Channel
* @return number of times pushed
*/
void digital_test(int channel);
};