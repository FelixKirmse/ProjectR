#include "RInput.hpp"

namespace ProjectR
{
struct RInputImpl : public RInput
{
  RInputImpl()
  {
    if(!LoadConfig())
      SetDefaults();
  }

  bool LoadConfig()
  {
    return false;
  }

  void SaveConfig()
  {
  }

  void SetDefaults()
  {
    Set(None, GetKey());
    Set(Up, GetKey(TCODK_UP), GetKey(TCODK_CHAR, 'w'));
    Set(Down, GetKey(TCODK_DOWN), GetKey(TCODK_CHAR, 's'));
    Set(Left, GetKey(TCODK_LEFT), GetKey(TCODK_CHAR, 'a'));
    Set(Right, GetKey(TCODK_RIGHT), GetKey(TCODK_CHAR, 'd'));
    Set(Confirm, GetKey(TCODK_ENTER), GetKey(TCODK_CHAR, 'e'));
    Set(Cancel, GetKey(TCODK_ESCAPE), GetKey(TCODK_CHAR, 'q'));
    Set(Inventory, GetKey(TCODK_CHAR, 'i'));
    Set(Party, GetKey(TCODK_CHAR, 'p'));
    Set(Back, GetKey(TCODK_BACKSPACE));
  }

  inline void Set(int action, TCOD_key_t primary)
  {
    Set(action, primary, primary);
  }

  inline void Set(int action, TCOD_key_t primary, TCOD_key_t secondary)
  {
    SetActionPrimary(action, primary);
    SetActionSecondary(action, secondary);
  }

  inline TCOD_key_t GetKey(TCOD_keycode_t code = TCODK_NONE, char chara = 0)
  {
    TCOD_key_t key;
    key.vk = code;
    key.c = chara;
    return key;
  }
};


std::shared_ptr<RInput> RInput::Create()
{
  return std::make_shared<RInputImpl>();
}

RInput::~RInput(){}
}

/*
enum Actions
{
  None,
  Up,
  Down,
  Left,
  Right,
  Accept,
  Cancel,
  Inventory,
  Party
};*/
