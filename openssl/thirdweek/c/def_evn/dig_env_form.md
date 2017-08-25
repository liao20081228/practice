# 数字信封格式
|类型| 名称           |大小
|----|------          |---
|int |cert_len        |4B
|int |signature_len   |4B
|int |digest_alg_len  |4B
|int |cipher_alg_len  |4B
|int |enc_key_len     |4B
|int |enc_data_len    |4B
unsigned char* | cert_data | nB
unsigned char* | signature | nB
char*          | digest_alg| nB      
char*          | cipher_alg| nB             
unsigned char* | enc_key   | nB        
unsigned char* | enc_data  | nB

*note
 * 证书为X509， PEM或者DER 自适应
 * cert_len 用于存放 cert_data长度
 * 类似的signature_len 用于存放 signature  ****
 * 密钥为PKCS#1 或者 PKCS#8 ， PEM或DER 自适应 
