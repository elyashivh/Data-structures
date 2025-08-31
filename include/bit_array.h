#ifndef __BIT_ARRAY_H__
#define __BIT_ARRAY_H__

#include <stddef.h>

typedef size_t bitarray_t;

typedef enum
{
	OFF,
	ON
}bit_val_t;

bit_val_t BitArrayGetBit(bitarray_t bit_array, size_t index);

bitarray_t BitArraySetOn(bitarray_t bit_array, size_t index);

bitarray_t BitArraySetOff(bitarray_t bit_array, size_t index);

bitarray_t BitArraySetVal(bitarray_t bit_array, size_t index, bit_val_t val);

bitarray_t BitArraySetAll(bitarray_t bit_array);

bitarray_t BitArrayResetAll(bitarray_t bit_array);

char* BitArrayToString(bitarray_t bit_array, char* dst);

bitarray_t BitArrayRotateL(bitarray_t bit_array, size_t num_of_rotates);

bitarray_t BitArrayRotateR(bitarray_t bit_array, size_t num_of_rotates);

size_t BitArrayCountOn(bitarray_t bit_array);

size_t BitArrayCountOff(bitarray_t bit_array);

bitarray_t BitArrayFlipBit(bitarray_t bit_array, size_t index);

bitarray_t BitArrayMirror(bitarray_t bit_array);

bitarray_t BitArrayMirrorWithLUT(bitarray_t bit_array);

size_t BitArrayCountOnWithLUT(bitarray_t bit_array);

#endif /* end of header guard BIT_ARRAY_H */
