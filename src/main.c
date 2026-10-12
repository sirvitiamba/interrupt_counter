#include "../interrupt_setup/interrupt.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
void app_main() {
    #ifndef task_4
    gpio_setup();
    
    while(1){
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    #endif
    #ifdef task_4
    uint8_t is_pressed=0;
    while(1){
        vTaskDelay(pdMS_TO_TICKS(10));
        is_pressed=gpio_get_level(GPIO_NUM_14);
        if(is_pressed){
            ESP_LOGI("log", "Counter = %u", counter);
        }
    }
    #endif
}