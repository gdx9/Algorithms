#include <iostream>
#include <string>
#include <cassert>

// g++ -std=c++17 -Wall otp_cipher.cc -o otp_cipher && ./otp_cipher

static constexpr char kFirstLetterPosition = 'a';
static constexpr char kAlphabetSize = 'z' - 'a' + 1;

std::string EncryptOneTimePad(const std::string& kMessage, const std::string& kKey) {
  assert(kMessage.length() == kKey.length());

  const size_t kMessageSize = kMessage.length();

  std::string res(kMessageSize, '0');
  for(size_t i = 0; i < kMessageSize; ++i){
    // we need alphabet positions, not ascii positions. For that purpose -'a' is applied for every letter
    const char kLetterMessage = std::tolower(kMessage[i]) - kFirstLetterPosition;
    const char kLetterKey = std::tolower(kKey[i]) - kFirstLetterPosition;

    const char kLetterPosition = (kLetterMessage + kLetterKey) % kAlphabetSize;// +26 to prevent negative values

    // +'a' is applied to return alphabet number to letter in ascii
    res[i] = kLetterPosition + kFirstLetterPosition;
  }

  return res;
}

std::string DecryptOneTimePad(const std::string& kEncrypted, const std::string& kKey) {
  assert(kEncrypted.length() == kKey.length());

  const size_t kMessageSize = kEncrypted.length();

  std::string res(kMessageSize, '0');
  for(size_t i = 0; i < kMessageSize; ++i){
    // we need alphabet positions not ascii positions. For that purpose -'a' is applied for every letter
    const char kLetterEncrypted = std::tolower(kEncrypted[i]) - kFirstLetterPosition;
    const char kLetterKey = std::tolower(kKey[i]) - kFirstLetterPosition;

    const char kLetterPosition = (kAlphabetSize + kLetterEncrypted - kLetterKey) % kAlphabetSize;// +26 to prevent negative values

    res[i] = kLetterPosition + kFirstLetterPosition;// restore ascii letter from position number in alphabet
  }

  return res;
}

// if not important to keep letters and that's fine to use any ASCII symbols
std::string EncryptOneTimePadXor(const std::string& kMessage, const std::string& kKey) {
  assert(kMessage.length() == kKey.length());

  const size_t kMessageSize = kMessage.length();

  std::string res(kMessageSize, '0');
  for(size_t i = 0; i < kMessageSize; ++i){
    res[i] = kMessage[i] ^ kKey[i];
  }

  return res;
}

std::string DecryptOneTimePadXor(const std::string& kEncrypted, const std::string& kKey) {
  assert(kEncrypted.length() == kKey.length());

  const size_t kMessageSize = kEncrypted.length();

  std::string res(kMessageSize, '0');
  for(size_t i = 0; i < kMessageSize; ++i){
    res[i] = kEncrypted[i] ^ kKey[i];
  }

  return res;
}
