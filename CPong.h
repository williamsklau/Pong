#pragma once

#include <stdlib.h>
#include "CBase4618.h"
#include "stdafx.h"
#include "CPong.h"
#include "CBase4618.h"

#include <iostream>
#include <string>
#include <conio.h>
#include <thread>

using namespace std;


#define game_width 1000
#define game_height 800
#define ball_x_velocity 250
#define ball_y_velocity 100
#define ball_radius 15
#define max_score 5

/**
*
* @brief Creates the game Pong. Inherits from CBase4618
* 
* A paddle controlled by the Y axis of the MSP's joystick will reflect a bouncing ball.
* One point is awarded when the ball passes by paddle. Game will end after 5 points and pushbutton 1 on MSP
* will reset the score to zero.
*
* @author William Lau
*
*/
class CPong : public CBase4618
{
private:
	int score = 0; ///< Score of AI. Player's score will always be zero
	bool buttonFlag = FALSE; ///< Flag is 1 when pushbutton is pressed
	bool _thread_exit = FALSE;
	cv::Rect paddlePlayer = cv::Rect(0, 0, 10, 100); ///< OpenCV object holding rectangle object of player's paddle
	cv::Rect paddleAI = cv::Rect((game_width-10), 0, 10, 100); ///< OpenCV object holding rectangle object of AI's paddle
	cv::Point p_ball = cv::Point(game_width/2, game_height/2); ///< Coordinate of ball
	cv::Point v_ball = cv::Point(ball_x_velocity, ball_y_velocity); ///< X & Y velocity of ball
	cv::Point2f joystick;  ///< Coordinate from joystick input. Scaled from 0.0-1.0
	enum { DIGITAL = 0, ANALOG = 1, PUSH1 = 33}; ///< emunerators used

public:
/** @brief Constructor. Initalizes comport, OpenCV Mat object, and gets frequency of clock speed
*
* @param portNum The number of the serial comport which is communicating with the MSP432
* @return None
*/
	CPong(int portNum); 
	
/** @brief Gets current value of joystick and state of pushbutton from MSP. Updates player's position
*
* @param None
* @return None
*/
	void CPong::update();

/** @brief Calculates position of ball and AI's paddle and draws to Mat object
*
* Maintains constant framerate and ball velocity by getting processing delay
* Draws ball, player's & AI's paddle, score, and framerate based on ball's position. 
*
* @param None
* @return None
*/
	void CPong::draw();
	
/** @brief Resets the position of the ball and increments AI's score
*
* Resets score to zero if buttonFlag is 1.
*
* @param None
* @return None
*/
	void CPong::reset();
	
/** @brief Freezes ball position and prints "Game Over" 
*
* @param None
* @return None
*/
	void CPong::endgame();

	void CPong::start();
	void CPong::update_thread(CPong* ptr);
	void CPong::run_thread(CPong* ptr);
};