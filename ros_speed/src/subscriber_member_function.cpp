#include <memory>
#include <chrono>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
using std::placeholders::_1;

class Subscriber : public rclcpp::Node
{
  public:
    Subscriber(int num)
    : Node("minimal_subscriber"),num_(num)
    {
      subscription_ = this->create_subscription<std_msgs::msg::String>(
      "topic", 10, std::bind(&Subscriber::topic_callback, this, _1));
    }

  private:
    void topic_callback(const std_msgs::msg::String::SharedPtr msg) 
    {
      count_++;
      std::string strtime;
      
      std::string strmessage = msg->data;
      size_t pos = strmessage.find("time");
       if (pos != std::string::npos) {
        strtime = strmessage.substr(0, pos);
      }
      auto msgtime = static_cast<std::time_t>(std::stol(strtime));

      auto time = std::chrono::system_clock::now();
      auto timestamp = std::chrono::duration_cast<std::chrono::nanoseconds>(time.time_since_epoch()).count(); 
      
      auto time_delay = timestamp - msgtime;
      time_ += time_delay;
      auto avg_time = time_ / count_ / 1000;
       RCLCPP_INFO(this->get_logger(), "listen_'%d', time delay is '%ld', now time is '%ld' , average time is '%ld'Us ",num_ ,time_delay, timestamp, avg_time);

    }
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
    int count_ = 0;
    uint64_t time_;
    int num_;
};

int main(int argc, char * argv[])
{
  int num = std::stoi(argv[1]);
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Subscriber>(num));
  rclcpp::shutdown();
  return 0;
}
