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

static void         config(int output_ch);
static void         loading_buffer(void);
static void        software(void);
static uint32_t    check   (void);



/**********************************************cgra_input******************************/
/**                                                                        **/
/*                            GLOBAL VARIABLES                              */
/**                                                                        **/
/****************************************************************************/




extern int32_t output[N_output][channel_output][row_output][col_output];
static int32_t cgra_input[CGRA_COLS][IN_VAR_DEPTH]     __attribute__ ((aligned (4)));
static int32_t cgra_output[CGRA_COLS][OUT_VAR_DEPTH]   __attribute__ ((aligned (4)));
static int32_t output_from_CGRA[channel_output][row_output][col_output];




int out_row;
int out_col;
int output_channel;


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






void config(int output_ch)
{
output_channel = output_ch;
//  config if the LWD = 32

for(int i = 0; i < 4; i++){
    cgra_input[0][i] = &(input[0][0][0][4*i]);
    cgra_input[1][i] = &(input[0][0][0][4*i + 1]);
    cgra_input[2][i] = &(input[0][0][0][4*i + 2]);
    cgra_input[3][i] = &(input[0][0][0][4*i + 3]);


}

for(int i = 4; i < 8; i++){
    cgra_input[0][i]=&(filter[output_ch][0][0][(i%4)*4]);
    cgra_input[1][i]=&(filter[output_ch][0][0][1+(i%4)*4]);
    cgra_input[2][i]=&(filter[output_ch][0][0][2+(i%4)*4]);
    cgra_input[3][i]=&(filter[output_ch][0][0][3+(i%4)*4]); 



      

/*
    cgra_input[0][i] = &(filter_to_CGRA[(i%4)*4]);
    cgra_input[1][i] = &(filter_to_CGRA[(i%4)*4+1]);
    cgra_input[2][i] = &(filter_to_CGRA[(i%4)*4+2]);
    cgra_input[3][i] = &(filter_to_CGRA[(i%4)*4+3]);

*/}


/*
cgra_input[0][0] = &input_to_CGRA[0];
cgra_input[0][1] = &filter_to_CGRA[0];
*/
}


void loading_buffer(){

for(int i = 0; i < row_output; i++){
    for(int j = 0; j < col_output; j++){
       // printf("cgra output: %d\n", cgra_output[0][j + i*col_output]);
        output_from_CGRA[output_channel][i][j]= cgra_output[0][j + i*col_output];
        
    }
}

}


void software(void)
{
    conv2D();
}

uint32_t check(void)
{

    uint32_t errors = 0;

for(int l = 0; l < channel_output; l ++){
    for(int i = 0; i < row_output; i++){
        for(int j = 0; j < col_output; j++){
            if(output[0][l][i][j] != output_from_CGRA[l][i][j]){
                errors++;
                printf("Error at %d %d\n", i, j);
                printf("Expected: %d, got: %d \n", output[0][l][i][j], output_from_CGRA[l][i][j]);
            }


            
            
        }
    }
    

    //if(errors == 0){
    //    printf("No errors\n");
    //    printf("For Filter %d there are no errors. \n", l);
    //}
    //else{
    //    printf("Errors: %d for filter %d\n", errors, l);
    //}
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