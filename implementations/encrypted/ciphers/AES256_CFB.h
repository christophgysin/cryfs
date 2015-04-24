#pragma once
#ifndef MESSMER_BLOCKSTORE_IMPLEMENTATIONS_ENCRYPTED_CIPHERS_AES256_CFB_H_
#define MESSMER_BLOCKSTORE_IMPLEMENTATIONS_ENCRYPTED_CIPHERS_AES256_CFB_H_

#include "../../../utils/FixedSizeData.h"
#include "../../../utils/Data.h"
#include <cryptopp/cryptopp/aes.h>
#include <boost/optional.hpp>

namespace blockstore {
namespace encrypted {

//TODO Add contract/interface for ciphers
class AES256_CFB {
public:
  using EncryptionKey = FixedSizeData<32>;
  static_assert(32 == CryptoPP::AES::MAX_KEYLENGTH, "If AES offered larger keys, we should offer a variant with it");

  AES256_CFB(const EncryptionKey &key);

  static constexpr unsigned int ciphertextSize(unsigned int plaintextBlockSize) {
    return plaintextBlockSize + IV_SIZE;
  }

  static constexpr unsigned int plaintextSize(unsigned int ciphertextBlockSize) {
    return ciphertextBlockSize - IV_SIZE;
  }

  static Data encrypt(const byte *plaintext, unsigned int plaintextSize, const EncryptionKey &encKey);
  static boost::optional<Data> decrypt(const byte *ciphertext, unsigned int ciphertextSize, const EncryptionKey &encKey);

private:
  static constexpr unsigned int IV_SIZE = CryptoPP::AES::BLOCKSIZE;
};

}
}

#endif