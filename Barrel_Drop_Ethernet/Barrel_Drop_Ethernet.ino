











/*
Barrel Drop Ethernet
Created on 2019-01-14
By the Arduino Description Language tool.
 

        An ethernet activated relay 
    
*/





#include <stdint.h>

#include "adl.h"


#include <EtherCard.h>



    #include "adl-util-limited-range-int.h"



#include "ENC28J60ADL.h"

#include "digital-output.h"



#include "integer-param.h"



static ENC28J60ADL s_ethernet = ENC28J60ADL();

static DigitalOutput s_relay_output = DigitalOutput(2);


static DeviceBase * s_device_pointers[] = 
{
    
    &s_ethernet
    
    ,
    
    
    &s_relay_output
    
    
};

static const adl_devices_struct adl_devices = {
    
    .pEthernet =  &s_ethernet
    
    ,
    
    
    .pRelay_Output =  &s_relay_output
    
    
};


static IntegerParam s_on_time = IntegerParam(0, 0, INT32_MAX, true, true);


static ParameterBase * s_params_pointers[] = 
{
    
    &s_on_time
    
    
};

static const adl_params_struct adl_params = {
    
    .pOn_Time =  &s_on_time
    
    
};






int handle_device1_command(char const * const command, char * reply)
{
    return s_ethernet.command_handler(command, reply);
}

int handle_device2_command(char const * const command, char * reply)
{
    return s_relay_output.command_handler(command, reply);
}


static COMMAND_HANDLER adl_device_command_handlers[] = {
    
    handle_device1_command,
    
    handle_device2_command,
    
};

COMMAND_HANDLER& adl_get_device_cmd_handler(DEVICE_ADDRESS address)
{
    return adl_device_command_handlers[address-1];
}

DeviceBase& adl_get_device(DEVICE_ADDRESS address)
{
    return *s_device_pointers[address-1];
}


int handle_param1_command(char const * const command, char * reply)
{
    return s_on_time.command_handler(command, reply);
}


static COMMAND_HANDLER adl_param_command_handlers[] = {
    
    handle_param1_command,
    
};

COMMAND_HANDLER& adl_get_param_cmd_handler(PARAM_ADDRESS address)
{
    return adl_param_command_handlers[address-1];
}

ParameterBase& adl_get_param(PARAM_ADDRESS address)
{
    return *s_params_pointers[address-1];
}



void setup()
{
    adl_on_setup_start();

    adl_serial_setup(115200, adl_add_incoming_char);
    
    adl_nonvolatile_setup();

    adl_logging_setup(Serial);

    
    // Setup for Ethernet
    s_ethernet.setup();
    // END Ethernet setup
    
    // Setup for Relay Output
    s_relay_output.setup();
    // END Relay Output setup
    

    
    // Setup for On Time
    s_on_time.setup();
    // END On Time setup
    

    adl_custom_setup(adl_devices, adl_params);

    adl_on_setup_complete();
    
    if (0)
    {
        adl_delay_start( 0 );
    }
}



void loop()
{
    adl_handle_any_pending_commands();
    adl_service_timer();
    adl_custom_loop(adl_devices, adl_params);
}


