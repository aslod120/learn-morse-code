#include "bitbyte.h"

// morse code data

char data[36][6];
void data_configureIndex(int index, const char *code);

// returns the string code for input
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
    /* A */data_configureIndex(0, ".-");
    /* B */data_configureIndex(1, "-...");
    /* C */data_configureIndex(2, "-.-.");
    /* D */data_configureIndex(3, "-..");
    /* E */data_configureIndex(4, ".");
    /* F */data_configureIndex(5, "..-.");
    /* G */data_configureIndex(6, "--.");
    /* H */data_configureIndex(7, "....");
    /* I */data_configureIndex(8, "..");
    /* J */data_configureIndex(9, ".---");
    /* K */data_configureIndex(10, "-.-");
    /* L */data_configureIndex(11, ".-..");
    /* M */data_configureIndex(12, "--");
    /* N */data_configureIndex(13, "-.");
    /* O */data_configureIndex(14, "---");
    /* P */data_configureIndex(15, ".--.");
    /* Q */data_configureIndex(16, "--.-");
    /* R */data_configureIndex(17, ".-.");
    /* S */data_configureIndex(18, "...");
    /* T */data_configureIndex(19, "-");
    /* U */data_configureIndex(20, "..-");
    /* V */data_configureIndex(21, "...-");
    /* W */data_configureIndex(22, ".--");
    /* X */data_configureIndex(23, "-..-");
    /* Y */data_configureIndex(24, "-.--");
    /* Z */data_configureIndex(25, "--..");
    /* 1 */data_configureIndex(26, ".----");
    /* 2 */data_configureIndex(27, "..---");
    /* 3 */data_configureIndex(28, "...--");
    /* 4 */data_configureIndex(29, "....-");
    /* 5 */data_configureIndex(30, ".....");
    /* 6 */data_configureIndex(31, "-....");
    /* 7 */data_configureIndex(32, "--...");
    /* 8 */data_configureIndex(33, "---..");
    /* 9 */data_configureIndex(34, "----.");
    /* 0 */data_configureIndex(35, "-----");
}