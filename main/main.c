#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

// Define the two timers
TimerHandle_t timer1;
TimerHandle_t timer2;

// Common callback function for both timers
void timer_callback(TimerHandle_t xTimer) {
    static int count1 = 0;
    static int count2 = 0;

    if (xTimer == timer1) {
        // Timer 1 callback
        printf("%ld - ahihi\n", pdTICKS_TO_MS(xTaskGetTickCount()));

        count1++;
        if (count1 >= 10) {
            // Stop timer 1 after 10 repetitions
            printf("Timer 1 stop\n");
            xTimerStop(timer1, portMAX_DELAY);
        }
    } else if (xTimer == timer2) {
        // Timer 2 callback
        printf("%ld - ihaha\n", pdTICKS_TO_MS(xTaskGetTickCount()));

        count2++;
        if (count2 >= 5) {
            // Stop timer 2 after 5 repetitions
            printf("Timer 2 stop\n");
            xTimerStop(timer2, portMAX_DELAY);
        }
    }
}

void app_main() {
    // Create timer 1 with a 2-second interval and auto-reload
    timer1 = xTimerCreate("Timer1", pdMS_TO_TICKS(2000), pdTRUE, (void *)1, timer_callback);

    // Create timer 2 with a 3-second interval and auto-reload
    timer2 = xTimerCreate("Timer2", pdMS_TO_TICKS(3000), pdTRUE, (void *)2, timer_callback);

    if (timer1 == NULL || timer2 == NULL) {
        printf("Failed to create timers\n");
        return;
    }

    // Start the timers
    xTimerStart(timer1, portMAX_DELAY);
    printf("%ld - Start Timer1\n", pdTICKS_TO_MS(xTaskGetTickCount()));
    xTimerStart(timer2, portMAX_DELAY);
    printf("%ld - Start Timer2\n", pdTICKS_TO_MS(xTaskGetTickCount()));
}
