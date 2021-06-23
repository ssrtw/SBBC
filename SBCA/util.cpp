#include "stdafx.h"
#include "Feistel.h"

// �C�L�r��
// @param v �n�i��C�L��vector
void print(vector<uint64_t>& v) {
    for (uint64_t ul : v) {
        printf("%016llx\n", ul);
    }
    printf("\n");
}

// �C�L�r��
// @param v �n�i��C�L��vector
void print(vector<uint8_t>& v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i];
    }
}

// ��permutation
// @param block �n�q��m���᪺��
// @param from ��l���
// @param position_from �q�o��bit�h��
// @param position_to �h��o��bit
void addbit(uint64_t& block, uint64_t from, int position_from, int position_to) {
    // �ˬd�p�G��0�N���ΰ�shift�P�[�k
    if (((from << (position_from)) & FIRSTBIT) != 0)
        block += (FIRSTBIT >> position_to);
}

// ���ư�����
// @param x �n���઺���
void reverse(uint64_t& x) {
    uint64_t n = x;
    n = ((n & 0xffffffff00000000) >> 32) | ((n & 0x00000000ffffffff) << 32);
    n = ((n & 0xffff0000ffff0000) >> 16) | ((n & 0x0000ffff0000ffff) << 16);
    n = ((n & 0xff00ff00ff00ff00) >> 8) | ((n & 0x00ff00ff00ff00ff) << 8);
    n = ((n & 0xf0f0f0f0f0f0f0f0) >> 4) | ((n & 0x0f0f0f0f0f0f0f0f) << 4);
    n = ((n & 0xcccccccccccccccc) >> 2) | ((n & 0x3333333333333333) << 2);
    n = ((n & 0xaaaaaaaaaaaaaaaa) >> 1) | ((n & 0x5555555555555555) << 1);
    x = n;
}

// �Nuint64_t���e��bbit�����
// @param val block���b��
// return Function��X����
void highLowChange(uint64_t& val) {
    // uint64_t �O 8byte
    // >>16�O����4��byte�A0xffffffff�@32��1
    // �Ⱚ�C������
    val = (val >> 32) | ((val & 0xffffffff) << 32);
}

// ��J32bit���Ȧ^�Ǩ�k��shift��bit����
// @param value �n���઺value
// @param shift �k�۴X��bit
// @return ����᪺���G
uint32_t rotateR(uint32_t value, uint8_t shift) {
    return value >> shift | value << (32 - shift);
}

// ��J64bit���Ȧ^�Ǩ�k��shift��bit����
// @param value �n���઺value
// @param shift �k�۴X��bit
// @return ����᪺���G
uint64_t rotateR(uint64_t value, uint8_t shift) {
    return value >> shift | value << (64 - shift);
}

// �Nstd::string�ରvector<uint8_t>
// @param str �r��
// @return �r���ഫ�᪺vector
vector<uint8_t>* str2Byte(string str) {
    vector<uint8_t>* bytes = new vector<uint8_t>();
    for (uint8_t c : str) {
        bytes->push_back(c);
    }
    return bytes;
}

// �Nbyte��^uint32_t
// @param bytes �n������ഫ��vector
// @return �s���ഫ�᪺vector
vector<uint32_t>* byteToU32(vector<uint8_t>* bytes) {
    vector<uint32_t>* data = new vector<uint32_t>();
    uint8_t* tmp = new uint8_t[4];
    // ���s�ոˬ�8byte�@���b��block�A�o�˥[�K�ɴN��@�Ӥ@��Ū���F
    for (int i = 0; i < bytes->size(); i += 4) {
        for (int j = 0; j < 4; j++) {
            tmp[j] = (*bytes)[i + j];
        }
        // �N�}�Cuint64_t���Ы����
        data->push_back(*((uint32_t*)tmp));
    }
    delete[] tmp;
    return data;
}

// �Nbyte��^uint64_t
// @param bytes �n������ഫ��vector
// @return �s���ഫ�᪺vector
vector<uint64_t>* byteToU64(vector<uint8_t>* bytes) {
    vector<uint64_t>* data = new vector<uint64_t>();
    uint8_t* tmp = new uint8_t[DATA_SIZE];
    // ���s�ոˬ�8byte�@���b��block�A�o�˥[�K�ɴN��@�Ӥ@��Ū���F
    for (int i = 0; i < bytes->size(); i += DATA_SIZE) {
        for (int j = 0; j < DATA_SIZE; j++) {
            tmp[j] = (*bytes)[i + j];
        }
        // �N�}�Cuint64_t���Ы����
        data->push_back(*((uint64_t*)tmp));
    }
    delete[] tmp;
    return data;
}

// �Nuint64_t��^byte
// @param byte �n������ഫ��vector
// @return �s���ഫ�᪺vector
vector<uint8_t>* u64ToByte(vector<uint64_t>* data) {
    vector<uint8_t>* bytes = new vector<uint8_t>();
    for (uint64_t i : (*data)) {
        bytes->push_back(i & 0xff);
        bytes->push_back((i >> 8) & 0xff);
        bytes->push_back((i >> 16) & 0xff);
        bytes->push_back((i >> 24) & 0xff);
        bytes->push_back((i >> 32) & 0xff);
        bytes->push_back((i >> 40) & 0xff);
        bytes->push_back((i >> 48) & 0xff);
        bytes->push_back((i >> 56) & 0xff);
    }
    return bytes;
}