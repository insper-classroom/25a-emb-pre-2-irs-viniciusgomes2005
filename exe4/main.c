#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int BTN_PIN_G = 26;
const int LED_R = 4;
const int LED_G = 6;
volatile int FLAG_RED;
volatile int FLAG_GREEN;
void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    if (gpio == BTN_PIN_R){
      FLAG_RED = 1;
    }
    else if (gpio == BTN_PIN_G){
      FLAG_GREEN = 1;
    }
  }
}

void update(){
  if (FLAG_GREEN){
    printf("fall green\n");
    if(gpio_get(LED_G)){
      gpio_put(LED_G,0);
    }else{
      gpio_put(LED_G,1);
    }
    FLAG_GREEN =0 ;
  }
  if (FLAG_RED){
    printf("fall red\n");
    if(gpio_get(LED_R)){
      gpio_put(LED_R,0);
    }else{
      gpio_put(LED_R,1);
    }
    FLAG_RED =0 ;
  }
}
int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);
  gpio_init(LED_G);
  gpio_set_dir(LED_G, GPIO_OUT);
  gpio_init(LED_R);
  gpio_set_dir(LED_R, GPIO_OUT);

  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);

  // callback led r (first)
  gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true,
                                     &btn_callback);

  // callback led g (nao usar _with_callback)
  gpio_set_irq_enabled(BTN_PIN_G, GPIO_IRQ_EDGE_FALL, true);

  while (true) {
    update();
  }
}
