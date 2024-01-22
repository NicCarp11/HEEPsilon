#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "conv.h"
// im2col parameters

#define col_im2col (row_filter * col_filter * C_filter)
#define row_im2col (row_output * col_output)




void __attribute((noinline)) im2col_conv(int32_t *input_to_CGRA, int out_row, int out_col)
{

  int i, j, k, l, c, m, n, o, p, q, r, s, t, u, v, w;


for (i = 0; i < row_filter; i++)
      {
#if CHW_notHWC == 1
             input_to_CGRA[0+C_filter*0+C_filter*col_filter*i]=input[0][0][i+out_row][0+out_col]; 
             input_to_CGRA[1+C_filter*0+C_filter*col_filter*i]=input[0][1][i+out_row][0+out_col]; 
             input_to_CGRA[2+C_filter*0+C_filter*col_filter*i]=input[0][2][i+out_row][0+out_col]; 
             input_to_CGRA[3+C_filter*0+C_filter*col_filter*i]=input[0][3][i+out_row][0+out_col]; 
             input_to_CGRA[4+C_filter*0+C_filter*col_filter*i]=input[0][4][i+out_row][0+out_col]; 
             input_to_CGRA[5+C_filter*0+C_filter*col_filter*i]=input[0][5][i+out_row][0+out_col]; 
             input_to_CGRA[6+C_filter*0+C_filter*col_filter*i]=input[0][6][i+out_row][0+out_col]; 
             input_to_CGRA[7+C_filter*0+C_filter*col_filter*i]=input[0][7][i+out_row][0+out_col]; 
             input_to_CGRA[8+C_filter*0+C_filter*col_filter*i]=input[0][8][i+out_row][0+out_col]; 
             input_to_CGRA[9+C_filter*0+C_filter*col_filter*i]=input[0][9][i+out_row][0+out_col]; 
             input_to_CGRA[10+C_filter*0+C_filter*col_filter*i]=input[0][10][i+out_row][0+out_col]; 
             input_to_CGRA[11+C_filter*0+C_filter*col_filter*i]=input[0][11][i+out_row][0+out_col]; 
             input_to_CGRA[12+C_filter*0+C_filter*col_filter*i]=input[0][12][i+out_row][0+out_col]; 
             input_to_CGRA[13+C_filter*0+C_filter*col_filter*i]=input[0][13][i+out_row][0+out_col]; 
             input_to_CGRA[14+C_filter*0+C_filter*col_filter*i]=input[0][14][i+out_row][0+out_col]; 
             input_to_CGRA[15+C_filter*0+C_filter*col_filter*i]=input[0][15][i+out_row][0+out_col]; 
           
             input_to_CGRA[0+C_filter*1+C_filter*col_filter*i]=input[0][0][i+out_row][1+out_col]; 
             input_to_CGRA[1+C_filter*1+C_filter*col_filter*i]=input[0][1][i+out_row][1+out_col]; 
             input_to_CGRA[2+C_filter*1+C_filter*col_filter*i]=input[0][2][i+out_row][1+out_col]; 
             input_to_CGRA[3+C_filter*1+C_filter*col_filter*i]=input[0][3][i+out_row][1+out_col]; 
             input_to_CGRA[4+C_filter*1+C_filter*col_filter*i]=input[0][4][i+out_row][1+out_col]; 
             input_to_CGRA[5+C_filter*1+C_filter*col_filter*i]=input[0][5][i+out_row][1+out_col]; 
             input_to_CGRA[6+C_filter*1+C_filter*col_filter*i]=input[0][6][i+out_row][1+out_col]; 
             input_to_CGRA[7+C_filter*1+C_filter*col_filter*i]=input[0][7][i+out_row][1+out_col]; 
             input_to_CGRA[8+C_filter*1+C_filter*col_filter*i]=input[0][8][i+out_row][1+out_col]; 
             input_to_CGRA[9+C_filter*1+C_filter*col_filter*i]=input[0][9][i+out_row][1+out_col]; 
             input_to_CGRA[10+C_filter*1+C_filter*col_filter*i]=input[0][10][i+out_row][1+out_col]; 
             input_to_CGRA[11+C_filter*1+C_filter*col_filter*i]=input[0][11][i+out_row][1+out_col]; 
             input_to_CGRA[12+C_filter*1+C_filter*col_filter*i]=input[0][12][i+out_row][1+out_col]; 
             input_to_CGRA[13+C_filter*1+C_filter*col_filter*i]=input[0][13][i+out_row][1+out_col]; 
             input_to_CGRA[14+C_filter*1+C_filter*col_filter*i]=input[0][14][i+out_row][1+out_col]; 
             input_to_CGRA[15+C_filter*1+C_filter*col_filter*i]=input[0][15][i+out_row][1+out_col]; 


             input_to_CGRA[0+C_filter*2+C_filter*col_filter*i]=input[0][0][i+out_row][2+out_col]; 
             input_to_CGRA[1+C_filter*2+C_filter*col_filter*i]=input[0][1][i+out_row][2+out_col]; 
             input_to_CGRA[2+C_filter*2+C_filter*col_filter*i]=input[0][2][i+out_row][2+out_col]; 
             input_to_CGRA[3+C_filter*2+C_filter*col_filter*i]=input[0][3][i+out_row][2+out_col]; 
             input_to_CGRA[4+C_filter*2+C_filter*col_filter*i]=input[0][4][i+out_row][2+out_col]; 
             input_to_CGRA[5+C_filter*2+C_filter*col_filter*i]=input[0][5][i+out_row][2+out_col]; 
             input_to_CGRA[6+C_filter*2+C_filter*col_filter*i]=input[0][6][i+out_row][2+out_col]; 
             input_to_CGRA[7+C_filter*2+C_filter*col_filter*i]=input[0][7][i+out_row][2+out_col]; 
             input_to_CGRA[8+C_filter*2+C_filter*col_filter*i]=input[0][8][i+out_row][2+out_col]; 
             input_to_CGRA[9+C_filter*2+C_filter*col_filter*i]=input[0][9][i+out_row][2+out_col]; 
             input_to_CGRA[10+C_filter*2+C_filter*col_filter*i]=input[0][10][i+out_row][2+out_col]; 
             input_to_CGRA[11+C_filter*2+C_filter*col_filter*i]=input[0][11][i+out_row][2+out_col]; 
             input_to_CGRA[12+C_filter*2+C_filter*col_filter*i]=input[0][12][i+out_row][2+out_col]; 
             input_to_CGRA[13+C_filter*2+C_filter*col_filter*i]=input[0][13][i+out_row][2+out_col]; 
             input_to_CGRA[14+C_filter*2+C_filter*col_filter*i]=input[0][14][i+out_row][2+out_col]; 
             input_to_CGRA[15+C_filter*2+C_filter*col_filter*i]=input[0][15][i+out_row][2+out_col];
                          
            
#elif CHW_notHWC == 0
             input_to_CGRA[0+C_filter*0+C_filter*col_filter*i]=input[0][i+out_row][0+out_col][0]; 
            
            
             input_to_CGRA[1+C_filter*0+C_filter*col_filter*i]=input[0][i+out_row][0+out_col][1]; 
           
             input_to_CGRA[2+C_filter*0+C_filter*col_filter*i]=input[0][i+out_row][0+out_col][2]; 
            

             input_to_CGRA[3+C_filter*0+C_filter*col_filter*i]=input[0][i+out_row][0+out_col][3]; 
            

             input_to_CGRA[4+C_filter*0+C_filter*col_filter*i]=input[0][i+out_row][0+out_col][4]; 
            

             input_to_CGRA[5+C_filter*0+C_filter*col_filter*i]=input[0][i+out_row][0+out_col][5]; 
            

             input_to_CGRA[6+C_filter*0+C_filter*col_filter*i]=input[0][i+out_row][0+out_col][6]; 
            
             input_to_CGRA[7+C_filter*0+C_filter*col_filter*i]=input[0][i+out_row][0+out_col][7]; 
            
             input_to_CGRA[8+C_filter*0+C_filter*col_filter*i]=input[0][i+out_row][0+out_col][8]; 
            
             input_to_CGRA[9+C_filter*0+C_filter*col_filter*i]=input[0][i+out_row][0+out_col][9]; 
           

             input_to_CGRA[10+C_filter*0+C_filter*col_filter*i]=input[0][i+out_row][0+out_col][10]; 
            
             input_to_CGRA[11+C_filter*0+C_filter*col_filter*i]=input[0][i+out_row][0+out_col][11]; 
           

             input_to_CGRA[12+C_filter*0+C_filter*col_filter*i]=input[0][i+out_row][0+out_col][12]; 
            

             input_to_CGRA[13+C_filter*0+C_filter*col_filter*i]=input[0][i+out_row][0+out_col][13]; 
           

             input_to_CGRA[14+C_filter*0+C_filter*col_filter*i]=input[0][i+out_row][0+out_col][14]; 
           

             input_to_CGRA[15+C_filter*0+C_filter*col_filter*i]=input[0][i+out_row][0+out_col][15]; 
           

                          
              input_to_CGRA[0+C_filter*1+C_filter*col_filter*i]=input[0][i+out_row][1+out_col][0]; 
            
              input_to_CGRA[1+C_filter*1+C_filter*col_filter*i]=input[0][i+out_row][1+out_col][1]; 
           

             input_to_CGRA[2+C_filter*1+C_filter*col_filter*i]=input[0][i+out_row][1+out_col][2]; 
            

             input_to_CGRA[3+C_filter*1+C_filter*col_filter*i]=input[0][i+out_row][1+out_col][3]; 
            
             input_to_CGRA[4+C_filter*1+C_filter*col_filter*i]=input[0][i+out_row][1+out_col][4]; 
          

             input_to_CGRA[5+C_filter*1+C_filter*col_filter*i]=input[0][i+out_row][1+out_col][5]; 
            
             input_to_CGRA[6+C_filter*1+C_filter*col_filter*i]=input[0][i+out_row][1+out_col][6]; 
           
             input_to_CGRA[7+C_filter*1+C_filter*col_filter*i]=input[0][i+out_row][1+out_col][7]; 
            

             input_to_CGRA[8+C_filter*1+C_filter*col_filter*i]=input[0][i+out_row][1+out_col][8]; 
           

             input_to_CGRA[9+C_filter*1+C_filter*col_filter*i]=input[0][i+out_row][1+out_col][9]; 
            

             input_to_CGRA[10+C_filter*1+C_filter*col_filter*i]=input[0][i+out_row][1+out_col][10]; 
            
             input_to_CGRA[11+C_filter*1+C_filter*col_filter*i]=input[0][i+out_row][1+out_col][11]; 
           

             input_to_CGRA[12+C_filter*1+C_filter*col_filter*i]=input[0][i+out_row][1+out_col][12]; 
           

             input_to_CGRA[13+C_filter*1+C_filter*col_filter*i]=input[0][i+out_row][1+out_col][13]; 
          

             input_to_CGRA[14+C_filter*1+C_filter*col_filter*i]=input[0][i+out_row][1+out_col][14]; 
           
             input_to_CGRA[15+C_filter*1+C_filter*col_filter*i]=input[0][i+out_row][1+out_col][15]; 
           
              input_to_CGRA[0+C_filter*2+C_filter*col_filter*i]=input[0][i+out_row][2+out_col][0]; 
            
             input_to_CGRA[1+C_filter*2+C_filter*col_filter*i]=input[0][i+out_row][2+out_col][1]; 
           

             input_to_CGRA[2+C_filter*2+C_filter*col_filter*i]=input[0][i+out_row][2+out_col][2]; 
        
             input_to_CGRA[3+C_filter*2+C_filter*col_filter*i]=input[0][i+out_row][2+out_col][3]; 
           

             input_to_CGRA[4+C_filter*2+C_filter*col_filter*i]=input[0][i+out_row][2+out_col][4]; 
           

             input_to_CGRA[5+C_filter*2+C_filter*col_filter*i]=input[0][i+out_row][2+out_col][5]; 
           

             input_to_CGRA[6+C_filter*2+C_filter*col_filter*i]=input[0][i+out_row][2+out_col][6]; 
           

             input_to_CGRA[7+C_filter*2+C_filter*col_filter*i]=input[0][i+out_row][2+out_col][7]; 
           

             input_to_CGRA[8+C_filter*2+C_filter*col_filter*i]=input[0][i+out_row][2+out_col][8]; 
           

             input_to_CGRA[9+C_filter*2+C_filter*col_filter*i]=input[0][i+out_row][2+out_col][9]; 
          

             input_to_CGRA[10+C_filter*2+C_filter*col_filter*i]=input[0][i+out_row][2+out_col][10]; 
         
             input_to_CGRA[11+C_filter*2+C_filter*col_filter*i]=input[0][i+out_row][2+out_col][11]; 
          

             input_to_CGRA[12+C_filter*2+C_filter*col_filter*i]=input[0][i+out_row][2+out_col][12]; 
          
             input_to_CGRA[13+C_filter*2+C_filter*col_filter*i]=input[0][i+out_row][2+out_col][13]; 
          

             input_to_CGRA[14+C_filter*2+C_filter*col_filter*i]=input[0][i+out_row][2+out_col][14]; 
           

             input_to_CGRA[15+C_filter*2+C_filter*col_filter*i]=input[0][i+out_row][2+out_col][15]; 
          
#endif
            
          }

        }
      
    
  









