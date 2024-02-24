#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// Sensor PIN Define
#define DHTPIN 2    // DHT22 temperature sensor
#define DHTTYPE DHT22

// static QueueHandle_t tempReading;

void TaskTemperatureRead(void *pvParamenters);