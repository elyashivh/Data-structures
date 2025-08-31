#include <stdio.h>

#include "bit_array.h"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define SIZE 64

void TestBitArrayGetBit(void);
void TestBitArraySetOn(void);
void TestBitArraySetOff(void);
void TestBitArraySetVal(void);
void TestBitArraySetAll(void);
void TestBitArrayResetAll(void);
void TestBitArrayToString(void);
void TestBitArrayRotateL(void);
void TestBitArrayRotateR(void);
void TestBitArrayCountOn(void);
void TestBitArrayFlipBit(void);
void TestBitArrayMirror(void);
void TestBitArrayMirrorWithLUT(void);
void TestBitArrayCountOnWithLUT(void);

int main ()
{
	TestBitArrayGetBit();
	TestBitArraySetOn();
	TestBitArraySetOff();
	TestBitArraySetVal();
	TestBitArraySetAll();
	TestBitArrayResetAll();
	TestBitArrayToString();
	TestBitArrayRotateL();
	TestBitArrayRotateR();
	TestBitArrayCountOn();
	TestBitArrayFlipBit();
	TestBitArrayMirror();
	TestBitArrayMirrorWithLUT();
	TestBitArrayCountOnWithLUT();
	
	return 0;
}


void TestBitArrayGetBit(void)
{
	bitarray_t num = 5;
	
	if (1 != BitArrayGetBit(num, 0))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	if (0 != BitArrayGetBit(num, 1))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	
	printf("%sTestBitArrayGetBit done\n%s", GREEN, RESET);

}

void TestBitArraySetOn(void)
{
	bitarray_t num = 0;
	
	if (1 != BitArraySetOn(num, 0))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	if (2 != BitArraySetOn(num, 1))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	printf("%sTestBitArraySetOn done\n%s", GREEN, RESET);
}

void TestBitArraySetOff(void)
{
	bitarray_t num = 93;
	
	if (92 != BitArraySetOff(num, 0))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	if (77 != BitArraySetOff(num, 4))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	
	printf("%sTestBitArraySetOff done\n%s", GREEN, RESET);
}

void TestBitArraySetVal(void)
{
	bitarray_t num1 = 0;
	bitarray_t num2 = 107;
	bitarray_t num3 = 5460;
		
	if (1 != BitArraySetVal(num1, 0, 1))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	if (1131 != BitArraySetVal(num2, 10, 1))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	if (4436 != BitArraySetVal(num3, 10, 0))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	
	printf("%sTestBitArraySetVal done\n%s", GREEN, RESET);
}

void TestBitArraySetAll(void)
{
	bitarray_t num1 = 0;
	bitarray_t num2 = 98;
	
	if (0xFFFFFFFFFFFFFFFF != BitArraySetAll(num1))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	if (0xFFFFFFFFFFFFFFFF != BitArraySetAll(num2))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	
	printf("%sTestBitArraySetAll done\n%s", GREEN, RESET);
}

void TestBitArrayResetAll(void)
{
	bitarray_t num1 = 0xFFFFFFFFFFFFFFFF;
	bitarray_t num2 = 98;
	
	if (0 != BitArrayResetAll(num1))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	if (0 != BitArrayResetAll(num2))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	
	printf("%sTestBitArrayResetAll done\n%s", GREEN, RESET);
}

void TestBitArrayToString(void)
{
	bitarray_t num1 = 0;
	bitarray_t num2 = 3;
	bitarray_t num3 = 0xFFFFFFFFFFFFFFFF;
	
	char arr1[NUM_OF_DICT+1];
	char arr2[NUM_OF_DICT+1];
	char arr3[NUM_OF_DICT+1];
	
	printf("%s\n", BitArrayToString(num1, arr1));
	printf("%s\n", BitArrayToString(num2, arr2));
	printf("%s\n", BitArrayToString(num3, arr3));
	
	printf("%sTestBitArrayToString done\n%s", GREEN, RESET);
}

void TestBitArrayRotateL(void)
{
	bitarray_t num1 = 2;
	bitarray_t num2 = 0x5FFFFFFFFFFFFF00;
	bitarray_t num3 = 0x5555FFFF5555FFFF;
	
	if (2 != BitArrayRotateL(num1, 0))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	if (0xFFFFFFFFFFFFF005 != BitArrayRotateL(num2, 4))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	if (0x55FFFF5555FFFF55 != BitArrayRotateL(num3, 8))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	
	printf("%sTestBitArrayRotateL done\n%s", GREEN, RESET);
}

void TestBitArrayRotateR(void)
{
	bitarray_t num1 = 2;
	bitarray_t num2 = 0x5FFFFFFFFFFFFF00;
	bitarray_t num3 = 0x5555FFFF5555FFFF;
	
	if (2 != BitArrayRotateL(num1, 0))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	if (0xFFFFFFFFFFFFF005 != BitArrayRotateL(num2, 4))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	if (0x55FFFF5555FFFF55 != BitArrayRotateL(num3, 8))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	
	printf("%sTestBitArrayRotateR done\n%s", GREEN, RESET);
}

void TestBitArrayCountOn(void)
{
	bitarray_t num1 = 0xFFFFFFFFFFFFFFFF;
	bitarray_t num2 = 0;
	bitarray_t num3 = 699730;
	
	if (64 != BitArrayCountOn(num1))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	if (0 != BitArrayCountOn(num2))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	if (10 != BitArrayCountOn(num3))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	
	printf("%sBitArrayCountOn done\n%s", GREEN, RESET);
}

void TestBitArrayCountOff(void)
{
	bitarray_t num1 = 0xFFFFFFFFFFFFFFFF;
	bitarray_t num2 = 0;
	bitarray_t num3 = 127;
	
	if (0 != BitArrayCountOff(num1))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	if (64 != BitArrayCountOff(num2))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	if (57 != BitArrayCountOff(num3))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	
	printf("%sBitArrayCountOff done\n%s", GREEN, RESET);
}

void TestBitArrayFlipBit(void)
{
	bitarray_t num1 = 2;
	bitarray_t num2 = 0xFF;
	bitarray_t num3 = 0x3;
	
	if (3 != BitArrayFlipBit(num1, 0))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	if (0x7F != BitArrayFlipBit(num2, 7))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	if (2 != BitArrayFlipBit(num3, 0))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	
	printf("%sTestBitArrayFlipBit done\n%s", GREEN, RESET);
}

void TestBitArrayMirror(void)
{
	bitarray_t num1 = 0x00000000FFFFFFFF;
	bitarray_t num2 = 0xFF;
	bitarray_t num3 = 0x0505050505050505;
	
	if (0xFFFFFFFF00000000 != BitArrayMirror(num1))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	if (0xFF00000000000000 != BitArrayMirror(num2))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	if (0xA0A0A0A0A0A0A0A0 != BitArrayMirror(num3))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	
	printf("%sTestBitArrayMirror done\n%s", GREEN, RESET);
}

void TestBitArrayMirrorWithLUT(void)
{
	bitarray_t num1 = 0x00000000FFFFFFFF;
	bitarray_t num2 = 0xFF;
	bitarray_t num3 = 0x0505050505050505;
	
	char arr1[NUM_OF_DICT+1];
	char arr2[NUM_OF_DICT+1];

	printf("%s\n", BitArrayToString(num3, arr1));
	printf("%s\n", BitArrayToString(BitArrayMirrorWithLUT(num3), arr2));
	printf("%s\n", BitArrayToString(BitArrayMirror(num3), arr2));
	
	
	if (0xFFFFFFFF00000000 != BitArrayMirrorWithLUT(num1))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	if (0xFF00000000000000 != BitArrayMirrorWithLUT(num2))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	if (0xA0A0A0A0A0A0A0A0 != BitArrayMirrorWithLUT(num3))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	
	printf("%sTestBitArrayMirrorWithLUT done\n%s", GREEN, RESET);
}


void TestBitArrayCountOnWithLUT(void)
{
	bitarray_t num1 = 0xFFFFFFFFFFFFFFFF;
	bitarray_t num2 = 0;
	bitarray_t num3 = 699730;
	
	if (64 != BitArrayCountOnWithLUT(num1))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	if (0 != BitArrayCountOnWithLUT(num2))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	if (10 != BitArrayCountOnWithLUT(num3))
	{
		printf("%s%d: Test failed\n%s", RED, __LINE__, RESET); 	
	}
	
	printf("%sTestBitArrayCountOnWithLUT done\n%s", GREEN, RESET);
}













