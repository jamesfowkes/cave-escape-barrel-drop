#ifndef _RAAT_UTIL_H_
#define _RAAT_UTIL_H_

typedef struct
{
    char * buffer;
    uint16_t max_size;
} raat_string_buffer;

bool raat_convert_numeric_range(char const * const range, int32_t& min, int32_t& max, char ** pend);
bool raat_parse_single_numeric(char const * const numeric, int32_t& parsed, char ** pend);
uint8_t raat_parse_comma_separated_numerics(char const * const s, int32_t * presults);
char nibble_to_hex(uint8_t b);
void byte_to_hex(char * buffer, uint8_t b);

#endif