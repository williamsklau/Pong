#pragma once

#include "CControl.h"
#include "opencv.hpp"

#define msDelay_fps 1000/60

/**
*
* @brief Parent class of CSketch. Holds method run() which calls pure virtual methods update() & draw() when 'q' is not pressed.
*
* Holds OpenCV object _canvas & CControl object. 
*
* @author William Lau
*
*/
class CBase4618
{
protected:
	CControl _msp; ///< Object for serial communication
	cv::Mat _canvas; ///< OpenCV Mat object which holds etchAsketch matrix
	double start_t = 0; ///< Holds the start time of draw(). Used for FPS control and ball velocity control
	double freq; ///< Holds the frequency value of CPU
	double elapsed_t = 0; ///< Holds time of when draw() finishes running. Used for FPS control and ball velocity control

public:
/** @brief pure virtual method which will be implemented by user to update MSP-related data
*
* @param None
* @return None
*/
virtual void update() = 0;

/** @brief pure virtual method which will be implemented by user to draw image on _canvas
*
* @param None
* @return None
*/
virtual void draw() = 0;

/** @brief Calls update() and draw()
*
* @param None
* @return None
*/
void run();
};