//
// Created by Elijah Ghossein on 5/20/25.
//

#ifndef SMVALIDATOR_H
#define SMVALIDATOR_H

#include <vector>
#include <string>
#include "FileReader.h"
#include "TextBox.h"
#include "../../ds/StateMachine.h"

enum class FSMStates {
  START,
  VALID,
  INVALID
};

class SMValidator {


  TextBox* textBox;

  StateMachine FSM;

  FileReader reader;

//   std::vector<std::string> reservedKeywords = {
//     "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor",
//     "bool", "break", "case", "catch", "char", "char16_t", "char32_t", "class",
//     "compl", "concept", "const", "const_cast", "constexpr", "continue",
//     "co_await", "co_return", "co_yield", "decltype", "default", "delete", "do",
//     "double", "dynamic_cast", "else", "enum", "explicit", "export", "extern",
//     "false", "float", "for", "friend", "goto", "if", "inline", "int", "long",
//     "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr",
//     "operator", "or", "or_eq", "private", "protected", "public", "register",
//     "reinterpret_cast", "requires", "return", "short", "signed", "sizeof",
//     "static", "static_assert", "static_cast", "struct", "switch", "template",
//     "this", "thread_local", "throw", "true", "try", "typedef", "typeid",
//     "typename", "union", "unsigned", "using", "virtual", "void", "volatile",
//     "wchar_t", "while", "xor", "xor_eq"
// };

  bool isReservedKeywords(const std::string& input);

public:

  SMValidator(const std::string &filename, TextBox *textBox);

  bool isValidIdentifier();

};



#endif //SMVALIDATOR_H
