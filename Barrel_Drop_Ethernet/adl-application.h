#ifndef _ADL_DECLS_H_
#define _ADL_DECLS_H_


    
#include "EtherCard.h"
    
#include "ENC28J60ADL.h"
    

    
#include "digital-output.h"
    



    
#include "adl-util-limited-range-int.h"
    
#include "integer-param.h"
    


typedef struct _adl_devices_struct
{
    
    ENC28J60ADL * pEthernet;
    
    DigitalOutput * pRelay_Output;
    
} adl_devices_struct;

typedef struct _adl_params_struct
{
    
    IntegerParam * pOn_Time;
    
} adl_params_struct;

#endif