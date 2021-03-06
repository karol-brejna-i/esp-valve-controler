#include <Arduino.h>
#include <ts.hpp>

#define DEFAULT_AUTOSWTICH_INTERVAL 20 * TASK_SECOND

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

class ValveController : public Task
{
public:
    VALVE_STATE_ENUM state;
    VALVE_STATE_ENUM previousState;
    String lastAction;
    unsigned long lastActionTimestamp;

    ValveController(Scheduler* aS, String name, int gpioOpen, int gpioClose, unsigned long openingTime, unsigned long closingTime);
    ~ValveController() {};

    bool startOpening();
    bool startClosing();
    String toString();
    String autoSwitchTaskToString();
    void setState(VALVE_STATE_ENUM newState);

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

    void markPreviousState(String reason, unsigned long timestamp);

    void finishClosing();
    void finishOpening();

    static void switchOn(int pin);
    static void switchOff(int pin);

    void startAutoSwitch(unsigned long interval);
};
#endif

extern ValveController* mainValve;
extern ValveController* drainValve;