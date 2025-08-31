#include <assert.h>		/*assert*/
#include <limits.h>		/*CHAR_BIT*/

#include "bit_array.h"

#define SIZE (64)
#define LUT_SIZE (256)

static unsigned char ByteMiror(unsigned char byte);
static void InitMirrorLut(size_t mirror_LUT[]);
static void InitCounterLut(size_t mirror_LUT[]);

bit_val_t BitArrayGetBit(bitarray_t bit_array, size_t index)
{
	size_t mask = (size_t)1;
	size_t bit = (size_t)0;
	
	assert (SIZE > index);
	
	mask <<= index;
	bit = mask & bit_array;
	return bit >> index;
}

bitarray_t BitArraySetOn(bitarray_t bit_array, size_t index)
{
	size_t mask = (size_t)1;
	assert (SIZE > index);
	
	mask <<= index;
	
	return mask | bit_array;
}

bitarray_t BitArraySetOff(bitarray_t bit_array, size_t index)
{
	size_t mask = ~((size_t)1 << index);
	assert (SIZE > index);
	
	return (bit_array & mask);
}

bitarray_t BitArraySetVal(bitarray_t bit_array, size_t index, bit_val_t val)
{
	assert (SIZE > index);
	assert(ON == val || OFF ==  val);
	
	if (ON == val)
	{
		return BitArraySetOn(bit_array, index);
	}
	
	return BitArraySetOff(bit_array, index);
}

bitarray_t BitArraySetAll(bitarray_t bit_array)
{
	bit_array = ~(size_t)0;
	
	return bit_array;
}

bitarray_t BitArrayResetAll(bitarray_t bit_array)
{
	bit_array = (size_t)0;
	
	return bit_array;
}

char* BitArrayToString(bitarray_t bit_array, char* dst)
{
	size_t index = 0;
	assert (NULL != dst);
	
	dst += SIZE;
	*dst = '\0';
	--dst;
	while (index < SIZE)
	{
		*dst = '0' + (BitArrayGetBit(bit_array, index));
		--dst;
		++index;
	}
	++dst;
	
	return dst;
}

bitarray_t BitArrayRotateL(bitarray_t bit_array, size_t num_of_rotates)
{
	size_t mask = bit_array;
	
	num_of_rotates %= SIZE;
	mask >>= SIZE - num_of_rotates;
	bit_array <<= num_of_rotates;
	
	return (bit_array | mask);
}

bitarray_t BitArrayRotateR(bitarray_t bit_array, size_t num_of_rotates)
{
	size_t mask = bit_array;
	
	num_of_rotates %= SIZE;
	mask <<= SIZE - num_of_rotates;
	bit_array >>= num_of_rotates;
	
	return (bit_array | mask);
}

size_t BitArrayCountOn(bitarray_t bit_array)
{
	int mask = 1;
	size_t i = 0;
	size_t counter = 0;
	
	for (i = 0; i < SIZE; ++i)
	{
		if (bit_array & mask)
		{
			++counter;
		}
		bit_array >>= mask;
	}
	return counter;
}

size_t BitArrayCountOff(bitarray_t bit_array)
{
	return (SIZE - BitArrayCountOn(bit_array));
}

bitarray_t BitArrayFlipBit(bitarray_t bit_array, size_t index)
{
	assert (SIZE > index);
	
	if (ON == BitArrayGetBit(bit_array, index))
	{
		return BitArraySetOff(bit_array, index);
	}
	return BitArraySetOn(bit_array, index);
}

bitarray_t BitArrayMirror(bitarray_t bit_array)
{
	size_t index = 0;
	bitarray_t ans = 0;
	
	for (index = 0; index < SIZE; ++index)
	{
		ans = BitArraySetVal(ans, index, BitArrayGetBit(bit_array, SIZE - index - 1));
	}
	return ans;
}

bitarray_t BitArrayMirrorWithLUT(bitarray_t bit_array)
{
	size_t i = 0;
	static size_t mirror_LUT[LUT_SIZE] = {0};
	bitarray_t ans = 0;
	
	InitMirrorLut(mirror_LUT);
	
	for (i = 0; i < CHAR_BIT - 1; ++i)
	{
		ans |= mirror_LUT[(unsigned char)bit_array];
		bit_array >>= CHAR_BIT;
		ans <<= CHAR_BIT;
	}
	
	return (ans | mirror_LUT[(unsigned char)bit_array]);
}


size_t BitArrayCountOnWithLUT(bitarray_t bit_array)
{
	size_t i = 0;
	static size_t counter_LUT[LUT_SIZE] = {0};
	size_t counter = 0;
	
	InitCounterLut(counter_LUT);
	
	for ( i = 0; i < LUT_SIZE; ++i)
	{
		counter += counter_LUT[(unsigned char)bit_array];
		bit_array >>= CHAR_BIT;
	}
	
	return counter;
}


static void InitMirrorLut(size_t mirror_LUT[])
{
	size_t i = 0;
	static int is_init = 0;
	
	if (1 == is_init)
	{
		return;
	}
	
	for (i = 0; i < LUT_SIZE; ++i)
	{
		mirror_LUT[i] = ByteMiror(i);
	}
	
	is_init = 1;
}

static unsigned char ByteMiror(unsigned char byte)
{
	/*divided bytes for 2 groups of 4 bits and swap them*/
   byte = (byte & 0xF0) >> 4 | (byte & 0x0F) << 4;
   /*divided to 4 groups of 2 bits and swap them*/
   byte = (byte & 0xCC) >> 2 | (byte & 0x33) << 2;
	/*divided to 8 groups of 1 bits and swap them*/
   byte = (byte & 0xAA) >> 1 | (byte & 0x55) << 1;
   
   return byte;
}



static void InitCounterLut(size_t counter_LUT[])
{
	static int is_init = 0;
	size_t i = 1;
	
	if (1 == is_init)
	{
		return;
	}
	
	counter_LUT[0] = 0;
	
	for(i = 1; i < LUT_SIZE; ++i)
	{
		counter_LUT[i] = counter_LUT[i / 2] + (i & 1);
	}
	
	is_init = 1;
}
















