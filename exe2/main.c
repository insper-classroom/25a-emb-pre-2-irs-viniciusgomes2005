#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>
const int BTN_PIN_R = 28;
const int LED = 4;
volatile int flag;
void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    flag = 1;
  } 
}
void update(){
  if(flag ==1){
    printf("PRESSED");
    if(gpio_get(LED)  ){
      printf("TURNING OFF");
      gpio_put(LED, 0);
    }
    else{
      printf("TURNING ON");
      gpio_put(LED,1);
    }

    flag = 0;
  }
}
int main() {
  stdio_init_all();


  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_init(LED);
  gpio_set_dir(LED, GPIO_OUT);
  gpio_pull_up(BTN_PIN_R);

  gpio_set_irq_enabled_with_callback(
    BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);
  while (true) {
    update();
  }
}
