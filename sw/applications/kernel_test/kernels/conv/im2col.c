#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "conv.h"
// im2col parameters

#define col_im2col (row_filter * col_filter * C_filter)
#define row_im2col (row_output * col_output)




void __attribute__((optimize("Os"))) im2col_conv(int32_t *input_to_CGRA, int out_row, int out_col, int output_channel)
{

  int i, j, k, l, c, m, n, o, p, q, r, s, t, u, v, w;


for (i = 0; i < row_filter; i++)
      {

input_to_CGRA[0 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][0];
input_to_CGRA[1 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][1];
input_to_CGRA[2 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][2];
input_to_CGRA[3 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][3];
input_to_CGRA[4 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][4];
input_to_CGRA[5 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][5];
input_to_CGRA[6 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][6];
input_to_CGRA[7 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][7];
input_to_CGRA[8 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][8];
input_to_CGRA[9 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][9];
input_to_CGRA[10 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][10];
input_to_CGRA[11 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][11];
input_to_CGRA[12 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][12];
input_to_CGRA[13 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][13];
input_to_CGRA[14 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][14];
input_to_CGRA[15 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][15];
input_to_CGRA[16 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][16];
input_to_CGRA[17 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][17];
input_to_CGRA[18 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][18];
input_to_CGRA[19 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][19];
input_to_CGRA[20 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][20];
input_to_CGRA[21 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][21];
input_to_CGRA[22 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][22];
input_to_CGRA[23 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][23];
input_to_CGRA[24 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][24];
input_to_CGRA[25 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][25];
input_to_CGRA[26 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][26];
input_to_CGRA[27 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][27];
input_to_CGRA[28 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][28];
input_to_CGRA[29 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][29];
input_to_CGRA[30 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][30];
input_to_CGRA[31 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][31];
input_to_CGRA[32 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][32];
input_to_CGRA[33 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][33];
input_to_CGRA[34 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][34];
input_to_CGRA[35 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][35];
input_to_CGRA[36 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][36];
input_to_CGRA[37 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][37];
input_to_CGRA[38 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][38];
input_to_CGRA[39 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][39];
input_to_CGRA[40 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][40];
input_to_CGRA[41 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][41];
input_to_CGRA[42 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][42];
input_to_CGRA[43 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][43];
input_to_CGRA[44 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][44];
input_to_CGRA[45 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][45];
input_to_CGRA[46 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][46];
input_to_CGRA[47 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][47];
input_to_CGRA[48 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][48];
input_to_CGRA[49 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][49];
input_to_CGRA[50 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][50];
input_to_CGRA[51 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][51];
input_to_CGRA[52 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][52];
input_to_CGRA[53 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][53];
input_to_CGRA[54 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][54];
input_to_CGRA[55 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][55];
input_to_CGRA[56 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][56];
input_to_CGRA[57 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][57];
input_to_CGRA[58 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][58];
input_to_CGRA[59 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][59];
input_to_CGRA[60 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][60];
input_to_CGRA[61 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][61];
input_to_CGRA[62 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][62];
input_to_CGRA[63 + C_filter * 0 + C_filter * col_filter*i] = input[0][i+out_row][0+out_col][63];
input_to_CGRA[0 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][0];
input_to_CGRA[1 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][1];
input_to_CGRA[2 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][2];
input_to_CGRA[3 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][3];
input_to_CGRA[4 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][4];
input_to_CGRA[5 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][5];
input_to_CGRA[6 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][6];
input_to_CGRA[7 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][7];
input_to_CGRA[8 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][8];
input_to_CGRA[9 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][9];
input_to_CGRA[10 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][10];
input_to_CGRA[11 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][11];
input_to_CGRA[12 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][12];
input_to_CGRA[13 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][13];
input_to_CGRA[14 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][14];
input_to_CGRA[15 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][15];
input_to_CGRA[16 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][16];
input_to_CGRA[17 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][17];
input_to_CGRA[18 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][18];
input_to_CGRA[19 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][19];
input_to_CGRA[20 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][20];
input_to_CGRA[21 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][21];
input_to_CGRA[22 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][22];
input_to_CGRA[23 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][23];
input_to_CGRA[24 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][24];
input_to_CGRA[25 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][25];
input_to_CGRA[26 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][26];
input_to_CGRA[27 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][27];
input_to_CGRA[28 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][28];
input_to_CGRA[29 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][29];
input_to_CGRA[30 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][30];
input_to_CGRA[31 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][31];
input_to_CGRA[32 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][32];
input_to_CGRA[33 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][33];
input_to_CGRA[34 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][34];
input_to_CGRA[35 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][35];
input_to_CGRA[36 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][36];
input_to_CGRA[37 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][37];
input_to_CGRA[38 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][38];
input_to_CGRA[39 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][39];
input_to_CGRA[40 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][40];
input_to_CGRA[41 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][41];
input_to_CGRA[42 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][42];
input_to_CGRA[43 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][43];
input_to_CGRA[44 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][44];
input_to_CGRA[45 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][45];
input_to_CGRA[46 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][46];
input_to_CGRA[47 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][47];
input_to_CGRA[48 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][48];
input_to_CGRA[49 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][49];
input_to_CGRA[50 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][50];
input_to_CGRA[51 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][51];
input_to_CGRA[52 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][52];
input_to_CGRA[53 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][53];
input_to_CGRA[54 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][54];
input_to_CGRA[55 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][55];
input_to_CGRA[56 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][56];
input_to_CGRA[57 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][57];
input_to_CGRA[58 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][58];
input_to_CGRA[59 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][59];
input_to_CGRA[60 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][60];
input_to_CGRA[61 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][61];
input_to_CGRA[62 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][62];
input_to_CGRA[63 + C_filter * 1 + C_filter * col_filter*i] = input[0][i+out_row][1+out_col][63];
input_to_CGRA[0 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][0];
input_to_CGRA[1 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][1];
input_to_CGRA[2 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][2];
input_to_CGRA[3 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][3];
input_to_CGRA[4 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][4];
input_to_CGRA[5 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][5];
input_to_CGRA[6 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][6];
input_to_CGRA[7 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][7];
input_to_CGRA[8 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][8];
input_to_CGRA[9 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][9];
input_to_CGRA[10 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][10];
input_to_CGRA[11 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][11];
input_to_CGRA[12 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][12];
input_to_CGRA[13 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][13];
input_to_CGRA[14 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][14];
input_to_CGRA[15 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][15];
input_to_CGRA[16 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][16];
input_to_CGRA[17 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][17];
input_to_CGRA[18 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][18];
input_to_CGRA[19 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][19];
input_to_CGRA[20 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][20];
input_to_CGRA[21 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][21];
input_to_CGRA[22 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][22];
input_to_CGRA[23 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][23];
input_to_CGRA[24 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][24];
input_to_CGRA[25 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][25];
input_to_CGRA[26 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][26];
input_to_CGRA[27 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][27];
input_to_CGRA[28 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][28];
input_to_CGRA[29 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][29];
input_to_CGRA[30 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][30];
input_to_CGRA[31 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][31];
input_to_CGRA[32 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][32];
input_to_CGRA[33 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][33];
input_to_CGRA[34 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][34];
input_to_CGRA[35 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][35];
input_to_CGRA[36 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][36];
input_to_CGRA[37 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][37];
input_to_CGRA[38 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][38];
input_to_CGRA[39 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][39];
input_to_CGRA[40 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][40];
input_to_CGRA[41 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][41];
input_to_CGRA[42 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][42];
input_to_CGRA[43 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][43];
input_to_CGRA[44 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][44];
input_to_CGRA[45 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][45];
input_to_CGRA[46 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][46];
input_to_CGRA[47 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][47];
input_to_CGRA[48 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][48];
input_to_CGRA[49 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][49];
input_to_CGRA[50 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][50];
input_to_CGRA[51 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][51];
input_to_CGRA[52 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][52];
input_to_CGRA[53 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][53];
input_to_CGRA[54 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][54];
input_to_CGRA[55 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][55];
input_to_CGRA[56 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][56];
input_to_CGRA[57 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][57];
input_to_CGRA[58 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][58];
input_to_CGRA[59 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][59];
input_to_CGRA[60 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][60];
input_to_CGRA[61 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][61];
input_to_CGRA[62 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][62];
input_to_CGRA[63 + C_filter * 2 + C_filter * col_filter*i] = input[0][i+out_row][2+out_col][63];



                  
            
          }

        }
      
    
  









