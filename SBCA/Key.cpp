#include "stdafx.h"
#include "util.h"
#include "Key.h"

// ��K�_���[�Wpadding
// padding���覡�PMD5�BSHA2�@�ˡA100...00||length
// @param key �n������ഫ��vector
void Key::keyPadding(vector<uint8_t>& key) {
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
void Key::keyHashing(vector<uint32_t>& in, vector<uint64_t>& out) {
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
void Key::genKeys(vector<uint8_t>& key, vector<uint64_t>& keys) {
    vector<uint8_t> keyBytes;
    vector<uint32_t>* calc = nullptr;

    // ��MD5�BSHA2�@�˪�padding�覡
    keyPadding(keyBytes);
    // ��32bit�����
    calc = byteToU32(&keyBytes);
    auto begin = chrono::steady_clock::now();
    // ��padding�L��key�i�������X�e���round key
    keyHashing(*calc, keys);
    auto end = chrono::steady_clock::now();
    /*if (verbose)
        cout << "hash time: " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "us" << endl;*/
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
    /*if (verbose) {
        cout << "other key gen time: " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "us" << endl;
        print(keys);
    }*/
}

// ����lkey���ͨC��Round�n�Ϊ�key vector
// @param key �o���ϥΪ��K�_�A�ǤJstring�Akey�h������A�|�Q���Y��64bit
// @param keys �Ҧ���round key
void Key::genKeys(string& key, vector<uint64_t>& keys) {
    vector<uint8_t>* keyBytes = nullptr;
    // ����쥻���K�_�r���নbytes vector
    keyBytes = str2Byte(key);
    genKeys(*keyBytes, keys);
    delete keyBytes;
}

// �غc�l
Key::Key() {}
Key::Key(vector<uint8_t> k) {
    auto begin = chrono::steady_clock::now();
    genKeys(k, keys);
    auto end = chrono::steady_clock::now();
    usingTime = chrono::duration_cast<chrono::microseconds>(end - begin).count();
}
Key::Key(Key* other) {
    keys = vector<uint64_t>(*other->getKeys());
    usingTime = other->getTime();
}
// �Ψ�Ū��round key��function
// @return ��i��round key
uint64_t Key::getIdx(int i) {
    return keys[i];
}
// round key��get���
// @return round key��vector
vector<uint64_t>* Key::getKeys() {
    return &keys;
}
// �ͦ���O�ɶ���get���
// @return round key�ͦ���O�ɶ�
uint64_t Key::getTime() {
    return usingTime;
}