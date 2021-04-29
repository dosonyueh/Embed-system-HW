#include "mbed.h"
DigitalOut led1(LED1);
InterruptIn sw(USER_BUTTON);
EventQueue queue(32 * EVENTS_EVENT_SIZE);
Thread t;
Timeout press_threhold;

void button_release_detect()
{
    sw.enable_irq();
}



void button_pressed()
{
    sw.disable_irq();
    press_threhold.attach(&button_release_detect, 1.0);
}

void button_released()
{
    led1 = !led1;
    printf("led status changed!\n");
}


// main() runs in its own thread in the OS
int main()
{
    t.start(callback(&queue, &EventQueue::dispatch_forever));
    printf("Starting in context %p\r\n", ThisThread::get_id());
    sw.fall(&button_pressed);
    sw.rise(queue.event(&button_released));
}
