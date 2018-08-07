#ifndef JSON_COMPRESSION_H
#define JSON_COMPRESSION_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool json_compress_ascii();
bool json_decompress_ascii();

char json_ascii_converter(char c);
char json_ascii_inverter(char c);

#endif  //  JSON_COMPRESSION_H
