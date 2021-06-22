#include "stdafx.h"
#include "feistel.h"

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

// ��sbox���Ȱ�����
// @param val ��l���
// @param hand ��Τ@��sbox
// @return ��l��Ƹg�Lsbox�����᪺��
uint32_t s(uint32_t val, int hand) {
    uint32_t res = 0;
    uint8_t tmp;
    for (int i = 0; i < 4; i++) {
        // ���@��byte�X��
        tmp = val >> 8 * i & 0xff;
        // ��box�n���N����
        res |= (sbox[hand][tmp >> 4][tmp & 0xf]) << 8 * i;
    }
    return res;
}

// �Nstd::string�ରvector<uint8_t>
// @param str �r��
// @param byte �r���ഫ�᪺vector
void str2Byte(string str, vector<uint8_t>& bytes) {
    for (uint8_t c : str) {
        bytes.push_back(c);
    }
}

// �Nbyte��^uint32_t
// @param bytes �n������ഫ��vector
// @param data �s���ഫ�᪺vector
void byteToU32(vector<uint8_t>& bytes, vector<uint32_t>& data) {
    uint8_t* tmp = new uint8_t[4];
    // ���s�ոˬ�8byte�@���b��block�A�o�˥[�K�ɴN��@�Ӥ@��Ū���F
    for (int i = 0; i < bytes.size(); i += 4) {
        for (int j = 0; j < 4; j++) {
            tmp[j] = bytes[i + j];
        }
        // �N�}�Cuint64_t���Ы����
        data.push_back(*((uint32_t*)tmp));
    }
    delete[] tmp;
}

// �Nbyte��^uint64_t
// @param bytes �n������ഫ��vector
// @param data �s���ഫ�᪺vector
void byteToU64(vector<uint8_t>& bytes, vector<uint64_t>& data) {
    uint8_t* tmp = new uint8_t[DATA_SIZE];
    // ���s�ոˬ�8byte�@���b��block�A�o�˥[�K�ɴN��@�Ӥ@��Ū���F
    for (int i = 0; i < bytes.size(); i += DATA_SIZE) {
        for (int j = 0; j < DATA_SIZE; j++) {
            tmp[j] = bytes[i + j];
        }
        // �N�}�Cuint64_t���Ы����
        data.push_back(*((uint64_t*)tmp));
    }
    delete[] tmp;
}

// �Nuint64_t��^byte
// @param byte �n������ഫ��vector
// @param data �s���ഫ�᪺vector
void u64ToByte(vector<uint64_t>& data, vector<uint8_t>& byte) {
    for (uint64_t i : data) {
        byte.push_back(i & 0xff);
        byte.push_back((i >> 8) & 0xff);
        byte.push_back((i >> 16) & 0xff);
        byte.push_back((i >> 24) & 0xff);
        byte.push_back((i >> 32) & 0xff);
        byte.push_back((i >> 40) & 0xff);
        byte.push_back((i >> 48) & 0xff);
        byte.push_back((i >> 56) & 0xff);
    }
}

// �HPKCS#7�����padding
// @param byte �n��padding������vector
void addPKCS7(vector<uint8_t>& bytes) {
    // �ˬd�npadding�h��
    // https://asecuritysite.com/encryption/padding_des
    // �ϥ�RFC 5652(PKCS#7 Padding)�覡�APadding��%16=0
    int needPadding = 16 - (bytes.size() % 16);
    for (int i = 0; i < needPadding; i++) {
        bytes.push_back(needPadding);
    }
}

// ����PKCS#7��padding
// @param bytes �n����padding��vector
void rmPKCS7(vector<uint8_t>& bytes) {
    uint8_t check = bytes[bytes.size() - 1];
    if (check > 16) {
        throw 1;
    }
    for (int i = 0; i < check; i++)
        bytes.pop_back();
}

// ��K�_���[�Wpadding
// padding���覡�PMD5�BSHA2�@�ˡA100...00||length
// @param key �n������ഫ��vector
void keyPadding(vector<uint8_t>& key) {
    uint64_t size = key.size();
    int needPadding = 64 - (key.size() % 64) - 9;
    key.push_back(0x80);
    for (int i = 0; i < needPadding; i++) {
        key.push_back(0);
    }
    for (int i = 0; i < 8; i++) {
        key.push_back((size >> (8 - i * 2)) && 0xff);
    }
}

// �λPmd5�ۦ����c���ͥX128bit�@��Feistel���e���key��
// �����ϥΤ@��SHA2������
// @param in �n���ꪺ��ƪ�vector
// @param out �n�s���X������Ȫ�vector
void keyHashing(vector<uint32_t>& in, vector<uint64_t>& out) {
    // �K�_���ꪺ��l��
    // �ڥͤ�B��H�ͤ�BC87��63����5ce34160a1f04b47f8
    // c8763�B48763�B�������ͤ�B�Z�Ůy���B�ڪ�������|�X
    uint32_t h0 = 0x19990423, h1 = 0x20081007, h2 = 0x5ce34160, h3 = 0xa1f04b47;
    uint32_t f, g, h, tmp;
    for (int i = 0; i < in.size(); i += 16) {
        for (int j = 0; j < 16; j++) {
            uint32_t a = h0, b = h1, c = h2, d = h3;
            for (int r = 0; r < 64; r++) {
                if (r < 16) {
                    // ��SHA2��s0
                    tmp = rotateR(a, 2) ^ rotateR(a, 13) ^ rotateR(a, 22);
                    // ��SHA2��maj
                    f = tmp + (a & b) ^ (a & c) ^ (b & c);
                    g = j;
                } else if (r >= 16 && r < 32) {
                    // ��SHA2��s1�Ae->d
                    f = rotateR(d, 6) ^ rotateR(d, 11) ^ rotateR(d, 25);
                    g = (5 * j + 1) % 16;
                } else if (r >= 32 && r < 48) {
                    f = b ^ c ^ d;
                    g = (3 * j + 5) % 16;
                } else {
                    f = c ^ (b | (~d)) + (a & b) ^ ((~a) & c);
                    g = (3 * j + 5) % 16;
                }
                tmp = d;
                d = c;
                c = b;
                h = rotateR((a + f + keyK[r] + in[i * 16 + g]), (uint8_t)rot[r]);
                b = h + b;
                a = tmp;
            }
            h0 += a;
            h1 += b;
            h2 += c;
            h3 += d;
        }
    }
    out.push_back((uint64_t)h0 << 32 | h1);
    out.push_back((uint64_t)h2 << 32 | h3);
}

// ����lkey���ͨC��Round�n�Ϊ�key vector
// @param key �o���ϥΪ��K�_�A�ǤJ�@��vector�Akey�h������A�|�Q���Y��64bit
// @param keys �Ҧ���round key
void genKeys(vector<uint8_t>& key, vector<uint64_t>& keys) {
    vector<uint8_t> keyBytes;
    vector<uint32_t> calc;

    // ��MD5�BSHA2�@�˪�padding�覡
    keyPadding(keyBytes);
    // ��32bit�����
    byteToU32(keyBytes, calc);
    auto begin = chrono::steady_clock::now();
    // ��padding�L��key�i�������X�e���round key
    keyHashing(calc, keys);
    auto end = chrono::steady_clock::now();
    if (verbose)
        cout << "hash time: " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "us" << endl;
    begin = chrono::steady_clock::now();
    // �]���e�����Φۭq���pmd5���禡����128bit���ȡA�γo2��64bit���Ȳ��ͳѤU��14��key
    for (int i = 2; i < 16; i++) {
        // i �O �ĴX��key
        // ���e���ĤG�Ӫ�key�P(C87��63)�̰���4byte��ڪ��ͤ�A�A�k��rot��(i or not(i-2))%64
        uint64_t tmp = rotateR((keys[i - 2] ^ 0x5ce3416019990423), rot[((i | ~keys[i - 2]) & 0xf) % 64]);
        // ����tmp
        reverse(tmp);
        // �A�N���p��e���ĤG��key���ȥhXOR( ((keys[i-1]<<<7)&(keys[i-1]<<<6)) ^ (keys[i-1]<<<3) )
        tmp ^= (rotateR(keys[i - 1], 7) & rotateR(keys[i - 1], 6)) ^ rotateR(keys[i - 1], 3);
        keys.push_back(tmp);
    }

    end = chrono::steady_clock::now();
    if (verbose) {
        cout << "other key gen time: " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "us" << endl;
        print(keys);
    }
}

// ����lkey���ͨC��Round�n�Ϊ�key vector
// @param key �o���ϥΪ��K�_�A�ǤJstring�Akey�h������A�|�Q���Y��64bit
// @param keys �Ҧ���round key
void genKeys(string& key, vector<uint64_t>& keys) {
    vector<uint8_t> keyBytes;
    // ����쥻���K�_�r���নbytes vector
    str2Byte(key, keyBytes);
    genKeys(keyBytes, keys);
}