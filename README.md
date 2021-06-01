# スターバストブロック暗号

Star Burst Block Cipher(SBBC, 星爆區塊密)
109TTU網路安全期末作業，設計Feistel結構的加解密演算法
需要在中間加入與自己相關訊息，其餘部分皆與星爆或桐人有關。

## 說明

使用Feistel結構的演算法
Block size是128bit
Key size是128bit
每個Block執行16 Round
使用S-Box與Permutation，與DES一樣為符合[香農](https://zh.wikipedia.org/wiki/克劳德·香农)的[混淆與擴散](https://zh.wikipedia.org/wiki/混淆與擴散)
用PKCS#7作padding

## TODO
- [ ] 加入test
- [ ] 將目前的64bit Block變成128bit
- [ ] 加入Key，算出16個Round的key
- [ ] 用Initial permutation，與IP^-1^
- [ ] 把目前padding使用的PKCS#5改成PKCS#7