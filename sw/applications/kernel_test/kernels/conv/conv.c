/*
                              *******************
******************************* C SOURCE FILE *******************************
**                            *******************                          **
**                                                                         **
** project  : CGRA-X-HEEP                                                  **
** filename : conv.c                                                 **
** version  : 1                                                            **
** date     : 2023-06-22                                                       **
**                                                                         **
*****************************************************************************
**                                                                         **
** Copyright (c) EPFL                                                      **
** All rights reserved.                                                    **
**                                                                         **
*****************************************************************************
*/

/***************************************************************************/
/***************************************************************************/

/**
* @file   conv.c
* @date   2023-06-22
* @brief  A description of the kernel...
*
*/

#define _CONVOLUTION_C

/****************************************************************************/
/**                                                                        **/
/*                             MODULES USED                                 */
/**                                                                        **/
/****************************************************************************/
#include <stdint.h>

#include "conv.h"
#include "function.h"

/****************************************************************************/
/**                                                                        **/
/*                        DEFINITIONS AND MACROS                            */
/**                                                                        **/
/****************************************************************************/

#define CGRA_COLS       4
#define IN_VAR_DEPTH    6
#define OUT_VAR_DEPTH   1
#define TRANSPOSE 1




/****************************************************************************/
/**                                                                        **/
/*                      PROTOTYPES OF LOCAL FUNCTIONS                       */
/**                                                                        **/
/****************************************************************************/

static void        config  (int input_ch, int output_ch);
static void         loading_buffer(void);
static void        software(void);
static uint32_t    check   (void);


/**********************************************cgra_input******************************/
/**                                                                        **/
/*                            GLOBAL VARIABLES                              */
/**                                                                        **/
/****************************************************************************/
#if TRANSPOSE == 1
const uint32_t  cgra_imem_conv[CGRA_IMEM_SIZE] = {0xa90000, 0xab0000, 0x6bf0000, 0x971d0000, 0x0, 0x0, 0x0, 0x500f0000, 0x971d0000, 0x0, 0x500f0000, 0x0, 0x500f0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc80000, 0xc80000, 0xa90000, 0xab0000, 0x6bf0000, 0x971d0000, 0x0, 0x0, 0x0, 0x500f0000, 0x971d0000, 0x0, 0x500f0000, 0x0, 0x500f0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0xab0000, 0x6bf0000, 0x971d0000, 0x820d0000, 0x820d0000, 0x0, 0x500f0000, 0x971d0000, 0x0, 0x500f0000, 0x0, 0x500f0000, 0x0, 0x820d0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x300d0000, 0x300d0000, 0x820d0000, 0x850d0000, 0x5080000e, 0x820d0000, 0x0, 0x0, 0x0, 0x0, 0x300d0000, 0x820d0000, 0x850d0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0xab0000, 0x6bf0000, 0x971d0000, 0x0, 0x0, 0x90080000, 0x500f0000, 0x971d0000, 0x90080000, 0x500f0000, 0x90080000, 0x500f0000, 0x90080000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0xab0000, 0x6bf0000, 0x971d0000, 0x0, 0x0, 0x90080000, 0x500f0000, 0x971d0000, 0x90080000, 0x500f0000, 0x90080000, 0x500f0000, 0x90080000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0xab0000, 0x6bf0000, 0x971d0000, 0x820d0000, 0x820d0000, 0x90080000, 0x500f0000, 0x971d0000, 0x90080000, 0x500f0000, 0x90080000, 0x500f0000, 0x90080000, 0x820d0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa00900c4, 0x6a110001, 0x300d0000, 0x300d0000, 0x820d0000, 0x6a110001, 0x60880005, 0x820d0000, 0x0, 0x0, 0x0, 0x0, 0x300d0000, 0x820d0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xab0000, 0x5bf0000, 0x971d0000, 0x0, 0x0, 0x90080000, 0x5bf0000, 0x971d0000, 0x90080000, 0x5bf0000, 0x90080000, 0x5bf0000, 0x90080000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xab0000, 0x5bf0000, 0x971d0000, 0x0, 0x0, 0x90080000, 0x5bf0000, 0x971d0000, 0x90080000, 0x5bf0000, 0x90080000, 0x5bf0000, 0x90080000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xab0000, 0x5bf0000, 0x971d0000, 0x820d0000, 0x820d0000, 0x90080000, 0x5bf0000, 0x971d0000, 0x90080000, 0x5bf0000, 0x90080000, 0x5bf0000, 0x90080000, 0x820d0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa009000d, 0x0, 0x300d0000, 0x300d0000, 0x820d0000, 0x6a110001, 0x60080000, 0x820d0000, 0x0, 0x0, 0xa009000e, 0x80080000, 0x300d0000, 0x820d0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0x60080000, 0x2a0b0000, 0x0, 0x7b80000, 0x7b80000, 0x6a090004, 0x7a0b0004, 0x0, 0x6a090004, 0x0, 0x6a090004, 0x0, 0x6a090004, 0x0, 0x0, 0x0, 0x3bf0000, 0x29080000, 0x0, 0x0, 0xa90000, 0x60080000, 0x0, 0x20080000, 0x0, 0x0, 0x6a090004, 0x0, 0x2a100004, 0x6a090004, 0x0, 0x6a090004, 0x0, 0x6a090004, 0x0, 0x1a0b0004, 0x0, 0x0, 0x0, 0x27c00000, 0x0, 0xa90000, 0x60080000, 0x0, 0xa0b0000, 0x70800006, 0x32c00000, 0x6a090004, 0x0, 0x0, 0x6a090004, 0x0, 0x6a090004, 0x90080000, 0x6a090004, 0x32c00000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xab0000, 0x0, 0x0, 0x0, 0x40800009, 0x300d0000, 0x840d0000, 0x850d0000, 0x300d0000, 0x0, 0x0, 0x0, 0x20800007, 0x0, 0x0, 0x40d0000, 0x850d0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, };
static uint32_t cgra_kmem_conv[CGRA_KMEM_SIZE] = {0x0, 0xf014, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,};
#elif TRANSPOSE == 0
const uint32_t  cgra_imem_conv[CGRA_IMEM_SIZE] = {0xa90000, 0xab0000, 0x6bf0000, 0x971d0000, 0x0, 0x0, 0x300f0000, 0x971d0000, 0x0, 0x0, 0x0, 0x300f0000, 0x0, 0x300f0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc80000, 0xc80000,
                                                  0xa90000, 0xab0000, 0x6bf0000, 0x971d0000, 0x0, 0x90080000, 0x300f0000, 0x971d0000, 0x0, 0x0, 0x90080000, 0x300f0000, 0x90080000, 0x300f0000, 0x90080000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
                                                  0x0, 0xab0000, 0x3bf0000, 0x971d0000, 0x0, 0x90080000, 0x3bf0000, 0x971d0000, 0x0, 0x0, 0x90080000, 0x3bf0000, 0x90080000, 0x3bf0000, 0x90080000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
                                                  0xa90000, 0x60080000, 0xab0000, 0x7a130004, 0x8a0d0004, 0x6a090004, 0x7a0b0004, 0x7bf0000, 0x49080000, 0x17c00000, 0x6a090004, 0x0, 0x6a090004, 0x0, 0x6a090004, 0x0, 0x8a0d0004, 0x7a0b0004, 0x7bf0000, 0x49080000, 0x17c00000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0xab0000, 0x6bf0000, 0x971d0000, 0x0, 0x0, 0x300f0000, 0x971d0000, 0x0, 0x0, 0x0, 0x300f0000, 0x0, 0x300f0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0xab0000, 0x6bf0000, 0x971d0000, 0x0, 0x90080000, 0x300f0000, 0x971d0000, 0x0, 0x0, 0x90080000, 0x300f0000, 0x90080000, 0x300f0000, 0x90080000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xab0000, 0x3bf0000, 0x971d0000, 0x0, 0x90080000, 0x3bf0000, 0x971d0000, 0x0, 0x0, 0x90080000, 0x3bf0000, 0x90080000, 0x3bf0000, 0x90080000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0x60080000, 0xa00d00c4, 0x8a150001, 0x0, 0x6a090004, 0x0, 0x8a150001, 0x0, 0x80880004, 0x6a090004, 0x0, 0x6a090004, 0x0, 0x6a090004, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0xab0000, 0x6bf0000, 0x971d0000, 0x840d0000, 0x0, 0x300f0000, 0x971d0000, 0x0, 0x0, 0x0, 0x300f0000, 0x0, 0x300f0000, 0x0, 0x840d0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0xab0000, 0x6bf0000, 0x971d0000, 0x840d0000, 0x90080000, 0x300f0000, 0x971d0000, 0x0, 0x0, 0x90080000, 0x300f0000, 0x90080000, 0x300f0000, 0x90080000, 0x840d0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xab0000, 0x3bf0000, 0x971d0000, 0x840d0000, 0x90080000, 0x3bf0000, 0x971d0000, 0x0, 0x0, 0x90080000, 0x3bf0000, 0x90080000, 0x3bf0000, 0x90080000, 0x840d0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0x60080000, 0xa00d000d, 0x0, 0x8080000a, 0x6a090004, 0x0, 0x8a150001, 0x0, 0x4080000f, 0x6a090004, 0x0, 0x6a090004, 0xa00d000e, 0x6a090004, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x500d0000, 0x840d0000, 0x830d0000, 0x0, 0x0, 0x0, 0x840d0000, 0x0, 0x0, 0x0, 0x0, 0x500d0000, 0x840d0000, 0x830d0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x500d0000, 0x840d0000, 0x0, 0x0, 0x0, 0x0, 0x840d0000, 0x0, 0x0, 0x0, 0x0, 0x500d0000, 0x840d0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x500d0000, 0x840d0000, 0x0, 0x0, 0x0, 0x0, 0x840d0000, 0x0, 0x0, 0x0, 0x0, 0x500d0000, 0x840d0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa0f0000, 0x0, 0x20d0000, 0x830d0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x90800006, 0x0, 0x0, 0x20d0000, 0x830d0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, };
static uint32_t cgra_kmem_conv[CGRA_KMEM_SIZE] = {0x0, 0xf015, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, };
#endif
extern int32_t outputs[N_output][channel_output][row_output][col_output];
static int32_t  cgra_input[CGRA_COLS][IN_VAR_DEPTH]     __attribute__ ((aligned (4)));
static int32_t  cgra_output[CGRA_COLS][OUT_VAR_DEPTH]   __attribute__ ((aligned (4)));
static int32_t  buffer[row_output][col_output] __attribute__ ((aligned (4)));
static int32_t  output_from_CGRA[N_filter][row_output][col_output] __attribute__ ((aligned (4)));

static int input_channel;
static int output_channel;


    static uint32_t	i_index_soft;
    static uint32_t	i_index_cgra;
    static uint32_t	i_NumBits_soft;
    static uint32_t	i_NumBits_cgra;

    static uint32_t	o_ret_soft;
    static uint32_t	o_ret_cgra;


/****************************************************************************/
/**                                                                        **/
/*                           EXPORTED VARIABLES                             */
/**                                                                        **/
/****************************************************************************/

extern kcom_kernel_t conv_kernel = {
    .kmem   = cgra_kmem_conv,
    .imem   = cgra_imem_conv,
    .col_n  = CGRA_N_COLS,
    .in_n   = IN_VAR_DEPTH,
    .out_n  = OUT_VAR_DEPTH,
    .input  = cgra_input,
    .output = cgra_output,
    .config = config,
    .func   = software,
    .check  = check,
    .loading_buffer = loading_buffer,
    .name   = "convolution",
};

/****************************************************************************/
/**                                                                        **/
/*                            LOCAL FUNCTIONS                               */
/**                                                                        **/
/****************************************************************************/

void config(int input_ch, int output_ch)
{


input_channel = input_ch;
output_channel = output_ch;

#if TRANSPOSE == 1

    for(int16_t i = 0; i < 3; i++) {
        cgra_input[0][i] =   &(input[0][input_channel][0][i]);
        cgra_input[1][i] =   &(input[0][input_channel][1][i]);
        cgra_input[2][i] =   &(input[0][input_channel][2][i]);
        
}

    cgra_input[3][0]= &output_from_CGRA[output_ch];

    for(int16_t i = 3; i < 6; i++){
        cgra_input[0][i] = filter[output_channel][input_channel][0][i-3];
        cgra_input[1][i] = filter[output_channel][input_channel][1][i-3];
        cgra_input[2][i] = filter[output_channel][input_channel][2][i-3];
    }

#elif TRANSPOSE == 0

    for(int16_t i = 0; i < 3; i++) {
        cgra_input[0][i] =   &(input[0][input_channel][i][0]);
        cgra_input[1][i] =   &(input[0][input_channel][i][1]);
        cgra_input[3][i] =   &(input[0][input_channel][i][2]);
        cgra_input[2][i] = filter[output_channel][input_channel][i][2];
}

    cgra_input[3][3]= &output_from_CGRA[output_ch];

    for(int16_t i = 3; i < 6; i++){
        cgra_input[0][i] = filter[output_channel][input_channel][i-3][0];
        cgra_input[1][i] = filter[output_channel][input_channel][i-3][1];
        
    }

#endif

}


void loading_buffer(){

    for(int i = 0; i < row_output; i++){
        for(int j = 0; j < col_output; j++){
            printf("%d ",output_from_CGRA[output_channel][i][j]); 
        }
        printf("\n");
    }
    


    


}


void software(void)
{
    printf("Software begins: \n");
    conv2D();
}

uint32_t check(void)
{
    printf("Check begins: \n");
    uint32_t errors = 0;

for(int l = 0; l < N_filter; l ++){
    for(int i = 0; i < row_output; i++){
        for(int j = 0; j < col_output; j++){
            if(outputs[0][l][i][j] != output_from_CGRA[l][i][j]){
                errors++;
                printf("Error at %d %d\n", i, j);
                printf("Expected %d, got %d\n", outputs[0][l][i][j], output_from_CGRA[l][i][j]);
            }
        }
    }
    printf("%d errors for filter %d \n", errors, l);
 
}
    if(errors == 0){
        
        for(int l = 0; l < N_filter; l ++){
    for(int i = 0; i < row_output; i++){
        for(int j = 0; j < col_output; j++){
            output_from_CGRA[l][i][j]=0;
        }
    }
        }
    }
    else{
        printf("Errors: %d\n", errors);
    }



    //for(int16_t i = 0; i < IN_VAR_DEPTH; i++) {
    //    outCGRA[4 + i*3] = cgra_output[3][i];
    //}
//
    //for( uint16_t i = 0; i < IMG_DIM; i++ ){
    //        PRINTF("[%d] %d != %d\n", i, outSW[i],outCGRA[i] );
    //    // if( outImg[i] != Gold_Out_Img[i] ){
    //    //     errors++;
    //    // }
//
//
    //}
//
    //o_ret_cgra = outCGRA[4];

    return errors;
}

/****************************************************************************/
/**                                                                        **/
/**                                EOF                                     **/
/**                                                                        **/
/****************************************************************************/