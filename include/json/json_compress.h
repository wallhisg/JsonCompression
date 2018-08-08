#ifndef JSON_COMPRESSION_H
#define JSON_COMPRESSION_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


typedef struct {
    uint8_t block1 : 2; // LSB
    uint8_t block2 : 2;
    uint8_t block3 : 2;
    uint8_t block4 : 2; // MSB
} ByteBlock;

void *coder_block(void *head, void *cursor, int idx);
void *decoder_block(void *head, void *cursor, int idx);
//bool json_compress_grammar();
//bool json_decompress_grammar();

//bool json_compress_ascii();
//bool json_decompress_ascii();

uint8_t json_ascii_coder(char c);
char json_ascii_decoder(uint8_t c);

#endif  //  JSON_COMPRESSION_H
