#include <json/json_compress.h>



//bool json_compress_grammar()
//{

//}

//bool json_decompress_grammar()
//{

//}


//bool json_compress_ascii()
//{
//    bool flag = false;
    
//    return flag;
//}

//bool json_decompress_ascii()
//{
//    bool flag = false;
    
//    return flag;
//}

uint8_t json_ascii_coder(char c)
{
    uint8_t result;
    
    switch(c)
    {
        // End string
        case '\0':  result = '\0';  break;  // NULL
        case '\n':  result = 10;    break;  // LF
        case '\r':  result = 13;    break;  // CR
        // Token
        case '\"':  result = 4;     break;      case ',':   result = 5;     break;
        case ':':   result = 6;     break;      case ';':   result = 7;     break;
        case '[':   result = 8;     break;      case ']':   result = 9;     break;
        case '{':   result = 1;     break;      case '}':   result = 11;    break;
        // Number
        case '0':   result = 12;    break;      case '1':   result = 2;    break;
        case '2':   result = 14;    break;      case '3':   result = 15;    break;
        case '4':   result = 16;    break;      case '5':   result = 17;    break;
        case '6':   result = 18;    break;      case '7':   result = 19;    break;
        case '8':   result = 20;    break;      case '9':   result = 21;    break;
        // Letter
        case 'a':   result = 22;    break;      case 'b':   result = 23;    break;
        case 'c':   result = 24;    break;      case 'd':   result = 25;    break;
        case 'e':   result = 26;    break;      case 'f':   result = 27;    break;
        case 'g':   result = 28;    break;      case 'h':   result = 29;    break;
        case 'i':   result = 30;    break;      case 'j':   result = 31;    break;
        case 'k':   result = 32;    break;      case 'l':   result = 33;    break;
        case 'm':   result = 34;    break;      case 'n':   result = 35;    break;
        case 'o':   result = 36;    break;      case 'p':   result = 37;    break;
        case 'q':   result = 38;    break;      case 'r':   result = 39;    break;
        case 's':   result = 40;    break;      case 't':   result = 41;    break;
        case 'u':   result = 42;    break;      case 'v':   result = 43;    break;
        case 'w':   result = 44;    break;      case 'x':   result = 45;    break;
        case 'y':   result = 46;    break;      case 'z':   result = 47;    break;
        default:
            result = '\0';
            break;
    }
    
    return result;
}

char json_ascii_decoder(uint8_t c)
{
    char result;

    switch(c)
    {
        // End string
        case '\0':  result = '\0';  break;  // NULL
        case 10:    result = '\n';  break;  // LF
        case 13:    result = '\r';  break;  // CR
        // Token
        case 4:     result = '\"';  break;      case 5:     result = ',';   break;
        case 6:     result = ':';   break;      case 7:     result = ';';   break;
        case 8:     result = '[';   break;      case 9:     result = ']';   break;
        case 1:     result = '{';   break;      case 11:    result = '}';   break;
        // Number
        case 12:    result = '0';   break;      case 2:     result = '1';   break;
        case 14:    result = '2';   break;      case 15:    result = '3';   break;
        case 16:    result = '4';   break;      case 17:    result = '5';   break;
        case 18:    result = '6';   break;      case 19:    result = '7';   break;
        case 20:    result = '8';   break;      case 21:    result = '9';   break;
        // Letter
        case 22:    result = 'a';   break;      case 23:    result = 'b';   break;
        case 24:    result = 'c';   break;      case 25:    result = 'd';   break;
        case 26:    result = 'e';   break;      case 27:    result = 'f';   break;
        case 28:    result = 'g';   break;      case 29:    result = 'h';   break;
        case 30:    result = 'i';   break;      case 31:    result = 'j';   break;
        case 32:    result = 'k';   break;      case 33:    result = 'l';   break;
        case 34:    result = 'm';   break;      case 35:    result = 'n';   break;
        case 36:    result = 'o';   break;      case 37:    result = 'p';   break;
        case 38:    result = 'q';   break;      case 39:    result = 'r';   break;
        case 40:    result = 's';   break;      case 41:    result = 't';   break;
        case 42:    result = 'u';   break;      case 43:    result = 'v';   break;
        case 44:    result = 'w';   break;      case 45:    result = 'x';   break;
        case 46:    result = 'y';   break;      case 47:    result = 'z';   break;
        default:
            result = '\0';
            break;
    }

    return result;
}

void *coder_block(void *head, void *cursor, int idx)
{
    ByteBlock *head_ = head;
    ByteBlock *cursor_ = cursor;
    ByteBlock *byteNext = cursor;
    byteNext++;

    switch (idx % 4) {
        case 0:
        {
            head_->block4 = cursor_->block3;
            head_->block3 = cursor_->block2;
            head_->block2 = cursor_->block1;
            head_->block1 = byteNext->block3;
            head_++;
            break;
        }
        case 1:
        {
            head_->block4 = cursor_->block2;
            head_->block3 = cursor_->block1;
            head_->block2 = byteNext->block3;
            head_->block1 = byteNext->block2;
            head_++;
            break;
        }
        case 2:
        {
            head_->block4 = cursor_->block1;
            head_->block3 = byteNext->block3;
            head_->block2 = byteNext->block2;
            head_->block1 = byteNext->block1;
            head_++;
            break;
        }
        case 3:
            head_ = head;
            break;
        default:
            head_ = head;
            break;
    }

    return head_;
}

void *decoder_block(void *head, void *cursor, int idx)
{
    ByteBlock *head_ = head + ((idx * 4) / 3);
    ByteBlock *headNext = head_;

    ByteBlock *cursor_ = cursor;
    ByteBlock *bytePrev = cursor;
    ByteBlock *byteNext = cursor;
    
    if(cursor != head)
    {
        bytePrev--;
        byteNext++;
        headNext++;
    }

    switch ((idx * 4) % 3) {
        case 0: // byte 0
        {
            head_->block4 = 0;
            head_->block3 = cursor_->block4;
            head_->block2 = cursor_->block3;
            head_->block1 = cursor_->block2;
            break;
        }
        case 1: // byte 1
        {
            head_->block4 = 0;
            head_->block3 = bytePrev->block1;
            head_->block2 = cursor_->block4;
            head_->block1 = cursor_->block3;
            break;
        }
        case 2: // byte 2, 3
        {
            head_->block4 = 0;
            head_->block3 = bytePrev->block2;
            head_->block2 = bytePrev->block1;
            head_->block1 = cursor_->block4;

            headNext->block4 = 0;
            headNext->block3 = cursor_->block3;
            headNext->block2 = cursor_->block2;
            headNext->block1 = cursor_->block1;
            break;
        }
        default:
            head_ = head;
            break;
    }

    return head_;
}
