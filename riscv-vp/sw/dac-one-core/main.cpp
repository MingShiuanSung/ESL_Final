#include "string"
#include "string.h"
#include "cassert"
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"


//DAC
static char* const MUL0_START_ADDR = (char* const) (0x73000000);
static char* const MUL0_READ_ADDR  = (char* const) (0x73000020);
static char* const MUL1_START_ADDR = (char* const) (0x73100000);
static char* const MUL1_READ_ADDR  = (char* const) (0x73100020);
static char* const MUL2_START_ADDR = (char* const) (0x73200000);
static char* const MUL2_READ_ADDR  = (char* const) (0x73200020);
static char* const MUL3_START_ADDR = (char* const) (0x73300000);
static char* const MUL3_READ_ADDR  = (char* const) (0x73300020);
static char* const MUL4_START_ADDR = (char* const) (0x73400000);
static char* const MUL4_READ_ADDR  = (char* const) (0x73400020);
static char* const MUL5_START_ADDR = (char* const) (0x73500000);
static char* const MUL5_READ_ADDR  = (char* const) (0x73500020);
static char* const MUL6_START_ADDR = (char* const) (0x73600000);
static char* const MUL6_READ_ADDR  = (char* const) (0x73600020);
static char* const MUL7_START_ADDR = (char* const) (0x73700000);
static char* const MUL7_READ_ADDR  = (char* const) (0x73700020);
static char* const ADD0_START_ADDR = (char* const) (0x73800000);
static char* const ADD0_READ_ADDR  = (char* const) (0x73800020);
static char* const ADD1_START_ADDR = (char* const) (0x73900000);
static char* const ADD1_READ_ADDR  = (char* const) (0x73900020);
static char* const ADD2_START_ADDR = (char* const) (0x73a00000);
static char* const ADD2_READ_ADDR  = (char* const) (0x73a00020);
static char* const ADD3_START_ADDR = (char* const) (0x73b00000);
static char* const ADD3_READ_ADDR  = (char* const) (0x73b00020);

// DMA 
static volatile uint32_t * const DMA_SRC_ADDR  = (uint32_t * const)0x70000000;
static volatile uint32_t * const DMA_DST_ADDR  = (uint32_t * const)0x70000004;
static volatile uint32_t * const DMA_LEN_ADDR  = (uint32_t * const)0x70000008;
static volatile uint32_t * const DMA_OP_ADDR   = (uint32_t * const)0x7000000C;
static volatile uint32_t * const DMA_STAT_ADDR = (uint32_t * const)0x70000010;
static const uint32_t DMA_OP_MEMCPY = 1;

bool _is_using_dma = false;

void write_data_to_ACC(char* ADDR, unsigned int* buffer, int len){
  if(_is_using_dma){  
    // Using DMA 
    *DMA_SRC_ADDR = (uint32_t)(buffer);
    *DMA_DST_ADDR = (uint32_t)(ADDR);
    *DMA_LEN_ADDR = len;
    *DMA_OP_ADDR  = DMA_OP_MEMCPY;
  }else{
    // Directly Send
    memcpy(ADDR, buffer, sizeof(unsigned int)*len);
  }
}
void read_data_from_ACC(char* ADDR, unsigned int* buffer, int len){
  if(_is_using_dma){
    // Using DMA 
    *DMA_SRC_ADDR = (uint32_t)(ADDR);
    *DMA_DST_ADDR = (uint32_t)(buffer);
    *DMA_LEN_ADDR = len;
    *DMA_OP_ADDR  = DMA_OP_MEMCPY;
  }else{
    // Directly Read
    memcpy(buffer, ADDR, sizeof(unsigned int)*len);
  }
}

int main(int argc, char *argv[]) {


  printf("Start processing...\n");

  unsigned int matrix_A[4][4] = { { 1, 1, 1, 1 },
                                  { 2, 2, 2, 2 },
                                  { 3, 3, 3, 3 },
                                  { 2, 2, 2, 2 } };

  unsigned int matrix_B[4][4] = { { 1, 1, 1, 1 },
                                  { 2, 2, 2, 2 },
                                  { 3, 3, 3, 3 },
                                  { 2, 2, 2, 2 } };

  unsigned int a[4] = { matrix_A[0][0], matrix_A[0][1], matrix_A[1][0], matrix_A[1][1]};
  unsigned int b[4] = { matrix_A[0][2], matrix_A[0][3], matrix_A[1][2], matrix_A[1][3]};
  unsigned int c[4] = { matrix_A[2][0], matrix_A[2][1], matrix_A[3][0], matrix_A[3][1]};
  unsigned int d[4] = { matrix_A[2][2], matrix_A[2][3], matrix_A[3][3], matrix_A[3][3]};
  unsigned int e[4] = { matrix_B[0][0], matrix_B[0][1], matrix_B[1][0], matrix_B[1][1]};
  unsigned int f[4] = { matrix_B[0][2], matrix_B[0][3], matrix_B[1][2], matrix_B[1][3]};
  unsigned int g[4] = { matrix_B[2][0], matrix_B[2][1], matrix_B[3][0], matrix_B[3][1]};
  unsigned int h[4] = { matrix_B[2][2], matrix_B[2][3], matrix_B[3][3], matrix_B[3][3]};

  unsigned int buffer[8] = {0};
  unsigned int ae[4] = {0};
  unsigned int bg[4] = {0};
  unsigned int af[4] = {0};
  unsigned int bh[4] = {0};
  unsigned int ce[4] = {0};
  unsigned int dg[4] = {0};
  unsigned int cf[4] = {0};
  unsigned int dh[4] = {0};
  unsigned int matrix_C_0[4] = {0};
  unsigned int matrix_C_1[4] = {0};
  unsigned int matrix_C_2[4] = {0};
  unsigned int matrix_C_3[4] = {0};
  unsigned int matrix_C[4][4] = { 0 };

  for (int i = 0; i < 8; i++) {
    if (i < 4)
      buffer[i] = a[i];
    else
      buffer[i] = e[i-4];
  }
  write_data_to_ACC(MUL0_START_ADDR, buffer, 8);
  read_data_from_ACC(MUL0_READ_ADDR, ae, 4);

  for (int i = 0; i < 8; i++) {
    if (i < 4)
      buffer[i] = b[i];
    else
      buffer[i] = g[i-4];
  }
  write_data_to_ACC(MUL1_START_ADDR, buffer, 8);
  read_data_from_ACC(MUL1_READ_ADDR, bg, 4);

  for (int i = 0; i < 8; i++) {
    if (i < 4)
      buffer[i] = a[i];
    else
      buffer[i] = f[i-4];
  }
  write_data_to_ACC(MUL2_START_ADDR, buffer, 8);
  read_data_from_ACC(MUL2_READ_ADDR, af, 4);

  for (int i = 0; i < 8; i++) {
    if (i < 4)
      buffer[i] = b[i];
    else
      buffer[i] = h[i-4];
  }
  write_data_to_ACC(MUL3_START_ADDR, buffer, 8);
  read_data_from_ACC(MUL3_READ_ADDR, bh, 4);

  for (int i = 0; i < 8; i++) {
    if (i < 4)
      buffer[i] = c[i];
    else
      buffer[i] = e[i-4];
  }
  write_data_to_ACC(MUL4_START_ADDR, buffer, 8);
  read_data_from_ACC(MUL4_READ_ADDR, ce, 4);

  for (int i = 0; i < 8; i++) {
    if (i < 4)
      buffer[i] = d[i];
    else
      buffer[i] = g[i-4];
  }
  write_data_to_ACC(MUL5_START_ADDR, buffer, 8);
  read_data_from_ACC(MUL5_READ_ADDR, dg, 4);

  for (int i = 0; i < 8; i++) {
    if (i < 4)
      buffer[i] = c[i];
    else
      buffer[i] = f[i-4];
  }
  write_data_to_ACC(MUL6_START_ADDR, buffer, 8);
  read_data_from_ACC(MUL6_READ_ADDR, cf, 4);

  for (int i = 0; i < 8; i++) {
    if (i < 4)
      buffer[i] = d[i];
    else
      buffer[i] = h[i-4];
  }
  write_data_to_ACC(MUL7_START_ADDR, buffer, 8);
  read_data_from_ACC(MUL7_READ_ADDR, dh, 4);

  for (int i = 0; i < 8; i++) {
    if (i < 4)
      buffer[i] = ae[i];
    else
      buffer[i] = bg[i-4];
  }
  write_data_to_ACC(ADD0_START_ADDR, buffer, 8);
  read_data_from_ACC(ADD0_READ_ADDR, matrix_C_0, 4);

  for (int i = 0; i < 8; i++) {
    if (i < 4)
      buffer[i] = af[i];
    else
      buffer[i] = bh[i-4];
  }
  write_data_to_ACC(ADD1_START_ADDR, buffer, 8);
  read_data_from_ACC(ADD1_READ_ADDR, matrix_C_1, 4);

  for (int i = 0; i < 8; i++) {
    if (i < 4)
      buffer[i] = ce[i];
    else
      buffer[i] = dg[i-4];
  }
  write_data_to_ACC(ADD2_START_ADDR, buffer, 8);
  read_data_from_ACC(ADD2_READ_ADDR, matrix_C_2, 4);

  for (int i = 0; i < 8; i++) {
    if (i < 4)
      buffer[i] = cf[i];
    else
      buffer[i] = dh[i-4];
  }
  write_data_to_ACC(ADD3_START_ADDR, buffer, 8);
  read_data_from_ACC(ADD3_READ_ADDR, matrix_C_3, 4);

  matrix_C[0][0] = matrix_C_0[0];
  matrix_C[0][1] = matrix_C_0[1];
  matrix_C[1][0] = matrix_C_0[2];
  matrix_C[1][1] = matrix_C_0[3];
  matrix_C[0][2] = matrix_C_1[0];
  matrix_C[0][3] = matrix_C_1[1];
  matrix_C[1][2] = matrix_C_1[2];
  matrix_C[1][3] = matrix_C_1[3];
  matrix_C[2][0] = matrix_C_2[0];
  matrix_C[2][1] = matrix_C_2[1];
  matrix_C[3][0] = matrix_C_2[2];
  matrix_C[3][1] = matrix_C_2[3];
  matrix_C[2][2] = matrix_C_3[0];
  matrix_C[2][3] = matrix_C_3[1];
  matrix_C[3][2] = matrix_C_3[2];
  matrix_C[3][3] = matrix_C_3[3];
  printf("matrix_C[4][4] = \n");
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      printf("%d ", matrix_C[i][j]);
    }
    printf("\n");
  }
}
