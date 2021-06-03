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

## Permutation

Feistel F function的置換表
第一列前五個值48763是星爆氣流斬，第一欄(idx=0,8,16...)是學號:410612011

| 0  | 1  | 2  | 3  | 4  | 5  | 6  | 7  |
|----|----|----|----|----|----|----|----|
| 4  | 8  | 7  | 6  | 3  | 14 | 16 | 12 |
| 10 | 40 | 51 | 57 | 59 | 60 | 29 | 42 |
| 61 | 2  | 15 | 1  | 25 | 31 | 0  | 22 |
| 20 | 54 | 50 | 48 | 58 | 55 | 18 | 36 |
| 11 | 9  | 13 | 26 | 24 | 30 | 35 | 43 |
| 63 | 33 | 46 | 32 | 56 | 62 | 41 | 53 |
| 49 | 23 | 19 | 17 | 27 | 21 | 28 | 5  |
| 44 | 39 | 38 | 45 | 34 | 47 | 52 | 37 |

## TODO

- [x] 包裝函數
- [ ] 加入test
- [x] 將目前的64bit Block變成128bit
- [ ] 加入Key，算出16個Round的key
- [ ] 用Initial permutation，與IP^-1^
- [ ] 把目前padding使用的PKCS#5改成PKCS#7