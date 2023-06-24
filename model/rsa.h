#pragma once

#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <random>
#include <string>
#include <vector>

class RSA {
 public:
  RSA();
  RSA(const RSA &other) = delete;
  RSA(RSA &&other) = delete;
  RSA &operator=(const RSA &other) = delete;
  RSA &operator=(RSA &&other) = delete;
  ~RSA() = default;

  bool GenerateKeys();
  bool Encode(const std::filesystem::path &path);
  bool Decode(const std::filesystem::path &path);
  bool SetKeysDir(const std::filesystem::path &path);
  bool SetSaveDir(const std::filesystem::path &path);

 private:
  std::filesystem::path m_keys_dir;
  std::filesystem::path m_save_dir;
  static const int m_shift = 255;

  std::uint64_t GeneratePrime(std::uniform_int_distribution<std::uint64_t> &dis,
                              std::mt19937 &gen);
  bool IsPrime(std::uint64_t n);
  std::uint64_t ChoosePublicExponent(std::uint64_t phi_n);
  std::uint64_t ComputePrivateExponent(std::uint64_t e, std::uint64_t phi_n);
  std::tuple<std::uint64_t, std::int64_t, std::int64_t> ExtendedEuclid(
      std::uint64_t a, std::uint64_t b);
  std::int32_t ModuloExponentiation(std::int32_t base, std::uint64_t exponent,
                                    std::uint64_t modulus) const;
};