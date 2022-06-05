#ifndef DAC_DEF_H_
#define DAC_DEF_H_

#define CLOCK_PERIOD 10


const int DMA_TRANS = 64;

// Color transfer transport addresses
// Used between blocking_transport() & do_filter()
const int MULTIPLY_R_ADDR_0 = 0x00000000;
const int MULTIPLY_R_ADDR_1 = 0x00000004;
const int MULTIPLY_R_ADDR_2 = 0x00000008;
const int MULTIPLY_R_ADDR_3 = 0x0000000c;
const int MULTIPLY_R_ADDR_4 = 0x00000010;
const int MULTIPLY_R_ADDR_5 = 0x00000014;
const int MULTIPLY_R_ADDR_6 = 0x00000018;
const int MULTIPLY_R_ADDR_7 = 0x0000001c;
const int MULTIPLY_RESULT_ADDR_0 = 0x00000020;
const int MULTIPLY_RESULT_ADDR_1 = 0x00000024;
const int MULTIPLY_RESULT_ADDR_2 = 0x00000028;
const int MULTIPLY_RESULT_ADDR_3 = 0x0000002c;

const int ADDITION_R_ADDR_0 = 0x00000000;
const int ADDITION_R_ADDR_1 = 0x00000004;
const int ADDITION_R_ADDR_2 = 0x00000008;
const int ADDITION_R_ADDR_3 = 0x0000000c;
const int ADDITION_R_ADDR_4 = 0x00000010;
const int ADDITION_R_ADDR_5 = 0x00000014;
const int ADDITION_R_ADDR_6 = 0x00000018;
const int ADDITION_R_ADDR_7 = 0x0000001c;
const int ADDITION_RESULT_ADDR_0 = 0x00000020;
const int ADDITION_RESULT_ADDR_1 = 0x00000024;
const int ADDITION_RESULT_ADDR_2 = 0x00000028;
const int ADDITION_RESULT_ADDR_3 = 0x0000002c;


union word {
	int sint;
	unsigned int uint;
	unsigned char uc[4];
};

#endif
