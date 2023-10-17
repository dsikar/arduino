#include <avr/pgmspace.h>

#define ENCODER_STEP 4
// SPEEDS
#define SPEED_ARRAY_ENTRIES 58
const char speed_0[] PROGMEM = " 1.00"; 
const char speed_1[] PROGMEM = " 1.10"; 
const char speed_2[] PROGMEM = " 1.20"; 
const char speed_3[] PROGMEM = " 1.30"; 
const char speed_4[] PROGMEM = " 1.40"; 
const char speed_5[] PROGMEM = " 1.50"; 
const char speed_6[] PROGMEM = " 1.60"; 
const char speed_7[] PROGMEM = " 1.70"; 
const char speed_8[] PROGMEM = " 1.80"; 
const char speed_9[] PROGMEM = " 1.90"; 
const char speed_10[] PROGMEM = " 2.00"; 
const char speed_11[] PROGMEM = " 2.10"; 
const char speed_12[] PROGMEM = " 2.20"; 
const char speed_13[] PROGMEM = " 2.30"; 
const char speed_14[] PROGMEM = " 2.40"; 
const char speed_15[] PROGMEM = " 2.50"; 
const char speed_16[] PROGMEM = " 2.60"; 
const char speed_17[] PROGMEM = " 2.70"; 
const char speed_18[] PROGMEM = " 2.80"; 
const char speed_19[] PROGMEM = " 2.90"; 
const char speed_20[] PROGMEM = " 3.00"; 
const char speed_21[] PROGMEM = " 3.10"; 
const char speed_22[] PROGMEM = " 3.20"; 
const char speed_23[] PROGMEM = " 3.30"; 
const char speed_24[] PROGMEM = " 3.40"; 
const char speed_25[] PROGMEM = " 3.50"; 
const char speed_26[] PROGMEM = " 3.60"; 
const char speed_27[] PROGMEM = " 3.70"; 
const char speed_28[] PROGMEM = " 3.80"; 
const char speed_29[] PROGMEM = " 3.90"; 
const char speed_30[] PROGMEM = " 4.00"; 
const char speed_31[] PROGMEM = " 4.10"; 
const char speed_32[] PROGMEM = " 4.20"; 
const char speed_33[] PROGMEM = " 4.30"; 
const char speed_34[] PROGMEM = " 4.40"; 
const char speed_35[] PROGMEM = " 4.50"; 
const char speed_36[] PROGMEM = " 4.60"; 
const char speed_37[] PROGMEM = " 4.70"; 
const char speed_38[] PROGMEM = " 4.80"; 
const char speed_39[] PROGMEM = " 4.90"; 
const char speed_40[] PROGMEM = " 5.00"; 
const char speed_41[] PROGMEM = " 6.00"; 
const char speed_42[] PROGMEM = " 7.00"; 
const char speed_43[] PROGMEM = " 8.00"; 
const char speed_44[] PROGMEM = " 9.00"; 
const char speed_45[] PROGMEM = "10.00"; 
const char speed_46[] PROGMEM = "11.00"; 
const char speed_47[] PROGMEM = "12.00"; 
const char speed_48[] PROGMEM = "13.00"; 
const char speed_49[] PROGMEM = "14.00"; 
const char speed_50[] PROGMEM = "15.00"; 
const char speed_51[] PROGMEM = "16.00"; 
const char speed_52[] PROGMEM = "18.00"; 
const char speed_53[] PROGMEM = "20.00"; 
const char speed_54[] PROGMEM = "22.00"; 
const char speed_55[] PROGMEM = "24.00"; 
const char speed_56[] PROGMEM = "27.00"; 
const char speed_57[] PROGMEM = "30.00"; 

// REFERENCE ARRAY
const char * const speed_table[] PROGMEM = { 
    speed_0, 
    speed_1, 
    speed_2, 
    speed_3, 
    speed_4, 
    speed_5, 
    speed_6, 
    speed_7, 
    speed_8, 
    speed_9, 
    speed_10, 
    speed_11, 
    speed_12, 
    speed_13, 
    speed_14, 
    speed_15, 
    speed_16, 
    speed_17, 
    speed_18, 
    speed_19, 
    speed_20, 
    speed_21, 
    speed_22, 
    speed_23, 
    speed_24, 
    speed_25, 
    speed_26, 
    speed_27, 
    speed_28, 
    speed_29, 
    speed_30, 
    speed_31, 
    speed_32, 
    speed_33, 
    speed_34, 
    speed_35, 
    speed_36, 
    speed_37, 
    speed_38, 
    speed_39, 
    speed_40, 
    speed_41, 
    speed_42, 
    speed_43, 
    speed_44, 
    speed_45, 
    speed_46, 
    speed_47, 
    speed_48, 
    speed_49, 
    speed_50, 
    speed_51, 
    speed_52, 
    speed_53, 
    speed_54, 
    speed_55, 
    speed_56, 
    speed_57 
};
// FREQUENCIES - different declaration
// Using reduction gears, so uint32_t to accomodate
// greater values
const PROGMEM uint16_t frequencies[] = {
    60000, 
    54545, 
    49999, 
    46153, 
    42857, 
    39999, 
    37499, 
    35294, 
    33333, 
    31578, 
    29999, 
    28571, 
    27272, 
    26086, 
    24999, 
    23999, 
    23076, 
    22222, 
    21428, 
    20689, 
    19999, 
    19354, 
    18749, 
    18181, 
    17647, 
    17142, 
    16666, 
    16216, 
    15789, 
    15384, 
    14999, 
    14634, 
    14285, 
    13953, 
    13636, 
    13333, 
    13043, 
    12765, 
    12499, 
    12244, 
    12000, 
    10000, 
    8571, 
    7500, 
    6666, 
    6000, 
    5454, 
    5000, 
    4615, 
    4285, 
    4000, 
    3750, 
    3333, 
    3000, 
    2727, 
    2500, 
    2222, 
    2000
};
// distances
const char distance_0_0[] PROGMEM = " 0.0"; 
const char distance_0_1[] PROGMEM = " 0.1"; 
const char distance_0_2[] PROGMEM = " 0.2"; 
const char distance_0_3[] PROGMEM = " 0.3"; 
const char distance_0_4[] PROGMEM = " 0.4"; 
const char distance_0_5[] PROGMEM = " 0.5"; 
const char distance_0_6[] PROGMEM = " 0.6"; 
const char distance_0_7[] PROGMEM = " 0.7"; 
const char distance_0_8[] PROGMEM = " 0.8"; 
const char distance_0_9[] PROGMEM = " 0.9"; 
const char distance_1_0[] PROGMEM = " 1.0"; 
const char distance_1_1[] PROGMEM = " 1.1"; 
const char distance_1_2[] PROGMEM = " 1.2"; 
const char distance_1_3[] PROGMEM = " 1.3"; 
const char distance_1_4[] PROGMEM = " 1.4"; 
const char distance_1_5[] PROGMEM = " 1.5"; 
const char distance_1_6[] PROGMEM = " 1.6"; 
const char distance_1_7[] PROGMEM = " 1.7"; 
const char distance_1_8[] PROGMEM = " 1.8"; 
const char distance_1_9[] PROGMEM = " 1.9"; 
const char distance_2_0[] PROGMEM = " 2.0"; 
const char distance_2_1[] PROGMEM = " 2.1"; 
const char distance_2_2[] PROGMEM = " 2.2"; 
const char distance_2_3[] PROGMEM = " 2.3"; 
const char distance_2_4[] PROGMEM = " 2.4"; 
const char distance_2_5[] PROGMEM = " 2.5"; 
const char distance_2_6[] PROGMEM = " 2.6"; 
const char distance_2_7[] PROGMEM = " 2.7"; 
const char distance_2_8[] PROGMEM = " 2.8"; 
const char distance_2_9[] PROGMEM = " 2.9"; 
const char distance_3_0[] PROGMEM = " 3.0"; 
const char distance_3_1[] PROGMEM = " 3.1"; 
const char distance_3_2[] PROGMEM = " 3.2"; 
const char distance_3_3[] PROGMEM = " 3.3"; 
const char distance_3_4[] PROGMEM = " 3.4"; 
const char distance_3_5[] PROGMEM = " 3.5"; 
const char distance_3_6[] PROGMEM = " 3.6"; 
const char distance_3_7[] PROGMEM = " 3.7"; 
const char distance_3_8[] PROGMEM = " 3.8"; 
const char distance_3_9[] PROGMEM = " 3.9"; 
const char distance_4_0[] PROGMEM = " 4.0"; 
const char distance_4_1[] PROGMEM = " 4.1"; 
const char distance_4_2[] PROGMEM = " 4.2"; 
const char distance_4_3[] PROGMEM = " 4.3"; 
const char distance_4_4[] PROGMEM = " 4.4"; 
const char distance_4_5[] PROGMEM = " 4.5"; 
const char distance_4_6[] PROGMEM = " 4.6"; 
const char distance_4_7[] PROGMEM = " 4.7"; 
const char distance_4_8[] PROGMEM = " 4.8"; 
const char distance_4_9[] PROGMEM = " 4.9"; 
const char distance_5_0[] PROGMEM = " 5.0"; 
const char distance_5_1[] PROGMEM = " 5.1"; 
const char distance_5_2[] PROGMEM = " 5.2"; 
const char distance_5_3[] PROGMEM = " 5.3"; 
const char distance_5_4[] PROGMEM = " 5.4"; 
const char distance_5_5[] PROGMEM = " 5.5"; 
const char distance_5_6[] PROGMEM = " 5.6"; 
const char distance_5_7[] PROGMEM = " 5.7"; 
const char distance_5_8[] PROGMEM = " 5.8"; 
const char distance_5_9[] PROGMEM = " 5.9"; 
const char distance_6_0[] PROGMEM = " 6.0"; 
const char distance_6_1[] PROGMEM = " 6.1"; 
const char distance_6_2[] PROGMEM = " 6.2"; 
const char distance_6_3[] PROGMEM = " 6.3"; 
const char distance_6_4[] PROGMEM = " 6.4"; 
const char distance_6_5[] PROGMEM = " 6.5"; 
const char distance_6_6[] PROGMEM = " 6.6"; 
const char distance_6_7[] PROGMEM = " 6.7"; 
const char distance_6_8[] PROGMEM = " 6.8"; 
const char distance_6_9[] PROGMEM = " 6.9"; 
const char distance_7_0[] PROGMEM = " 7.0"; 
const char distance_7_1[] PROGMEM = " 7.1"; 
const char distance_7_2[] PROGMEM = " 7.2"; 
const char distance_7_3[] PROGMEM = " 7.3"; 
const char distance_7_4[] PROGMEM = " 7.4"; 
const char distance_7_5[] PROGMEM = " 7.5"; 
const char distance_7_6[] PROGMEM = " 7.6"; 
const char distance_7_7[] PROGMEM = " 7.7"; 
const char distance_7_8[] PROGMEM = " 7.8"; 
const char distance_7_9[] PROGMEM = " 7.9"; 
const char distance_8_0[] PROGMEM = " 8.0"; 
const char distance_8_1[] PROGMEM = " 8.1"; 
const char distance_8_2[] PROGMEM = " 8.2"; 
const char distance_8_3[] PROGMEM = " 8.3"; 
const char distance_8_4[] PROGMEM = " 8.4"; 
const char distance_8_5[] PROGMEM = " 8.5"; 
const char distance_8_6[] PROGMEM = " 8.6"; 
const char distance_8_7[] PROGMEM = " 8.7"; 
const char distance_8_8[] PROGMEM = " 8.8"; 
const char distance_8_9[] PROGMEM = " 8.9"; 
const char distance_9_0[] PROGMEM = " 9.0"; 
const char distance_9_1[] PROGMEM = " 9.1"; 
const char distance_9_2[] PROGMEM = " 9.2"; 
const char distance_9_3[] PROGMEM = " 9.3"; 
const char distance_9_4[] PROGMEM = " 9.4"; 
const char distance_9_5[] PROGMEM = " 9.5"; 
const char distance_9_6[] PROGMEM = " 9.6"; 
const char distance_9_7[] PROGMEM = " 9.7"; 
const char distance_9_8[] PROGMEM = " 9.8"; 
const char distance_9_9[] PROGMEM = " 9.9"; 
const char distance_10_0[] PROGMEM = "10.0"; 
const char distance_10_1[] PROGMEM = "10.1"; 
const char distance_10_2[] PROGMEM = "10.2"; 
const char distance_10_3[] PROGMEM = "10.3"; 
const char distance_10_4[] PROGMEM = "10.4"; 
const char distance_10_5[] PROGMEM = "10.5"; 
const char distance_10_6[] PROGMEM = "10.6"; 
const char distance_10_7[] PROGMEM = "10.7"; 
const char distance_10_8[] PROGMEM = "10.8"; 
const char distance_10_9[] PROGMEM = "10.9"; 
const char distance_11_0[] PROGMEM = "11.0"; 
const char distance_11_1[] PROGMEM = "11.1"; 
const char distance_11_2[] PROGMEM = "11.2"; 
const char distance_11_3[] PROGMEM = "11.3"; 
const char distance_11_4[] PROGMEM = "11.4"; 
const char distance_11_5[] PROGMEM = "11.5"; 
const char distance_11_6[] PROGMEM = "11.6"; 
const char distance_11_7[] PROGMEM = "11.7"; 
const char distance_11_8[] PROGMEM = "11.8"; 
const char distance_11_9[] PROGMEM = "11.9"; 
const char distance_12_0[] PROGMEM = "12.0"; 
const char distance_12_1[] PROGMEM = "12.1"; 
const char distance_12_2[] PROGMEM = "12.2"; 
const char distance_12_3[] PROGMEM = "12.3"; 
const char distance_12_4[] PROGMEM = "12.4"; 
const char distance_12_5[] PROGMEM = "12.5"; 
const char distance_12_6[] PROGMEM = "12.6"; 
const char distance_12_7[] PROGMEM = "12.7"; 
const char distance_12_8[] PROGMEM = "12.8"; 
const char distance_12_9[] PROGMEM = "12.9"; 
const char distance_13_0[] PROGMEM = "13.0"; 
const char distance_13_1[] PROGMEM = "13.1"; 
const char distance_13_2[] PROGMEM = "13.2"; 
const char distance_13_3[] PROGMEM = "13.3"; 
const char distance_13_4[] PROGMEM = "13.4"; 
const char distance_13_5[] PROGMEM = "13.5"; 
const char distance_13_6[] PROGMEM = "13.6"; 
const char distance_13_7[] PROGMEM = "13.7"; 
const char distance_13_8[] PROGMEM = "13.8"; 
const char distance_13_9[] PROGMEM = "13.9"; 
const char distance_14_0[] PROGMEM = "14.0"; 
const char distance_14_1[] PROGMEM = "14.1"; 
const char distance_14_2[] PROGMEM = "14.2"; 
const char distance_14_3[] PROGMEM = "14.3"; 
const char distance_14_4[] PROGMEM = "14.4"; 
const char distance_14_5[] PROGMEM = "14.5"; 
const char distance_14_6[] PROGMEM = "14.6"; 
const char distance_14_7[] PROGMEM = "14.7"; 
const char distance_14_8[] PROGMEM = "14.8"; 
const char distance_14_9[] PROGMEM = "14.9"; 
const char distance_15_0[] PROGMEM = "15.0"; 
const char distance_15_1[] PROGMEM = "15.1"; 
const char distance_15_2[] PROGMEM = "15.2"; 
const char distance_15_3[] PROGMEM = "15.3"; 
const char distance_15_4[] PROGMEM = "15.4"; 
const char distance_15_5[] PROGMEM = "15.5"; 
const char distance_15_6[] PROGMEM = "15.6"; 
const char distance_15_7[] PROGMEM = "15.7"; 
const char distance_15_8[] PROGMEM = "15.8"; 
const char distance_15_9[] PROGMEM = "15.9"; 
const char distance_16_0[] PROGMEM = "16.0"; 
const char distance_16_1[] PROGMEM = "16.1"; 
const char distance_16_2[] PROGMEM = "16.2"; 
const char distance_16_3[] PROGMEM = "16.3"; 
const char distance_16_4[] PROGMEM = "16.4"; 
const char distance_16_5[] PROGMEM = "16.5"; 
const char distance_16_6[] PROGMEM = "16.6"; 
const char distance_16_7[] PROGMEM = "16.7"; 
const char distance_16_8[] PROGMEM = "16.8"; 
const char distance_16_9[] PROGMEM = "16.9"; 
const char distance_17_0[] PROGMEM = "17.0"; 
const char distance_17_1[] PROGMEM = "17.1"; 
const char distance_17_2[] PROGMEM = "17.2"; 
const char distance_17_3[] PROGMEM = "17.3"; 
const char distance_17_4[] PROGMEM = "17.4"; 
const char distance_17_5[] PROGMEM = "17.5"; 
const char distance_17_6[] PROGMEM = "17.6"; 
const char distance_17_7[] PROGMEM = "17.7"; 
const char distance_17_8[] PROGMEM = "17.8"; 
const char distance_17_9[] PROGMEM = "17.9"; 
const char distance_18_0[] PROGMEM = "18.0"; 
const char distance_18_1[] PROGMEM = "18.1"; 
const char distance_18_2[] PROGMEM = "18.2"; 
const char distance_18_3[] PROGMEM = "18.3"; 
const char distance_18_4[] PROGMEM = "18.4"; 
const char distance_18_5[] PROGMEM = "18.5"; 
const char distance_18_6[] PROGMEM = "18.6"; 
const char distance_18_7[] PROGMEM = "18.7"; 
const char distance_18_8[] PROGMEM = "18.8"; 
const char distance_18_9[] PROGMEM = "18.9"; 
const char distance_19_0[] PROGMEM = "19.0"; 
const char distance_19_1[] PROGMEM = "19.1"; 
const char distance_19_2[] PROGMEM = "19.2"; 
const char distance_19_3[] PROGMEM = "19.3"; 
const char distance_19_4[] PROGMEM = "19.4"; 
const char distance_19_5[] PROGMEM = "19.5"; 
const char distance_19_6[] PROGMEM = "19.6"; 
const char distance_19_7[] PROGMEM = "19.7"; 
const char distance_19_8[] PROGMEM = "19.8"; 
const char distance_19_9[] PROGMEM = "19.9"; 
const char distance_20_0[] PROGMEM = "20.0"; 
const char distance_20_1[] PROGMEM = "20.1"; 
const char distance_20_2[] PROGMEM = "20.2"; 
const char distance_20_3[] PROGMEM = "20.3"; 
const char distance_20_4[] PROGMEM = "20.4"; 
const char distance_20_5[] PROGMEM = "20.5"; 
const char distance_20_6[] PROGMEM = "20.6"; 
const char distance_20_7[] PROGMEM = "20.7"; 
const char distance_20_8[] PROGMEM = "20.8"; 
const char distance_20_9[] PROGMEM = "20.9"; 
const char distance_21_0[] PROGMEM = "21.0"; 
const char distance_21_1[] PROGMEM = "21.1"; 
const char distance_21_2[] PROGMEM = "21.2"; 
const char distance_21_3[] PROGMEM = "21.3"; 
const char distance_21_4[] PROGMEM = "21.4"; 
const char distance_21_5[] PROGMEM = "21.5"; 
const char distance_21_6[] PROGMEM = "21.6"; 
const char distance_21_7[] PROGMEM = "21.7"; 
const char distance_21_8[] PROGMEM = "21.8"; 
const char distance_21_9[] PROGMEM = "21.9"; 
const char distance_22_0[] PROGMEM = "22.0"; 
const char distance_22_1[] PROGMEM = "22.1"; 
const char distance_22_2[] PROGMEM = "22.2"; 
const char distance_22_3[] PROGMEM = "22.3"; 
const char distance_22_4[] PROGMEM = "22.4"; 
const char distance_22_5[] PROGMEM = "22.5"; 
const char distance_22_6[] PROGMEM = "22.6"; 
const char distance_22_7[] PROGMEM = "22.7"; 
const char distance_22_8[] PROGMEM = "22.8"; 
const char distance_22_9[] PROGMEM = "22.9"; 
const char distance_23_0[] PROGMEM = "23.0"; 
const char distance_23_1[] PROGMEM = "23.1"; 
const char distance_23_2[] PROGMEM = "23.2"; 
const char distance_23_3[] PROGMEM = "23.3"; 
const char distance_23_4[] PROGMEM = "23.4"; 
const char distance_23_5[] PROGMEM = "23.5"; 
const char distance_23_6[] PROGMEM = "23.6"; 
const char distance_23_7[] PROGMEM = "23.7"; 
const char distance_23_8[] PROGMEM = "23.8"; 
const char distance_23_9[] PROGMEM = "23.9"; 
const char distance_24_0[] PROGMEM = "24.0"; 
const char distance_24_1[] PROGMEM = "24.1"; 
const char distance_24_2[] PROGMEM = "24.2"; 
const char distance_24_3[] PROGMEM = "24.3"; 
const char distance_24_4[] PROGMEM = "24.4"; 
const char distance_24_5[] PROGMEM = "24.5"; 
const char distance_24_6[] PROGMEM = "24.6"; 
const char distance_24_7[] PROGMEM = "24.7"; 
const char distance_24_8[] PROGMEM = "24.8"; 
const char distance_24_9[] PROGMEM = "24.9"; 
const char distance_25_0[] PROGMEM = "25.0"; 
const char distance_25_1[] PROGMEM = "25.1"; 
const char distance_25_2[] PROGMEM = "25.2"; 
const char distance_25_3[] PROGMEM = "25.3"; 
const char distance_25_4[] PROGMEM = "25.4"; 
const char distance_25_5[] PROGMEM = "25.5"; 
const char distance_25_6[] PROGMEM = "25.6"; 
const char distance_25_7[] PROGMEM = "25.7"; 
const char distance_25_8[] PROGMEM = "25.8"; 
const char distance_25_9[] PROGMEM = "25.9"; 
const char distance_26_0[] PROGMEM = "26.0"; 
const char distance_26_1[] PROGMEM = "26.1"; 
const char distance_26_2[] PROGMEM = "26.2"; 
const char distance_26_3[] PROGMEM = "26.3"; 
const char distance_26_4[] PROGMEM = "26.4"; 
const char distance_26_5[] PROGMEM = "26.5"; 
const char distance_26_6[] PROGMEM = "26.6"; 
const char distance_26_7[] PROGMEM = "26.7"; 
const char distance_26_8[] PROGMEM = "26.8"; 
const char distance_26_9[] PROGMEM = "26.9"; 
const char distance_27_0[] PROGMEM = "27.0"; 
const char distance_27_1[] PROGMEM = "27.1"; 
const char distance_27_2[] PROGMEM = "27.2"; 
const char distance_27_3[] PROGMEM = "27.3"; 
const char distance_27_4[] PROGMEM = "27.4"; 
const char distance_27_5[] PROGMEM = "27.5"; 
const char distance_27_6[] PROGMEM = "27.6"; 
const char distance_27_7[] PROGMEM = "27.7"; 
const char distance_27_8[] PROGMEM = "27.8"; 
const char distance_27_9[] PROGMEM = "27.9"; 
const char distance_28_0[] PROGMEM = "28.0"; 
const char distance_28_1[] PROGMEM = "28.1"; 
const char distance_28_2[] PROGMEM = "28.2"; 
const char distance_28_3[] PROGMEM = "28.3"; 
const char distance_28_4[] PROGMEM = "28.4"; 
const char distance_28_5[] PROGMEM = "28.5"; 
const char distance_28_6[] PROGMEM = "28.6"; 
const char distance_28_7[] PROGMEM = "28.7"; 
const char distance_28_8[] PROGMEM = "28.8"; 
const char distance_28_9[] PROGMEM = "28.9"; 
const char distance_29_0[] PROGMEM = "29.0"; 
const char distance_29_1[] PROGMEM = "29.1"; 
const char distance_29_2[] PROGMEM = "29.2"; 
const char distance_29_3[] PROGMEM = "29.3"; 
const char distance_29_4[] PROGMEM = "29.4"; 
const char distance_29_5[] PROGMEM = "29.5"; 
const char distance_29_6[] PROGMEM = "29.6"; 
const char distance_29_7[] PROGMEM = "29.7"; 
const char distance_29_8[] PROGMEM = "29.8"; 
const char distance_29_9[] PROGMEM = "29.9"; 
const char distance_30_0[] PROGMEM = "30.0"; 
const char distance_30_1[] PROGMEM = "30.1"; 
const char distance_30_2[] PROGMEM = "30.2"; 
const char distance_30_3[] PROGMEM = "30.3"; 
const char distance_30_4[] PROGMEM = "30.4"; 
const char distance_30_5[] PROGMEM = "30.5"; 
const char distance_30_6[] PROGMEM = "30.6"; 
const char distance_30_7[] PROGMEM = "30.7"; 
const char distance_30_8[] PROGMEM = "30.8"; 
const char distance_30_9[] PROGMEM = "30.9"; 
const char distance_31_0[] PROGMEM = "31.0"; 
const char distance_31_1[] PROGMEM = "31.1"; 
const char distance_31_2[] PROGMEM = "31.2"; 
const char distance_31_3[] PROGMEM = "31.3"; 
const char distance_31_4[] PROGMEM = "31.4"; 
const char distance_31_5[] PROGMEM = "31.5"; 
const char distance_31_6[] PROGMEM = "31.6"; 
const char distance_31_7[] PROGMEM = "31.7"; 
const char distance_31_8[] PROGMEM = "31.8"; 
const char distance_31_9[] PROGMEM = "31.9"; 
const char distance_32_0[] PROGMEM = "32.0"; 

// DISTANCE ARRAY REFERENCE
// Change this define to adjust distance
// with distance_table array adjustment 
#define DISTANCE_ARRAY_ENTRIES 311 // 31cm // we can go up to 321 (32cm)
// NB array contains 301 entry 
// address is unsigned int
const char * const distance_table[] PROGMEM = { 
    distance_0_0,
    distance_0_1,
    distance_0_2,
    distance_0_3,
    distance_0_4,
    distance_0_5,
    distance_0_6,
    distance_0_7,
    distance_0_8,
    distance_0_9,
    distance_1_0,
    distance_1_1,
    distance_1_2,
    distance_1_3,
    distance_1_4,
    distance_1_5,
    distance_1_6,
    distance_1_7,
    distance_1_8,
    distance_1_9,
    distance_2_0,
    distance_2_1,
    distance_2_2,
    distance_2_3,
    distance_2_4,
    distance_2_5,
    distance_2_6,
    distance_2_7,
    distance_2_8,
    distance_2_9,
    distance_3_0,
    distance_3_1,
    distance_3_2,
    distance_3_3,
    distance_3_4,
    distance_3_5,
    distance_3_6,
    distance_3_7,
    distance_3_8,
    distance_3_9,
    distance_4_0,
    distance_4_1,
    distance_4_2,
    distance_4_3,
    distance_4_4,
    distance_4_5,
    distance_4_6,
    distance_4_7,
    distance_4_8,
    distance_4_9,
    distance_5_0,
    distance_5_1,
    distance_5_2,
    distance_5_3,
    distance_5_4,
    distance_5_5,
    distance_5_6,
    distance_5_7,
    distance_5_8,
    distance_5_9,
    distance_6_0,
    distance_6_1,
    distance_6_2,
    distance_6_3,
    distance_6_4,
    distance_6_5,
    distance_6_6,
    distance_6_7,
    distance_6_8,
    distance_6_9,
    distance_7_0,
    distance_7_1,
    distance_7_2,
    distance_7_3,
    distance_7_4,
    distance_7_5,
    distance_7_6,
    distance_7_7,
    distance_7_8,
    distance_7_9,
    distance_8_0,
    distance_8_1,
    distance_8_2,
    distance_8_3,
    distance_8_4,
    distance_8_5,
    distance_8_6,
    distance_8_7,
    distance_8_8,
    distance_8_9,
    distance_9_0,
    distance_9_1,
    distance_9_2,
    distance_9_3,
    distance_9_4,
    distance_9_5,
    distance_9_6,
    distance_9_7,
    distance_9_8,
    distance_9_9,
    distance_10_0,
    distance_10_1,
    distance_10_2,
    distance_10_3,
    distance_10_4,
    distance_10_5,
    distance_10_6,
    distance_10_7,
    distance_10_8,
    distance_10_9,
    distance_11_0,
    distance_11_1,
    distance_11_2,
    distance_11_3,
    distance_11_4,
    distance_11_5,
    distance_11_6,
    distance_11_7,
    distance_11_8,
    distance_11_9,
    distance_12_0,
    distance_12_1,
    distance_12_2,
    distance_12_3,
    distance_12_4,
    distance_12_5,
    distance_12_6,
    distance_12_7,
    distance_12_8,
    distance_12_9,
    distance_13_0,
    distance_13_1,
    distance_13_2,
    distance_13_3,
    distance_13_4,
    distance_13_5,
    distance_13_6,
    distance_13_7,
    distance_13_8,
    distance_13_9,
    distance_14_0,
    distance_14_1,
    distance_14_2,
    distance_14_3,
    distance_14_4,
    distance_14_5,
    distance_14_6,
    distance_14_7,
    distance_14_8,
    distance_14_9,
    distance_15_0,
    distance_15_1,
    distance_15_2,
    distance_15_3,
    distance_15_4,
    distance_15_5,
    distance_15_6,
    distance_15_7,
    distance_15_8,
    distance_15_9,
    distance_16_0,
    distance_16_1,
    distance_16_2,
    distance_16_3,
    distance_16_4,
    distance_16_5,
    distance_16_6,
    distance_16_7,
    distance_16_8,
    distance_16_9,
    distance_17_0,
    distance_17_1,
    distance_17_2,
    distance_17_3,
    distance_17_4,
    distance_17_5,
    distance_17_6,
    distance_17_7,
    distance_17_8,
    distance_17_9,
    distance_18_0,
    distance_18_1,
    distance_18_2,
    distance_18_3,
    distance_18_4,
    distance_18_5,
    distance_18_6,
    distance_18_7,
    distance_18_8,
    distance_18_9,
    distance_19_0,
    distance_19_1,
    distance_19_2,
    distance_19_3,
    distance_19_4,
    distance_19_5,
    distance_19_6,
    distance_19_7,
    distance_19_8,
    distance_19_9,
    distance_20_0,
    distance_20_1,
    distance_20_2,
    distance_20_3,
    distance_20_4,
    distance_20_5,
    distance_20_6,
    distance_20_7,
    distance_20_8,
    distance_20_9,
    distance_21_0,
    distance_21_1,
    distance_21_2,
    distance_21_3,
    distance_21_4,
    distance_21_5,
    distance_21_6,
    distance_21_7,
    distance_21_8,
    distance_21_9,
    distance_22_0,
    distance_22_1,
    distance_22_2,
    distance_22_3,
    distance_22_4,
    distance_22_5,
    distance_22_6,
    distance_22_7,
    distance_22_8,
    distance_22_9,
    distance_23_0,
    distance_23_1,
    distance_23_2,
    distance_23_3,
    distance_23_4,
    distance_23_5,
    distance_23_6,
    distance_23_7,
    distance_23_8,
    distance_23_9,
    distance_24_0,
    distance_24_1,
    distance_24_2,
    distance_24_3,
    distance_24_4,
    distance_24_5,
    distance_24_6,
    distance_24_7,
    distance_24_8,
    distance_24_9,
    distance_25_0,
    distance_25_1,
    distance_25_2,
    distance_25_3,
    distance_25_4,
    distance_25_5,
    distance_25_6,
    distance_25_7,
    distance_25_8,
    distance_25_9,
    distance_26_0,
    distance_26_1,
    distance_26_2,
    distance_26_3,
    distance_26_4,
    distance_26_5,
    distance_26_6,
    distance_26_7,
    distance_26_8,
    distance_26_9,
    distance_27_0,
    distance_27_1,
    distance_27_2,
    distance_27_3,
    distance_27_4,
    distance_27_5,
    distance_27_6,
    distance_27_7,
    distance_27_8,
    distance_27_9,
    distance_28_0,
    distance_28_1,
    distance_28_2,
    distance_28_3,
    distance_28_4,
    distance_28_5,
    distance_28_6,
    distance_28_7,
    distance_28_8,
    distance_28_9,
    distance_29_0,
    distance_29_1,
    distance_29_2,
    distance_29_3,
    distance_29_4,
    distance_29_5,
    distance_29_6,
    distance_29_7,
    distance_29_8,
    distance_29_9,
    distance_30_0,
    distance_30_1,
    distance_30_2,
    distance_30_3,
    distance_30_4,
    distance_30_5,
    distance_30_6,
    distance_30_7,
    distance_30_8,
    distance_30_9,
    distance_31_0,
    distance_31_1,
    distance_31_2,
    distance_31_3,
    distance_31_4,
    distance_31_5,
    distance_31_6,
    distance_31_7,
    distance_31_8,
    distance_31_9,
    distance_32_0
};

// CYCLES' ARRAYS
const char cycles_0_1[] PROGMEM = " 1"; 
const char cycles_0_2[] PROGMEM = " 2"; 
const char cycles_0_3[] PROGMEM = " 3"; 
const char cycles_0_4[] PROGMEM = " 4"; 
const char cycles_0_5[] PROGMEM = " 5"; 
const char cycles_0_6[] PROGMEM = " 6"; 
const char cycles_0_7[] PROGMEM = " 7"; 
const char cycles_0_8[] PROGMEM = " 8"; 
const char cycles_0_9[] PROGMEM = " 9"; 
const char cycles_1_0[] PROGMEM = "10"; 

// CYCLES ARRAY REFERENCE
#define CYCLES_ARRAY_ENTRIES 10
const char * const cycles_table[] PROGMEM = { 
    cycles_0_1,
    cycles_0_2,
    cycles_0_3,
    cycles_0_4,
    cycles_0_5,
    cycles_0_6,
    cycles_0_7,
    cycles_0_8,
    cycles_0_9,
    cycles_1_0
};

#define MAN_PROG_ARRAY_ENTRIES 2
const char man_prog_0[] PROGMEM = "Manual"; 
const char man_prog_1[] PROGMEM = "Prog"; 

// REFERENCE ARRAY
const char * const man_prog_table[] PROGMEM = { 
    man_prog_0,
    man_prog_1
};

// Moving some elements of menuItem struct to program memory

// ADDING ITEMS:
// 1. ADD ARRAY and update TOTAL_MENU_ITEMS to array size - 1
// 2. Add new menu array to menuItemProgMem at correct position as has defined i.e. END_POS_INDEX
// 3. Add entry in menuItem struct


#define TOTAL_MENU_ITEMS 9 // array base 0 e.g. number of elements - 1
// TODO - GET RID OF ALL MAGIC NUMBERS
const unsigned int menuController[5] PROGMEM =  {TOTAL_MENU_ITEMS - 1,8, 9, 5, 0};  // x y asterisk x offset, asterisk y offset
const unsigned int menuStartPause[5] PROGMEM =  {1,7,11, 5, 2}; // 2 array entries - 1 = 1
const unsigned int menuUpDown[5] PROGMEM =      {1,28,11,8, 2};// same
const unsigned int menuManProg[5] PROGMEM =     {MAN_PROG_ARRAY_ENTRIES - 1,55,9, 10, 0}; // 2 array entries // 55, 9, 10, 0};
const unsigned int menuCycles[5] PROGMEM =      {CYCLES_ARRAY_ENTRIES - 1,113,9, 10, 0};
const unsigned int menuUpSpeed[5] PROGMEM =     {SPEED_ARRAY_ENTRIES - 1,12, 19, 10, 0};
const unsigned int menuDownSpeed[5] PROGMEM =   {SPEED_ARRAY_ENTRIES - 1,12,29, 10, 0}; 
const unsigned int menuEndPos[5] PROGMEM =      {DISTANCE_ARRAY_ENTRIES - 1,12,39, 10  , 0}; // END_POS_INDEX 5
const unsigned int menuStartPos[5] PROGMEM =    {DISTANCE_ARRAY_ENTRIES - 1,12,49, 10, 0}; // START_POS_INDEX 6
const unsigned int menuPos[5] PROGMEM =    {301,10,10, 8, 0};


// FORGOT TO ADD HERE
const uint16_t * const menuItemProgMem[] PROGMEM = {   
                                                    menuController, 
                                                    menuStartPause,
                                                    menuUpDown,
                                                    menuManProg,                                                                                                           
                                                    menuCycles,
                                                    menuUpSpeed,                                                       
                                                    menuDownSpeed,                                                    
                                                    menuEndPos,
                                                    menuStartPos
                                                };

// INDEXES
#define MENU_TRACKER_IDX 0
#define START_STOP_INDEX 1
#define UP_DOWN_INDEX 2
#define MAN_PROG_INDEX 3
#define CYCLES_INDEX 4
#define UP_SPEED_INDEX 5
#define DOWN_SPEED_INDEX 6
#define END_POS_INDEX 7
#define START_POS_INDEX 8
#define POS_INDEX 9

// SELECTED ASTERISK OFFSET INDEXES
#define MENU_TRACKER_IDX 0
#define START_STOP_INDEX 1
#define UP_DOWN_INDEX 2
#define MAN_PROG_INDEX 3
#define CYCLES_INDEX 4
#define UP_SPEED_INDEX 5
#define DOWN_SPEED_INDEX 6
#define END_POS_INDEX 7
#define START_POS_INDEX 8
#define POS_INDEX 9

#define ARR_MAX_INDEX 0
#define X_POS_INDEX 1
#define Y_POS_INDEX 2
#define ASTERISK_X_OFFSET_INDEX 3
#define ASTERISK_Y_OFFSET_INDEX 4

// LCD POSITIONING INCLUDING "SELECTED" *
// MENU ASTERISK SELECTED TRACKER
#define LCD_MENU_X_POS 10 
#define LCD_MENU_Y_POS 10
// START TOP 
#define LCD_START_STOP_X_POS 9 
#define LCD_START_STOP_Y_POS 19
// UP DOWN
#define LCD_UP_DOWN_X_POS 30 
#define LCD_UP_DOWN_Y_POS 19
// SPEED
#define LCD_SPEED_X_POS 55 
#define LCD_SPEED_Y_POS 19 

// SPECIAL u8g2_font_unifont_t_symbols font group characters
#define PAUSE_SYMBOL 0x23f8
#define PLAY_SYMBOL 0x23f5
#define UP_SYMBOL 0x23f6
#define DOWN_SYMBOL 0x23f7

// STRINGS
#define SPEED_RATE "cm/min"
#define DISTANCE_UNIT "cm"
#define NOT_CALIBRATED "??.?"
#define SPEED_RATE_OFFSET 42

// STATE MACHINE DEFINES
#define STOP_INDEX 0
#define PLAY_INDEX 1
#define UP_INDEX 0
#define DOWN_INDEX 1
#define MANUAL_INDEX 0
#define PROG_INDEX 1
#define STEP_COUNTER_RESET 5
// STEPS PER MILLIMITER
#define STEPS_PER_MILLIMITER 50 // 50 ~ reduction gears // 159 ~ lead screw

// ICON POSITIONS
#define ICON_X_POS 106
#define ICON_Y_OFFSET 2
#define ACRONYM_OFFSET 7

// SPLASH SCREEN
#define SPLASH_SCREEN_DELAY 2000

// CRC ADDRESSES
#define DATA_EEPROM_OFFSET 0
#define COPY_EEPROM_OFFSET 18 // 7 integers (14 bytes) 1 unsigned long (4 bytes)
