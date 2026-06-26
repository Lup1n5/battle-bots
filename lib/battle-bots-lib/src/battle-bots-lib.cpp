#include "battle-bots-lib.h"
#include <Arduino.h>

Motor::Motor(int pin, int deadzone, int min_speed, int max_speed)
    : pin(pin), deadzone(deadzone),
      min_speed(constrain(min_speed, 0, 255)),
      max_speed(constrain(max_speed, 0, 255)) {
    pinMode(pin, INPUT);
}

void Motor::setPWMRange(int pwmMin, int pwmMax, int pwmCenter) {
    this->pwmMin = pwmMin;
    this->pwmMax = pwmMax;
    this->pwmCenter = pwmCenter;
}

int Motor::getJoystickValue() {
    return pulseIn(pin, HIGH, 25000);
}

int Motor::getOutput() {
    int pwm = getJoystickValue();
    if (pwm == 0) return 0;  // no signal / timeout

    if (throttleMode) {
        pwm = constrain(pwm, pwmMin, pwmMax);
        return map(pwm, pwmMin, pwmMax, 0, max_speed);
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