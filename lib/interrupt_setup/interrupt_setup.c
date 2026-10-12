#include "interrupt.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"


TaskHandle_t log_task_handle;
uint8_t counter=0;


#ifndef task_4
void log_trigger(void*arg){
    BaseType_t is_awoken=pdFALSE;
    #ifdef delay
        delay();
    #endif
    #ifdef state
    state=(state+1)%2;
    #endif
    vTaskNotifyGiveFromISR(log_task_handle, &is_awoken);
    if(is_awoken==pdTRUE){
        portYIELD_FROM_ISR();
    }
}

void func_for_task(void*arg){
    while(1){
        #ifdef state
        if(state==1){
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    }
        #endif
        #ifndef state
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        #endif
        counter++;
        ESP_LOGI("required log", "Button state = %u", counter);
        
    }
}
#endif


void gpio_setup(){
    gpio_config_t gpio_input_c={
        .pin_bit_mask=1ULL<<14,
        .mode=GPIO_MODE_INPUT,
        .pull_up_en=GPIO_PULLUP_ENABLE,
        .intr_type=GPIO_INTR_NEGEDGE
    };
    gpio_config(&gpio_input_c);
    #ifndef task_4
    gpio_install_isr_service(0);
    xTaskCreate(func_for_task, "Task for logs", 2048, NULL, 1, &log_task_handle);
    gpio_isr_handler_add(GPIO_NUM_14, log_trigger, NULL);
    gpio_intr_enable(GPIO_NUM_14);
    #endif
    
}