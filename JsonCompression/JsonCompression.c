#include <string.h>
#include <stdlib.h>
#include "JsonCompression.h"
#include <json/json_compress.h>

#define JSON_CODE_LENGTH    47
#define JSON_ASCII_LENGTH   126

void test_json_ascii_converter()
{
    printf("JSON_TEST_CONVERT\r\n");
    char byte;
    uint8_t c[JSON_CODE_LENGTH];

    int i = 0;
    int j = 0;
    // print ascii invert
    for(i = 0; i < JSON_ASCII_LENGTH; ++i)
    {
        byte = json_ascii_coder(i);
        if(byte != '\0')
        {
            c[j++] = byte;
        }
    }
    for(i = 0; i < JSON_CODE_LENGTH; ++i)
    {
        if(byte != '\0')
        {
//            byte = json_ascii_converter(c[i]);
            printf("idx: %d - code %d - decode %c\r\n", i, c[i], json_ascii_decoder(c[i]));

        }
    }
}

void test_json_ascii_inverter()
{
    printf("JSON_TEST_INVERT\r\n");
    char c[JSON_CODE_LENGTH];
    char byte;

    // init ascii by number
    int i = 0;
    for(i = 0; i < JSON_CODE_LENGTH; ++i)
    {
        c[i] = i;
    }
    // print ascii invert
    for(i = 0; i < JSON_CODE_LENGTH; ++i)
    {
        byte = json_ascii_decoder(c[i]);
        if(byte != '\0')
        {
            printf("code %d - decode: %c\r\n", c[i], byte);
        }
    }
}

void test_coder_block(char *c)
{
    int len = strlen(c) + 1;
    char *inBuff = (char*)malloc(len * sizeof(char));
    memcpy(inBuff, c, len);
    char *cursor = inBuff;
    
    char *outBuff = (char*)malloc(len * sizeof(char));
    memset(outBuff, 0, len);
    char *head = outBuff;
    
    printf("HEAD: %p\r\n", head);
    printf("CODER BLOCK:\r\n");

    int i = 0;
    for(i = 0; i < len; ++i, ++cursor)
    {
//        printf("IDX: %d - HEAD %p - CURSOR %p\r\n", i, head, cursor);
        head = coder_block(head, cursor, i);
    }

//    printf("HEAD: %p\r\n", head);
    printf("BUFF\r\n");
    len = strlen(outBuff);
    for(i = 0; i < len; ++i)
    {
        printf("BUFF[%d]: %02x \r\n", i, (unsigned char)outBuff[i]);
    }
}

void test_decoder_block(char *c)
{
    int len = strlen(c) + 1;
    char *inBuff = (char*)malloc(len * sizeof(char));
    memcpy(inBuff, c, len);
    char *cursor = inBuff;
    
    char *outBuff = (char*)malloc(len * sizeof(char));
    memset(outBuff, 0, len);
    char *head = outBuff;
    
//    printf("HEAD: %p\r\n", head);
    printf("DECODER BLOCK:\r\n");
    int i = 0;
    for(i = 0; i < len; ++i, ++cursor)
    {
//        printf("IDX: %d - HEAD %p - CURSOR %p\r\n", i, head, cursor);
        /*head = */decoder_block(head, cursor, i);
    }

    printf("HEAD: %s\r\n", head);
//    printf("BUFF\r\n");
//    len = strlen(outBuff);
//    for(i = 0; i < len; ++i)
//    {
////        printf("BUFF[%d]: %02x \r\n", i, (unsigned char)outBuff[i]);
//    }
}
int main(int argc, char **argv)
{
//    test_json_ascii_converter();
//    test_json_ascii_inverter();

    printf("SIZE OF ByteBlock %lu\r\n", sizeof(ByteBlock));
    char *code = "123456789";
    int len = strlen(code);

    int i = 0;
    for(i = 0; i < len; ++i)
    {
        printf("%02x ", code[i]);
    }
    printf("\r\n");

    test_coder_block(code);
//    printf("CODER BLOCK %02x\r\n", coder_block_1(&c[0], 0));
//    printf("CODER BLOCK %02x\r\n", coder_block_1(&c[1], 1));

    char decode[] = { 0xc7, 0x2c, 0xf4, 0xd7, 0x6d, 0xf8, 0xe4, 0};
    test_decoder_block(decode);

//    char *p = &decode;
//    printf("P: %2x\r\n", (unsigned char)p[0]);
//    p = p + 3;
//    printf("P: %2x\r\n", (unsigned char)p[0]);
    return 0;
}
