#include "rsa.h"

RSA::RSA()
    : m_keys_dir{std::filesystem::current_path()},
      m_save_dir{std::filesystem::current_path()} {}

bool RSA::GenerateKeys() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<std::uint64_t> dis(3, 255);
  auto p = GeneratePrime(dis, gen);
  auto q = GeneratePrime(dis, gen);

  auto n = p * q;

  auto phi_n = (p - 1) * (q - 1);

  auto e = ChoosePublicExponent(phi_n);
  std::ofstream pub_file(m_keys_dir / "public_key", std::ios::binary);
  pub_file.write(reinterpret_cast<const char *>(&n), sizeof(n));
  pub_file.write(reinterpret_cast<const char *>(&e), sizeof(e));

  auto d = ComputePrivateExponent(e, phi_n);
  std::ofstream prv_file(m_keys_dir / "private_key", std::ios::binary);
  prv_file.write(reinterpret_cast<const char *>(&n), sizeof(n));
  prv_file.write(reinterpret_cast<const char *>(&d), sizeof(d));
  return true;
}

bool RSA::Encode(const std::filesystem::path &path) {
  std::filesystem::path pub_path(m_keys_dir / "public_key");

  bool flag{std::filesystem::exists(path)};
  if (flag = (flag && std::filesystem::exists(pub_path) &&
              std::filesystem::is_regular_file(pub_path)),
      flag) {
    std::ifstream pub_key_file(pub_path, std::ios::binary);

    std::uint64_t n, e;
    pub_key_file.read(reinterpret_cast<char *>(&n), sizeof(n));
    pub_key_file.read(reinterpret_cast<char *>(&e), sizeof(e));
    pub_key_file.close();

    std::ifstream ifs(path, std::ios::binary);
    std::vector<char> buffer((std::istreambuf_iterator<char>(ifs)),
                             std::istreambuf_iterator<char>());
    ifs.close();

    std::vector<std::int32_t> encrypted_data(buffer.size());
    for (std::size_t i = 0; i < buffer.size(); ++i) {
      std::int32_t m = buffer[i] + m_shift;
      encrypted_data[i] = ModuloExponentiation(m, e, n);
    }
    std::ofstream ofs(m_save_dir / (path.stem().string() + "_encoded" +
                                    path.extension().string()),
                      std::ios::binary);
    ofs.write(reinterpret_cast<const char *>(encrypted_data.data()),
              encrypted_data.size() * sizeof(std::int32_t));
    ofs.close();
  }
  return flag;
}

bool RSA::Decode(const std::filesystem::path &path) {
  std::filesystem::path prv_path(m_keys_dir / "private_key");

  bool flag{std::filesystem::exists(path)};
  if (flag = (flag && std::filesystem::exists(prv_path) &&
              std::filesystem::is_regular_file(prv_path)),
      flag) {
    std::ifstream priv_key_file(prv_path, std::ios::binary);

    std::uint64_t n, d;
    priv_key_file.read(reinterpret_cast<char *>(&n), sizeof(n));
    priv_key_file.read(reinterpret_cast<char *>(&d), sizeof(d));
    priv_key_file.close();

    std::ifstream ifs(path, std::ios::binary);
    std::vector<std::int32_t> buffer;
    for (std::int32_t value;
         ifs.read(reinterpret_cast<char *>(&value), sizeof(value));) {
      buffer.push_back(value);
    }
    ifs.close();

    std::vector<char> decrypted_data(buffer.size());
    for (std::size_t i = 0; i < buffer.size(); ++i) {
      auto c = ModuloExponentiation(buffer[i], d, n) - m_shift;
      decrypted_data[i] = static_cast<char>(c);
    }

    std::ofstream ofs(m_save_dir / (path.stem().string() + "_decode" +
                                    path.extension().string()),
                      std::ios::binary);
    ofs.write(decrypted_data.data(), decrypted_data.size());
    ofs.close();
  }
  return flag;
}

bool RSA::SetKeysDir(const std::filesystem::path &path) {
  bool flag{std::filesystem::exists(path)};
  if (flag = (flag && std::filesystem::is_directory(path)), flag) {
    m_keys_dir = path;
  }
  return flag;
}

bool RSA::SetSaveDir(const std::filesystem::path &path) {
  bool flag{std::filesystem::exists(path)};
  if (flag = (flag && std::filesystem::is_directory(path)), flag) {
    m_save_dir = path;
  }
  return flag;
}

std::uint64_t RSA::GeneratePrime(
    std::uniform_int_distribution<std::uint64_t> &dis, std::mt19937 &gen) {
  std::uint64_t prime;
  do {
    prime = dis(gen);
  } while (!IsPrime(prime));
  return prime;
}

bool RSA::IsPrime(std::uint64_t n) {
  if (n <= 1) {
    return false;
  }
  if (n <= 3) {
    return true;
  }
  if (n % 2 == 0 || n % 3 == 0) {
    return false;
  }
  for (std::uint64_t i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) {
      return false;
    }
  }
  return true;
}

std::uint64_t RSA::ChoosePublicExponent(std::uint64_t phi_n) {
  std::uint64_t e = 2;
  while (std::gcd(e, phi_n) != 1) {
    ++e;
  }
  return e;
}

std::uint64_t RSA::ComputePrivateExponent(std::uint64_t e,
                                          std::uint64_t phi_n) {
  auto [gcd, x, y] = ExtendedEuclid(e, phi_n);
  if (x < 0) {
    x += phi_n;
  }
  return x;
}

std::tuple<std::uint64_t, std::int64_t, std::int64_t> RSA::ExtendedEuclid(
    std::uint64_t a, std::uint64_t b) {
  if (b == 0) {
    return {a, 1, 0};
  }
  auto [gcd, x, y] = ExtendedEuclid(b, a % b);
  return {gcd, y, x - (a / b) * y};
}

std::int32_t RSA::ModuloExponentiation(std::int32_t base,
                                       std::uint64_t exponent,
                                       std::uint64_t modulus) const {
  std::int32_t result = 1;
  base = base % modulus;
  while (exponent > 0) {
    if (exponent & 1) {
      result = (result * base) % modulus;
    }
    exponent = exponent >> 1;
    base = (base * base) % modulus;
  }
  return result;
}
