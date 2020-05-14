////////////////////////////////////////////////////////////////
// ELEX 4618 Lab 5
////////////////////////////////////////////////////////////////
// ISSUES:
// 
////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include <string>
#include <iostream>
#include <thread>

#include "Client.h"
#include "Server.h"
#include "Serial.h" // Must include Windows.h after Winsock2.h, so Serial must include after Client/Server
#include "CPong.h"

#include <thread>

// OpenCV Include
#include "opencv.hpp"

// OpenCV Library
#pragma comment(lib,".\\opencv\\lib\\opencv_world310d.lib")

//void func1() {
//    for (int n = 0; n < 5; n++) {
//        std::cout << "thread 1\n";
//    }
//}
//void func2() {
//    for (int n = 0; n < 5; n++) {
//        std::cout << "thread 2\n";
//    }
//}

void main(){
    CPong pong(5);
    pong.start();
    
    //while (1) {
    //    std::thread th1(func1);
    //    std::thread th2(func2);
    //    th1.detach();
    //    th2.detach();
    //    Sleep(500);
    //}

}