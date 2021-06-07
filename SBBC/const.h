﻿#ifndef CONST_H
#define CONST_H
static const uint8_t DATA_SIZE = sizeof(uint64_t);    // 半個block的大小
static const uint64_t FIRSTBIT = 0x8000000000000000;  // 1000000000...
static const uint64_t ssrH = 0xf35a82e5759b0fa8;      // "孫學任"的md5高的那半
static const uint64_t ssrL = 0xf35a82e5759b0fa8;      // "孫學任"的md5低的那半
static const uint64_t gojoH = 0xd1cc5e9b4eb66b90;     // "五条悟"的md5高的那半
static const uint64_t gojoL = 0xd2ec42b22ed6ad52;     // "五条悟"的md5低的那半
static const uint64_t kirotoH = 0xcc74f0e4b37aa6ef;   // "桐ヶ谷和人"的md5高的那半
static const uint64_t kirotoL = 0x0da4527eee7a35b7;   // "桐ヶ谷和人"的md5低的那半

// Feistel F 使用的置換表
// row 1前5個值是48763(星爆氣流斬)
// col 1(idx=0,8,16...)的前五個值是學號410612011
static const int Pbox[64] = {4, 8, 7, 6, 3, 14, 16, 12,
                             10, 40, 51, 57, 59, 60, 29, 42,
                             61, 2, 15, 1, 25, 31, 0, 22,
                             20, 54, 50, 48, 58, 55, 18, 36,
                             11, 9, 13, 26, 24, 30, 35, 43,
                             63, 33, 46, 32, 56, 62, 41, 53,
                             49, 23, 19, 17, 27, 21, 28, 5,
                             44, 39, 38, 45, 34, 47, 52, 37};

static const uint8_t hands[16][2] = {{5, 3}, {3, 3}, {3, 3}, {7, 6}, {4, 5}, {0, 0}, {6, 5}, {1, 1}, {4, 7}, {7, 4}, {2, 6}, {0, 6}, {3, 1}, {2, 2}, {3, 3}, {0, 0}};

static const uint8_t sbox[8][16][16] = {{{0x5d, 0x5b, 0x97, 0x63, 0x34, 0x0e, 0x11, 0xaf, 0x5c, 0x79, 0x6e, 0x38, 0xa5, 0xec, 0x62, 0x3a},
                                         {0x8f, 0xf8, 0xb5, 0x0b, 0x20, 0x8a, 0x9c, 0x1c, 0xcf, 0xf4, 0x36, 0x6a, 0xfe, 0xfc, 0xc7, 0x00},
                                         {0x4a, 0xa2, 0xc2, 0xc5, 0x4e, 0x9f, 0xe7, 0x06, 0x33, 0x10, 0xf8, 0x9f, 0x3b, 0x6a, 0xff, 0xcd},
                                         {0xd3, 0x5c, 0x96, 0xb6, 0x07, 0x58, 0x35, 0x71, 0x48, 0xc7, 0xad, 0x96, 0x78, 0xfe, 0x39, 0x31},
                                         {0x96, 0xbc, 0xcf, 0xaf, 0x3e, 0x4e, 0x40, 0xb4, 0x5c, 0xea, 0xae, 0x63, 0xc9, 0xcd, 0x23, 0x0c},
                                         {0x71, 0x20, 0x5c, 0xc3, 0xae, 0x92, 0x35, 0xde, 0x30, 0x3d, 0x6a, 0x92, 0xce, 0xde, 0x4b, 0x99},
                                         {0x31, 0xf6, 0xfa, 0xa6, 0x02, 0x01, 0x0b, 0x19, 0x5d, 0xf6, 0x83, 0x61, 0xaf, 0xbc, 0xb9, 0xe1},
                                         {0x91, 0x82, 0x00, 0xb7, 0xd5, 0xa0, 0x57, 0x1c, 0x2f, 0x43, 0x1c, 0x74, 0x3f, 0x62, 0xf9, 0xb9},
                                         {0xe2, 0x4a, 0xca, 0xc2, 0xb2, 0x69, 0xfc, 0x29, 0x25, 0x41, 0x52, 0x46, 0xa4, 0xbf, 0xf3, 0x0a},
                                         {0xa1, 0xc5, 0xfc, 0x5f, 0xf0, 0x6d, 0x1c, 0x0b, 0xc4, 0xaa, 0x76, 0xd5, 0x09, 0xd4, 0xd3, 0x62},
                                         {0x10, 0x14, 0xa8, 0x99, 0x66, 0x92, 0xc8, 0x6a, 0xbc, 0x6e, 0x04, 0x80, 0x7e, 0xac, 0x0b, 0x36},
                                         {0xf4, 0x33, 0x90, 0xe9, 0x86, 0x00, 0x36, 0x70, 0xd1, 0xdd, 0x81, 0x4b, 0x82, 0xf7, 0x79, 0x06},
                                         {0x49, 0x07, 0x8c, 0x37, 0x73, 0x79, 0xf7, 0x59, 0x88, 0x9e, 0x95, 0xd9, 0x31, 0x87, 0xf8, 0x03},
                                         {0x8e, 0xc1, 0x3c, 0x4a, 0xc6, 0xd6, 0x0b, 0x73, 0x79, 0x30, 0xe8, 0xc1, 0xde, 0x0c, 0xdb, 0xee},
                                         {0x0f, 0x4b, 0x2a, 0x64, 0x5a, 0xe0, 0x1a, 0x37, 0xda, 0x52, 0xe2, 0x32, 0x82, 0xc0, 0xeb, 0xee},
                                         {0x2c, 0x49, 0xe0, 0xce, 0x10, 0xb1, 0x99, 0x54, 0xb7, 0x81, 0x8b, 0x77, 0xee, 0xe6, 0xdd, 0x63}},
                                        {{0x0a, 0xa8, 0xf3, 0xfe, 0xeb, 0x2e, 0xf0, 0x70, 0x53, 0x31, 0xed, 0x0e, 0xc7, 0x15, 0x81, 0x98},
                                         {0xce, 0x69, 0x8c, 0xf4, 0x70, 0x47, 0x89, 0x98, 0x1c, 0x4b, 0x8c, 0xba, 0x3d, 0x64, 0xba, 0xc7},
                                         {0x5a, 0x76, 0xfe, 0xeb, 0xae, 0x15, 0xac, 0x86, 0xa2, 0x0e, 0xd1, 0x48, 0x0e, 0x4e, 0x82, 0x08},
                                         {0xbe, 0xc6, 0xc9, 0x57, 0xf2, 0xe9, 0x1a, 0xfb, 0x28, 0xc1, 0x64, 0x10, 0xd0, 0x28, 0x98, 0xc6},
                                         {0x51, 0x32, 0x76, 0x6d, 0x39, 0x9b, 0x6c, 0xbc, 0x9c, 0x73, 0xa2, 0x89, 0xbb, 0xe6, 0x6d, 0x36},
                                         {0x94, 0xc8, 0x8c, 0xf5, 0x1e, 0xd4, 0x31, 0x10, 0x61, 0x48, 0x53, 0x4e, 0xce, 0xd2, 0x25, 0x16},
                                         {0xf1, 0x87, 0xce, 0x6b, 0xcd, 0xa4, 0xfb, 0x2a, 0xb3, 0x54, 0x1e, 0xa8, 0x73, 0x2d, 0x61, 0xdb},
                                         {0x0b, 0x9e, 0x01, 0x20, 0x40, 0xa4, 0x40, 0xde, 0xf0, 0x2a, 0x60, 0x80, 0x9e, 0xde, 0xb0, 0xbd},
                                         {0xb8, 0x72, 0x32, 0xb0, 0x9f, 0x0c, 0x08, 0xca, 0x31, 0xfb, 0x30, 0xd9, 0x53, 0x13, 0x84, 0xab},
                                         {0xfa, 0x05, 0xf8, 0xe7, 0x32, 0x49, 0x71, 0xda, 0xf8, 0x6c, 0xda, 0x7b, 0xb6, 0x48, 0x95, 0x0d},
                                         {0x8f, 0xbc, 0x75, 0x8d, 0xbf, 0xab, 0x83, 0x18, 0xb0, 0x2f, 0xdc, 0x17, 0xc5, 0xb0, 0x53, 0x76},
                                         {0x46, 0xd1, 0xff, 0x83, 0x91, 0x67, 0x12, 0x8c, 0x1b, 0x0d, 0x01, 0x4c, 0xba, 0xb9, 0x1b, 0x38},
                                         {0xa4, 0x4a, 0x83, 0xe9, 0xed, 0x16, 0x32, 0x8c, 0xe1, 0x1f, 0xf8, 0x4d, 0xe5, 0x1d, 0x93, 0xe4},
                                         {0x1c, 0xf4, 0xe0, 0xa5, 0x2b, 0x1b, 0x94, 0xa9, 0x5f, 0x51, 0xe1, 0x1b, 0xcb, 0xec, 0x60, 0x75},
                                         {0xcd, 0x63, 0xdc, 0x7e, 0x6d, 0xd7, 0x6d, 0xf2, 0x96, 0xc8, 0xff, 0x25, 0x5f, 0xc0, 0x4f, 0x49},
                                         {0xf0, 0x82, 0x93, 0x9f, 0xca, 0xbf, 0xc8, 0x84, 0x80, 0x42, 0xba, 0x2d, 0x64, 0x46, 0x05, 0x2c}},
                                        {{0xd7, 0x4b, 0xe0, 0xb2, 0x92, 0xb4, 0x2e, 0xc0, 0xc2, 0x69, 0x2d, 0xb5, 0x3d, 0x59, 0x9c, 0x01},
                                         {0xd9, 0x5b, 0xae, 0x41, 0xac, 0x1f, 0x40, 0x41, 0x2e, 0x6a, 0x64, 0xe8, 0xb7, 0xf4, 0xbf, 0xc4},
                                         {0xcb, 0x6e, 0xf0, 0x36, 0x94, 0x4a, 0x21, 0x3d, 0xa8, 0x05, 0x98, 0x6e, 0xca, 0x59, 0xbd, 0x22},
                                         {0x77, 0x96, 0x66, 0x75, 0x14, 0xa3, 0xa2, 0x9a, 0x26, 0xea, 0x24, 0x3e, 0x21, 0xbb, 0x06, 0xd6},
                                         {0x71, 0xfd, 0xb3, 0x05, 0xa8, 0xff, 0x77, 0x6b, 0x83, 0x24, 0xd4, 0x39, 0xe4, 0x4b, 0xaa, 0xf5},
                                         {0x59, 0xbd, 0x61, 0x61, 0xea, 0xc9, 0x00, 0xfd, 0xc5, 0xed, 0xc6, 0x16, 0xe9, 0x25, 0xd1, 0x2d},
                                         {0x29, 0x17, 0x4a, 0x50, 0x2d, 0x8b, 0x5e, 0x3b, 0x47, 0xcf, 0x96, 0x5e, 0xfe, 0x63, 0x8e, 0xd1},
                                         {0x97, 0xb4, 0xfa, 0xbe, 0x43, 0x8b, 0x81, 0xd0, 0xaa, 0xfe, 0xb2, 0x9f, 0x72, 0xd9, 0xe1, 0x45},
                                         {0x66, 0x3c, 0x2e, 0x28, 0x32, 0xda, 0x0d, 0x95, 0xed, 0x49, 0xb2, 0xd9, 0xd6, 0x6b, 0x1d, 0x29},
                                         {0x12, 0xd1, 0xd7, 0xf4, 0x1b, 0xbe, 0x33, 0xff, 0x4e, 0xdf, 0xc5, 0x36, 0xb8, 0x09, 0x10, 0x50},
                                         {0x77, 0x49, 0x3e, 0x10, 0xcb, 0x46, 0xef, 0x33, 0x7a, 0x98, 0xda, 0x4a, 0xfb, 0xaa, 0x68, 0x3f},
                                         {0x9a, 0x5e, 0xb3, 0x8d, 0x16, 0x74, 0x0a, 0xff, 0x7d, 0x74, 0x8b, 0x5c, 0xeb, 0x32, 0xd1, 0x09},
                                         {0x71, 0x46, 0xeb, 0x78, 0xe1, 0xe5, 0x91, 0xe8, 0x89, 0xb9, 0xce, 0xe7, 0x28, 0x8f, 0xc5, 0x7c},
                                         {0x67, 0x36, 0xcf, 0x5d, 0x03, 0xcd, 0x1d, 0x76, 0xdd, 0xac, 0xbf, 0x2b, 0x1a, 0xe6, 0xf6, 0x91},
                                         {0xd6, 0x30, 0x97, 0xa6, 0xb6, 0x63, 0xc6, 0xe8, 0x57, 0x48, 0xd0, 0x08, 0x77, 0x35, 0x56, 0x9a},
                                         {0x77, 0x60, 0x54, 0x81, 0x5d, 0x77, 0x28, 0x28, 0xcc, 0xc7, 0x48, 0x3b, 0x6a, 0xb0, 0xfd, 0x54}},
                                        {{0xfd, 0xd5, 0xa3, 0x73, 0xea, 0x93, 0xe8, 0x7c, 0x80, 0x31, 0x09, 0xf3, 0x70, 0x37, 0x64, 0x03},
                                         {0x84, 0xf3, 0xdf, 0xbe, 0x2d, 0x3e, 0x54, 0xb1, 0x5f, 0xbf, 0xd6, 0xbc, 0xfb, 0xf4, 0xdc, 0x88},
                                         {0x4a, 0x2e, 0xbe, 0x7f, 0xf1, 0xf0, 0xcd, 0x34, 0xf6, 0xf5, 0xfc, 0xb5, 0x1b, 0xb2, 0xe6, 0xa2},
                                         {0x82, 0x16, 0xf0, 0x69, 0x45, 0xbf, 0x87, 0x27, 0x5f, 0xa2, 0x03, 0x5f, 0x97, 0xc8, 0xfc, 0x67},
                                         {0xac, 0xd8, 0x6d, 0xa4, 0xe5, 0xf5, 0x05, 0x91, 0x2f, 0xc4, 0xd3, 0xcf, 0xb0, 0xdb, 0x55, 0x68},
                                         {0x8f, 0x9b, 0x3c, 0xaf, 0x98, 0x35, 0xf6, 0x23, 0x52, 0xcd, 0x44, 0x63, 0xf2, 0xb9, 0xec, 0xd3},
                                         {0x5f, 0x25, 0x78, 0x33, 0x60, 0x76, 0x60, 0x16, 0x79, 0x69, 0x88, 0x2e, 0xe8, 0xab, 0xc6, 0x71},
                                         {0x14, 0xaf, 0x15, 0x89, 0x46, 0x3d, 0xd8, 0xf4, 0xe2, 0x2f, 0x19, 0xf2, 0x92, 0xc6, 0x10, 0x83},
                                         {0x3e, 0x1f, 0xed, 0xd7, 0xd8, 0xaf, 0xb7, 0x0e, 0x53, 0x5c, 0x16, 0x31, 0xa1, 0x88, 0xb4, 0xfb},
                                         {0x70, 0x08, 0x39, 0x28, 0x27, 0x98, 0xaa, 0x89, 0x9f, 0x17, 0xf5, 0x99, 0x1d, 0x82, 0xa4, 0x15},
                                         {0x8e, 0x81, 0x82, 0x63, 0x33, 0x2d, 0xeb, 0xa7, 0x15, 0x7e, 0x07, 0x60, 0x83, 0x93, 0x5d, 0xcf},
                                         {0x0c, 0x09, 0x84, 0x90, 0x27, 0x69, 0xd3, 0xc7, 0x96, 0xe1, 0x0a, 0x6b, 0xe1, 0x60, 0xa5, 0xfc},
                                         {0x58, 0x3e, 0x12, 0xba, 0x06, 0xee, 0x5b, 0x11, 0xa7, 0xff, 0x03, 0x98, 0x06, 0x31, 0x7f, 0xb7},
                                         {0xf1, 0x05, 0xda, 0x5d, 0xe9, 0x1a, 0xf2, 0x03, 0xfd, 0x3c, 0x6d, 0x94, 0x3b, 0x59, 0xc7, 0x29},
                                         {0x1d, 0xd6, 0x40, 0xb3, 0x0f, 0xb6, 0x94, 0xaf, 0xfc, 0x82, 0x05, 0xa1, 0x98, 0x60, 0xb5, 0x3a},
                                         {0x0e, 0x4e, 0xe4, 0x91, 0x46, 0x6c, 0xee, 0x0b, 0x62, 0x23, 0xca, 0x46, 0xb1, 0x50, 0x16, 0xf1}},
                                        {{0x88, 0xb2, 0x4e, 0x9a, 0xa9, 0xf0, 0xbf, 0x83, 0x5a, 0xf8, 0xce, 0x15, 0xab, 0xa7, 0x66, 0x56},
                                         {0x04, 0x30, 0x25, 0x1b, 0x96, 0x75, 0x99, 0xfa, 0xb8, 0xfb, 0x10, 0x35, 0xdd, 0xd4, 0x05, 0xfa},
                                         {0x5e, 0xf5, 0x06, 0xde, 0x98, 0xfb, 0xe7, 0x5b, 0xfb, 0x03, 0xc6, 0x89, 0xf7, 0xa0, 0x20, 0x91},
                                         {0x86, 0xc7, 0x26, 0x15, 0x61, 0x83, 0x5d, 0xde, 0x6d, 0x78, 0x09, 0xe5, 0x7b, 0xc5, 0x41, 0x05},
                                         {0x78, 0xca, 0xb8, 0xe7, 0x9f, 0xce, 0x82, 0x5e, 0xb9, 0xc8, 0x09, 0xa2, 0x79, 0xdf, 0xee, 0xb0},
                                         {0xd3, 0xab, 0xf4, 0x22, 0x90, 0xd3, 0xec, 0x84, 0x12, 0xe7, 0xcb, 0xfd, 0xc6, 0x32, 0x81, 0x65},
                                         {0x36, 0x49, 0x3f, 0xf5, 0x9e, 0xc8, 0x3f, 0x57, 0xfa, 0xd8, 0xd8, 0x2b, 0x40, 0xc0, 0xf1, 0x25},
                                         {0xd1, 0xbe, 0x4b, 0xae, 0xb6, 0xc4, 0xac, 0xed, 0x4d, 0x79, 0xed, 0xc7, 0xdd, 0x71, 0xc1, 0x86},
                                         {0x31, 0x0a, 0x9c, 0xd0, 0xe8, 0x77, 0x13, 0x33, 0x78, 0x0d, 0x47, 0xd6, 0x00, 0x85, 0x56, 0x30},
                                         {0x8a, 0xa5, 0x4c, 0x00, 0x83, 0x78, 0x53, 0xc5, 0x08, 0x0c, 0xa3, 0xed, 0x65, 0x01, 0xc0, 0x8d},
                                         {0xfc, 0x35, 0x65, 0xc8, 0x35, 0x90, 0x58, 0x5b, 0x61, 0xa9, 0xb3, 0x5f, 0xf5, 0xc9, 0x66, 0x63},
                                         {0xba, 0x6f, 0xd1, 0xee, 0x24, 0x3a, 0xe6, 0x8a, 0xef, 0xc7, 0x8c, 0x9e, 0xcd, 0x6f, 0x1d, 0x49},
                                         {0x8c, 0x4b, 0xda, 0x6c, 0xf9, 0xcc, 0xdb, 0x78, 0xd7, 0x33, 0x99, 0xca, 0xef, 0x58, 0x85, 0x79},
                                         {0x6a, 0xf6, 0xa2, 0x31, 0x03, 0x14, 0xbf, 0xf2, 0x2b, 0xe8, 0x22, 0x1c, 0x9a, 0x13, 0xb2, 0xc5},
                                         {0x6b, 0xe3, 0x8c, 0x82, 0x5a, 0x7a, 0xd8, 0x1c, 0x8c, 0x61, 0x0b, 0x37, 0xa8, 0x90, 0x96, 0x60},
                                         {0xa0, 0x60, 0x10, 0xca, 0x61, 0x29, 0x97, 0x92, 0x29, 0x91, 0x55, 0x5b, 0x7e, 0x75, 0x62, 0xc8}},
                                        {{0xe5, 0xf3, 0xf3, 0x03, 0xd1, 0x28, 0x3b, 0x91, 0xff, 0x14, 0xe6, 0x89, 0x66, 0x7c, 0x1d, 0xa6},
                                         {0xba, 0xfa, 0x51, 0x2f, 0x1b, 0x22, 0xd1, 0x19, 0xb1, 0x09, 0xc1, 0x02, 0x49, 0x3d, 0xcb, 0x29},
                                         {0xd9, 0x13, 0x67, 0x13, 0x7e, 0x8a, 0x29, 0xbf, 0x8a, 0xfc, 0x79, 0xf0, 0x93, 0x5d, 0x76, 0xa4},
                                         {0xcc, 0x11, 0xee, 0x5a, 0x6c, 0x55, 0x0c, 0x95, 0x73, 0x02, 0xdd, 0x09, 0x15, 0xbc, 0xb6, 0x14},
                                         {0xb9, 0xe6, 0x0f, 0xf3, 0x7a, 0x53, 0x03, 0x70, 0x85, 0xae, 0x36, 0x14, 0xe9, 0xf7, 0x02, 0x3d},
                                         {0xb7, 0xa2, 0xd6, 0x3c, 0xe3, 0x14, 0x9b, 0xca, 0xf8, 0x08, 0xaf, 0x76, 0x02, 0x65, 0x67, 0xb7},
                                         {0xad, 0x2c, 0x8b, 0x5f, 0x4b, 0x5f, 0xe4, 0x84, 0xa2, 0x81, 0x2b, 0x47, 0x85, 0x39, 0x8e, 0xfe},
                                         {0x1a, 0x1a, 0x70, 0xd0, 0xf6, 0xe7, 0xb2, 0x32, 0x81, 0x0b, 0xc0, 0x0a, 0x16, 0x9f, 0x70, 0xeb},
                                         {0xca, 0x9a, 0x84, 0xb9, 0xdb, 0x75, 0xc6, 0x13, 0x36, 0x7e, 0x87, 0x21, 0x6c, 0x89, 0x8c, 0xdb},
                                         {0xb3, 0x34, 0xcb, 0xe7, 0x1f, 0x99, 0x8b, 0xff, 0xcc, 0x4a, 0x5c, 0xb2, 0x06, 0x6e, 0x52, 0x60},
                                         {0x2d, 0x27, 0xb5, 0xb4, 0xc2, 0xa6, 0x78, 0xf3, 0xf9, 0xca, 0x01, 0xbd, 0x10, 0xa1, 0x1c, 0xac},
                                         {0xb2, 0x42, 0x36, 0x70, 0xe3, 0xeb, 0x34, 0x29, 0x9a, 0x77, 0xca, 0x6b, 0x1b, 0x55, 0xba, 0xdd},
                                         {0x05, 0xbc, 0x77, 0x99, 0x43, 0xec, 0x78, 0x02, 0x09, 0x2e, 0x91, 0x74, 0x2c, 0x50, 0x5f, 0xe3},
                                         {0x33, 0x8e, 0x68, 0x84, 0xf5, 0x93, 0xe9, 0xe7, 0xfc, 0x84, 0x60, 0x25, 0x56, 0x0f, 0xb2, 0x6d},
                                         {0x41, 0x69, 0x40, 0x17, 0x55, 0x6b, 0x87, 0x53, 0xb5, 0x3c, 0x39, 0x21, 0x86, 0x89, 0x72, 0x3c},
                                         {0x5e, 0x55, 0xf0, 0xb5, 0xd6, 0x31, 0x2e, 0x16, 0x54, 0x87, 0xee, 0xd0, 0x55, 0xd1, 0xbd, 0x93}},
                                        {{0x42, 0x49, 0xc6, 0x3e, 0xe3, 0x48, 0xb9, 0x08, 0xad, 0xc2, 0xf8, 0x54, 0xf7, 0x78, 0x08, 0xd2},
                                         {0x38, 0xa6, 0xb0, 0x84, 0x90, 0xd1, 0x9d, 0x0b, 0xe4, 0x4f, 0x07, 0xb9, 0xb9, 0x89, 0x55, 0xed},
                                         {0x4d, 0xc0, 0xff, 0x9d, 0x5f, 0xee, 0xd1, 0xb8, 0x6b, 0xdd, 0x0e, 0xa9, 0xee, 0x56, 0xef, 0x02},
                                         {0x62, 0xf3, 0xc3, 0x73, 0xeb, 0xe9, 0x9f, 0x1b, 0xce, 0x62, 0x5f, 0x33, 0xc0, 0xe7, 0x07, 0xee},
                                         {0x0a, 0x0b, 0x60, 0x4e, 0x65, 0x52, 0x34, 0x36, 0x5f, 0xf3, 0x4d, 0x9a, 0xdf, 0x6e, 0xd2, 0x1a},
                                         {0x86, 0xde, 0x8d, 0x89, 0xe7, 0x45, 0x09, 0x71, 0xd2, 0x00, 0x0e, 0x14, 0xc9, 0xc0, 0x7b, 0x63},
                                         {0xf7, 0xc0, 0xce, 0xa8, 0xb0, 0x02, 0xbd, 0x0f, 0x69, 0x18, 0x8c, 0x99, 0xd4, 0xa5, 0xa5, 0x81},
                                         {0xdd, 0x0f, 0xd2, 0xe9, 0x38, 0x52, 0x6c, 0x5d, 0xde, 0x99, 0xee, 0xae, 0xbe, 0xd4, 0xc1, 0xa2},
                                         {0xa5, 0xb5, 0x06, 0xd7, 0x31, 0x6c, 0x82, 0xcb, 0xed, 0x02, 0x91, 0x33, 0xe0, 0xaa, 0x97, 0x6b},
                                         {0xe0, 0x7c, 0x10, 0x3f, 0xea, 0xfa, 0x78, 0xd8, 0x20, 0x49, 0x88, 0x70, 0x59, 0x53, 0x60, 0x49},
                                         {0xa8, 0x20, 0xf0, 0x3c, 0x13, 0x28, 0xbd, 0xed, 0x34, 0x9b, 0x16, 0x16, 0xd0, 0x1c, 0x1e, 0x7a},
                                         {0x21, 0x16, 0x33, 0xf2, 0xa0, 0xa3, 0xf4, 0x27, 0xe9, 0x22, 0x12, 0xf9, 0x27, 0xd6, 0x73, 0x01},
                                         {0x04, 0x70, 0xf0, 0x0a, 0x66, 0x70, 0x49, 0x72, 0x51, 0x14, 0x8b, 0x9d, 0x6c, 0xd0, 0xde, 0x65},
                                         {0x34, 0xf1, 0xee, 0x43, 0xff, 0x7d, 0x1d, 0x55, 0x14, 0x26, 0x25, 0x2d, 0xcb, 0xb9, 0xf8, 0xa1},
                                         {0xe8, 0x09, 0xfb, 0x83, 0x8a, 0x51, 0xad, 0x5e, 0x76, 0xc2, 0x25, 0x85, 0x80, 0x96, 0x37, 0x26},
                                         {0xd4, 0x5b, 0xca, 0xd1, 0xe9, 0x49, 0xba, 0xab, 0x4b, 0xe8, 0x3d, 0xa8, 0x01, 0xad, 0x0f, 0xba}},
                                        {{0xb2, 0x21, 0x45, 0x2b, 0x93, 0x56, 0x1d, 0xd6, 0x59, 0x6b, 0x2a, 0x30, 0xa5, 0x8b, 0x27, 0xc9},
                                         {0x08, 0xc5, 0x82, 0x23, 0xcd, 0x1a, 0xdf, 0x89, 0xda, 0x4b, 0xc8, 0xbf, 0x75, 0xaa, 0x0e, 0x89},
                                         {0x53, 0xd1, 0xa7, 0x50, 0x8b, 0x08, 0x39, 0xb7, 0x1f, 0x95, 0x70, 0x96, 0x52, 0x02, 0x19, 0xf3},
                                         {0xdd, 0x6c, 0xa7, 0x8e, 0xa3, 0x7f, 0x9d, 0xac, 0x96, 0xb7, 0xce, 0x8f, 0xc3, 0x34, 0x66, 0x40},
                                         {0xdc, 0xb0, 0xb8, 0x94, 0x61, 0xe6, 0x6d, 0x9b, 0xfc, 0x67, 0xf5, 0xd3, 0x14, 0xa0, 0xbf, 0x1e},
                                         {0xe1, 0xa5, 0x6f, 0x77, 0x80, 0xc7, 0x47, 0x34, 0x15, 0xbc, 0xe3, 0x5a, 0x93, 0xce, 0x18, 0x91},
                                         {0xdc, 0xca, 0x37, 0x62, 0x1c, 0xc7, 0xb1, 0xf5, 0x99, 0x4b, 0x8e, 0x49, 0x95, 0xc4, 0x08, 0xce},
                                         {0x2c, 0x8f, 0xee, 0x67, 0x7f, 0x9c, 0xe1, 0x91, 0x98, 0xd3, 0x3b, 0xbb, 0xf4, 0xa3, 0x23, 0x4f},
                                         {0xc4, 0x56, 0x07, 0xaa, 0x1c, 0x78, 0x17, 0xbd, 0x74, 0xb8, 0x37, 0xad, 0xf2, 0x8d, 0x61, 0x20},
                                         {0x22, 0x42, 0xb7, 0xf1, 0xb6, 0xaf, 0x62, 0xb2, 0xa7, 0xe4, 0xf9, 0x4b, 0xae, 0x32, 0x10, 0x8f},
                                         {0x6b, 0xcd, 0x85, 0x25, 0x61, 0x25, 0xd4, 0x41, 0xe0, 0xaa, 0xf9, 0x8f, 0x5c, 0x41, 0xa0, 0x04},
                                         {0x62, 0x6f, 0xcb, 0x5e, 0xa7, 0xf7, 0x6b, 0x0c, 0xea, 0x1f, 0x17, 0x43, 0x96, 0x5b, 0xf3, 0x59},
                                         {0xde, 0x10, 0xc3, 0x55, 0x9a, 0x83, 0x1c, 0x4b, 0xde, 0xd4, 0x8b, 0x6a, 0xbb, 0xda, 0x64, 0x66},
                                         {0xe9, 0xe0, 0xf9, 0x15, 0xe5, 0x12, 0xf5, 0xc6, 0x16, 0xa4, 0xc9, 0xba, 0x2e, 0xf0, 0xd9, 0x53},
                                         {0x84, 0x70, 0x3c, 0x73, 0xf4, 0xa4, 0x5b, 0x25, 0xde, 0x8b, 0xd5, 0xab, 0x17, 0x49, 0x72, 0x4a},
                                         {0xcb, 0x68, 0xe9, 0x1a, 0xdd, 0x3a, 0x3b, 0xad, 0xf4, 0x36, 0x14, 0x45, 0x28, 0x06, 0xba, 0x8d}}};

// 學MD5，但改用cos做生成
// for(int i=0;i<64;i++)
//     (uint32_t)floor(abs(cos(i + 1)) * (1l << 32)))
static const uint32_t keyK[64] = {0x8a51407d, 0x6a88995d, 0xfd7025f4, 0xa7553036, 0x489e15c1, 0xf5cdb84b, 0xc0ffbcf6, 0x253f7d7e,
                                  0xe93fd535, 0xd6cd6448, 0x01220ae4, 0xd806d023, 0xe84e6ea9, 0x230135d8, 0xc27ae834, 0xf5292bf4,
                                  0x46711ac1, 0xa90a840a, 0xfd1bbef0, 0x687810e5, 0x8c37fc1b, 0xfffd6ec6, 0x8867beac, 0x6c96fed4,
                                  0xfdbf77ac, 0xa59c8134, 0x4ac99be5, 0xf66d568a, 0xbf80b2c1, 0x277d05e4, 0xea2c8e1f, 0xd58fa982,
                                  0x03661adb, 0xd93be6ca, 0xe7585f52, 0x20c23a76, 0xc3f22ce1, 0xf47fb4d2, 0x4442b612, 0xaabc73eb,
                                  0xfcc24453, 0x66657006, 0x8e1be7c3, 0xfff5bb27, 0x867b8079, 0x6ea336bb, 0xfe09b282, 0xa3e07fda,
                                  0x4cf3a208, 0xf708037e, 0xbdfdd143, 0x29b9c389, 0xeb1494a7, 0xd44da632, 0x05aa195e, 0xda6ca20a,
                                  0xe65dac20, 0x1e8296e0, 0xc5658374, 0xf3d1564b, 0x4212f2e5, 0xac6af723, 0xfc63b7e7, 0x6450c165};

// hash function要rotate所查的表
static const uint8_t rot[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                                5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
                                4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                                6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

#endif