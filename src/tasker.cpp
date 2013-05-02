#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Header.h"
#include "taskallocator/Request.h"
#include "taskallocator/Bid.h"
#include "taskallocator/Instruction.h"
#include <math.h>
#include <queue>
#include <iostream>
#include <vector>

//std::queue<float> taskQueue;
//float totalTime;
//float lastX;
//float lastY;


ros::Publisher taskPub;



//float getDistance (float startX, float startY, float endX, float endY){
//  return sqrt(pow(endX-startX,2)+pow(endY-startY,2));
//}
	
void processRequest(taskallocator::Request msg){
	/*
	float travelDistance = getDistance(lastX, lastY, msg.startX, msg.startY);
	float taskDistance   = getDistance(msg.startX, msg.startY, msg.endX, msg.endY);
	
	float totalDistance = travelDistance + taskDistance;

	lastX = msg.endX;
	lastY = msg.endY;

	taskQueue.push(totalDistance);
	totalTime+=totalDistance;
	*/
	

	taskallocator::Task task;
	taskallocator::Instruction inst;


	inst.reqsHumanHelp = false;
	inst.helpDescriptor = "";
	
	inst.startFloor = 1;
	inst.startX = msg.startX;
	inst.startY = msg.startY;
	
	inst.endFloor = 1;
	inst.endX = msg.endX;
	inst.endY = msg.endY;

	task.instructions.push_back(inst);

	taskPub.publish(task);

	

	//ROS_INFO("Message type: %s",msg.taskType.c_str());
	//ROS_INFO("Request device %s", msg.requestDevice.c_str());
	//ROS_INFO("Distance - %f ",totalDistance);
	//ROS_INFO("Total Time - %f",totalTime);
	//ROS_INFO("Total Tasks - %d",(int)taskQueue.size());
}

int main (int argc, char **argv) {

	ros::init(argc, argv, "tasker");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe<taskallocator::Request>("requests", 1000, processRequest);
	
	taskPub = n.advertise<taskallocator::Task>("tasks",1000);

	ros::spin();
	return 0;

}
