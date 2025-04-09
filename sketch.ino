#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>

const int LED_PIN = 13;
const int BUTTON_PIN = 2;

volatile bool isAwake = true;

void onButtonPress() {
    isAwake = true;
}

ISR(WDT_vect) {
    isAwake = true;
}

void setup() {
    Serial.begin(5000);
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onButtonPress, FALLING);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

void loop() {
    digitalWrite(LED_PIN, HIGH);
    delay(5000);
    digitalWrite(LED_PIN, LOW);

    Serial.println("Enters sleep...");
    setupWatchdogTimer();
    enterSleepMode();
    Serial.println("Wakes up");
}

void enterSleepMode() {
    noInterrupts();
    isAwake = false;

    sleep_enable();
    interrupts();
    sleep_cpu();

    while (!isAwake) {}

    sleep_disable();
}

void setupWatchdogTimer() {
    cli();
    wdt_reset();

    WDTCSR = (1 << WDCE) | (1 << WDE);
    WDTCSR = (1 << WDIE) | (1 << WDP3);

    sei();
}
