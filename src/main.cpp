
#include <Arduino.h>
#include <micro_ros_platformio.h>

#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <rcutils/logging_macros.h>

#include <std_msgs/msg/int16_multi_array.h>

#define ENCODER1_CA_PIN   23
#define ENCODER1_CB_PIN   22
#define ENCODER2_CA_PIN   19
#define ENCODER2_CB_PIN   18

#define MOTOR1_INA_PIN    14
#define MOTOR1_INB_PIN    27
#define MOTOR2_INA_PIN    25
#define MOTOR2_INB_PIN    26

#define MOTOR1_PWM_PIN    12
#define MOTOR2_PWM_PIN    13

#define TEST_PIN          34

rcl_publisher_t enconders_publisher;
rcl_subscription_t control_law_subscription;
std_msgs__msg__Int16MultiArray encoders_msg;
std_msgs__msg__Int16MultiArray control_law_msg;

rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rcl_timer_t timer;

volatile int16_t motor1_speed = 0;
volatile int16_t motor2_speed = 0;

volatile int16_t encoder1_count = 0;
volatile int16_t encoder2_count = 0;

int16_t encoders_data[2];

void error_loop();
void encoder1_callback();
void encoder2_callback();
void timer_callback(rcl_timer_t*, int64_t);
void control_law_callback(const void*);

#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}

void setup() {
  // Configure serial transport
  Serial.begin(115200);
  set_microros_serial_transports(Serial);
  delay(2000);

  pinMode(ENCODER1_CA_PIN, INPUT_PULLUP);
  pinMode(ENCODER1_CB_PIN, INPUT_PULLUP);
  pinMode(ENCODER2_CA_PIN, INPUT_PULLUP);
  pinMode(ENCODER2_CB_PIN, INPUT_PULLUP);

  pinMode(MOTOR1_INA_PIN, OUTPUT);
  pinMode(MOTOR1_INB_PIN, OUTPUT);
  pinMode(MOTOR2_INA_PIN, OUTPUT);
  pinMode(MOTOR2_INB_PIN, OUTPUT);

  pinMode(MOTOR1_PWM_PIN, OUTPUT);
  pinMode(MOTOR2_PWM_PIN, OUTPUT);

  pinMode(TEST_PIN, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ENCODER1_CA_PIN), encoder1_callback, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER2_CA_PIN), encoder2_callback, CHANGE);

  allocator = rcl_get_default_allocator();

  // create init_options
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

  // create node
  RCCHECK(rclc_node_init_default(&node, "motor_driver", "", &support));

  // create publisher
  RCCHECK(rclc_publisher_init_default(
    &enconders_publisher,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int16MultiArray),
    "encoders"));

  printf("Encoders publisher is executing!");

  RCCHECK(rclc_subscription_init_default(
    &control_law_subscription,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int16MultiArray),
    "/control_law"));

  printf("Control Law subscriber is executing!");

  // create timer,
  const unsigned int timer_timeout = 100;
  RCCHECK(rclc_timer_init_default(
    &timer,
    &support,
    RCL_MS_TO_NS(timer_timeout),
    timer_callback));

  // create executor
  RCCHECK(rclc_executor_init(&executor, &support.context, 2, &allocator));
  RCCHECK(rclc_executor_add_timer(&executor, &timer));
  RCCHECK(rclc_executor_add_subscription(&executor, &control_law_subscription, &control_law_msg, &control_law_callback, ON_NEW_DATA));
}

void loop() {
  delay(100);
  RCCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
}

// Error handle loop
void error_loop() {
  while(1) {
    delay(100);
  }
}

void timer_callback(rcl_timer_t * timer, int64_t last_call_time) {
  RCLC_UNUSED(last_call_time);
  if (timer != NULL) {
    encoders_msg.data.size = 2;
    encoders_msg.data.capacity = 2;
    encoders_msg.data.data = encoders_data;

    encoders_msg.data.data[0] = encoder1_count;
    encoders_msg.data.data[1] = encoder2_count;

    RCSOFTCHECK(rcl_publish(&enconders_publisher, &encoders_msg, NULL));
  }
}

void control_law_callback(const void* msgin) {
  analogWrite(MOTOR1_PWM_PIN, 125);
  delay(1000);
  analogWrite(MOTOR1_PWM_PIN, 0);
  delay(1000);
  analogWrite(MOTOR1_PWM_PIN, 255);
  delay(1000);
  analogWrite(MOTOR1_PWM_PIN, 0);
  delay(1000);
  // digitalWrite(TEST_PIN, HIGH);

  // std_msgs__msg__Int16MultiArray* msg = (std_msgs__msg__Int16MultiArray*) msgin;

  // RCUTILS_LOG_INFO_NAMED("motor_driver", "Recibido control: [%d, %d]",
  //   control_msg->data.data[0], control_msg->data.data[1]);

  // int16_t motor1_pwm_signal = msg->data.data[0];
  // int16_t motor2_pwm_signal = msg->data.data[1];

  // if (motor1_pwm_signal < 0) {
  //   digitalWrite(MOTOR1_INA_PIN, HIGH);
  //   digitalWrite(MOTOR1_INB_PIN, LOW);
  // } else {
  //   digitalWrite(MOTOR1_INA_PIN, LOW);
  //   digitalWrite(MOTOR1_INB_PIN, HIGH);
  // }

  // if (motor2_pwm_signal < 0) {
  //   digitalWrite(MOTOR2_INA_PIN, HIGH);
  //   digitalWrite(MOTOR2_INB_PIN, LOW);
  // } else {
  //   digitalWrite(MOTOR2_INA_PIN, LOW);
  //   digitalWrite(MOTOR2_INB_PIN, HIGH);
  // }

  // analogWrite(MOTOR1_PWM_PIN, abs(motor1_pwm_signal));
  // analogWrite(MOTOR2_PWM_PIN, abs(motor2_pwm_signal));

  // digitalWrite(TEST_PIN, LOW);
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
