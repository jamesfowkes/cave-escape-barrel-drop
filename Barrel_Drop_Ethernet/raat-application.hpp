#ifndef _RAAT_DECLS_H_
#define _RAAT_DECLS_H_


#include "EtherCard.h"



#include "ENC28J60RAAT.hpp"

#include "digital-output.hpp"



#include "integer-param.hpp"


struct _raat_devices_struct
{
    ENC28J60RAAT * pEthernet;
    DigitalOutput * pRelay_Output;
    
    
};
typedef struct _raat_devices_struct raat_devices_struct;

struct _raat_params_struct
{
    IntegerParam<uint16_t> * pOn_Time;
    
    
};
typedef struct _raat_params_struct raat_params_struct;

#endif