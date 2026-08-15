#ifndef BOOLBITS
#define BOOLBITS

int int32GetBit(const unsigned int storage, int bitLocation);   // should return the 1 or 0 of the requested bit
unsigned int int32SetBit(const unsigned int storage, int bitLocation);  // select index 0 - 31 to set the bit value to 1
unsigned int int32RemoveBit(const unsigned int storage, int bitLocation);   // select index 0 - 31 to set the bit value to 0

#endif