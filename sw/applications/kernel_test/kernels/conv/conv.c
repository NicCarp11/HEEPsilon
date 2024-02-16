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
#include "bitstream.h"
/****************************************************************************/
/**                                                                        **/
/*                        DEFINITIONS AND MACROS                            */
/**                                                                        **/
/****************************************************************************/

#define CGRA_COLS       4
#define IN_VAR_DEPTH    8
#define OUT_VAR_DEPTH   256




/****************************************************************************/
/**                                                                        **/
/*                      PROTOTYPES OF LOCAL FUNCTIONS                       */
/**                                                                        **/
/****************************************************************************/


static void         config(void);
static void         loading_buffer(void);
static void        software(void);
static uint32_t    check   (void);
static void         im2col_conv(int32_t *input_to_CGRA, int out_row, int out_col);
static void         im2col_DMA(int32_t *input_to_CGRA, int32_t *filter_to_CGRA, int out_row, int out_col, int output_channel);


/**********************************************cgra_input******************************/
/**                                                                        **/
/*                            GLOBAL VARIABLES                              */
/**                                                                        **/
/****************************************************************************/

/* BITSTREAM for CGRA: this bitstream could be used if the im2col preparare not just one block of [3*3*16], but n
kmem: 0x0, 0xf017, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
imem: 0xa90000, 0xad0000, 0x0, 0x0, 0xa080009, 0x1ac00004, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0040, 0xab80004, 0x1a100001, 0x10880006, 0x90080000, 0x15080000, 0xf0000, 0x0, 0x0, 0x0, 0x0, 0xc80000, 0xc80000, 0xa90000, 0xad0000, 0xa0800c4, 0x1ac00008, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0040, 0x0, 0x0, 0x0, 0x90080000, 0x15080000, 0xf0000, 0x0, 0xab80008, 0x1a100001, 0x10880004, 0x0, 0x0, 0xa90000, 0xad0000, 0x0, 0x0, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0040, 0x0, 0x0, 0x0, 0x90080000, 0x15080000, 0xf0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0xad0000, 0x0, 0x0, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0040, 0x0, 0x0, 0x0, 0x90080000, 0x15080000, 0xf0000, 0x0, 0x0, 0x40b00000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0xad0000, 0x0, 0x0, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0040, 0x0, 0x0, 0x4ac00004, 0x90080000, 0xf0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0xad0000, 0x0, 0x0, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0040, 0x0, 0x0, 0x0, 0x90080000, 0xf0000, 0x0, 0x0, 0x0, 0x0, 0x4ac00008, 0x0, 0x0, 0xa90000, 0xad0000, 0x0, 0x0, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0040, 0x0, 0x0, 0x0, 0x90080000, 0xf0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0xad0000, 0x0, 0x0, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0040, 0x0, 0x0, 0x0, 0x90080000, 0xf0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0xad0000, 0x0, 0x0, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0040, 0x0, 0x0, 0x0, 0x90080000, 0xf0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0xad0000, 0x0, 0x0, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0040, 0x0, 0x0, 0x0, 0x90080000, 0xf0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0xad0000, 0x0, 0x0, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0040, 0x0, 0x0, 0x0, 0x90080000, 0xf0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0xad0000, 0x0, 0x0, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0040, 0x0, 0x0, 0x0, 0x90080000, 0xf0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0xad0000, 0x0, 0x0, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0040, 0x0, 0x0, 0x0, 0x90080000, 0x14080000, 0x15080000, 0x13080000, 0x0, 0xf0000, 0x0, 0x0, 0x0, 0xa90000, 0xad0000, 0x0, 0x0, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0040, 0x0, 0x0, 0x0, 0x90080000, 0x14080000, 0x15080000, 0xf0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0xad0000, 0x0, 0x0, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0040, 0x0, 0x0, 0x0, 0x90080000, 0x14080000, 0x15080000, 0xf0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0xad0000, 0x0, 0x0, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0040, 0x0, 0x0, 0x0, 0x90080000, 0x14080000, 0x15080000, 0x12080000, 0x13080000, 0xf0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
*/

 // BITSTREAM for CGRA: faster

extern int32_t output[N_output][channel_output][row_output][col_output];
static int32_t cgra_input[CGRA_COLS][IN_VAR_DEPTH]     __attribute__ ((aligned (4)));
static int32_t cgra_output[CGRA_COLS][OUT_VAR_DEPTH]   __attribute__ ((aligned (4)));
static int32_t input_to_CGRA[row_filter * col_filter * C_filter];
static int32_t output_from_CGRA[N_filter][row_output][col_output] __attribute__ ((aligned (4)));

static int out_row;
static int out_col;
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


void config(void)
{

//  config if the LWD = 32

for(int i = 0; i < 4; i++){
    cgra_input[0][i] = &(filter[(4*i)][0][0][0]);
    cgra_input[1][i] = &(filter[(4*i)+1][0][0][0]);
    cgra_input[2][i] = &(filter[(4*i)+2][0][0][0]);
    cgra_input[3][i] = &(filter[(4*i)+3][0][0][0]);
}

for(int i = 4; i < 8; i++){
    cgra_input[0][i] = &(input[0][0][0][0]);
    cgra_input[1][i] = &(input[0][0][0][0]);
    cgra_input[2][i] = &(input[0][0][0][0]);
    cgra_input[3][i] = &(input[0][0][0][0]);
}


/*
cgra_input[0][0] = &input_to_CGRA[0];
cgra_input[0][1] = &filter_to_CGRA[0];
*/
}

/*
void loading_buffer(){

    for(int j = 0; j < row_output; j++){
        for(int k = 0; k < col_output; k++){
    output_from_CGRA[0][j][k]= cgra_output[0][0+k+j*col_output];
    output_from_CGRA[1][j][k]= cgra_output[0][1+k+j*col_output];
    output_from_CGRA[2][j][k]= cgra_output[0][2+k+j*col_output];
    output_from_CGRA[3][j][k]= cgra_output[0][3+k+j*col_output];
    output_from_CGRA[4][j][k]= cgra_output[1][0+k+j*col_output];
    output_from_CGRA[5][j][k]= cgra_output[1][1+k+j*col_output];
    output_from_CGRA[6][j][k]= cgra_output[1][2+k+j*col_output];
    output_from_CGRA[7][j][k]= cgra_output[1][3+k+j*col_output];
    output_from_CGRA[8][j][k]= cgra_output[2][0+k+j*col_output];
    output_from_CGRA[9][j][k]= cgra_output[2][1+k+j*col_output];
    output_from_CGRA[10][j][k]= cgra_output[2][2+k+j*col_output];
    output_from_CGRA[11][j][k]= cgra_output[2][3+k+j*col_output];
    output_from_CGRA[12][j][k]= cgra_output[3][0+k+j*col_output];
    output_from_CGRA[13][j][k]= cgra_output[3][1+k+j*col_output];
    output_from_CGRA[14][j][k]= cgra_output[3][2+k+j*col_output];
    output_from_CGRA[15][j][k]= cgra_output[3][3+k+j*col_output];
    printf("output_from_CGRA[0][%d][%d] = %d\n", j, k, output_from_CGRA[0][j][k]);
    printf("output_from_CGRA[1][%d][%d] = %d\n", j, k, output_from_CGRA[1][j][k]);
    printf("output_from_CGRA[2][%d][%d] = %d\n", j, k, output_from_CGRA[2][j][k]);
    printf("output_from_CGRA[3][%d][%d] = %d\n", j, k, output_from_CGRA[3][j][k]);
    printf("output_from_CGRA[4][%d][%d] = %d\n", j, k, output_from_CGRA[4][j][k]);
    printf("output_from_CGRA[5][%d][%d] = %d\n", j, k, output_from_CGRA[5][j][k]);
    printf("output_from_CGRA[6][%d][%d] = %d\n", j, k, output_from_CGRA[6][j][k]);
    printf("output_from_CGRA[7][%d][%d] = %d\n", j, k, output_from_CGRA[7][j][k]);
    printf("output_from_CGRA[8][%d][%d] = %d\n", j, k, output_from_CGRA[8][j][k]);
    printf("output_from_CGRA[9][%d][%d] = %d\n", j, k, output_from_CGRA[9][j][k]);
    printf("output_from_CGRA[10][%d][%d] = %d\n", j, k, output_from_CGRA[10][j][k]);
    printf("output_from_CGRA[11][%d][%d] = %d\n", j, k, output_from_CGRA[11][j][k]);
    printf("output_from_CGRA[12][%d][%d] = %d\n", j, k, output_from_CGRA[12][j][k]);
    printf("output_from_CGRA[13][%d][%d] = %d\n", j, k, output_from_CGRA[13][j][k]);
    printf("output_from_CGRA[14][%d][%d] = %d\n", j, k, output_from_CGRA[14][j][k]);
    printf("output_from_CGRA[15][%d][%d] = %d\n", j, k, output_from_CGRA[15][j][k]);



        }
    }


}
*/

void loading_buffer(){

    for(int i = 0; i < 16 ; i++){

      cgra_output[0][4*i];
      cgra_output[1][4*i];
      cgra_output[2][4*i];
      cgra_output[3][4*i];
      cgra_output[0][4*i+1];
      cgra_output[1][4*i+1];
      cgra_output[2][4*i+1];
      cgra_output[3][4*i+1];
      cgra_output[0][4*i+2];
      cgra_output[1][4*i+2];
      cgra_output[2][4*i+2];
      cgra_output[3][4*i+2];
      cgra_output[0][4*i+3];
      cgra_output[1][4*i+3];
      cgra_output[2][4*i+3];
      cgra_output[3][4*i+3];      
}

    
}

void software(void)
{
    conv2D();
}

uint32_t check(void)
{

    uint32_t errors = 0;

for(int l = 0; l < N_filter; l ++){
    for(int i = 0; i < row_output; i++){
        for(int j = 0; j < col_output; j++){
            if(output[0][l][i][j] != output_from_CGRA[l][i][j]){
                errors++;
                //printf("Error at %d %d\n", i, j);
                //printf("Expected %d, got %d\n", output[0][l][i][j], output_from_CGRA[l][i][j]);
            }
            //else{
            //    printf("Expected %d, got %d\n", output[0][l][i][j], output_from_CGRA[l][i][j]);
            //}
        }
    }
    

    if(errors == 0){
        printf("No errors\n");
        printf("For Filter %d there are no errors. \n", l);
    }
    else{
        printf("Errors: %d for filter %d\n", errors, l);
    }
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