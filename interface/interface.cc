#include "interface.h"

const std::vector<std::string> Interface::AbstractInterface::m_menus{
    " -------------------------------------------------------------- \n"
    "|                       RSA algorithm 1.0                      |\n"
    " -------------------------------------------------------------- \n",
    " -------------------------------------------------------------- \n"
    "|                       Select menu item                       |\n"
    " -------------------------------------------------------------- \n"
    "| 0. Exit                                                      |\n"
    "| 1. Public and private key generation                         |\n"
    "| 2. Encoding information by the RSA method                    |\n"
    "| 3. Decoding information by the RSA method                    |\n"
    "| 4. Setting the default path to save keys                     |\n"
    "| 5. Setting the default path to save files                    |\n"
    " -------------------------------------------------------------- \n"
    " > ",
    " -------------------------------------------------------------- \n"
    "|                       Select menu item                       |\n"
    " -------------------------------------------------------------- \n"
    "| 0. Exit                                                      |\n"
    "| 1. Enter the full path to the encoded(decoded) file ...      |\n"
    " -------------------------------------------------------------- \n"
    " > ",
    " -------------------------------------------------------------- \n"
    "|                       Select menu item                       |\n"
    " -------------------------------------------------------------- \n"
    "| 0. Exit                                                      |\n"
    "| 1. Enter the full path to the save directory                 |\n"
    " -------------------------------------------------------------- \n"
    " > ",
    " -------------------------------------------------------------- \n"
    "|       A file(directory) with that name does not exist        |\n"
    " -------------------------------------------------------------- \n",
    " -------------------------------------------------------------- \n"
    "|          Missing keys or valid save directory(file)          |\n"
    " -------------------------------------------------------------- \n",
    " -------------------------------------------------------------- \n"
    "|            Successful completion of the programme            |\n"
    " -------------------------------------------------------------- \n"};

Interface::Interface() {
  InitFuncMenus();
  ShowMenu(m_menus[MenuItem::kIntroduction]);
}

void Interface::InitFuncMenus() {
  m_funcs.resize(MenuFuncs::kMenuFuncsAll);

  m_funcs[MenuFuncs::kMainFuncMenu] = {
      std::bind(&Interface::Exit, this),
      std::bind(&RSA::GenerateKeys, std::ref(m_model)),
      std::bind(&Interface::RunMenu, this,
                std::ref(m_funcs[MenuFuncs::kEncodeFuncMenu]),
                MenuItem::kLoadCodeMenu),
      std::bind(&Interface::RunMenu, this,
                std::ref(m_funcs[MenuFuncs::kDecodeFuncMenu]),
                MenuItem::kLoadCodeMenu),
      std::bind(&Interface::RunMenu, this,
                std::ref(m_funcs[MenuFuncs::kSetKeysDirFuncMenu]),
                MenuItem::kSaveDirectoryMenu),
      std::bind(&Interface::RunMenu, this,
                std::ref(m_funcs[MenuFuncs::kSetSaveDirFuncMenu]),
                MenuItem::kSaveDirectoryMenu)};

  m_funcs[MenuFuncs::kEncodeFuncMenu] = {
      std::bind(&Interface::Exit, this), [this]() -> bool {
        return RunProcessFile(
            std::bind(&RSA::Encode, std::ref(m_model), std::placeholders::_1));
      }};

  m_funcs[MenuFuncs::kDecodeFuncMenu] = {
      std::bind(&Interface::Exit, this), [this]() -> bool {
        return RunProcessFile(
            std::bind(&RSA::Decode, std::ref(m_model), std::placeholders::_1));
      }};

  m_funcs[MenuFuncs::kSetKeysDirFuncMenu] = {
      std::bind(&Interface::Exit, this), [this]() -> bool {
        return RunProcessFile(std::bind(&RSA::SetKeysDir, std::ref(m_model),
                                        std::placeholders::_1));
      }};

  m_funcs[MenuFuncs::kSetSaveDirFuncMenu] = {
      std::bind(&Interface::Exit, this), [this]() -> bool {
        return RunProcessFile(std::bind(&RSA::SetSaveDir, std::ref(m_model),
                                        std::placeholders::_1));
      }};
}

bool Interface::RunProcessFile(
    std::function<bool(const std::filesystem::path&)> func) {
  const auto [success, path]{CheckInputPathFile()};
  if (success) {
    if (!func(path)) {
      ShowMenu(m_menus[MenuItem::kMissingMenu]);
    }
  } else {
    ShowMenu(m_menus[MenuItem::kNotExistMenu]);
  }
  return !success;
}

Interface::~Interface() { ShowMenu(m_menus[MenuItem::kCompletion]); }

void Interface::Exec() {
  RunMenu(m_funcs[MenuFuncs::kMainFuncMenu], MenuItem::kMainMenu);
}