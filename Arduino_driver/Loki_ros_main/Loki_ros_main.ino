/*
 * rosserial PubSub Example
 * Drives the robot in different direction
 */

#include <ros.h>
#include <std_msgs/String.h>
#include <Loki.h>

ros::NodeHandle  nh;
Loki evilLoki = Loki();

// call back function for navigation masage
void lokiDriveDirection( const std_msgs::String& directionMsg);
// creating the subscriber topi with name LokiDriveDirection
ros::Subscriber<std_msgs::String> sub("Loki_drive_direction", lokiDriveDirection );

// Publisher massage 
std_msgs::String str_msg;
ros::Publisher Sensor_value("Distance_sensor", &str_msg);
char hello[13] = "hello world!";

void setup()
{
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.advertise(Sensor_value);
  nh.subscribe(sub);
}

void loop()
{
  str_msg.data = hello;
  Sensor_value.publish( &str_msg );
  nh.spinOnce();
  delay(500);
}

void lokiDriveDirection( const std_msgs::String& directionMsg){
  
  if (strcmp(directionMsg.data, "Forward") == 0)
  {
    evilLoki.go_advance();
    nh.loginfo("Moving Robot Forward");
  }
  else if (strcmp(directionMsg.data, "Backward") == 0) 
  {
    evilLoki.go_back();
    nh.loginfo("Moving Robot Backward");
  }
  else if (strcmp(directionMsg.data, "Left") == 0) 
  {
    evilLoki.counterclockwise();
    nh.loginfo("Moving Robot Left");
  }
  else if (strcmp(directionMsg.data, "Right") == 0)
  {    
    evilLoki.clockwise();
    nh.loginfo("Moving Robot Right");
  }
  else if (strcmp(directionMsg.data, "Stop") == 0) 
  {
    evilLoki.stop_Stop();
    nh.loginfo("Stopping the robot");
  }

  
  nh.loginfo("Got new data");
  nh.loginfo(directionMsg.data);
  
}