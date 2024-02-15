
#define _CONVOLUTION_C


#include <stdint.h>

#include "conv.h"
#include "bitstream.h"


#define CGRA_COLS       4
#define IN_VAR_DEPTH    6
#define OUT_VAR_DEPTH   1

static void        config  ();
static void        software(void);
static uint32_t    check   (void);

static int32_t cgra_input[CGRA_COLS][IN_VAR_DEPTH]     __attribute__ ((aligned (4)));
static int32_t cgra_output[CGRA_COLS][OUT_VAR_DEPTH]   __attribute__ ((aligned (4)));

static int32_t output_from_CGRA[N_filter][row_output][col_output] __attribute__ ((aligned (4)));

static int input_channel;
static int output_channel;

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
    .name   = "convolution",
};

void config()
{

    input_channel = 0;
    output_channel = 0;

    for(int16_t i = 0; i < 3; i++) {
        cgra_input[0][i] =   &(input[0][input_channel][0][i]);
        cgra_input[1][i] =   &(input[0][input_channel][1][i]);
        cgra_input[2][i] =   &(input[0][input_channel][2][i]);

    }

    cgra_input[3][0]= &output_from_CGRA[output_channel];

    for(int16_t i = 3; i < 6; i++){
        cgra_input[0][i] = filter[output_channel][input_channel][0][i-3];
        cgra_input[1][i] = filter[output_channel][input_channel][1][i-3];
        cgra_input[2][i] = filter[output_channel][input_channel][2][i-3];
    }
}

void software(void){
}

uint32_t check(void){
}

