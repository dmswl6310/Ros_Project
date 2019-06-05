#include <ros/ros.h>
#include <knu_ros_lecture/srvKnuRosLecture.h>

bool calculation(knu_ros_lecture::srvKnuRosLecture::Request& req, knu_ros_lecture::srvKnuRosLecture::Response& res) {
    res.result = req.a + req.b;
    ROS_INFO("request: x = %ld, y = %ld", (long int)req.a, (long int)req.b);
    ROS_INFO("sending back response : [%ld]", (long int)res.result);
    return true;
}
/*
bool calculation2(knu_ros_lecture::srvKnuRosLecture::Request& req, knu_ros_lecture::srvKnuRosLecture::Response& res) {
    res.result = req.a - req.b;
    ROS_INFO("request: x = %ld, y = %ld", (long int)req.a, (long int)req.b);
    ROS_INFO("sending back response : [%ld]", (long int)res.result);
    return true;
}
*/

int main(int argc, char** argv) {
    ros::init(argc, argv, "server_srv_tutorial");
    ros::NodeHandle nh;
    ros::ServiceServer server = nh.advertiseService("knu_ros_lecture_srv_tutorial", calculation);
    // ros::ServiceServer server2 = nh.advertiseService("knu_ros_lecture_srv_tutorial2", calculation2);
    ROS_INFO("ready srv server!");
    ros::spin();
    return 0;
}
