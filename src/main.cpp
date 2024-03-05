#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#include <queue.h>

void TaskDisplay(void * pvParamenters);

// Include modules
#include <DHT22.h>
#include <MQ135m.h>
#include <LCD16x2.h>
#include <Fan.h>
#include <Lamp.h>

// init queue for temp and smoke sensor's values
static QueueHandle_t tempReading;
static QueueHandle_t smokeReading; // ppm value
// init task handle for fan and lamp
TaskHandle_t autoFan_handle = NULL;
TaskHandle_t autoLamp_handle = NULL;

/* Init sensors */
// init LCD with I2C
LiquidCrystal_I2C lcd(0x27,16,2);
// Init temp sensor
DHT_Unified dht(DHTPIN, DHTTYPE);
// // Init smoke sensor
MQ135 mq135(PIN_MQ135);

// Init check status
bool autoFan_Status = false;
bool autoLamp_Status = false;
bool smoke_Status = false;

void TaskSerial(void *pvParamenters);
void TaskController(void *pvParamenters);


void setup() {
    Serial.begin(9600);
    Wire.begin();
    
    // Define PIN modes
    pinMode(Lamp, OUTPUT); // Lamp
    pinMode(Fan,OUTPUT); // Fan
    digitalWrite(Lamp, LOW);
    digitalWrite(Fan, LOW);

    // Config LCD
    lcd.init();                      // initialize the lcd 
    // Print a message to the LCD.
    lcd.backlight();
    
    // Begin read temp value
    dht.begin();

    /* Config RTOS tasks */
    // Create queues
    tempReading = xQueueCreate(10, sizeof(int));
    smokeReading = xQueueCreate(10, sizeof(int));
    // Create tasks (6 tasks)
    xTaskCreate(TaskDetectSmoke, "detect smoke", 128*5, NULL, 3, NULL);
    xTaskCreate(TaskTemperatureRead, "Temperature", 128*5, NULL, 3, NULL);
    xTaskCreate(TaskAutoFan, "auto Fan", 128, NULL, 2, &autoFan_handle);
    xTaskCreate(TaskAutoLamp, "auto Lamp", 128, NULL, 2, &autoLamp_handle);
    xTaskCreate(TaskDisplay, "Display on LCD", 128*5, NULL, 1, NULL);
    xTaskCreate(TaskSerial, "Print", 128, NULL, 1, NULL);
    xTaskCreate(TaskController,"controller tasks",128, NULL, 4, NULL);
    // Suspending auto mode tasks at start
    vTaskSuspend(autoFan_handle);
    vTaskSuspend(autoLamp_handle);
}

void loop() {
    lcd.setCursor(0,0);
    lcd.print("Hello, world!");
    lcd.setCursor(0,1);
    lcd.print("Ywrobot Arduino!");

    delay(1000);
    lcd.clear(); 
}

// temperature sensor
void TaskTemperatureRead(void *pvParameters) {

}


void TaskDisplay(void *pvParementers) {

}

void TaskDetectSmoke(void *pvParementers) {

}
void DHT22Detail() {
    sensor_t sensor;
   dht.temperature().getSensor(&sensor); 
}