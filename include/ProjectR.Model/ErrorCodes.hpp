#pragma once
#include <iostream>

enum ErrorCodes
{
  LUA_ERROR_RELOAD = 129,
  LUA_ERROR_BINDING = 130,
  LUA_ERROR_ASSIGNING = 131,
  LUA_ERROR_CASTING = 132,
  ERROR_SPELL_NOT_FOUND = 150,
  ERROR_TEMPLATE_NOT_FOUND = 151,
  ERROR_CHAR_LIMIT_REACHED_FRONTROW = 152,
  ERROR_CHAR_LIMIT_REACHED_BACKSEAT = 153,
  ERROR_CHAR_LIMIT_REACHED_RESERVE = 154,
  UNKNOWN_ERROR = 255
};

template<typename T>
void Exit(int errorCode, T const& message)
{
  std::cerr << message << std::endl;
  exit(errorCode);
}
