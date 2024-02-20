#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#include <semphr.h>
/*
    Semaphore không truyền dữ liệu giữa các task như một cơ chế giao tiếp, 
    mà nó được sử dụng để đồng bộ hóa và đảm bảo truy cập an toàn vào tài nguyên được chia sẻ giữa các task trong một hệ thống.
*/
SemaphoreHandle_t interruptSemaphore;

void TaskLed(void *pvParamenters);
void interruptHandler();


/*
    Mutex (Mutual Exclusion) là một loại semaphore đặc biệt được sử dụng trong các hệ thống nhúng
    để đảm bảo rằng chỉ một task có thể truy cập vào một tài nguyên cụ thể tại một thời điểm. 
    Mục tiêu của mutex là ngăn chặn sự đối đầu (contention) và đảm bảo tính nhất quán của dữ liệu trong khi nhiều task cùng truy cập vào tài nguyên đó.
*/
SemaphoreHandle_t mutex;
int count = 0;

void TaskCountMutex(void *pvParamenters);

void setup() {

    Serial.begin(9600);

    pinMode(2, INPUT_PULLUP);

    xTaskCreate(TaskLed, "LED", 128, NULL, 0, NULL);

    // Create binary semephore
    interruptSemaphore = xSemaphoreCreateBinary();
    if (interruptSemaphore != NULL) {
        attachInterrupt(digitalPinToInterrupt(2), interruptHandler, LOW);
    }

    //Create mutex;
    mutex = xSemaphoreCreateMutex();
    if(mutex != NULL)
        Serial.println("Mutex is created!");
    
    xTaskCreate(TaskCountMutex, "Task1", 128, NULL, 1, NULL);
    
    xTaskCreate(TaskCountMutex, "Task2", 128, NULL, 1, NULL);
}

void loop() {}

void TaskLed(void *pvParamenters) {
    (void) pvParamenters;

    pinMode(LED_BUILTIN, OUTPUT);

    while (1)
    {
        // Receive data from semaphore
        if(xSemaphoreTake(interruptSemaphore, portMAX_DELAY) == pdPASS) {
            digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        }
        vTaskDelay(10);
    }
    
}
void interruptHandler() {
    // Give semaphore in the interrupt handler

    xSemaphoreGiveFromISR(interruptSemaphore, NULL);
}

void TaskCountMutex(void *pvParamenters) {
    (void) pvParamenters;
    
    while(1) {
        if(xSemaphoreTake(mutex,10) ==pdTRUE) {
            Serial.print(pcTaskGetName(NULL));
            Serial.print(", count read value: ");
            Serial.println(count);

            count++;

            Serial.println("Updated count");

            xSemaphoreGive(mutex);
        }
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
