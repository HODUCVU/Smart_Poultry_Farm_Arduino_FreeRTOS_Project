#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#include <queue.h>

int pinReadArray[4] = {0,0,0,0};

void TaskBlink(void *pvParamenters);
void TaskSerial(void *pvParamenters);
void TaskAnalogReadPin(void *pvParamenters);
void TaskDigitalReadPin(void *pvParamenters);

QueueHandle_t arrayQueue;

void setup() {
  // Create a queue
  arrayQueue = xQueueCreate(10, sizeof(int));
  if(arrayQueue!=NULL) {
    xTaskCreate(TaskSerial, "Print result", 128, NULL, 2, NULL);
    xTaskCreate(TaskBlink, "Blink Led", 128, NULL, 0, NULL);
    xTaskCreate(TaskAnalogReadPin, "Read analog sensor", 128, NULL, 1, NULL);
    xTaskCreate(TaskDigitalReadPin, "Read digital sensor", 128, NULL, 1, NULL);
  }
}

void loop() {}

void TaskBlink(void *pvParamenters) {
  (void) pvParamenters;
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  while(1) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    vTaskDelay(500/portTICK_PERIOD_MS);
  }
}
void TaskSerial(void *pvParamenters) {
  (void) pvParamenters;

  //init Serial
  Serial.begin(9600);
  while(!Serial){
    vTaskDelay(1);
  }
  while (1)
  {
    if(xQueueReceive(arrayQueue, &pinReadArray, portMAX_DELAY) == pdPASS) {
      Serial.print("PIN: ");
      Serial.println(pinReadArray[0]);
      Serial.print("value: ");
      Serial.println(pinReadArray[1]);
      Serial.print("PIN: ");
      Serial.println(pinReadArray[2]);
      Serial.print("value: ");
      Serial.println(pinReadArray[3]);
      vTaskDelay(500/portTICK_PERIOD_MS);
    }
  }
}
void TaskAnalogReadPin(void *pvParamenters) {
  (void) pvParamenters;
  while(1) {
    pinReadArray[0] = 0;
    pinReadArray[1] = analogRead(A0);

    // Post an item on a queue;
    // if don't send, then pinReadArray will not update and xQueueReceive with false
    // xQueueSend(arrayQueue, &pinReadArray, portMAX_DELAY);
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}
void TaskDigitalReadPin(void *pvParamenters) {
  (void) pvParamenters;
  while (1){
    pinReadArray[2] = 1;
    pinReadArray[3] = digitalRead(2);
    // Post to queue
    // xQueueSend(arrayQueue, &pinReadArray, portMAX_DELAY);
    vTaskDelay(1);
  }  
}
