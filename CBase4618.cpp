#include "stdafx.h"
#include "CBase4618.h"

#include <chrono>
#include <thread>
#include <conio.h>

using namespace std;

void CBase4618::run() {
	
	char quit_ch;

	while (1) {
		// Set update rate
		auto end_time = chrono::system_clock::now() + chrono::milliseconds(msDelay_fps);
		start_t = cv::getTickCount();

		// quits while loop if 'q' is read
		if (kbhit()) {
			quit_ch = getch();
			if (quit_ch == 'q')
				break;


			draw();

			this_thread::sleep_until(end_time);
		}
	}
}