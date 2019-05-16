#ifndef _RAAT_DEFS_H_
#define _RAAT_DEFS_H_


#define ENC28J60_BUFFER_SIZE 256


#define PROGRAM_MEMORY PROGMEM

enum raat_devices_enum
{
    RAAT_DEVICE_BOARD,

    RAAT_DEVICE_ETHERNET,

    RAAT_DEVICE_RELAY_OUTPUT,

};
typedef enum raat_devices_enum RAAT_DEVICES_ENUM;

enum raat_parameters_enum
{

    RAAT_PARAM_ON_TIME,

};
typedef enum raat_parameters_enum RAAT_PARAMETERS_ENUM;

typedef uint16_t RAAT_NV_ADDR;

static const int RAAT_DEVICE_COUNT = 2;
static const int RAAT_PARAM_COUNT = 1;

static const int RAAT_BUFFER_SIZE = 64;

static const unsigned long RAAT_TICK_MS = 10;

#endif