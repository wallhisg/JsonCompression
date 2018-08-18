#include <string.h>
#include <system/system.h>
#include <stdlib.h>
#include <buffer/buffer_alloc.h>
#include <json/json_compress.h>

#define JSON_CODE_LENGTH    47
#define JSON_ASCII_LENGTH   126


int main(int argc, char **argv)
{
    system_init();
    char *src = "1112\n";
    int len = strlen(src);
    printf("RAW STRING: %s\r\n", src);
    printf("LENGTH OF RAW STRING: %d\r\n", len);

    char *com = json_compress_ascii(src);

    printf("COMPRESSED STRING: %s\r\n", com);
    printf("LENGTH OF COMPRESSED STRING: %lu\r\n", strlen(com));
    
    char *deCom = json_decompress_ascii(com);
    printf("DECOMPRESSED STRING: %s\r\n", deCom);
    printf("LENGTH OF DECOMPRESSED STRING: %lu\r\n", strlen(deCom));
    
    buffer_free(deCom);
    buffer_free(com);

    display_heap();
    
    return 0;
}
