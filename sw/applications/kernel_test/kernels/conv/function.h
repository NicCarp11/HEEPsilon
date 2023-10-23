// Adapted from https://github.com/pulp-platform/pulpino/tree/master/sw/apps/sequential_tests/convolution
#include <stdint.h>

#define DATA_WIDTH  14
#define IMG_ROW     9
#define IMG_COL     3
#define IMG_DIM     IMG_ROW*IMG_COL



#define FILT_WIN    3
#define FILT_DIM    FILT_WIN*FILT_WIN

#define FILT_HALF   FILT_WIN/2

typedef int16_t    Filtc;
typedef int16_t    Pixel;

// static Pixel In_Img[IMG_DIM]        = { 6674, 2269, 7298, 4660, 2129, 6392, 3988, 7413, 5563, 6599, 1420, 5459, 6753, 4353, 4933, 5305, 4456, 364, 6298, 4, 4524, 866, 444, 4892, 2770, 5601, 6406, 487, 4569, 3476, 6629, 6464, 7420, 378, 7859, 3845, 6554, 3193, 3571, 8026, 3240, 4725, 3203, 4417, 8050, 2664, 3168, 5563, 5907, 6184, 1370, 7090, 5160, 1164, 1451, 2457, 2408, 1082, 824, 2587, 2568, 3517, 6133, 6982, 1040, 796, 4483, 98, 3534, 1980, 3660, 3595, 3010, 1499, 6811, 5719, 5982, 865, 7504, 5208, 4280, 1989, 7061, 5018, 262, 1364, 5430, 1099, 6114, 5921, 2409, 6330, 1362, 1023, 985, 4142, 7482, 6746, 1136, 2762, 7460, 3309, 2510, 910, 8094, 1966, 6581, 5460, 2817, 5005, 9, 7743, 8140, 3624, 8109, 8110, 5036, 5087, 2710, 1742, 85, 904, 1945, 5705, 5099, 200, 4301, 5207, 5180, 5692, 1223, 1329, 1490, 790, 4166, 2114, 309, 7262, 495, 1459, 4785, 6380, 3788, 1712, 1791, 5634, 4214, 4323, 2969, 4700, 7360, 7331, 397, 963, 4349, 1027, 8093, 2377, 2669, 7790, 799, 2598, 2110, 6507, 2161, 1081, 4184, 3348, 7251, 235, 3271, 1049, 883, 3469, 3476, 5810, 867, 2943, 7244, 3928, 406, 427, 968, 585, 5472, 5249, 750, 1066, 1396, 2601, 4477, 3637, 2281, 7784, 6887, 2549, 1192, 7717, 6698, 4873, 7482, 4013, 4316, 8184, 7424, 744, 3776, 1935, 899, 6032, 4817, 6565, 4011, 7628, 8097, 1986, 4944, 2694, 3320, 757, 2112, 5355, 3268, 492, 4480, 282, 2083, 4330, 1115, 7833, 6511, 2148, 6522, 1376, 3414, 1402, 7206, 2183, 6309, 978, 521, 3233, 1268, 1866, 1577, 5969, 4424, 440, 4310, 5356, 859, 64, 3251, 7839, 3400, 7100, 7844, 3594, 6671, 1357, 7121, 4712, 5278, 4938, 809, 8017, 5381, 267, 6699, 1259, 2642, 4975, 3314, 5599, 1637, 4080, 1008, 6044, 5791, 3619, 5978, 6137, 920, 3466, 606, 7666, 1481, 5171, 7904, 3126, 1995, 4931, 4749, 490, 3102, 5826, 2145, 5838, 5144, 4597, 2136, 2302, 6429, 3688, 3673, 5768, 3334, 7380, 1683, 519, 8188, 109, 5794, 4777, 6426, 5370, 5604, 3751, 2092, 2909, 1291, 6271, 7613, 2154, 4504, 1923, 6648, 1817, 2747, 4100, 2392, 7224, 4869, 3605, 3861, 3758, 2997, 3623, 6133, 4708, 1200, 7049, 2358, 7350, 6401, 6062, 2389, 5922, 3296, 1970, 168, 8167, 7951, 6514, 2867, 5358, 1187, 2893, 4365, 962, 5568, 3859, 3536, 5482, 184, 4318, 293, 5423, 6255, 160, 6763, 6924, 1549, 7655, 3396, 1611, 2359, 1924, 4944, 4352, 8051, 6258, 7567, 1836, 7841, 1531, 1611, 5646, 6988, 6727, 2873, 2430, 1119, 488, 127, 1560, 3484, 3747, 1441, 6310, 5144, 2710, 6471, 6051, 349, 8064, 3808, 765, 5673, 6021, 7901, 891, 3295, 6220, 5355, 5345, 3976, 4012, 2057, 6129, 5096, 126, 7692, 2611, 5908, 5587, 8061, 3022, 2562, 7171, 5913, 2869, 6324, 3476, 2609, 4800, 5204, 7036, 6258, 2518, 4560, 7951, 3543, 5175, 5085, 6067, 7640, 4956, 6556, 3650, 5047, 3691, 2875, 352, 7176, 3475, 875, 348, 1369, 3774, 1323, 4244, 3879, 5423, 7642, 2214, 4375, 2021, 2309, 6435, 6703, 3736, 3248, 7102, 5691, 1036, 1265, 6092, 1339, 3172, 1162, 5295, 3877, 687, 4205, 1384, 4507, 4160, 5356, 585, 870, 8042, 1464, 7730, 1251, 3409, 7969, 1614, 737, 5459, 4412, 4206, 821, 833, 505, 706, 6210, 1100, 3124, 868, 7546, 1165, 3455, 5811, 2881, 1876, 3292, 5318, 5099, 701, 4048, 4273, 3051, 1281, 3464, 5224, 2794, 6897, 1573, 6732, 915, 684, 5695, 1455, 1459, 8154, 6391, 3002, 3544, 808, 1320, 5583, 6510, 206, 7502, 6182, 6806, 7482, 622, 5994, 4809, 2150, 6382, 792, 1623, 7008, 772, 7845, 4976, 6823, 1138, 3522, 1117, 5128, 4089, 3265, 2946, 2721, 2765, 3024, 5370, 1163, 6210, 3795, 4730, 3450, 6490, 2261, 4794, 1248, 1965, 5306, 1702, 6562, 5858, 6702, 4012, 5282, 4903, 1972, 1571, 2101, 5704, 7273, 5560, 5414, 4389, 1097, 465, 2436, 4980, 5612, 899, 1378, 7136, 1738, 3605, 1508, 7860, 5568, 4503, 6765, 1010, 3694, 2468, 239, 7403, 6697, 2781, 3082, 3858, 5539, 6049, 5025, 769, 3205, 4056, 5978, 3647, 253, 4275, 508, 6072, 4898, 7649, 1608, 2874, 807, 2110, 5946, 5372, 5367, 7514, 4410, 1507, 4481, 3858, 7609, 7298, 5918, 7796, 1564, 5701, 2368, 1989, 4770, 4304, 6301, 1554, 7297, 1015, 7693, 2751, 2443, 859, 6466, 1536, 2601, 5616, 6747, 6160, 3034, 293, 1332, 2342, 8160, 1966, 2427, 1888, 5983, 2737, 1228, 7539, 3508, 5733, 5503, 7516, 4430, 4345, 3251, 4055, 8047, 4017, 2468, 1439, 380, 1048, 3012, 2181, 2592, 2410, 1434, 1873, 6894, 6956, 975, 6203, 640, 3418, 6101, 6917, 4003, 5724, 5403, 432, 3949, 5231, 5695, 2204, 7127, 7054, 6623, 1209, 6300, 6988, 2421, 1712, 4140, 4502, 1688, 6536, 1782, 4347, 1340, 526, 6015, 7651, 4083, 6175, 3626, 407, 1548, 1596, 4739, 1620, 4248, 6045, 988, 275, 557, 6271, 2169, 3972, 6186, 450, 4763, 7159, 2727, 7415, 6238, 3975, 710, 3994, 2057, 6819, 5456, 6286, 4678, 5560, 7862, 3117, 874, 7395, 5626, 1851, 1944, 250, 7971, 2205, 4829, 564, 2087, 1546, 2606, 3223, 3092, 6969, 7605, 2214, 3826, 5533, 5170, 7295, 6324, 6299, 7315, 4895, 7327, 5498, 1449, 6207, 2788, 4652, 7880, 7740, 1503, 1398, 3759, 6095, 5317, 3464, 1853, 2618, 1835, 2355, 977, 5500, 1770, 4592, 4752, 1708, 5310, 3838, 736, 6545, 1685, 3244, 5761, 2747, 4232, 5859, 7843, 6088, 4795, 621, 38, 4021, 3019, 1865, 7890, 4096, 6556, 4488, 3151, 4349, 5471, 746, 7699, 6072, 6475, 7615, 139, 4628, 207, 7472, 662, 6016, 3181, 2236, 4553, 2451, 5757, 5260, 2174, 3213, 1833, 442, 6348, 4008, 5125, 3569, 4479, 3932, 3718, 7723, 4776, 5361, 6917, 4720, 5288, 4260, 7777, 5707, 990, 5245, 6899, 852, 6367, 421, 4520, 305, 1511, 3708, 1258, 3433, 7574, 5370, 6154, 4348, 6695, 2767, 6392, 2549, 4269, 7411, 3542, 3422, 2063, 3339, 2822, 5598, 3928, 2848, 2683, 4774, 7067, 3416, 4580, 6108, 7415, 597, 1876, 5516, 1737, 3462, 7811, 3201, 1833, 1402, 2090, 6383, 7116, 7373, 665, 7564, 1897, 4996, 6761, 8053, 2379, 6717, 6394, 4478, 5237, 1229, 5499, 6680, 3967, 1687, 6997, 6032, 4373, 725, 5259, 3519, 634, 2946, 4431, 6686, 3060, 5784, 4145, 7651, 692, 3025, 7614, 3524, 4005, 5060, 684, 2470, 5055, 5885, 5532, 3488, 4462, 4801, 3593, 7201, 6921, 7765, 2850, 4603, 894, 6540, 3969, 3701, 7486, 4574, 5568, 2600, 717, 261, 5727, 1064, 3275, 911, 6355, 1514, 5112, 7041, 1091, 5743, 2173, 7935, 55, 5279, 5303, 2147, 6828, 8101, 1715, 672, 3654, 1509, 6765, 7725, 1244, 4996, 5789, 6083, 300, 6673, 5244, };
static Pixel In_Img[IMG_DIM]        = { 1,1,1, 2,2,2, 3,3,3, 4,4,4, 5,5,5, 6,6,6, 7,7,7, 8,8,8, 9,9,9 };

static Filtc Filter_Kern[FILT_DIM]  = { 2, 2, 2, 2, 2, 2, 2, 2, 2};

// static Pixel Gold_Out_Img[IMG_DIM]  = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1107, 0, 0, 1586, 0, 0, 580, 0, 0, 0, 6978, 3177, 0, 0, 3691, 0, 0, 8191, 8191, 3772, 526, 260, 0, 0, 0, 0, 5911, 0, 0, 0, 0, 0, 6496, 0, 0, 2654, 0, 0, 0, 0, 0, 0, 2242, 1291, 0, 0, 0, 0, 0, 8191, 8191, 630, 2714, 7323, 3784, 0, 0, 0, 6835, 1700, 0, 0, 0, 0, 6682, 600, 80, 0, 0, 0, 0, 2494, 2933, 0, 0, 0, 773, 0, 0, 0, 0, 8191, 6585, 0, 1159, 7808, 5379, 181, 0, 0, 350, 0, 0, 0, 0, 0, 3673, 4747, 0, 0, 0, 0, 2600, 6683, 1781, 0, 0, 584, 3016, 4244, 0, 0, 0, 8191, 3543, 0, 1526, 3575, 1496, 5406, 5599, 0, 0, 0, 0, 0, 0, 0, 2610, 4523, 0, 0, 0, 2022, 4904, 6901, 0, 0, 3510, 4624, 4239, 5577, 0, 0, 0, 4639, 0, 0, 5921, 2722, 0, 8191, 8191, 0, 0, 0, 0, 0, 0, 0, 2417, 217, 0, 0, 3259, 5079, 2023, 3454, 676, 0, 3018, 5290, 3832, 4171, 0, 0, 999, 661, 0, 0, 6848, 2902, 0, 8191, 8191, 0, 0, 0, 0, 0, 0, 0, 2251, 0, 0, 0, 2341, 4463, 0, 0, 4001, 1831, 1758, 1468, 48, 1529, 0, 0, 2440, 2676, 0, 0, 1995, 568, 0, 6545, 8191, 0, 0, 0, 0, 0, 0, 0, 3540, 1527, 1923, 0, 0, 2290, 0, 0, 1775, 4485, 3919, 0, 0, 0, 0, 0, 444, 6657, 649, 0, 0, 0, 0, 3257, 4292, 309, 2130, 4606, 0, 0, 0, 0, 5202, 5155, 3720, 0, 0, 1824, 0, 0, 0, 2548, 5431, 356, 0, 0, 156, 0, 0, 7688, 2350, 0, 522, 0, 0, 387, 0, 0, 4019, 5326, 0, 0, 0, 0, 3268, 1274, 2228, 1579, 4064, 2993, 0, 0, 0, 0, 2575, 341, 0, 0, 2169, 0, 0, 5892, 257, 0, 7326, 1224, 0, 0, 403, 0, 0, 603, 0, 0, 0, 0, 0, 0, 2052, 3484, 4941, 4637, 533, 0, 0, 0, 0, 0, 0, 0, 3459, 22, 0, 2033, 0, 0, 8191, 2513, 0, 0, 5936, 1601, 0, 0, 0, 0, 0, 0, 0, 0, 3677, 0, 0, 6148, 3555, 0, 0, 0, 0, 0, 0, 0, 4421, 6087, 0, 0, 0, 0, 8191, 3753, 0, 0, 8191, 5313, 0, 0, 0, 0, 0, 0, 2126, 2819, 2679, 0, 0, 6446, 7647, 0, 0, 0, 0, 0, 0, 0, 5390, 8191, 1480, 0, 0, 0, 8191, 4234, 0, 0, 8191, 7440, 0, 0, 0, 0, 0, 0, 6874, 4928, 0, 0, 0, 4814, 7680, 2582, 0, 0, 0, 0, 0, 0, 5808, 8191, 1857, 0, 0, 3142, 3122, 600, 0, 0, 6596, 6609, 0, 0, 0, 0, 0, 0, 8191, 5960, 0, 0, 1759, 2200, 3804, 4263, 0, 0, 0, 0, 0, 438, 5258, 8191, 1451, 0, 611, 6028, 0, 0, 345, 1996, 5387, 2225, 0, 0, 0, 0, 0, 0, 7886, 8048, 0, 0, 1138, 0, 186, 5415, 23, 0, 0, 0, 521, 2253, 2000, 2777, 207, 0, 5966, 7624, 0, 0, 0, 4266, 5926, 0, 0, 0, 0, 0, 0, 0, 7339, 8191, 1406, 0, 0, 0, 0, 6710, 4621, 0, 0, 67, 997, 878, 0, 0, 0, 3237, 8191, 8191, 0, 0, 0, 2935, 7543, 0, 0, 1811, 0, 0, 0, 0, 5417, 8191, 4992, 0, 0, 0, 0, 6334, 8191, 2563, 0, 465, 1004, 786, 0, 0, 0, 4217, 8191, 7636, 1791, 0, 0, 0, 7962, 1029, 0, 185, 0, 0, 0, 0, 162, 8191, 7067, 0, 0, 0, 0, 3582, 6824, 2738, 0, 0, 368, 865, 1476, 0, 0, 1483, 8191, 8191, 6379, 0, 0, 0, 5094, 377, 0, 0, 0, 0, 0, 0, 0, 6186, 4661, 0, 0, 0, 1581, 1773, 2344, 137, 0, 0, 0, 0, 2986, 3387, 0, 0, 8191, 8191, 6243, 228, 0, 0, 1072, 0, 0, 0, 0, 0, 0, 0, 1207, 5345, 674, 0, 0, 0, 892, 1098, 3159, 1320, 0, 0, 0, 0, 1451, 5935, 0, 0, 7837, 8191, 867, 537, 2038, 0, 0, 0, 280, 371, 0, 0, 0, 0, 7274, 4640, 70, 0, 773, 0, 0, 0, 7293, 7750, 376, 0, 0, 0, 0, 1816, 0, 0, 5087, 2891, 0, 696, 5630, 1208, 0, 0, 0, 950, 0, 0, 0, 0, 6199, 0, 2559, 8191, 3106, 0, 0, 0, 8191, 8191, 3151, 0, 0, 0, 0, 0, 0, 2218, 4016, 0, 0, 0, 2877, 1992, 0, 0, 0, 0, 0, 0, 0, 0, 1910, 0, 3526, 8191, 0, 0, 0, 1556, 8191, 7492, 2267, 639, 0, 0, 0, 0, 1967, 7440, 1997, 0, 0, 0, 0, 2729, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1020, 5820, 0, 0, 0, 2022, 6648, 3752, 0, 1542, 0, 0, 0, 428, 8191, 8191, 0, 0, 1366, 1094, 1794, 3696, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 369, 2950, 0, 0, 0, 821, 4210, 2196, 0, 0, 98, 0, 0, 0, 7923, 6146, 0, 0, 2103, 7055, 6029, 2358, 999, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3471, 3304, 0, 0, 0, 940, 4429, 1104, 0, 0, 2947, 4275, 0, 0, 771, 4827, 0, 0, 2843, 8191, 7074, 0, 1606, 0, 0, 0, 0, 0, 0, 0, 0, 1728, 2815, 1910, 1361, 0, 0, 1277, 2125, 0, 0, 723, 4373, 5309, 0, 0, 0, 6040, 1733, 0, 3251, 8191, 3493, 0, 569, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };


void conv2D ( Pixel * Out_Img )
{
  int32_t r, c, k, i, j, w, t;
  Filtc coeff;
  Pixel data;
  int32_t S;

  //image board is black
  for (r=FILT_HALF; r < IMG_ROW-FILT_HALF; r++) {
    for (c=FILT_HALF; c < IMG_COL-FILT_HALF; c++) {

        S = 0;
        t = r*IMG_ROW + c;
        //move in the window
        /* Coordinate window
            (-2;-2) (-2;-1) (-2; 0) (-2;+1) (-2;+2)
            (-1;-2) (-1;-1) (-1; 0) (-1;+1) (-1;+2)
            ( 0;-2) ( 0;-1) ( 0; 0) ( 0;+1) ( 0;+2)
            (+1;-2) (+1;-1) (+1; 0) (+1;+1) (+1;+2)
            (+2;-2) (+2;-1) (+2; 0) (+2;+1) (+2;+2)
        */
        for (i = -FILT_HALF; i <= FILT_HALF; i++) {
            for (j = -FILT_HALF; j <= FILT_HALF; j++) {

                k = (r+i)*IMG_ROW + (c+j); //coeff for one dimension matrix
                data = In_Img[k];
                w = (i+FILT_HALF)*FILT_WIN + (j+FILT_HALF);
                coeff = Filter_Kern[w];
                S += (int32_t)(coeff*data);
            }
        }

        Out_Img[t] = S;

    }
  }
}