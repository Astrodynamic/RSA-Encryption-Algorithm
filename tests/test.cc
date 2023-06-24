#include <gtest/gtest.h>

#include "rsa.h"

TEST(RSA, RSA_test_1) {
  std::filesystem::path path_0{"CMakeCache.txt"};
  std::filesystem::path path_1{"CMakeCache_encoded.txt"};
  std::filesystem::path path_2{"CMakeCache_encoded_decode.txt"};

  RSA rsa;

  ASSERT_TRUE(rsa.GenerateKeys());
  ASSERT_TRUE(rsa.Encode(path_0));
  ASSERT_TRUE(rsa.Decode(path_1));

  std::ifstream f1(path_0), f2(path_2);
  std::string content1((std::istreambuf_iterator<char>(f1)),
                       (std::istreambuf_iterator<char>())),
      content2((std::istreambuf_iterator<char>(f2)),
               (std::istreambuf_iterator<char>()));
  ASSERT_EQ(content1, content2);
}