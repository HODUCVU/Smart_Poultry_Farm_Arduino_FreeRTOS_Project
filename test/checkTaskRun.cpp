#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

void TaskBlink(void *pvParamenters);
void Task1(void *pvParamenters);
void Task2(void *pvParamenters);

void setup() {
  Serial.begin(115200);
  while(!Serial) {}

  xTaskCreate(TaskBlink,
        "Blink Led",
        128,
        NULL,
        0,
        NULL);

  xTaskCreate(Task1, "Task count 1", 128, NULL, 0, NULL);
  
  xTaskCreate(Task2, "Task count 10", 128, NULL, 0, NULL);
}

void loop() {}

void TaskBlink(void *pvParamenters) {
  (void) pvParamenters;

  pinMode(LED_BUILTIN, OUTPUT);

  while(1){
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void Task1(void *pvParamenters) {
  (void) pvParamenters;
  int i =0;
  while(1) {
    Serial.print("i0 = ");
    Serial.println(i);
    i++;
    Serial.println("i1 = ");
    vTaskDelay(5);
    Serial.println("i2 = ");
    vTaskDelay(5);
    Serial.println("i3 = ");
    vTaskDelay(5);
    Serial.println("i4 = ");
    vTaskDelay(5);
    Serial.println("i5 = ");
    vTaskDelay(5);
    Serial.println("i6 = ");
    vTaskDelay(5);
    Serial.println("i7 = ");
    vTaskDelay(5);
    Serial.println("i8 = ");
    vTaskDelay(5);
    Serial.println("i9 = ");
    vTaskDelay(5);
    Serial.println("i10 = ");
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}
void Task2(void *pvParamenters) {
  (void) pvParamenters;
  int i =0;
  while(1) {
    Serial.print("y0 = ");
    Serial.println(i);
    i += 10;
    Serial.println("y1 = ");
    vTaskDelay(5);
    Serial.println("y2 = ");
    vTaskDelay(5);
    Serial.println("y3 = ");
    vTaskDelay(5);
    Serial.println("y4 = ");
    vTaskDelay(5);
    Serial.println("y5 = ");
    vTaskDelay(5);
    Serial.println("y6 = ");
    vTaskDelay(5);
    Serial.println("y7 = ");
    vTaskDelay(5);
    Serial.println("y8 = ");
    vTaskDelay(5);
    Serial.println("y9 = ");
    vTaskDelay(5);
    Serial.println("y10 = ");
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}
