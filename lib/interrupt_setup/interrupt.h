#include <stdint.h>
//#define delay() vTaskDelay(pdMS_TO_TICKS(50))//розкоментувати щоб був пункт 2
//#define state 0;//розкоментувати щоб був пункт 3
//#define task_4 1//розкоментувати щоб був пункт 4
extern uint8_t counter;
#ifndef task_4
void log_trigger(void*arg);
void func_for_task(void*arg);
#endif
void gpio_setup();