#include "MenuItem.hpp"

namespace ProjectR
{
struct MenuItemImpl : public MenuItem
{
  MenuItemImpl(std::string const& label, std::function<void()> callback)
    : _label(label),
      _active(false),
      _disabled(false),
      _callBack(callback)
  {
  }

  MenuItemImpl(std::string const& label)
    : _label(label),
      _active(false),
      _disabled(false)
  {
  }

  void Disabled(bool disabled)
  {
    _disabled = disabled;
  }

  bool Disabled()
  {
    return _disabled;
  }

  void Activate()
  {
    _active = true;
  }

  void Deactivate()
  {
    _active = false;
  }

  void Run()
  {
    _callBack();
  }

  void SetStateMachine(std::shared_ptr<IStateMachine> const& machine)
  {
    _master = machine;
  }

  bool IsSelected()
  {
    return _active;
  }

  std::string const& GetLabel()
  {
    return _label;
  }

  void SetLabel(std::string const& label)
  {
    _label = label;
  }

  void SetCallBack(std::function<void ()> const& callback)
  {
    _callBack = callback;
  }

  std::string _label;
  bool _active;
  bool _disabled;
  std::function<void()> _callBack;
  std::shared_ptr<IStateMachine> _master;
};

std::shared_ptr<MenuItem> MenuItem::Create(std::string const& label)
{
  return std::make_shared<MenuItemImpl>(label);
}

std::shared_ptr<MenuItem> MenuItem::Create(std::string const& label, std::function<void()> callback)
{
  return std::make_shared<MenuItemImpl>(label, callback);
}
}
