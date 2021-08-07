#include <avr/pgmspace.h>

#define ENCODER_STEP 4
// SPEEDS
#define SPEED_ARRAY_ENTRIES  144
const char speed_0[] PROGMEM = " 0.20"; 
const char speed_1[] PROGMEM = " 0.21"; 
const char speed_2[] PROGMEM = " 0.22"; 
const char speed_3[] PROGMEM = " 0.23"; 
const char speed_4[] PROGMEM = " 0.24"; 
const char speed_5[] PROGMEM = " 0.25"; 
const char speed_6[] PROGMEM = " 0.26"; 
const char speed_7[] PROGMEM = " 0.27"; 
const char speed_8[] PROGMEM = " 0.28"; 
const char speed_9[] PROGMEM = " 0.29"; 
const char speed_10[] PROGMEM = " 0.30"; 
const char speed_11[] PROGMEM = " 0.31"; 
const char speed_12[] PROGMEM = " 0.32"; 
const char speed_13[] PROGMEM = " 0.33"; 
const char speed_14[] PROGMEM = " 0.34"; 
const char speed_15[] PROGMEM = " 0.35"; 
const char speed_16[] PROGMEM = " 0.36"; 
const char speed_17[] PROGMEM = " 0.37"; 
const char speed_18[] PROGMEM = " 0.38"; 
const char speed_19[] PROGMEM = " 0.39"; 
const char speed_20[] PROGMEM = " 0.40"; 
const char speed_21[] PROGMEM = " 0.41"; 
const char speed_22[] PROGMEM = " 0.42"; 
const char speed_23[] PROGMEM = " 0.43"; 
const char speed_24[] PROGMEM = " 0.44"; 
const char speed_25[] PROGMEM = " 0.45"; 
const char speed_26[] PROGMEM = " 0.46"; 
const char speed_27[] PROGMEM = " 0.47"; 
const char speed_28[] PROGMEM = " 0.48"; 
const char speed_29[] PROGMEM = " 0.49"; 
const char speed_30[] PROGMEM = " 0.50"; 
const char speed_31[] PROGMEM = " 0.51"; 
const char speed_32[] PROGMEM = " 0.52"; 
const char speed_33[] PROGMEM = " 0.53"; 
const char speed_34[] PROGMEM = " 0.54"; 
const char speed_35[] PROGMEM = " 0.55"; 
const char speed_36[] PROGMEM = " 0.56"; 
const char speed_37[] PROGMEM = " 0.57"; 
const char speed_38[] PROGMEM = " 0.58"; 
const char speed_39[] PROGMEM = " 0.59"; 
const char speed_40[] PROGMEM = " 0.60"; 
const char speed_41[] PROGMEM = " 0.61"; 
const char speed_42[] PROGMEM = " 0.62"; 
const char speed_43[] PROGMEM = " 0.63"; 
const char speed_44[] PROGMEM = " 0.64"; 
const char speed_45[] PROGMEM = " 0.65"; 
const char speed_46[] PROGMEM = " 0.66"; 
const char speed_47[] PROGMEM = " 0.67"; 
const char speed_48[] PROGMEM = " 0.68"; 
const char speed_49[] PROGMEM = " 0.69"; 
const char speed_50[] PROGMEM = " 0.70"; 
const char speed_51[] PROGMEM = " 0.71"; 
const char speed_52[] PROGMEM = " 0.72"; 
const char speed_53[] PROGMEM = " 0.73"; 
const char speed_54[] PROGMEM = " 0.74"; 
const char speed_55[] PROGMEM = " 0.75"; 
const char speed_56[] PROGMEM = " 0.76"; 
const char speed_57[] PROGMEM = " 0.77"; 
const char speed_58[] PROGMEM = " 0.78"; 
const char speed_59[] PROGMEM = " 0.79"; 
const char speed_60[] PROGMEM = " 0.80"; 
const char speed_61[] PROGMEM = " 0.81"; 
const char speed_62[] PROGMEM = " 0.82"; 
const char speed_63[] PROGMEM = " 0.83"; 
const char speed_64[] PROGMEM = " 0.84"; 
const char speed_65[] PROGMEM = " 0.85"; 
const char speed_66[] PROGMEM = " 0.86"; 
const char speed_67[] PROGMEM = " 0.87"; 
const char speed_68[] PROGMEM = " 0.88"; 
const char speed_69[] PROGMEM = " 0.89"; 
const char speed_70[] PROGMEM = " 0.90"; 
const char speed_71[] PROGMEM = " 0.91"; 
const char speed_72[] PROGMEM = " 0.92"; 
const char speed_73[] PROGMEM = " 0.93"; 
const char speed_74[] PROGMEM = " 0.94"; 
const char speed_75[] PROGMEM = " 0.95"; 
const char speed_76[] PROGMEM = " 0.96"; 
const char speed_77[] PROGMEM = " 0.97"; 
const char speed_78[] PROGMEM = " 0.98"; 
const char speed_79[] PROGMEM = " 0.99"; 
const char speed_80[] PROGMEM = " 1.00"; 
const char speed_81[] PROGMEM = " 1.10"; 
const char speed_82[] PROGMEM = " 1.20"; 
const char speed_83[] PROGMEM = " 1.30"; 
const char speed_84[] PROGMEM = " 1.40"; 
const char speed_85[] PROGMEM = " 1.50"; 
const char speed_86[] PROGMEM = " 1.60"; 
const char speed_87[] PROGMEM = " 1.70"; 
const char speed_88[] PROGMEM = " 1.80"; 
const char speed_89[] PROGMEM = " 1.90"; 
const char speed_90[] PROGMEM = " 2.00"; 
const char speed_91[] PROGMEM = " 2.10"; 
const char speed_92[] PROGMEM = " 2.20"; 
const char speed_93[] PROGMEM = " 2.30"; 
const char speed_94[] PROGMEM = " 2.40"; 
const char speed_95[] PROGMEM = " 2.50"; 
const char speed_96[] PROGMEM = " 2.60"; 
const char speed_97[] PROGMEM = " 2.70"; 
const char speed_98[] PROGMEM = " 2.80"; 
const char speed_99[] PROGMEM = " 2.90"; 
const char speed_100[] PROGMEM = " 3.00"; 
const char speed_101[] PROGMEM = " 3.10"; 
const char speed_102[] PROGMEM = " 3.20"; 
const char speed_103[] PROGMEM = " 3.30"; 
const char speed_104[] PROGMEM = " 3.40"; 
const char speed_105[] PROGMEM = " 3.50"; 
const char speed_106[] PROGMEM = " 3.60"; 
const char speed_107[] PROGMEM = " 3.70"; 
const char speed_108[] PROGMEM = " 3.80"; 
const char speed_109[] PROGMEM = " 3.90"; 
const char speed_110[] PROGMEM = " 4.00"; 
const char speed_111[] PROGMEM = " 4.10"; 
const char speed_112[] PROGMEM = " 4.20"; 
const char speed_113[] PROGMEM = " 4.30"; 
const char speed_114[] PROGMEM = " 4.40"; 
const char speed_115[] PROGMEM = " 4.50"; 
const char speed_116[] PROGMEM = " 4.60"; 
const char speed_117[] PROGMEM = " 4.70"; 
const char speed_118[] PROGMEM = " 4.80"; 
const char speed_119[] PROGMEM = " 4.90"; 
const char speed_120[] PROGMEM = " 5.00"; 
const char speed_121[] PROGMEM = " 6.00"; 
const char speed_122[] PROGMEM = " 7.00"; 
const char speed_123[] PROGMEM = " 8.00"; 
const char speed_124[] PROGMEM = " 9.00"; 
const char speed_125[] PROGMEM = "10.00"; 
const char speed_126[] PROGMEM = "11.00"; 
const char speed_127[] PROGMEM = "12.00"; 
const char speed_128[] PROGMEM = "13.00"; 
const char speed_129[] PROGMEM = "14.00"; 
const char speed_130[] PROGMEM = "15.00"; 
const char speed_131[] PROGMEM = "16.00"; 
const char speed_132[] PROGMEM = "17.00"; 
const char speed_133[] PROGMEM = "18.00"; 
const char speed_134[] PROGMEM = "20.00"; 
const char speed_135[] PROGMEM = "22.00"; 
const char speed_136[] PROGMEM = "24.00"; 
const char speed_137[] PROGMEM = "27.00"; 
const char speed_138[] PROGMEM = "30.00"; 
const char speed_139[] PROGMEM = "30.00"; 
const char speed_140[] PROGMEM = "35.00"; 
const char speed_141[] PROGMEM = "40.00"; 
const char speed_142[] PROGMEM = "45.00"; 
const char speed_143[] PROGMEM = "50.00"; 

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
    speed_57, 
    speed_58, 
    speed_59, 
    speed_60, 
    speed_61, 
    speed_62, 
    speed_63, 
    speed_64, 
    speed_65, 
    speed_66, 
    speed_67, 
    speed_68, 
    speed_69, 
    speed_70, 
    speed_71, 
    speed_72, 
    speed_73, 
    speed_74, 
    speed_75, 
    speed_76, 
    speed_77, 
    speed_78, 
    speed_79, 
    speed_80, 
    speed_81, 
    speed_82, 
    speed_83, 
    speed_84, 
    speed_85, 
    speed_86, 
    speed_87, 
    speed_88, 
    speed_89, 
    speed_90, 
    speed_91, 
    speed_92, 
    speed_93, 
    speed_94, 
    speed_95, 
    speed_96, 
    speed_97, 
    speed_98, 
    speed_99, 
    speed_100, 
    speed_101, 
    speed_102, 
    speed_103, 
    speed_104, 
    speed_105, 
    speed_106, 
    speed_107, 
    speed_108, 
    speed_109, 
    speed_110, 
    speed_111, 
    speed_112, 
    speed_113, 
    speed_114, 
    speed_115, 
    speed_116, 
    speed_117, 
    speed_118, 
    speed_119, 
    speed_120, 
    speed_121, 
    speed_122, 
    speed_123, 
    speed_124, 
    speed_125, 
    speed_126, 
    speed_127, 
    speed_128, 
    speed_129, 
    speed_130, 
    speed_131, 
    speed_132, 
    speed_133, 
    speed_134, 
    speed_135, 
    speed_136, 
    speed_137, 
    speed_138, 
    speed_139, 
    speed_140, 
    speed_141, 
    speed_142, 
    speed_143, 
};

// FREQUENCIES - different declaration
const uint16_t halfFrequencies[]  PROGMEM  = { 
    600000, 
    571428, 
    545454, 
    521739, 
    499999, 
    479999, 
    461538, 
    444444, 
    428571, 
    413793, 
    399999, 
    387096, 
    374999, 
    363636, 
    352941, 
    342857, 
    333333, 
    324324, 
    315789, 
    307692, 
    299999, 
    292682, 
    285714, 
    279069, 
    272727, 
    266666, 
    260869, 
    255319, 
    249999, 
    244897, 
    239999, 
    235294, 
    230769, 
    226415, 
    222222, 
    218181, 
    214285, 
    210526, 
    206896, 
    203389, 
    199999, 
    196721, 
    193548, 
    190476, 
    187499, 
    184615, 
    181818, 
    179104, 
    176470, 
    173913, 
    171428, 
    169014, 
    166666, 
    164383, 
    162162, 
    159999, 
    157894, 
    155844, 
    153846, 
    151898, 
    149999, 
    148148, 
    146341, 
    144578, 
    142857, 
    141176, 
    139534, 
    137931, 
    136363, 
    134831, 
    133333, 
    131868, 
    130434, 
    129032, 
    127659, 
    126315, 
    124999, 
    123711, 
    122448, 
    121212, 
    120000, 
    109090, 
    99999, 
    92307, 
    85714, 
    79999, 
    74999, 
    70588, 
    66666, 
    63157, 
    59999, 
    57142, 
    54545, 
    52173, 
    49999, 
    47999, 
    46153, 
    44444, 
    42857, 
    41379, 
    39999, 
    38709, 
    37499, 
    36363, 
    35294, 
    34285, 
    33333, 
    32432, 
    31578, 
    30769, 
    29999, 
    29268, 
    28571, 
    27906, 
    27272, 
    26666, 
    26086, 
    25531, 
    24999, 
    24489, 
    24000, 
    20000, 
    17142, 
    15000, 
    13333, 
    12000, 
    10909, 
    10000, 
    9230, 
    8571, 
    8000, 
    7500, 
    7058, 
    6666, 
    6000, 
    5454, 
    5000, 
    4444, 
    4000, 
    4000, 
    3428, 
    3000, 
    2666, 
    2400, 
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
const char distance_32_1[] PROGMEM = "32.1"; 
const char distance_32_2[] PROGMEM = "32.2"; 
const char distance_32_3[] PROGMEM = "32.3"; 
const char distance_32_4[] PROGMEM = "32.4"; 
const char distance_32_5[] PROGMEM = "32.5"; 
const char distance_32_6[] PROGMEM = "32.6"; 
const char distance_32_7[] PROGMEM = "32.7"; 
const char distance_32_8[] PROGMEM = "32.8"; 
const char distance_32_9[] PROGMEM = "32.9"; 
const char distance_33_0[] PROGMEM = "33.0"; 
const char distance_33_1[] PROGMEM = "33.1"; 
const char distance_33_2[] PROGMEM = "33.2"; 
const char distance_33_3[] PROGMEM = "33.3"; 
const char distance_33_4[] PROGMEM = "33.4"; 
const char distance_33_5[] PROGMEM = "33.5"; 
const char distance_33_6[] PROGMEM = "33.6"; 
const char distance_33_7[] PROGMEM = "33.7"; 
const char distance_33_8[] PROGMEM = "33.8"; 
const char distance_33_9[] PROGMEM = "33.9"; 
const char distance_34_0[] PROGMEM = "34.0"; 
const char distance_34_1[] PROGMEM = "34.1"; 
const char distance_34_2[] PROGMEM = "34.2"; 
const char distance_34_3[] PROGMEM = "34.3"; 
const char distance_34_4[] PROGMEM = "34.4"; 
const char distance_34_5[] PROGMEM = "34.5"; 
const char distance_34_6[] PROGMEM = "34.6"; 
const char distance_34_7[] PROGMEM = "34.7"; 
const char distance_34_8[] PROGMEM = "34.8"; 
const char distance_34_9[] PROGMEM = "34.9"; 
const char distance_35_0[] PROGMEM = "35.0"; 
const char distance_35_1[] PROGMEM = "35.1"; 
const char distance_35_2[] PROGMEM = "35.2"; 
const char distance_35_3[] PROGMEM = "35.3"; 
const char distance_35_4[] PROGMEM = "35.4"; 
const char distance_35_5[] PROGMEM = "35.5"; 
const char distance_35_6[] PROGMEM = "35.6"; 
const char distance_35_7[] PROGMEM = "35.7"; 
const char distance_35_8[] PROGMEM = "35.8"; 
const char distance_35_9[] PROGMEM = "35.9"; 
const char distance_36_0[] PROGMEM = "36.0"; 
const char distance_36_1[] PROGMEM = "36.1"; 
const char distance_36_2[] PROGMEM = "36.2"; 
const char distance_36_3[] PROGMEM = "36.3"; 
const char distance_36_4[] PROGMEM = "36.4"; 
const char distance_36_5[] PROGMEM = "36.5"; 
const char distance_36_6[] PROGMEM = "36.6"; 
const char distance_36_7[] PROGMEM = "36.7"; 
const char distance_36_8[] PROGMEM = "36.8"; 
const char distance_36_9[] PROGMEM = "36.9"; 
const char distance_37_0[] PROGMEM = "37.0"; 
const char distance_37_1[] PROGMEM = "37.1"; 
const char distance_37_2[] PROGMEM = "37.2"; 
const char distance_37_3[] PROGMEM = "37.3"; 
const char distance_37_4[] PROGMEM = "37.4"; 
const char distance_37_5[] PROGMEM = "37.5"; 
const char distance_37_6[] PROGMEM = "37.6"; 
const char distance_37_7[] PROGMEM = "37.7"; 
const char distance_37_8[] PROGMEM = "37.8"; 
const char distance_37_9[] PROGMEM = "37.9"; 
const char distance_38_0[] PROGMEM = "38.0"; 
const char distance_38_1[] PROGMEM = "38.1"; 
const char distance_38_2[] PROGMEM = "38.2"; 
const char distance_38_3[] PROGMEM = "38.3"; 
const char distance_38_4[] PROGMEM = "38.4"; 
const char distance_38_5[] PROGMEM = "38.5"; 
const char distance_38_6[] PROGMEM = "38.6"; 
const char distance_38_7[] PROGMEM = "38.7"; 
const char distance_38_8[] PROGMEM = "38.8"; 
const char distance_38_9[] PROGMEM = "38.9"; 
const char distance_39_0[] PROGMEM = "39.0"; 
const char distance_39_1[] PROGMEM = "39.1"; 
const char distance_39_2[] PROGMEM = "39.2"; 
const char distance_39_3[] PROGMEM = "39.3"; 
const char distance_39_4[] PROGMEM = "39.4"; 
const char distance_39_5[] PROGMEM = "39.5"; 
const char distance_39_6[] PROGMEM = "39.6"; 
const char distance_39_7[] PROGMEM = "39.7"; 
const char distance_39_8[] PROGMEM = "39.8"; 
const char distance_39_9[] PROGMEM = "39.9"; 
const char distance_40_0[] PROGMEM = "40.0"; 
const char distance_40_1[] PROGMEM = "40.1"; 
const char distance_40_2[] PROGMEM = "40.2"; 
const char distance_40_3[] PROGMEM = "40.3"; 
const char distance_40_4[] PROGMEM = "40.4"; 
const char distance_40_5[] PROGMEM = "40.5"; 
const char distance_40_6[] PROGMEM = "40.6"; 
const char distance_40_7[] PROGMEM = "40.7"; 
const char distance_40_8[] PROGMEM = "40.8"; 
const char distance_40_9[] PROGMEM = "40.9"; 
const char distance_41_0[] PROGMEM = "41.0"; 
const char distance_41_1[] PROGMEM = "41.1"; 
const char distance_41_2[] PROGMEM = "41.2"; 
const char distance_41_3[] PROGMEM = "41.3"; 
const char distance_41_4[] PROGMEM = "41.4"; 
const char distance_41_5[] PROGMEM = "41.5"; 
const char distance_41_6[] PROGMEM = "41.6"; 
const char distance_41_7[] PROGMEM = "41.7"; 
const char distance_41_8[] PROGMEM = "41.8"; 
const char distance_41_9[] PROGMEM = "41.9"; 
const char distance_42_0[] PROGMEM = "42.0"; 
const char distance_42_1[] PROGMEM = "42.1"; 
const char distance_42_2[] PROGMEM = "42.2"; 
const char distance_42_3[] PROGMEM = "42.3"; 
const char distance_42_4[] PROGMEM = "42.4"; 
const char distance_42_5[] PROGMEM = "42.5"; 
const char distance_42_6[] PROGMEM = "42.6"; 
const char distance_42_7[] PROGMEM = "42.7"; 
const char distance_42_8[] PROGMEM = "42.8"; 
const char distance_42_9[] PROGMEM = "42.9"; 
const char distance_43_0[] PROGMEM = "43.0"; 
const char distance_43_1[] PROGMEM = "43.1"; 
const char distance_43_2[] PROGMEM = "43.2"; 
const char distance_43_3[] PROGMEM = "43.3"; 
const char distance_43_4[] PROGMEM = "43.4"; 
const char distance_43_5[] PROGMEM = "43.5"; 
const char distance_43_6[] PROGMEM = "43.6"; 
const char distance_43_7[] PROGMEM = "43.7"; 
const char distance_43_8[] PROGMEM = "43.8"; 
const char distance_43_9[] PROGMEM = "43.9"; 
const char distance_44_0[] PROGMEM = "44.0"; 
const char distance_44_1[] PROGMEM = "44.1"; 
const char distance_44_2[] PROGMEM = "44.2"; 
const char distance_44_3[] PROGMEM = "44.3"; 
const char distance_44_4[] PROGMEM = "44.4"; 
const char distance_44_5[] PROGMEM = "44.5"; 
const char distance_44_6[] PROGMEM = "44.6"; 
const char distance_44_7[] PROGMEM = "44.7"; 
const char distance_44_8[] PROGMEM = "44.8"; 
const char distance_44_9[] PROGMEM = "44.9"; 
const char distance_45_0[] PROGMEM = "45.0"; 
const char distance_45_1[] PROGMEM = "45.1"; 
const char distance_45_2[] PROGMEM = "45.2"; 
const char distance_45_3[] PROGMEM = "45.3"; 
const char distance_45_4[] PROGMEM = "45.4"; 
const char distance_45_5[] PROGMEM = "45.5"; 
const char distance_45_6[] PROGMEM = "45.6"; 
const char distance_45_7[] PROGMEM = "45.7"; 
const char distance_45_8[] PROGMEM = "45.8"; 
const char distance_45_9[] PROGMEM = "45.9"; 
const char distance_46_0[] PROGMEM = "46.0"; 
const char distance_46_1[] PROGMEM = "46.1"; 
const char distance_46_2[] PROGMEM = "46.2"; 
const char distance_46_3[] PROGMEM = "46.3"; 
const char distance_46_4[] PROGMEM = "46.4"; 
const char distance_46_5[] PROGMEM = "46.5"; 
const char distance_46_6[] PROGMEM = "46.6"; 
const char distance_46_7[] PROGMEM = "46.7"; 
const char distance_46_8[] PROGMEM = "46.8"; 
const char distance_46_9[] PROGMEM = "46.9"; 
const char distance_47_0[] PROGMEM = "47.0"; 
const char distance_47_1[] PROGMEM = "47.1"; 
const char distance_47_2[] PROGMEM = "47.2"; 
const char distance_47_3[] PROGMEM = "47.3"; 
const char distance_47_4[] PROGMEM = "47.4"; 
const char distance_47_5[] PROGMEM = "47.5"; 
const char distance_47_6[] PROGMEM = "47.6"; 
const char distance_47_7[] PROGMEM = "47.7"; 
const char distance_47_8[] PROGMEM = "47.8"; 
const char distance_47_9[] PROGMEM = "47.9"; 
const char distance_48_0[] PROGMEM = "48.0"; 
const char distance_48_1[] PROGMEM = "48.1"; 
const char distance_48_2[] PROGMEM = "48.2"; 
const char distance_48_3[] PROGMEM = "48.3"; 
const char distance_48_4[] PROGMEM = "48.4"; 
const char distance_48_5[] PROGMEM = "48.5"; 
const char distance_48_6[] PROGMEM = "48.6"; 
const char distance_48_7[] PROGMEM = "48.7"; 
const char distance_48_8[] PROGMEM = "48.8"; 
const char distance_48_9[] PROGMEM = "48.9"; 
const char distance_49_0[] PROGMEM = "49.0"; 
const char distance_49_1[] PROGMEM = "49.1"; 
const char distance_49_2[] PROGMEM = "49.2"; 
const char distance_49_3[] PROGMEM = "49.3"; 
const char distance_49_4[] PROGMEM = "49.4"; 
const char distance_49_5[] PROGMEM = "49.5"; 
const char distance_49_6[] PROGMEM = "49.6"; 
const char distance_49_7[] PROGMEM = "49.7"; 
const char distance_49_8[] PROGMEM = "49.8"; 
const char distance_49_9[] PROGMEM = "49.9"; 
const char distance_50_0[] PROGMEM = "50.0"; 
const char distance_50_1[] PROGMEM = "50.1"; 
const char distance_50_2[] PROGMEM = "50.2"; 
const char distance_50_3[] PROGMEM = "50.3"; 
const char distance_50_4[] PROGMEM = "50.4"; 
const char distance_50_5[] PROGMEM = "50.5"; 
const char distance_50_6[] PROGMEM = "50.6"; 
const char distance_50_7[] PROGMEM = "50.7"; 
const char distance_50_8[] PROGMEM = "50.8"; 
const char distance_50_9[] PROGMEM = "50.9"; 
const char distance_51_0[] PROGMEM = "51.0"; 
const char distance_51_1[] PROGMEM = "51.1"; 
const char distance_51_2[] PROGMEM = "51.2"; 
const char distance_51_3[] PROGMEM = "51.3"; 
const char distance_51_4[] PROGMEM = "51.4"; 
const char distance_51_5[] PROGMEM = "51.5"; 
const char distance_51_6[] PROGMEM = "51.6"; 
const char distance_51_7[] PROGMEM = "51.7"; 
const char distance_51_8[] PROGMEM = "51.8"; 
const char distance_51_9[] PROGMEM = "51.9"; 


// DISTANCE ARRAY REFERENCE
#define DISTANCE_ARRAY_ENTRIES 520
// NB array contains 520 entries 
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
    distance_32_0,
    distance_32_1,
    distance_32_2,
    distance_32_3,
    distance_32_4,
    distance_32_5,
    distance_32_6,
    distance_32_7,
    distance_32_8,
    distance_32_9,
    distance_33_0,
    distance_33_1,
    distance_33_2,
    distance_33_3,
    distance_33_4,
    distance_33_5,
    distance_33_6,
    distance_33_7,
    distance_33_8,
    distance_33_9,
    distance_34_0,
    distance_34_1,
    distance_34_2,
    distance_34_3,
    distance_34_4,
    distance_34_5,
    distance_34_6,
    distance_34_7,
    distance_34_8,
    distance_34_9,
    distance_35_0,
    distance_35_1,
    distance_35_2,
    distance_35_3,
    distance_35_4,
    distance_35_5,
    distance_35_6,
    distance_35_7,
    distance_35_8,
    distance_35_9,
    distance_36_0,
    distance_36_1,
    distance_36_2,
    distance_36_3,
    distance_36_4,
    distance_36_5,
    distance_36_6,
    distance_36_7,
    distance_36_8,
    distance_36_9,
    distance_37_0,
    distance_37_1,
    distance_37_2,
    distance_37_3,
    distance_37_4,
    distance_37_5,
    distance_37_6,
    distance_37_7,
    distance_37_8,
    distance_37_9,
    distance_38_0,
    distance_38_1,
    distance_38_2,
    distance_38_3,
    distance_38_4,
    distance_38_5,
    distance_38_6,
    distance_38_7,
    distance_38_8,
    distance_38_9,
    distance_39_0,
    distance_39_1,
    distance_39_2,
    distance_39_3,
    distance_39_4,
    distance_39_5,
    distance_39_6,
    distance_39_7,
    distance_39_8,
    distance_39_9,
    distance_40_0,
    distance_40_1,
    distance_40_2,
    distance_40_3,
    distance_40_4,
    distance_40_5,
    distance_40_6,
    distance_40_7,
    distance_40_8,
    distance_40_9,
    distance_41_0,
    distance_41_1,
    distance_41_2,
    distance_41_3,
    distance_41_4,
    distance_41_5,
    distance_41_6,
    distance_41_7,
    distance_41_8,
    distance_41_9,
    distance_42_0,
    distance_42_1,
    distance_42_2,
    distance_42_3,
    distance_42_4,
    distance_42_5,
    distance_42_6,
    distance_42_7,
    distance_42_8,
    distance_42_9,
    distance_43_0,
    distance_43_1,
    distance_43_2,
    distance_43_3,
    distance_43_4,
    distance_43_5,
    distance_43_6,
    distance_43_7,
    distance_43_8,
    distance_43_9,
    distance_44_0,
    distance_44_1,
    distance_44_2,
    distance_44_3,
    distance_44_4,
    distance_44_5,
    distance_44_6,
    distance_44_7,
    distance_44_8,
    distance_44_9,
    distance_45_0,
    distance_45_1,
    distance_45_2,
    distance_45_3,
    distance_45_4,
    distance_45_5,
    distance_45_6,
    distance_45_7,
    distance_45_8,
    distance_45_9,
    distance_46_0,
    distance_46_1,
    distance_46_2,
    distance_46_3,
    distance_46_4,
    distance_46_5,
    distance_46_6,
    distance_46_7,
    distance_46_8,
    distance_46_9,
    distance_47_0,
    distance_47_1,
    distance_47_2,
    distance_47_3,
    distance_47_4,
    distance_47_5,
    distance_47_6,
    distance_47_7,
    distance_47_8,
    distance_47_9,
    distance_48_0,
    distance_48_1,
    distance_48_2,
    distance_48_3,
    distance_48_4,
    distance_48_5,
    distance_48_6,
    distance_48_7,
    distance_48_8,
    distance_48_9,
    distance_49_0,
    distance_49_1,
    distance_49_2,
    distance_49_3,
    distance_49_4,
    distance_49_5,
    distance_49_6,
    distance_49_7,
    distance_49_8,
    distance_49_9,
    distance_50_0,
    distance_50_1,
    distance_50_2,
    distance_50_3,
    distance_50_4,
    distance_50_5,
    distance_50_6,
    distance_50_7,
    distance_50_8,
    distance_50_9,
    distance_51_0,
    distance_51_1,
    distance_51_2,
    distance_51_3,
    distance_51_4,
    distance_51_5,
    distance_51_6,
    distance_51_7,
    distance_51_8,
    distance_51_9,
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
const unsigned int menuPos[5] PROGMEM =    {259,10,10, 8, 0};


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
// #define STEPS_PER_MILLIMITER 98
// Assuming 50 steps per revolution, 2mm thread
#define STEPS_PER_MILLIMITER 25

// ICON POSITIONS
#define ICON_X_POS 106
#define ICON_Y_OFFSET 2
#define ACRONYM_OFFSET 7

// SPLASH SCREEN
#define SPLASH_SCREEN_DELAY 2000

// CRC ADDRESSES
#define DATA_EEPROM_OFFSET 0
#define COPY_EEPROM_OFFSET 18 // 7 integers (14 bytes) 1 unsigned long (4 bytes)
