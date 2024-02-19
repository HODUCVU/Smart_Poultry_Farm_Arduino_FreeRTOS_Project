#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

const boolean checkAssert = false;

void TaskSerial(void *pvParamenters);

void setup() {
    /*
        nếu điều khiện truyền vào configAssert là true thì chương trình sẽ tiếp tục thực thi, còn nếu điều kiện
        là false thì chương trình sẽ thông báo lỗi và dừng lại.
        configASSERT thường được dùng để debug lỗi phát sinh.
    */
   
    Serial.begin(9600);
    xTaskCreate(TaskSerial, "Print", 128, NULL, 0, NULL);
    
}

void loop() {}

void TaskSerial(void *pvParamenters) {
    (void) pvParamenters;
    
    while(!Serial)
    {
        vTaskDelay(1);
    }
    int i = 0;
    while (1)
    {
        Serial.println("executing program");
        vTaskDelay(1000/portTICK_PERIOD_MS);
        configASSERT(i <= 10);
        i++;
    }
}
