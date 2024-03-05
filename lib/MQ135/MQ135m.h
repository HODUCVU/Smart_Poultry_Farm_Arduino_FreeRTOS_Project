#include <MQ135.h>

#define PIN_MQ135 16 // A0

// static QueueHandle_t smokeAlarm;

// Kết hợp với DHT22 để lấy nồng độ ppm của khí độc trong không khí
void TaskDetectSmoke(void *pvParamenters);