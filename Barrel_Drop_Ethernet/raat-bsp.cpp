#include <EEPROM.h>

#include "raat.hpp"


    #include "raat-util-limited-range-int.hpp"


int raat_board_strcpy_progmem(char * const pMemoryDst, char const * const pProgmemSrc)
{
    return(strlen(strcpy_P(pMemoryDst, pProgmemSrc)));
}

int raat_board_memcmp_progmem(char * const pMemory, char const * const pProgmem, size_t len)
{
    return memcmp_P(pMemory, pProgmem, len);
}

int raat_board_strcmp_progmem(char * const pMemory, char const * const pProgmem)
{
    return strcmp_P(pMemory, pProgmem);
}

int raat_board_strncmp_progmem(char * const pMemory, char const * const pProgmem, size_t len)
{
    return strncmp_P(pMemory, pProgmem, len);
}

int raat_board_strlen_progmem(char const * const pProgmem)
{
	return strlen_P(pProgmem);
}

uint16_t raat_board_max_adc_reading()
{
	return 1023U;
}