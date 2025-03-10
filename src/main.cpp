
#include <Arduino.h>
#include <micro_ros_platformio.h>

#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/int16.h>

#define ENCODER1_CA_PIN     23
#define ENCODER1_CB_PIN     22
#define ENCODER2_CA_PIN     19
#define ENCODER2_CB_PIN     18

#define MOTOR1_INA_PIN      4
#define MOTOR1_INB_PIN      21
#define MOTOR2_INA_PIN      25
#define MOTOR2_INB_PIN      26

#define MOTOR1_PWM_PIN      15
#define MOTOR2_PWM_PIN      2

#define LED_PIN             5

#define ENCODER1_RESOLUTION   493
#define ENCODER2_RESOLUTION   493

rcl_allocator_t allocator;
rclc_executor_t executor;
rclc_support_t support;
rcl_timer_t timer;
rcl_node_t node;

rcl_publisher_t encoder1_pub;
rcl_publisher_t encoder2_pub;
rcl_subscription_t control_law1_sub;
rcl_subscription_t control_law2_sub;

std_msgs__msg__Int16 encoder1_msg;
std_msgs__msg__Int16 encoder2_msg;
std_msgs__msg__Int16 motor1_msg;
std_msgs__msg__Int16 motor2_msg;

int16_t encoder1_count = 0;
int16_t encoder2_count = 0;

int16_t motor1_pwm_signal = 0;
int16_t motor2_pwm_signal = 0;

void error_loop() {
  while (1) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));  // Parpadeo LED si hay error
    delay(100);
  }
}

void lower_motor_callback(const void *msgin) {
  const std_msgs__msg__Int16 *msg = (const std_msgs__msg__Int16 *)msgin;
  motor1_pwm_signal = msg->data;

  if (motor1_pwm_signal < 0) {
    digitalWrite(MOTOR1_INA_PIN, HIGH);
    digitalWrite(MOTOR1_INB_PIN, LOW);
  } else {
    digitalWrite(MOTOR1_INA_PIN, LOW);
    digitalWrite(MOTOR1_INB_PIN, HIGH);
  }

  analogWrite(MOTOR1_PWM_PIN, abs(motor1_pwm_signal));
}

void upper_motor_callback(const void *msgin) {
  const std_msgs__msg__Int16 *msg = (const std_msgs__msg__Int16 *)msgin;
  motor2_pwm_signal = msg->data;

  if (motor2_pwm_signal < 0) {
    digitalWrite(MOTOR2_INA_PIN, HIGH);
    digitalWrite(MOTOR2_INB_PIN, LOW);
  } else {
    digitalWrite(MOTOR2_INA_PIN, LOW);
    digitalWrite(MOTOR2_INB_PIN, HIGH);
  }

  analogWrite(MOTOR2_PWM_PIN, abs(motor2_pwm_signal));
}

void timer_callback(rcl_timer_t* timer, int64_t last_call_time) {
  RCLC_UNUSED(last_call_time);
  if (timer != NULL) {
    encoder1_msg.data = (encoder1_count * 360 / ENCODER1_RESOLUTION) % 360;
    encoder2_msg.data = (encoder2_count * 360 / ENCODER2_RESOLUTION) % 360;

    rcl_publish(&encoder1_pub, &encoder1_msg, NULL);
    rcl_publish(&encoder2_pub, &encoder2_msg, NULL);
  }
}

void encoder1_callback() {
  if (digitalRead(ENCODER1_CA_PIN) == digitalRead(ENCODER1_CB_PIN)) {
    encoder1_count++;
  } else {
    encoder1_count--;
  }
}

void encoder2_callback() {
  if (digitalRead(ENCODER2_CA_PIN) == digitalRead(ENCODER2_CB_PIN)) {
    encoder2_count++;
  } else {
    encoder2_count--;
  }
}

void setup() {
  pinMode(ENCODER1_CA_PIN, INPUT_PULLDOWN);
  pinMode(ENCODER1_CB_PIN, INPUT_PULLDOWN);
  pinMode(ENCODER2_CA_PIN, INPUT_PULLDOWN);
  pinMode(ENCODER2_CB_PIN, INPUT_PULLDOWN);

  pinMode(MOTOR1_INA_PIN, OUTPUT);
  pinMode(MOTOR1_INB_PIN, OUTPUT);
  pinMode(MOTOR2_INA_PIN, OUTPUT);
  pinMode(MOTOR2_INB_PIN, OUTPUT);

  pinMode(MOTOR1_PWM_PIN, OUTPUT);
  pinMode(MOTOR2_PWM_PIN, OUTPUT);

  pinMode(LED_PIN, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ENCODER1_CA_PIN), encoder1_callback, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER2_CA_PIN), encoder2_callback, CHANGE);

  Serial.begin(115200);
  set_microros_serial_transports(Serial);

  // Waits until the serial communication is ready and stable
  delay(2000);

  // Iniitalizaes MicroROS in the ESP32
  allocator = rcl_get_default_allocator();
  if (rclc_support_init(&support, 0, NULL, &allocator) != RCL_RET_OK) {
    error_loop();
  }

  // Creates the node
  if (rclc_node_init_default(&node, "motor_driver", "", &support) != RCL_RET_OK) {
    error_loop();
  }

  // Creates the publisher
  rclc_publisher_init_default(&encoder1_pub, &node, ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int16), "lower_encoder");
  rclc_publisher_init_default(&encoder2_pub, &node, ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int16), "upper_encoder");

  // Creates the subscriber
  rclc_subscription_init_default(&control_law1_sub, &node, ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int16), "/lower_motor");
  rclc_subscription_init_default(&control_law2_sub, &node, ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int16), "/upper_motor");

  // Creates the timer the publishes each 1000ms
  rclc_timer_init_default(&timer, &support, RCL_MS_TO_NS(50), timer_callback);

  // Creates the executor to handle the publisher and subscriber
  rclc_executor_init(&executor, &support.context, 4, &allocator);

  // Add the timer to the executor
  rclc_executor_add_timer(&executor, &timer);

  // Agregar el suscriptor al ejecutor
  rclc_executor_add_subscription(&executor, &control_law1_sub, &motor1_msg, &lower_motor_callback, ON_NEW_DATA);
  rclc_executor_add_subscription(&executor, &control_law2_sub, &motor2_msg, &upper_motor_callback, ON_NEW_DATA);
}

void loop() {
  delay(100);
  rclc_executor_spin_some(&executor, RCL_MS_TO_NS(50));
}
