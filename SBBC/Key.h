#pragma once

class Key {
   private:
    uint64_t usingTime = 0;
    vector<uint64_t> keys;
    void keyPadding(vector<uint8_t>& key);
    void keyHashing(vector<uint32_t>& in, vector<uint64_t>& out);
    void genKeys(vector<uint8_t>& key, vector<uint64_t>& keys);
    void genKeys(string& key, vector<uint64_t>& keys);

   public:
    Key();
    Key(vector<uint8_t> k);
    Key(Key* other);
    uint64_t getIdx(int i);
    vector<uint64_t>* getKeys();
    uint64_t getTime();
};