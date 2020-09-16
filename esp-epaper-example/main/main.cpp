#include "epaper.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/timer.h"


unsigned long time_start_ms;
unsigned long time_now_s;

#define COLORED     0
#define UNCOLORED   1

extern "C" void app_main() 
{
  Epd epd;

  unsigned char* frame = (unsigned char*)malloc(epd.width * epd.height / 8);
  unsigned char* frame_ = (unsigned char*)malloc(epd.width * epd.height / 8);

  Paint paint(frame, epd.width, epd.height);
  Paint paint_(frame_, epd.width, epd.height);
  paint.Clear(UNCOLORED);
  paint_.Clear(UNCOLORED);

  ESP_LOGI("EPD", "e-Paper init and clear");
  epd.LDirInit();
  epd.Clear();

  // paint.DrawStringAt(10, 10, "hello world", &Font20, COLORED);
  // epd.Display(frame);
  vTaskDelay(2000);
  int d = 3;
  for (char i = '0'; i <= '9'; i++)
  {
    // paint_.Clear(UNCOLORED);
    paint_.DrawCharAt(d, d, i, &Font20, COLORED);
    epd.DisplayPart(frame_);
    // epd.DisplayPart(frame);
    vTaskDelay(100);
    d = d + 20; 
  }
  epd.Sleep();
}

