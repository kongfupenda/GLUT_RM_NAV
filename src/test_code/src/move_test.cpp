#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class node_pub:public rclcpp::Node{
private:
    //步骤一： 声明话题发布者
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr command_publisher_;

    //1、 声名定时器指针
    rclcpp::TimerBase::SharedPtr timer_;

    //3、 定义定时器回调
    void timer_callback()
    {
        // 创建消息
        std_msgs::msg::String message;
        message.data = "forward";
        // 日志打印
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        //步骤三： 发布消息
        command_publisher_->publish(message);
    }
public:
    node_pub(std::string name) : Node(name) //构造函数
    {
        RCLCPP_INFO(this->get_logger(),"%s节点已经启动.", name.c_str());
        //步骤二： 创建发布者
        command_publisher_ = this->create_publisher<std_msgs::msg::String>("command", 10); //队列长度设置10，其余的都扔掉

        //2、 创建定时器，500ms为周期，定时执行回调函数timer_callback
        timer_ = this->create_wall_timer(std::chrono::milliseconds(500), std::bind(&node_pub::timer_callback, this));
    }

};


int main(int argc, char *argv[])
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<node_pub>("topic_publisher_01");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}