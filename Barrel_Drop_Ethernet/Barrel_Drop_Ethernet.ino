











/*
Barrel Drop Ethernet
Created on 2019-05-16
By the Rapid Arduino Application Tool.

RAAT Repo Info: Branch: master, SHA: a109eefd (repo is dirty)


        An ethernet activated relay 
    
*/





#include <stdint.h>

#include "raat.hpp"


#include <EtherCard.h>



    #include "raat-util-limited-range-int.hpp"



#include "ENC28J60RAAT.hpp"

#include "digital-output.hpp"



#include "integer-param.hpp"



static ENC28J60RAAT s_ethernet = ENC28J60RAAT(10);

static DigitalOutput s_relay_output = DigitalOutput(2);


static DeviceBase * s_device_pointers[2] =
{
    &s_ethernet,
    &s_relay_output
    
};

static const raat_devices_struct raat_devices = {
    
    .pEthernet =  &s_ethernet,
    
    .pRelay_Output =  &s_relay_output,
    

    
};


static IntegerParam<uint16_t> s_on_time = IntegerParam<uint16_t>(0, 0, UINT16_MAX, true, true);


static ParameterBase * s_params_pointers[1] =
{
    &s_on_time
    
};

static const raat_params_struct raat_params = {
    .pOn_Time = &s_on_time,
    

    
};






int handle_device1_command(char const * const command, char * reply)
{
    return s_ethernet.command_handler(command, reply);
}

int handle_device2_command(char const * const command, char * reply)
{
    return s_relay_output.command_handler(command, reply);
}


static COMMAND_HANDLER raat_device_command_handlers[] = {
    
    handle_device1_command,
    
    handle_device2_command,
    
};

COMMAND_HANDLER& raat_get_device_cmd_handler(DEVICE_ADDRESS address)
{
    return raat_device_command_handlers[address-1];
}

DeviceBase& raat_get_device(DEVICE_ADDRESS address)
{
    return *s_device_pointers[address-1];
}


int handle_param1_command(char const * const command, char * reply)
{
    return s_on_time.command_handler(command, reply);
}


static COMMAND_HANDLER raat_param_command_handlers[] = {
    
    handle_param1_command,
    
};

COMMAND_HANDLER& raat_get_param_cmd_handler(PARAM_ADDRESS address)
{
    return raat_param_command_handlers[address-1];
}

ParameterBase& raat_get_param(PARAM_ADDRESS address)
{
    return *s_params_pointers[address-1];
}



void setup()
{
    raat_on_setup_start();

    raat_serial_setup(115200, raat_add_incoming_char);

    raat_nonvolatile_setup();

    raat_logging_setup(Serial);

    
    // Setup for Ethernet
    s_ethernet.setup();
    // END Ethernet setup
    
    // Setup for Relay Output
    s_relay_output.setup();
    // END Relay Output setup
    

    
    // Setup for On Time
    s_on_time.setup();
    // END On Time setup
    

    raat_custom_setup(raat_devices, raat_params);

    raat_on_setup_complete();

    if (0)
    {
        raat_delay_start( 0 );
    }
}



void loop()
{
    raat_handle_any_pending_commands();
    raat_service_timer();
    raat_custom_loop(raat_devices, raat_params);
}


