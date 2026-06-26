#include "battle-bots-lib.h"
#include <Arduino.h>

Motor::Motor(uint8_t pin, uint16_t deadzone, uint8_t min_speed, uint8_t max_speed)
    : pin(pin), deadzone(deadzone),
      min_speed(constrain(min_speed, 0, 255)),
      max_speed(constrain(max_speed, 0, 255)) {
    pinMode(pin, INPUT);
}

void Motor::setPWMRange(uint16_t pwmMin, uint16_t pwmMax, uint16_t pwmCenter) {
    this->pwmMin = pwmMin;
    this->pwmMax = pwmMax;
    this->pwmCenter = pwmCenter;
}

uint16_t Motor::getJoystickValue() {
    return pulseIn(pin, HIGH, 25000);
}

int Motor::getOutput() {
    int pwm = getJoystickValue();
    if (pwm == 0) return 0;  // no signal / timeout

    if (throttleMode) {
        pwm = constrain(pwm, pwmMin, pwmMax);
        return map(pwm, pwmMin, pwmMax, min_speed, max_speed);
    }

    int offset = pwm - pwmCenter;
    if (abs(offset) <= deadzone) return 0;

    int sign = (offset > 0) ? 1 : -1;
    int absOffset = abs(offset) - deadzone;
    int halfRange = (offset > 0) ? (pwmMax - pwmCenter - deadzone)
                                 : (pwmCenter - pwmMin - deadzone);
    int speed = map(absOffset, 0, halfRange, min_speed, max_speed);
    return sign * constrain(speed, min_speed, max_speed);
}

void Motor::setThrottleMode(bool throttleMode) {
    this->throttleMode = throttleMode;
}
Switch::Switch(uint8_t pin, bool threeStage) : pin(pin), threeStage(threeStage) {
    pinMode(pin, INPUT);
}
uint8_t Switch::getValue() {
    int pulse = pulseIn(pin, HIGH, 25000);
    if (threeStage) {
        if (pulse > highLimit) {
            return 2;
        } else if (pulse < lowLimit) {
            return 0;
        } else {
            return 1;
        }
    }
    if (pulse > highLimit) return 1;
    return 0;
}
uint8_t Switch::getLastValue() {
    return (lastState == 3) ? getValue() : lastState;
}
