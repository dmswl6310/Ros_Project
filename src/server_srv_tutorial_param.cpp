#include <ros/ros.h>
#include <knu_ros_lecture/srvKnuRosLecture.h>

#define PLUS 1
#define MINUS 2
#define MULTIPLICATION 3
#define DIVISION 4

int g_operator = PLUS;

bool calculation(knu_ros_lecture::srvKnuRosLecture::Request& req, knu_ros_lecture::srvKnuRosLecture::Response& res) {
    char operator_ch = '+';

    switch(g_operator) {
        case PLUS:
            res.result = req.a + req.b;
            operator_ch = '+';
            break;
        case MINUS:
            res.result = req.a - req.b;
            operator_ch = '-';
            break;
        case MULTIPLICATION:
            res.result = req.a * req.b;
            operator_ch = '*';
            break;
        case DIVISION:
            if(req.b == 0) res.result = 0;
            else {
                res.result = req.a / req.b;
                operator_ch = '/';
            }
            break;
        default:
            res.result = req.a + req.b;
            break;
    }
    ROS_INFO("request: x = %ld, y = %ld, operation = %c", (long int)req.a, (long int)req.b, operator_ch);
    ROS_INFO("sending back response: [%ld]", (long int)res.result);
    return true;
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "server_srv_param_tutorial");
    ros::NodeHandle nh;
    nh.setParam("calculation_method", g_operator);

    ros::ServiceServer server = nh.advertiseService("knu_ros_lecture_srv_tutorial", calculation);
    ROS_INFO("ready srv server!");
    ros::Rate rate(10);

    while(ros::ok()) {
        nh.getParam("calculation_method",g_operator);
        ros::spinOnce();
        rate.sleep();
    }
    return 0;
}