#include "led_control.h"

#include "pinout.h"
#include "led.h"
#include "timer.h"
#include "zwave_encoding.h"
#include "settings.h"

static LedClass LED0(PIN_LED_R1, PIN_LED_G1, PIN_LED_B1);
static LedClass LED1(PIN_LED_R2, PIN_LED_G2, PIN_LED_B2);
static LedClass LED2(PIN_LED_R3, PIN_LED_G3, PIN_LED_B3);

static TimerClass BLINK_TIMER(LED_BLINK_PERIOD);
static TimerClass FLASH_TIMER(LED_FLASH_PERIOD);
static TimerClass ANIMATION_TIMER(LED_ANIMATION_STEP_PERIOD);
static TimerClass TEMP_CHANGE_TIMER(LED_ANIMATION_TOTAL_PERIOD);

bool ledBlinkState = false;
byte flashColor = COLOR_BLACK;
byte flashCounter = 0;
int animationDirection = 0;
int animationIndex = 0;
float lastTemp = SensorTemperature;
byte flashQueueSize = 0;
byte flashQueue[FLASH_QUEUE_LEN];
byte ledColors[LED_COUNT];


void FlashEnqueue(byte color)
{
    if (flashQueueSize < FLASH_QUEUE_LEN) {
        flashQueue[flashQueueSize] = color;
        flashQueueSize++;
    }
}

byte FlashDequeue()
{
    byte color = flashQueue[0];
    flashQueueSize--;
    for (byte i = 0; i < FLASH_QUEUE_LEN; i++) {
        if (i < flashQueueSize)
            flashQueue[i] = flashQueue[i + 1];
        else
            flashQueue[i] = COLOR_BLACK;
    }
    return color;
}

void DoFlash(byte color)
{
    FLASH_TIMER.Start();
    flashCounter = FLASHES;
    flashColor = color;
}

/**
 * @brief Controls LED animation
 * 
 * @param direction 0=off, -1=down, 1=up
 * @param period millis between each frame of the animation
 */
void StartAnimation(int direction, int period)
{
    if (animationDirection == direction && ANIMATION_TIMER.DurationInMillis == period) return;
    animationDirection = direction;
    ANIMATION_TIMER.DurationInMillis = period;
    if (animationDirection != 0) {
        ANIMATION_TIMER.Start();
    }
}




void LedsSetFlash(byte color)
{
    FlashEnqueue(color);
}

void LedsSetBlinkingState()
{
    bool state = CurrentBoilerState;
    if (BLINK_TIMER.IsActive != state) {
        BLINK_TIMER.IsActive = state;
        if (BLINK_TIMER.IsActive)
            BLINK_TIMER.Start();
    }
}

/**
* @brief Set the LED animation according to temperature change
*
*/
void LedsSetAnimationState()
{
    if (TEMP_CHANGE_TIMER.IsElapsedRestart()) {
        Prm.TempDelta = SensorTemperature - lastTemp;
        if (Prm.TempDelta != 0) {
            int period = LED_ANIMATION_MIN_PERIOD / abs(Prm.TempDelta);
            if (period < LED_ANIMATION_MIN_PERIOD) period = LED_ANIMATION_MIN_PERIOD;
            if (period > LED_ANIMATION_MAX_PERIOD) period = LED_ANIMATION_MAX_PERIOD;
            StartAnimation(Prm.TempDelta > 0 ? 1 : -1, period);
        }
        else
            StartAnimation(0, LED_ANIMATION_STEP_PERIOD);
        lastTemp = SensorTemperature;
    }
}

/**
* @brief Set each LED's color according to implemented behaviours
*
*/
void LedsDrawAll()
{
    byte ledColor = COLOR_BLACK;

    if (Prm.IlluminationPower) {
        // Toggle boiler blink
        if (BLINK_TIMER.IsActive && BLINK_TIMER.IsElapsedRestart()) {
            ledBlinkState = !ledBlinkState;
            if (ledBlinkState)
                LedsSetFlash(BOILER_BLINK_COLOR);
        }

        // Set base color according to mode
        ledColor = ColorsByMode[byte(Prm.CurrentThermostatMode)];

        // Flash LED
        if (!FLASH_TIMER.IsActive && flashQueueSize > 0) {
            DoFlash(FlashDequeue());
        }
        if (flashCounter > 0) {
            if (FLASH_TIMER.IsElapsed()) {
                flashCounter--;
                if (flashCounter > 0)
                    FLASH_TIMER.Start();
            }
            if (flashCounter == FLASHES - 1)
                ledColor = flashColor;
            else
                ledColor = COLOR_BLACK;
        }
    }

    // Draw animations
    for (byte i = 0; i < LED_COUNT; i++)
        ledColors[i] = ledColor;

    if (animationDirection != 0) {
        if (ANIMATION_TIMER.IsElapsedRestart()) {
            animationIndex += animationDirection;
            if (animationIndex < 0)
                animationIndex = LED_COUNT;
            if (animationIndex > LED_COUNT)
                animationIndex = 0;
        }
        if (animationIndex > 0)
            ledColors[animationIndex - 1] = COLOR_BLACK;
    }

    LED0.DisplayColor(ledColors[0]);
    LED1.DisplayColor(ledColors[1]);
    LED2.DisplayColor(ledColors[2]);
}
