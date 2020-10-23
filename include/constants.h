/**
 * @file constants.h
 * @author
 * @brief Important constants (configuration) for the project
 * @version 0.1
 * @date 2020-10-23
 *
 * @copyright Copyright (c) 2020
 *
 */

/// timeout for autoswitch (automatically turning off ON/OFF signal for a rely)
#define DEFAULT_AUTOSWTICH_INTERVAL 20 * TASK_SECOND

#define MAIN_VALVE_OPEN     D2
#define MAIN_VALVE_CLOSE    D1
#define DRAIN_VALVE_OPEN    D6 //1 //GPIO01 //Tx
#define DRAIN_VALVE_CLOSE   D7 //3 //GPIO03 //Rx

#define VALUE_FOR_ON        LOW
