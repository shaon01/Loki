#ifndef Loki_h
#define Loki_h

#include "Loki.h"
#include "Arduino.h"

class Loki
{
private:
    int deafultSpeed        = 85;  
    int deafultTrunSpeed    = 90;
    int deafultShiftSpeed   =  130;  

    int TURN_TIME = 500;  
    int MOVE_TIME = 500; 

    int speedPinR = 9;   //  RIGHT WHEEL PWM pin D45 connect front MODEL-X ENA 
    int RightMotorDirPin1 =  22;    //Front Right Motor direction pin 1 to Front MODEL-X IN1  (K1)
    int RightMotorDirPin2 = 24;   //Front Right Motor direction pin 2 to Front MODEL-X IN2   (K1)                                 
    int LeftMotorDirPin1 = 26;    //Left front Motor direction pin 1 to Front MODEL-X IN3 (  K3)
    int LeftMotorDirPin2 = 28;   //Left front Motor direction pin 2 to Front MODEL-X IN4 (  K3)
    int speedPinL = 10;   // Left WHEEL PWM pin D7 connect front MODEL-X ENB

    int speedPinRB = 11;   //  RIGHT WHEEL PWM pin connect Back MODEL-X ENA 
    int RightMotorDirPin1B = 5;    //Rear Right Motor direction pin 1 to Back MODEL-X IN1 (  K1)
    int RightMotorDirPin2B = 6;    //Rear Right Motor direction pin 2 to Back MODEL-X IN2 (  K1) 
    int LeftMotorDirPin1B = 7;    //Rear left Motor direction pin 1 to Back MODEL-X IN3  K3
    int LeftMotorDirPin2B = 8;  //Rear left Motor direction pin 2 to Back MODEL-X IN4  k3
    int speedPinLB = 12;    //   LEFT WHEEL  PWM pin D8 connect Rear MODEL-X ENB

    //ulatra sound pin
    int Echo_PIN  =  31; // Ultrasonic Echo pin connect to A5
    int Trig_PIN  =  30;  // Ultrasonic Trig pin connect to A4
    // private functions for driving actual robot
    void FR_bck(int speed);
    void FR_fwd(int speed);
    void FL_bck(int speed);
    void FL_fwd(int speed);
    void RR_bck(int speed);
    void RR_fwd(int speed);
    void RL_bck(int speed);
    void RL_fwd(int speed);
    
public:
    Loki(/* args */);
    void stop_Stop();
    void right_shift(int speed_fl_fwd,int speed_rl_bck ,int speed_rr_fwd,int speed_fr_bck);
    void left_shift(int speed_fl_bck,int speed_rl_fwd ,int speed_rr_bck,int speed_fr_fwd);
    void go_advance(int speed);
    void go_advance();
    void go_back(int speed);
    void go_back();
    void left_turn(int speed);
    void left_turn();
    void right_turn(int speed);
    void right_turn();
    void left_back(int speed);
    void right_back(int speed);
    void clockwise(int speed);
    void clockwise();
    void counterclockwise(int speed);
    void counterclockwise();
    int getCurrentDistance();

};


#endif