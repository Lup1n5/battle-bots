#ifndef battle_bots_lib_h
#define battle_bots_lib_h
#include <Arduino.h>

class Motor {
public:
    /** @brief Constructor for the Motor class
     *  @param pin The pin number to which the joystick is connected
     *  @param deadzone The deadzone for the joystick input. This is the range of values around the center position of the joystick that will be considered as "no movement". For example, if deadzone is set to 10, then any joystick input between -10 and 10 will be treated as zero input.
     *  @param min_speed The minimum speed for the motor (inclusive between 0-255)
     *  @param max_speed The maximum speed for the motor (inclusive between 0-255)
     */
    Motor(uint8_t pin, uint16_t deadzone, uint8_t min_speed, uint8_t max_speed);
    /** @brief Sets the PWM range for the motor
     *  @param pwmMin The minimum PWM value
     *  @param pwmMax The maximum PWM value
     *  @param pwmCenter The center PWM value
     */
    void setPWMRange(uint16_t pwmMin, uint16_t pwmMax, uint16_t pwmCenter);
    /** @brief Gets the output value for the motor
     *  @return The output value for the motor
     */
    int getOutput();
    /** @brief Gets the joystick value
     *  @return The joystick value
     */
    uint16_t getJoystickValue();
    /** @brief Sets the throttle mode for the motor
     * @param throttleMode The throttle mode for the motor. If true, the motor will be in throttle mode, where the joystick input directly controls the speed of the motor. If false, the motor will be in normal mode, where the joystick input controls the direction and speed of the motor.
     */
    void setThrottleMode(bool throttleMode);
    private:
    uint8_t pin, min_speed, max_speed;
    uint16_t deadzone, pwmMax = 2000, pwmMin = 1000,  pwmCenter = 1500;
    bool throttleMode = false;
};
class Switch {
    public: 
    /** @brief Constructor for switch class.
     *  @param pin pin number for digital input.
     *  @param threeStage whether or not the switch is three stage. False means two stage.
     */
    Switch(uint8_t pin, bool threeStage);
    /** @brief Gives the current switch value. Updates the lastValue variable.
     *  @returns 0 or 1 if two stage and 0, 1, or 2 if three stage.
     */
    uint8_t getValue();
    /** @brief Gives the value that was last given by getValue. If it was never called it is called and then returned.
     *  @returns 0 or 1 if two stage and 0, 1, or 2 if three stage.
     */
    uint8_t getLastValue();
    private:
    uint8_t pin, lastState = 3;
    uint16_t lowLimit = 1200, highLimit = 1800;
    bool threeStage;
};
#endif