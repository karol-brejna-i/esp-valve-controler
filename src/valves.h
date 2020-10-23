#include <Arduino.h>
#include <ts.hpp>

#if !defined(VALVES_CONSTANTS_H)
#define VALVES_CONSTANTS_H 1

#define FOREACH_VALVE_STATE(VALVE_STATE) \
        VALVE_STATE(VS_UNKNOWN)  \
        VALVE_STATE(VS_OPEN)     \
        VALVE_STATE(VS_CLOSED)    \
        VALVE_STATE(VS_OPENING)  \
        VALVE_STATE(VS_CLOSING)

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

enum VALVE_STATE_ENUM {
    FOREACH_VALVE_STATE(GENERATE_ENUM)
};

static const char *VALVE_STATE_STRING[] = {
    FOREACH_VALVE_STATE(GENERATE_STRING)};


/**
 * @brief Encapsulates logic for controling a single valve.
 *
 */
class ValveController : public Task
{
public:
     /// current sate of the valve.
    VALVE_STATE_ENUM state;
    /// previos state of the valve
    VALVE_STATE_ENUM previousState;
    /// last action performed on the object
    String lastAction;
    /// the timestamp of last action
    unsigned long lastActionTimestamp;

    /**
     * @brief Construct a new Valve Controller object
     *
     * @param aS scheduler
     * @param name name of the controlled valve
     * @param gpioOpen the number of GPIO used to open the valve
     * @param gpioClose the number of GPIO used to close the valve
     * @param openingTime for how long "open" signal should be sent to the rely in order for the valve to fully open
     * @param closingTime for how long "close" signal should be sent to the rely in order for the valve to fully close
     * @param valueForOn some setups may require HIGH signal to be sent in order to switch on the rely, others LOW. Use this parameter to configure the behaviour.
     */
    ValveController(Scheduler* aS, String name, int gpioOpen, int gpioClose, unsigned long openingTime, unsigned long closingTime, uint8_t valueForOn);
    ~ValveController() {};

    bool startOpening();
    bool startClosing();
    /// get string representation of the object
    String toString();
    // String autoSwitchTaskToString();
    void setState(VALVE_STATE_ENUM newState);

    /// Get valve name.
    String getName();

    bool Callback();
    bool OnEnable();
    void OnDisable();

private:
    String name;
    int gpioClose;
    int gpioOpen;
    unsigned long openingTime;
    unsigned long closingTime;
    uint8_t valueForOn;

    void markPreviousState(String reason, unsigned long timestamp);

    void finishClosing();
    void finishOpening();

    void switchOn(int pin);
    void switchOff(int pin);

    void startAutoSwitch(unsigned long interval);
};
#endif

extern ValveController* mainValve;
extern ValveController* drainValve;