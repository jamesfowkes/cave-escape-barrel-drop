#include <stdint.h>
#include <string.h>

#include "adl.h"
#include "adl-buffer.h"

#include "adl-oneshot-timer.h"
#include "adl-oneshot-task.h"

#include "http-get-server.h"

static HTTPGetServer s_server(true);

static DigitalOutput * pRelay;
static IntegerParam * pOnTime;

static void relay_delay_task_fn(ADLOneShotTask& pThisTask, void * pTaskData)
{
    (void)pThisTask;
    (void)pTaskData;
    
    pRelay->set(false);
}
static ADLOneShotTask s_relay_delay_task(3000, relay_delay_task_fn, NULL);

static void send_standard_erm_response()
{
    s_server.set_response_code("200 OK");
    s_server.set_header("Access-Control-Allow-Origin", "*");
    s_server.finish_headers();
}

static void relay_open(char const * const url)
{
    (void)url;
    pRelay->set(true);
    s_relay_delay_task.set_period(pOnTime->get() * 1000);
    s_relay_delay_task.start();
    send_standard_erm_response();
}

static http_get_handler s_handlers[] = 
{
    {"/barrel/open", relay_open},
    {"/command/", relay_open},
    {"", NULL}
};

void ethernet_packet_handler(char * req)
{
    s_server.handle_req(s_handlers, req);
}

char * ethernet_response_provider()
{
    return s_server.get_response();
}

void adl_custom_setup(const adl_devices_struct& devices, const adl_params_struct& params)
{
    pRelay = devices.pRelay_Output;
    pOnTime = params.pOn_Time;
}

void adl_custom_loop(const adl_devices_struct& devices, const adl_params_struct& params)
{
    (void)devices; (void)params;
    s_relay_delay_task.run();
}
