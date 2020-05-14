#include "stdafx.h"
#include "CPong.h"
#include "CBase4618.h"

#include <iostream>
#include <string>
#include <conio.h>
#include <thread>

using namespace std;

void CPong::update() {
	_msp.get_joystick(joystick.x, joystick.y);
	
	buttonFlag = _msp.get_button(PUSH1);

	// Compute player position
	paddlePlayer.y = joystick.y * (game_height - paddlePlayer.height) / 100;

	cv::waitKey(1);
}

//// Multi Threading
//void CPong::start() {
//	thread t1(&CPong::update_thread, this);
//	t1.detach();
//}
//
//void CPong::update_thread(CPong* ptr) {
//	while (ptr->_thread_exit == false)
//	{
//		ptr->update();
//	}
//}

void CPong::draw() {
	// Compute ball position
	p_ball += v_ball * elapsed_t;
	cout << "ball = " << p_ball << endl;


	// Collison detection with walls & AI paddle
	if (p_ball.x > (game_width - ball_radius - paddleAI.width)){
		//cout << "wall hit!\n";
		v_ball.x *= -1;
	}
	if (p_ball.y > (game_height - ball_radius) || p_ball.y < ball_radius) {
		v_ball.y *= -1;
	}

	// Collision detection with player paddle
	if ((p_ball.x - ball_radius) < paddlePlayer.width) {		// if ball is on y axis as paddle
		cv::Point ballEdge1 = cv::Point(p_ball.x - ball_radius*0.75, p_ball.y + ball_radius * 1.0);
		cv::Point ballEdge2 = cv::Point(p_ball.x - ball_radius * 0.75, p_ball.y - ball_radius * 1.0);
		cv::Point ballEdge3 = cv::Point(p_ball.x - ball_radius, p_ball.y);
		//cout << "Edge1 = " << ballEdge1 << "\tEdge2 = " << ballEdge2 << "\t Edge3 = " << ballEdge3 << "\tball = " << p_ball << endl;

		if (paddlePlayer.contains(ballEdge1) || paddlePlayer.contains(ballEdge2) || paddlePlayer.contains(ballEdge3)) {
			v_ball.x = ball_x_velocity;
		}
	}

	// Reset game
	if (p_ball.x < 0 || buttonFlag == TRUE) {
		reset();
	}

	// End game
	if(score >= max_score)
		endgame();

	// Compute AI position
	paddleAI.y = (p_ball.y - ball_radius) * (game_height - paddleAI.height + 2*ball_radius) / game_height;


	// Draw objects
	cv::circle(_canvas, p_ball, ball_radius, cv::Scalar(255, 255, 255), cv::FILLED, cv::LINE_AA);
	cv::rectangle(_canvas, paddlePlayer, cv::Scalar(255, 255, 255), cv::FILLED, cv::LINE_AA);
	cv::rectangle(_canvas, paddleAI, cv::Scalar(255, 255, 255), cv::FILLED, cv::LINE_AA);
	cv::putText(_canvas, to_string(score), cv::Point(200, 30), cv::FONT_HERSHEY_SIMPLEX, 0.5, cvScalar(250, 250, 250), 1, CV_AA);
	cv::putText(_canvas, "Score:  0 | ", cv::Point(100, 30), cv::FONT_HERSHEY_SIMPLEX, 0.5, cvScalar(250, 250, 250), 1, CV_AA);

	// Timing control & FPS counter
	elapsed_t = (cv::getTickCount() - start_t) / freq;
	cv::putText(_canvas, to_string(1/elapsed_t), cv::Point(800,30), cv::FONT_HERSHEY_SIMPLEX, 0.5, cvScalar(250, 250, 250), 1, CV_AA);
	cv::imshow("Image", _canvas);
	cv::waitKey(1);

	// Clear screen
	_canvas = cv::Mat::zeros(game_height, game_width, CV_8UC3);

}

CPong::CPong(int portNum) {
	// initiate objects
	_msp.init_com(portNum);
	_canvas = cv::Mat::zeros(game_height, game_width, CV_8UC3);

	freq = cv::getTickFrequency();
}

void CPong::reset() {
	// Reset game
	p_ball = cv::Point(game_width / 2, game_height / 2);
	v_ball = cv::Point(ball_x_velocity, ball_y_velocity);
	score++;
	if (buttonFlag == TRUE) {
		buttonFlag = FALSE;
		score = 0;
	}
	cout << "reset\n";
}

void CPong::endgame() {
	p_ball = cv::Point(500, 500);
	v_ball = cv::Point(0, 0);
	cv::putText(_canvas, "Game Over", cv::Point(300, 400), cv::FONT_HERSHEY_SIMPLEX, 2, cvScalar(250, 250, 250), 1, CV_AA);
}

void CPong::start() {
	thread t1(&CPong::update_thread, this);
	thread t2(&CPong::run_thread, this);
	t1.join();
	t2.join();
}

void CPong::update_thread(CPong* ptr) {
	while (ptr->_thread_exit == false) {
		ptr->update();
	}
	
}

void CPong::run_thread(CPong* ptr) {
	while (ptr->_thread_exit == false) {
		ptr->run();
	}
}