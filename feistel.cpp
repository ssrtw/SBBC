#include "feistel.h"

void print(vector<DATA>* v) {
    for (DATA ul : *v) {
        printf("%08x\n", ul);
    }
    printf("\n");
}

void addbit(DATA* block, DATA from, int position_from, int position_to) {
    if (((from << (position_from)) & FIRSTBIT) != 0)
        *block += (FIRSTBIT >> position_to);
}

void reverse(DATA* x) {
    DATA n = *x;
    n = ((n & 0xffff0000) >> 16) | ((n & 0x0000ffff) << 16);
    n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
    n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
    n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
    n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
    *x = n;
}

void highLowChange(DATA* val) {
    DATA high, low;
    // DATA 是 4byte
    // >>16是移動2個byte，0xffff共16個1
    high = (*val >> 16);
    low = (*val & 0xffff);
    // 把高低兩邊對調
    *val = high | (low << 16);
}

DATA F(DATA val) {
    val ^= 0xC8763423;  // C8763星爆氣流斬，4/23我生日
    reverse(&val);
    val ^= 0x10612011;    // 學號去掉前面的4
    highLowChange(&val);  // 高byte與低byte交換
    val ^= 0x5b006b00;    // 孫:5b6b
    reverse(&val);
    val ^= 0x005b0078;    // 學:5b78
    highLowChange(&val);  // 高byte與低byte交換
    val ^= 0x4e00fb00;    // 任:4efb

    // Permutation
    DATA tmp = 0, tmp2 = 0;
    for (int ii = 0; ii < 32; ii++)
        addbit(&tmp, val, Pbox[ii] - 1, ii);
    for (int ii = 0; ii < 32; ii++)
        addbit(&tmp2, tmp, Pbox[ii] - 1, ii);
    val = tmp2;
    return val;
}