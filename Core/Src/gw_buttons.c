#include "gw_buttons.h"

#include "stm32h7xx_hal.h"
#include "main.h"
#include "odroid_system.h"

#include <stdbool.h>

#if ENABLE_TURBO_BUTTONS == 1
#define TURBO_FREQUENCY_HZ 30

bool is_turbo_high() {
  int turbo_period_ms = 1000 / TURBO_FREQUENCY_HZ;
  return (get_elapsed_time() % turbo_period_ms) < (turbo_period_ms / 2);
}
#endif

uint32_t buttons_get() {
    bool left = HAL_GPIO_ReadPin(BTN_Left_GPIO_Port, BTN_Left_Pin) == GPIO_PIN_RESET;
    bool right = HAL_GPIO_ReadPin(BTN_Right_GPIO_Port, BTN_Right_Pin) == GPIO_PIN_RESET;
    bool up = HAL_GPIO_ReadPin(BTN_Up_GPIO_Port, BTN_Up_Pin) == GPIO_PIN_RESET ;
    bool down = HAL_GPIO_ReadPin(BTN_Down_GPIO_Port, BTN_Down_Pin) == GPIO_PIN_RESET;
    bool a = HAL_GPIO_ReadPin(BTN_A_GPIO_Port, BTN_A_Pin) == GPIO_PIN_RESET;
    bool b = HAL_GPIO_ReadPin(BTN_B_GPIO_Port, BTN_B_Pin) == GPIO_PIN_RESET;
    bool time = HAL_GPIO_ReadPin(BTN_TIME_GPIO_Port, BTN_TIME_Pin) == GPIO_PIN_RESET;
    bool game = HAL_GPIO_ReadPin(BTN_GAME_GPIO_Port, BTN_GAME_Pin) == GPIO_PIN_RESET;
    bool pause = HAL_GPIO_ReadPin(BTN_PAUSE_GPIO_Port, BTN_PAUSE_Pin) == GPIO_PIN_RESET;
    bool power = HAL_GPIO_ReadPin(BTN_PWR_GPIO_Port, BTN_PWR_Pin) == GPIO_PIN_RESET;

#if ENABLE_TURBO_BUTTONS == 1
    a |= HAL_GPIO_ReadPin(BTN_START_GPIO_Port, BTN_START_Pin) == GPIO_PIN_RESET && is_turbo_high();
    b |= HAL_GPIO_ReadPin(BTN_SELECT_GPIO_Port, BTN_SELECT_Pin) == GPIO_PIN_RESET && is_turbo_high();
#else
    game |= HAL_GPIO_ReadPin(BTN_START_GPIO_Port, BTN_START_Pin) == GPIO_PIN_RESET;
    time |= HAL_GPIO_ReadPin(BTN_SELECT_GPIO_Port, BTN_SELECT_Pin) == GPIO_PIN_RESET;
#endif

    return (
        left | (up << 1) | (right << 2) | (down << 3) | (a << 4) | (b << 5) |
        (time << 6) | (game << 7) | (pause << 8) | (power << 9)
    );


}
