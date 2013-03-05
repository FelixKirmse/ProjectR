#pragma once
#include "IState.hpp"
#include <functional>
#include <string>

namespace ProjectR
{
class MenuItem : public IState
{
public:
  virtual bool IsSelected() = 0;
  virtual std::string const& GetLabel() = 0;
  virtual void SetLabel(std::string const& label) = 0;
  virtual void SetCallBack(std::function<void ()> const& callback) = 0;
  virtual void Disabled(bool disabled) = 0;
  virtual bool Disabled() = 0;

  virtual ~MenuItem(){}
  static std::shared_ptr<MenuItem> Create(std::string const& label);
  static std::shared_ptr<MenuItem> Create(std::string const& label,
                                          std::function<void()> callback);
};
}
