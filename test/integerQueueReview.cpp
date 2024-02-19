#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

// IntegerQueue được dùng để truyền dữ liệu (int) từ một Task đến một/nhiều Task khác một cách an toàn và đồng bộ.
/*
    Nhiệm vụ:
        1. Cung cấp chức năng thêm giá trị vào queue từ một task.
        2. Cung cấp chức năng lấy giá trị ra khỏi queue từ một task khác.
        3.  Đồng bộ hóa dữ liệu trong các task liên quan, ví dụ một task có thể đợi cho đến khi 
            integerQueue không rỗng trước khi lấy dữ liệu ra khỏi hàng đợi, giúp đảm bảo rằng dữ liệu 
            sẽ chỉ được xử lý khi nó có sẵn.
        4. Nó có chức năng đồng bộ hóa dữ liệu tương tự như mutex, semaphore.

*/
#include <queue.h>

QueueHandle_t integerQueue;

void TaskSerial(void *pvParamenters);
void TaskAnalogRead(void *pvParamenters);
void TaskBlink(void *pvParamenters);

void setup() {
    // Create queue
    integerQueue = xQueueCreate(10, sizeof(int));

    if(integerQueue != NULL) {
        xTaskCreate(TaskSerial, "Print", 128, NULL, 2, NULL);

        xTaskCreate(TaskAnalogRead, "AnalogRead", 128, NULL, 1, NULL);
        
        xTaskCreate(TaskBlink, "blink", 128, NULL, 0, NULL);
    }
}

void loop() {}

void TaskSerial(void *pvParamenters) {
    (void) pvParamenters;

    Serial.begin(9600);
    while(!Serial){ vTaskDelay(1);}
    int valueFromQueue = 0;
    while(1) {
        //check queue rỗng
        // if(uxQueueMessagesWaiting(integerQueue) > 0) {
            if(xQueueReceive(integerQueue, &valueFromQueue, portMAX_DELAY) == pdPASS) {
                Serial.println(valueFromQueue);
            }
        // }
    }
}
void TaskAnalogRead(void *pvParamenters) {
    (void) pvParamenters;

    int i = 0;
    while(1) {
        i+=3;
        xQueueSend(integerQueue, &i, portMAX_DELAY);
        vTaskDelay(500/portTICK_PERIOD_MS);
    }
}

void TaskBlink(void *pvParamenters) {
    (void) pvParamenters;

    pinMode(LED_BUILTIN, OUTPUT);

    while(1) {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        vTaskDelay(500/portTICK_PERIOD_MS);
    }
}
