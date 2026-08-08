#include "bitbyte.h"

// morse code data

char data[36][6];
void data_configureIndex(int index, const char *code);

char* data_get(char code)
{
    char *string = data[0]; // default setting

    if(isalpha(code))
    {
        string = data[toupper(code) - 'A'];
    }
    else if(isdigit(code))
    {
        int index = (code - '1') + 26;
        if(code == '0')
        {
            index = 35;
        }
        string = data[index];
    }

    return string;
}

// s -> dot
// l -> dash
void data_configureIndex(int index, const char *code)
{
    int i = 0;
    while(true)
    {
        data[index][i] = code[i];
        if(code[i] == '\0')
        {
            break;
        }
        i++;
    }
}

void data_init()
{
    /* A */data_configureIndex(0, "sl");
    /* B */data_configureIndex(1, "lsss");
    /* C */data_configureIndex(2, "lsls");
    /* D */data_configureIndex(3, "lss");
    /* E */data_configureIndex(4, "s");
    /* F */data_configureIndex(5, "ssls");
    /* G */data_configureIndex(6, "lls");
    /* H */data_configureIndex(7, "ssss");
    /* I */data_configureIndex(8, "ss");
    /* J */data_configureIndex(9, "slll");
    /* K */data_configureIndex(10, "lsl");
    /* L */data_configureIndex(11, "slss");
    /* M */data_configureIndex(12, "ll");
    /* N */data_configureIndex(13, "ls");
    /* O */data_configureIndex(14, "lll");
    /* P */data_configureIndex(15, "slls");
    /* Q */data_configureIndex(16, "llsl");
    /* R */data_configureIndex(17, "sls");
    /* S */data_configureIndex(18, "sss");
    /* T */data_configureIndex(19, "l");
    /* U */data_configureIndex(20, "ssl");
    /* V */data_configureIndex(21, "sssl");
    /* W */data_configureIndex(22, "sll");
    /* X */data_configureIndex(23, "lssl");
    /* Y */data_configureIndex(24, "lsll");
    /* Z */data_configureIndex(25, "llss");
    /* 1 */data_configureIndex(26, "sllll");
    /* 2 */data_configureIndex(27, "sslll");
    /* 3 */data_configureIndex(28, "sssll");
    /* 4 */data_configureIndex(29, "ssssl");
    /* 5 */data_configureIndex(30, "sssss");
    /* 6 */data_configureIndex(31, "lssss");
    /* 7 */data_configureIndex(32, "llsss");
    /* 8 */data_configureIndex(33, "lllss");
    /* 9 */data_configureIndex(34, "lllls");
    /* 0 */data_configureIndex(35, "lllll");
}