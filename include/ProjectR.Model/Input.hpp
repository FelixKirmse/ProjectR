#pragma once
#include <boost/unordered_map.hpp>
#include <array>
#include "libtcod/libtcod.hpp"

namespace ProjectR
{
template<typename T>
class Input
{
public:
  typedef boost::unordered::unordered_map<T, std::array<TCOD_key_t, 2> > InputMap;

  inline void SetActionPrimary(T action, TCOD_key_t key)
  {
    _inputs[action][0] = key;
  }

  inline void SetActionSecondary(T action, TCOD_key_t key)
  {
    _inputs[action][1] = key;
  }

  inline void SetAction(T action, std::array<TCOD_key_t, 2> keys)
  {
    _inputs[action] = keys;
  }

  inline bool Action(T action)
  {
    return Check(_inputs[action][0]) || Check(_inputs[action][1]);
  }

  inline void Update()
  {
    do
    {
      TCODConsole::flush();
      _currentInput = TCODConsole::checkForKeypress(TCOD_KEY_PRESSED);
      if(TCODConsole::isWindowClosed())
        break;
    }while(_currentInput.vk == TCODK_NONE);
  }

  virtual bool LoadConfig() = 0;
  virtual void SaveConfig() = 0;

private:
  inline bool Check(TCOD_key_t const& key)
  {
    if(_currentInput.vk != key.vk)
      return false;

    if(key.vk == TCODK_CHAR)
    return _currentInput.c == key.c;

    return true;
  }

  InputMap _inputs;
  TCOD_key_t _currentInput;
};
}
