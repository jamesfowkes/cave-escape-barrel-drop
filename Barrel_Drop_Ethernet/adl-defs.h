#ifndef _ADL_DEFS_H_
#define _ADL_DEFS_H_


#define ENC28J60_BUFFER_SIZE 256


#define PROGRAM_MEMORY PROGMEM

enum adl_devices_enum
{
    ADL_DEVICE_BOARD,

    ADL_DEVICE_ETHERNET,

    ADL_DEVICE_RELAY_OUTPUT,

};
typedef enum adl_devices_enum ADL_DEVICES_ENUM;

enum adl_parameters_enum
{

    ADL_PARAM_ON_TIME,

};
typedef enum adl_parameters_enum ADL_PARAMETERS_ENUM;

typedef uint16_t ADL_NV_ADDR;

static const int ADL_DEVICE_COUNT = 2;
static const int ADL_PARAM_COUNT = 1;

static const int ADL_BUFFER_SIZE = 64;

static const unsigned long ADL_TICK_MS = 10;

#endif