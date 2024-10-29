
#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class Publisher : public rclcpp::Node
{
  public:
    Publisher(int message_size, double frequency)
    : Node("minimal_publisher"), count_(0), message_size_(message_size)
    {
      strpyload_ = std::string(message_size * 1024, 'a');
      publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
      auto timer_duration = std::chrono::duration<double>(1.0 / frequency); // 1Hz
      timer_ = this->create_wall_timer(
      timer_duration, std::bind(&Publisher::timer_callback, this));
    }

  private:
    void timer_callback()
    {
      auto message = std_msgs::msg::String();
      //std::string strpyload;
      //strpyload.resize(message_size_ * 1024);

      auto time = std::chrono::system_clock::now();
      auto timestamp = std::chrono::duration_cast<std::chrono::nanoseconds>(time.time_since_epoch()).count();  
      message.data = std::to_string(timestamp) + "time is ! " + std::to_string(count_++) + strpyload_;
      RCLCPP_INFO(this->get_logger(), "Publishing: '%d'",count_);
      publisher_->publish(message); 
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    size_t count_;
    size_t message_size_;
    std::string strpyload_;
};

int main(int argc, char * argv[])
{
  int message_size = std::stoi(argv[1]);
  double frequency = std::stoi(argv[2]);
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Publisher>(message_size, frequency));
  rclcpp::shutdown();
  return 0;
}
