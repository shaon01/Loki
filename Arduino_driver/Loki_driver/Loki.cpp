#include "Loki.h"

// loki main initialization of pins
Loki::Loki()
{
    pinMode(RightMotorDirPin1, OUTPUT);
    pinMode(RightMotorDirPin2, OUTPUT);
    pinMode(speedPinL, OUTPUT);

    pinMode(LeftMotorDirPin1, OUTPUT);
    pinMode(LeftMotorDirPin2, OUTPUT);
    pinMode(speedPinR, OUTPUT);
    
    pinMode(RightMotorDirPin1B, OUTPUT);
    pinMode(RightMotorDirPin2B, OUTPUT);
    pinMode(speedPinLB, OUTPUT);

    pinMode(LeftMotorDirPin1B, OUTPUT);
    pinMode(LeftMotorDirPin2B, OUTPUT);
    pinMode(speedPinRB, OUTPUT);

      /*init HC-SR04*/
    pinMode(Trig_PIN, OUTPUT); 
    pinMode(Echo_PIN,INPUT);

    stop_Stop();
}

/*motor control*/
void Loki::right_shift(int speed_fl_fwd, int speed_rl_bck, int speed_rr_fwd, int speed_fr_bck)
{
    FL_fwd(speed_fl_fwd);
    RL_bck(speed_rl_bck);
    FR_bck(speed_fr_bck);
    RR_fwd(speed_rr_fwd);
    ;
}
void Loki::left_shift(int speed_fl_bck, int speed_rl_fwd, int speed_rr_bck, int speed_fr_fwd)
{
    FL_bck(speed_fl_bck);
    RL_fwd(speed_rl_fwd);
    FR_fwd(speed_fr_fwd);
    RR_bck(speed_rr_bck);
}
void Loki::go_advance(int speed)
{
    RL_fwd(speed);
    RR_fwd(speed);
    FR_fwd(speed);
    FL_fwd(speed);
}

void Loki::go_advance()
{
    RL_fwd(deafultSpeed);
    RR_fwd(deafultSpeed);
    FR_fwd(deafultSpeed);
    FL_fwd(deafultSpeed);
}

void Loki::go_back(int speed)
{
    RL_bck(speed);
    RR_bck(speed);
    FR_bck(speed);
    FL_bck(speed);
}

void Loki::go_back()
{
    RL_bck(deafultSpeed);
    RR_bck(deafultSpeed);
    FR_bck(deafultSpeed);
    FL_bck(deafultSpeed);
}

void Loki::left_turn(int speed)
{
    RL_bck(0);
    RR_fwd(speed);
    FR_fwd(speed);
    FL_bck(0);
}
void Loki::right_turn(int speed)
{
    RL_fwd(speed);
    RR_bck(0);
    FR_bck(0);
    FL_fwd(speed);
}
void Loki::left_back(int speed)
{
    RL_fwd(0);
    RR_bck(speed);
    FR_bck(speed);
    FL_fwd(0);
}
void Loki::right_back(int speed)
{
    RL_bck(speed);
    RR_fwd(0);
    FR_fwd(0);
    FL_bck(speed);
}

void Loki::clockwise(int speed)
{
    RL_fwd(speed);
    RR_bck(speed);
    FR_bck(speed);
    FL_fwd(speed);
}

void Loki::clockwise()
{
    RL_fwd(deafultSpeed);
    RR_bck(deafultSpeed);
    FR_bck(deafultSpeed);
    FL_fwd(deafultSpeed);
}

void Loki::counterclockwise(int speed)
{
    RL_bck(speed);
    RR_fwd(speed);
    FR_fwd(speed);
    FL_bck(speed);
}

void Loki::counterclockwise()
{
    RL_bck(deafultSpeed);
    RR_fwd(deafultSpeed);
    FR_fwd(deafultSpeed);
    FL_bck(deafultSpeed);
}

void Loki::FR_bck(int speed) //front-right wheel forward turn
{
    digitalWrite(RightMotorDirPin1, LOW);
    digitalWrite(RightMotorDirPin2, HIGH);
    analogWrite(speedPinR, speed);
}
void Loki::FR_fwd(int speed) // front-right wheel backward turn
{
    digitalWrite(RightMotorDirPin1, HIGH);
    digitalWrite(RightMotorDirPin2, LOW);
    analogWrite(speedPinR, speed);
}
void Loki::FL_bck(int speed) // front-left wheel forward turn
{
    digitalWrite(LeftMotorDirPin1, LOW);
    digitalWrite(LeftMotorDirPin2, HIGH);
    analogWrite(speedPinL, speed);
}
void Loki::FL_fwd(int speed) // front-left wheel backward turn
{
    digitalWrite(LeftMotorDirPin1, HIGH);
    digitalWrite(LeftMotorDirPin2, LOW);
    analogWrite(speedPinL, speed);
}

void Loki::RR_bck(int speed) //rear-right wheel forward turn
{
    digitalWrite(RightMotorDirPin1B, LOW);
    digitalWrite(RightMotorDirPin2B, HIGH);
    analogWrite(speedPinRB, speed);
}
void Loki::RR_fwd(int speed) //rear-right wheel backward turn
{
    digitalWrite(RightMotorDirPin1B, HIGH);
    digitalWrite(RightMotorDirPin2B, LOW);
    analogWrite(speedPinRB, speed);
}
void Loki::RL_bck(int speed) //rear-left wheel forward turn
{
    digitalWrite(LeftMotorDirPin1B, LOW);
    digitalWrite(LeftMotorDirPin2B, HIGH);
    analogWrite(speedPinLB, speed);
}
void Loki::RL_fwd(int speed) //rear-left wheel backward turn
{
    digitalWrite(LeftMotorDirPin1B, HIGH);
    digitalWrite(LeftMotorDirPin2B, LOW);
    analogWrite(speedPinLB, speed);
}

void Loki::stop_Stop() //Stop
{
    analogWrite(speedPinLB, 0);
    analogWrite(speedPinRB, 0);
    analogWrite(speedPinL, 0);
    analogWrite(speedPinR, 0);
}

int Loki::getCurrentDistance()
{
    long echo_distance;
    digitalWrite(Trig_PIN, LOW);
    delayMicroseconds(5);
    digitalWrite(Trig_PIN, HIGH);
    delayMicroseconds(15);
    digitalWrite(Trig_PIN, LOW);
    echo_distance = pulseIn(Echo_PIN, HIGH);
    echo_distance = echo_distance * 0.01657; //how far away is the object in cm
                                             //Serial.println((int)echo_distance);
    return round(echo_distance);
}