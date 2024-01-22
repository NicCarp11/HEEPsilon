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
#define IN_VAR_DEPTH    8
#define OUT_VAR_DEPTH   4




/****************************************************************************/
/**                                                                        **/
/*                      PROTOTYPES OF LOCAL FUNCTIONS                       */
/**                                                                        **/
/****************************************************************************/

static void        config  (int output_row, int output_col);
static void         loading_buffer(void);
static void        software(void);
static uint32_t    check   (void);


/**********************************************cgra_input******************************/
/**                                                                        **/
/*                            GLOBAL VARIABLES                              */
/**                                                                        **/
/****************************************************************************/

const uint32_t  cgra_imem_conv[CGRA_IMEM_SIZE] = {0xa90000, 0xad0000, 0x0, 0x0, 0x0, 0x0, 0xa0080003, 0x1ac00004, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0004, 0xab80004, 0x1a100001, 0x10880008, 0x8a0d0034, 0xab80008, 0x1a100001, 0x10880006, 0x8a0d0340, 0xab8000c, 0x1a100001, 0x10880004, 0x90b00000, 0xc80000, 0xc80000, 
                                                  0xa90000, 0xad0000, 0x0, 0x0, 0xa0080003, 0x1ac00008, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0004, 0x0, 0x0, 0x0, 0x8a0d0034, 0x0, 0x0, 0x0, 0x8a0d0340, 0x0, 0x0, 0x0, 0x90b00000, 0x0, 0x0, 
                                                  0xa90000, 0xad0000, 0xa0080010, 0x1ac0000c, 0x0, 0x0, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0004, 0x0, 0x0, 0x0, 0x8a0d0034, 0x0, 0x0, 0x0, 0x8a0d0340, 0x0, 0x0, 0x0, 0x90b00000, 0x0, 0x0, 
                                                  0xa90000, 0xad0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0004, 0x0, 0x0, 0x0, 0x8a0d0034, 0x0, 0x0, 0x0, 0x8a0d0340, 0x0, 0x0, 0x0, 0x90b00000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0xad0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0004, 0x0, 0x0, 0x4ac00004, 0x8a0d0034, 0x0, 0x0, 0x4ac00008, 0x8a0d0340, 0x0, 0x0, 0x4ac0000c, 0x90b00000, 0x0, 0x0, 0xa90000, 0xad0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0004, 0x0, 0x0, 0x0, 0x8a0d0034, 0x0, 0x0, 0x0, 0x8a0d0340, 0x0, 0x0, 0x0, 0x90b00000, 0x0, 0x0, 0xa90000, 0xad0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0004, 0x0, 0x0, 0x0, 0x8a0d0034, 0x0, 0x0, 0x0, 0x8a0d0340, 0x0, 0x0, 0x0, 0x90b00000, 0x0, 0x0, 0xa90000, 0xad0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0004, 0x0, 0x0, 0x0, 0x8a0d0034, 0x0, 0x0, 0x0, 0x8a0d0340, 0x0, 0x0, 0x0, 0x90b00000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0xad0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0004, 0x0, 0x0, 0x0, 0x8a0d0034, 0x0, 0x0, 0x0, 0x8a0d0340, 0x0, 0x0, 0x0, 0x90b00000, 0x0, 0x0, 0xa90000, 0xad0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0004, 0x0, 0x0, 0x0, 0x8a0d0034, 0x0, 0x0, 0x0, 0x8a0d0340, 0x0, 0x0, 0x0, 0x90b00000, 0x0, 0x0, 0xa90000, 0xad0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0004, 0x0, 0x0, 0x0, 0x8a0d0034, 0x0, 0x0, 0x0, 0x8a0d0340, 0x0, 0x0, 0x0, 0x90b00000, 0x0, 0x0, 0xa90000, 0xad0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0004, 0x0, 0x0, 0x0, 0x8a0d0034, 0x0, 0x0, 0x0, 0x8a0d0340, 0x0, 0x0, 0x0, 0x90b00000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa90000, 0xad0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0004, 0x0, 0x0, 0x0, 0x8a0d0034, 0x0, 0x0, 0x0, 0x8a0d0340, 0x0, 0x0, 0x0, 0x90b00000, 0x0, 0x0, 0xa90000, 0xad0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0004, 0x0, 0x0, 0x0, 0x8a0d0034, 0x0, 0x0, 0x0, 0x8a0d0340, 0x0, 0x0, 0x0, 0x90b00000, 0x0, 0x0, 0xa90000, 0xad0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0004, 0x0, 0x0, 0x0, 0x8a0d0034, 0x0, 0x0, 0x0, 0x8a0d0340, 0x0, 0x0, 0x0, 0x90b00000, 0x0, 0x0, 0xa90000, 0xad0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6bb0000, 0x8b80000, 0x17180000, 0x190f0000, 0x6a090040, 0x8a0d0004, 0x0, 0x0, 0x0, 0x8a0d0034, 0x0, 0x0, 0x0, 0x8a0d0340, 0x0, 0x0, 0x0, 0x90b00000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,  };
static uint32_t cgra_kmem_conv[CGRA_KMEM_SIZE] = {  0x0, 0xf01b, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, };
extern int32_t __attribute__((section(".xheep_data_interleaved"))) outputs[N_output][channel_output][row_output][col_output];
static int32_t cgra_input[CGRA_COLS][IN_VAR_DEPTH]     __attribute__ ((aligned (4)));
static int32_t __attribute__((section(".xheep_data_interleaved"))) cgra_output[CGRA_COLS][OUT_VAR_DEPTH]  ;
static int32_t __attribute__((section(".xheep_data_interleaved"))) input_to_CGRA[batch_size][C_input][row_input][col_input];
static int32_t __attribute__((section(".xheep_data_interleaved"))) filter_to_CGRA [C_filter][row_filter][col_filter][N_filter];
static int32_t __attribute__((section(".xheep_data_interleaved"))) buffer[row_output][col_output] __attribute__ ((aligned (4)));
static int32_t __attribute__((section(".xheep_data_interleaved"))) output_from_CGRA[N_filter][row_output][col_output] ;

static int output_CGRA_row;
static int output_CGRA_col;


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

void config(int output_row, int output_col)
{
for(int i = 0; i < C_filter; i++) {
    for(int j = 0; j < row_filter; j++) {
        for(int k = 0; k < col_filter; k++) {
            for(int l = 0; l < N_filter; l++) {
                filter_to_CGRA[i][j][k][l] = filter[l][i][j][k];
                                            }
                                        }
                                    }
}

for(int i = 0; i < batch_size; i++){
    for(int j = 0; j < C_input; j++){
        for(int k = 0; k < row_input; k++){
            for(int l = 0; l < col_input; l++){
                input_to_CGRA[i][j][k][l] = input[i][j][k][l];
            }
        }
    }
}



output_CGRA_row=output_row;
output_CGRA_col=output_col;

for(int i = 0; i < 4; i++){
    cgra_input[0][i] = &(filter_to_CGRA[0][0][0][4*i]);
    cgra_input[1][i] = &(filter_to_CGRA[0][0][0][(4*i)+1]);
    cgra_input[2][i] = &(filter_to_CGRA[0][0][0][(4*i)+2]);
    cgra_input[3][i] = &(filter_to_CGRA[0][0][0][(4*i)+3]);
}





for(int i = 4; i < 8; i++){
    cgra_input[0][i] = &(input_to_CGRA[0][0][output_CGRA_row][output_CGRA_col]);
    cgra_input[1][i] = &(input_to_CGRA[0][0][output_CGRA_row][output_CGRA_col]);
    cgra_input[2][i] = &(input_to_CGRA[0][0][output_CGRA_row][output_CGRA_col]);
    cgra_input[3][i] = &(input_to_CGRA[0][0][output_CGRA_row][output_CGRA_col]);
}



}


void loading_buffer(){

for(int i = 0; i < 4 ; i++){
    
    output_from_CGRA[4*i][output_CGRA_row][output_CGRA_col] = cgra_output[0][i];
    output_from_CGRA[4*i+1][output_CGRA_row][output_CGRA_col] = cgra_output[1][i];
    output_from_CGRA[4*i+2][output_CGRA_row][output_CGRA_col] = cgra_output[2][i];
    output_from_CGRA[4*i+3][output_CGRA_row][output_CGRA_col] = cgra_output[3][i];
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

            }
        }
    }
 
}
    if(errors == 0){
        printf("No errors\n");
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