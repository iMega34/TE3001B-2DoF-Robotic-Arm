
#include <Arduino.h>
#include <micro_ros_platformio.h>

#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/int16_multi_array.h>

#define ENCODER1_CA_PIN   23
#define ENCODER1_CB_PIN   22
#define ENCODER2_CA_PIN   19
#define ENCODER2_CB_PIN   18

#define MOTOR1_INA_PIN    4
#define MOTOR1_INB_PIN    21
#define MOTOR2_INA_PIN    25
#define MOTOR2_INB_PIN    26

#define MOTOR1_PWM_PIN    15
#define MOTOR2_PWM_PIN    2

#define LED_PIN 5

rcl_allocator_t allocator;
rclc_executor_t executor;
rclc_support_t support;
rcl_node_t node;

rcl_timer_t timer;
rcl_publisher_t encoders_pub;
rcl_subscription_t control_law_sub;

std_msgs__msg__Int16MultiArray encoders_msg;
int16_t encoders_data[2] = {0, 0};

std_msgs__msg__Int16MultiArray control_law_msg;
int16_t control_law_data[2] = {0, 0};

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

void subscription_callback(const void *msgin) {
  const std_msgs__msg__Int16MultiArray *msg = (const std_msgs__msg__Int16MultiArray *)msgin;

  control_law_data[0] = msg->data.data[0];
  control_law_data[1] = msg->data.data[1];

  motor1_pwm_signal = msg->data.data[0];
  motor2_pwm_signal = msg->data.data[1];

  if (motor1_pwm_signal < 0) {
    digitalWrite(MOTOR1_INA_PIN, HIGH);
    digitalWrite(MOTOR1_INB_PIN, LOW);
  } else {
    digitalWrite(MOTOR1_INA_PIN, LOW);
    digitalWrite(MOTOR1_INB_PIN, HIGH);
  }

  if (motor2_pwm_signal < 0) {
    digitalWrite(MOTOR2_INA_PIN, HIGH);
    digitalWrite(MOTOR2_INB_PIN, LOW);
  } else {
    digitalWrite(MOTOR2_INA_PIN, LOW);
    digitalWrite(MOTOR2_INB_PIN, HIGH);
  }

  analogWrite(MOTOR1_PWM_PIN, abs(motor1_pwm_signal));
  analogWrite(MOTOR2_PWM_PIN, abs(motor2_pwm_signal));
}

void timer_callback(rcl_timer_t* timer, int64_t last_call_time) {
  RCLC_UNUSED(last_call_time);
  if (timer != NULL) {
    encoders_msg.data.data = encoders_data;
    encoders_msg.data.size = 2;
    encoders_msg.data.capacity = 2;

    rcl_publish(&encoders_pub, &encoders_msg, NULL);
  }
}

void encoder1_callback() {
  if (digitalRead(ENCODER1_CA_PIN) == digitalRead(ENCODER1_CB_PIN)) {
    encoders_data[0] = encoder1_count++;
  } else {
    encoders_data[0] = encoder1_count--;
  }
}

void encoder2_callback() {
  if (digitalRead(ENCODER2_CA_PIN) == digitalRead(ENCODER2_CB_PIN)) {
    encoders_data[1] = encoder2_count++;
  } else {
    encoders_data[1] = encoder2_count--;
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
  Serial.println("Starting MicroROS in the ESP32...");  

  // Iniitalizaes MicroROS in the ESP32
  allocator = rcl_get_default_allocator();
  if (rclc_support_init(&support, 0, NULL, &allocator) != RCL_RET_OK) {
    Serial.println("[ERROR] Can't start Micro-ROS.");
    error_loop();
  }

  // Creates the node
  if (rclc_node_init_default(&node, "motor_driver", "", &support) != RCL_RET_OK) {
    Serial.println("[ERROR] Can't create the node.");
    error_loop();
  }

  encoders_msg.data.data = encoders_data;
  encoders_msg.data.size = 2;
  encoders_msg.data.capacity = 2;

  // Creates the publisher
  if (rclc_publisher_init_default(
    &encoders_pub, &node, ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int16MultiArray), "encoders"
  ) != RCL_RET_OK ) {
    Serial.println("[ERROR] Can't start the publisher.");
    error_loop();
  }

  control_law_msg.data.data = control_law_data;
  control_law_msg.data.size = 2;
  control_law_msg.data.capacity = 2;

  if (rclc_subscription_init_default(
    &control_law_sub, &node, ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int16MultiArray), "control_law"
  ) != RCL_RET_OK) {
    Serial.println("[ERROR] Can't start the subscriber.");
    error_loop();
  }

  // Creates the timer the publishes each 1000ms
  if (rclc_timer_init_default(
      &timer, &support, RCL_MS_TO_NS(50), timer_callback
  ) != RCL_RET_OK) {
    Serial.println("[ERROR] Can't start the timer.");
    error_loop();
  }

  // Creates the executor to handle the publisher and subscriber
  if (rclc_executor_init(&executor, &support.context, 2, &allocator) != RCL_RET_OK) {
    Serial.println("[ERROR] Can't start the executor.");
    error_loop();
  }

  // Add the timer to the executor
  if (rclc_executor_add_timer(&executor, &timer) != RCL_RET_OK) {
      Serial.println("[ERROR] Can't add the timer to the executor");
      error_loop();
  }

  // Agregar el suscriptor al ejecutor
  if (rclc_executor_add_subscription(
    &executor, &control_law_sub, &control_law_msg, &subscription_callback, ON_NEW_DATA
  ) != RCL_RET_OK) {
    Serial.println("[ERROR] Can't add the subscriber to the executor.");
    error_loop();
  }

  Serial.println("Micro-ROS started successfully.");
}

void loop() {
  delay(100);
  rcl_ret_t ret = rclc_executor_spin_some(&executor, RCL_MS_TO_NS(50));
  if (ret != RCL_RET_OK) {
      Serial.print("[ERROR] Executor failed: ");
      Serial.println(ret);
  }
}
