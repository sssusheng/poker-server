#ifndef SERVER_DDZ_RSACRYPTO_H
#define SERVER_DDZ_RSACRYPTO_H

#include <string>
#include <openssl/evp.h>
#include "Hash.h"

class RsaCrypto {
public:
    enum KeyLength {
        BITS_1k = 1024,
        BITS_2k = 2048,
        BITS_3k = 3072,
        BITS_4k = 4096,
    };

    enum KeyType { PublicKey, PrivateKey };

    explicit RsaCrypto() = default;

    // 构造对象并加载秘钥文件中的数据到内存中
    explicit RsaCrypto(std::string fileName, KeyType type);

    ~RsaCrypto();

    // 将秘钥字符串解析为秘钥类型
    void parseStringToKey(std::string data, KeyType type);

    // 生成密钥对
    void generateRsaKey(KeyLength bits, std::string pub = "public.pem", std::string pri = "private.pem");

    // 通过公钥进行加密
    std::string pubKeyEncrypt(std::string data);

    // 通过私钥进行解密
    std::string priKeyDecrypt(std::string data);

    // 数据签名
    std::string sign(std::string data, HashType hash = HashType::Sha256);

    // 签名校验
    bool verify(std::string sign, std::string data, HashType hash = HashType::Sha256);

private:
    EVP_PKEY *m_pubKey = NULL;
    EVP_PKEY *m_priKey = NULL;
};


#endif //SERVER_DDZ_RSACRYPTO_H
