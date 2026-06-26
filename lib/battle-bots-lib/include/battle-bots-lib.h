#ifndef battle_bots_lib_h
#define battle_bots_lib_h

class Motor {
public:
    /** @brief Constructor for the Motor class
     *  @param pin The pin number to which the joystick is connected
     *  @param deadzone The deadzone for the joystick input. This is the range of values around the center position of the joystick that will be considered as "no movement". For example, if deadzone is set to 10, then any joystick input between -10 and 10 will be treated as zero input.
     *  @param min_speed The minimum speed for the motor (inclusive between 0-255)
     *  @param max_speed The maximum speed for the motor (inclusive between 0-255)
     */
    Motor(int pin, int deadzone, int min_speed, int max_speed);
    /** @brief Sets the PWM range for the motor
     *  @param pwmMin The minimum PWM value
     *  @param pwmMax The maximum PWM value
     *  @param pwmCenter The center PWM value
     */
    void setPWMRange(int pwmMin, int pwmMax, int pwmCenter);
    /** @brief Gets the output value for the motor
     *  @return The output value for the motor
     */
    int getOutput();
    /** @brief Gets the joystick value
     *  @return The joystick value
     */
    int getJoystickValue();
    /** @brief Sets the throttle mode for the motor
     * @param throttleMode The throttle mode for the motor. If true, the motor will be in throttle mode, where the joystick input directly controls the speed of the motor. If false, the motor will be in normal mode, where the joystick input controls the direction and speed of the motor.
     */
    void setThrottleMode(bool throttleMode);
    private:
    int pin, deadzone, min_speed, max_speed, pwmMax = 2000, pwmMin = 1000,  pwmCenter = 1500;
    bool throttleMode = false;
};
#endif