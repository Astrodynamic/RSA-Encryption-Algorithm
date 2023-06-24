#pragma once

#include "ainterface.h"
#include "rsa.h"

class Interface final : virtual public AbstractInterface {
 public:
  Interface();
  explicit Interface(const Interface &other) = delete;
  explicit Interface(Interface &&other) = delete;
  Interface &operator=(const Interface &other) = delete;
  Interface &operator=(Interface &&other) = delete;
  ~Interface();

  virtual void Exec() final override;

 private:
  enum MenuFuncs : std::size_t {
    kMainFuncMenu = 0U,
    kEncodeFuncMenu,
    kDecodeFuncMenu,
    kSetKeysDirFuncMenu,
    kSetSaveDirFuncMenu,
    kMenuFuncsAll
  };

  enum MenuItem : std::size_t {
    kIntroduction = 0U,
    kMainMenu,
    kLoadCodeMenu,
    kSaveDirectoryMenu,
    kNotExistMenu,
    kMissingMenu,
    kCompletion
  };

  RSA m_model;

  void InitFuncMenus();
  bool RunProcessFile(std::function<bool(const std::filesystem::path &)> func);
};