#include "boolbits.h"

// should return the 1 or 0 of the requested bit
int int32GetBit(const unsigned int storage, int bitLocation)
{
    if(bitLocation > 31 || bitLocation < 0)
    {
        return -1;
    }

    unsigned int temp = storage & (1 << bitLocation);

    return temp >> bitLocation;
}

// select index 0 - 31 to set the bit value to 1
unsigned int int32SetBit(const unsigned int storage, int bitLocation)
{
    if(bitLocation > 31 || bitLocation < 0)
    {
        return 0;
    }

    unsigned int temp = storage | (1 << bitLocation);

    return temp;
}

// select index 0 - 31 to set the bit value to 0
unsigned int int32RemoveBit(const unsigned int storage, int bitLocation)
{
    if(bitLocation > 31 || bitLocation < 0)
    {
        return 0;
    }

    unsigned int temp = storage & ~(1 << bitLocation);

    return temp;
}