#include <stdint.h>
#include <string.h>

#include "raat.hpp"
#include "raat-buffer.hpp"

#include "raat-oneshot-timer.hpp"
#include "raat-oneshot-task.hpp"

#include "http-get-server.hpp"

static HTTPGetServer s_server(true);

static DigitalOutput * pRelay;

static void relay_delay_task_fn(RAATOneShotTask& pThisTask, void * pTaskData)
{
    (void)pThisTask;
    (void)pTaskData;
    
    pRelay->set(false);
}
static RAATOneShotTask s_relay_delay_task(3000, relay_delay_task_fn, NULL);

static void send_standard_erm_response()
{
    s_server.set_response_code("200 OK");
    s_server.set_header("Access-Control-Allow-Origin", "*");
    s_server.finish_headers();
}

static void relay_open(char const * const url)
{

    int32_t timeout;

    char const * const pTime = &url[13];

    bool success = false;

    Serial.println("Got barrel open command");
    
    send_standard_erm_response();

    if ((success = raat_parse_single_numeric(pTime, timeout, NULL)))
    {
        if (timeout < 200) { timeout = 200; }
        timeout = (timeout / 100) * 100;
        pRelay->set(true);
        s_relay_delay_task.set_period(timeout);
        s_relay_delay_task.start();
        s_server.add_body_P(PSTR("OK\r\n\r\n"));
    }
    else
    {
        s_server.add_body_P(PSTR("?\r\n\r\n"));
    }
}

static const char BARREL_OPEN_URL[] PROGMEM = "/barrel/open";

static http_get_handler s_handlers[] = 
{
    {BARREL_OPEN_URL, relay_open},
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

void raat_custom_setup(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)params;
    pRelay = devices.pRelay_Output;
}

void raat_custom_loop(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)devices; (void)params;
    s_relay_delay_task.run();
}
