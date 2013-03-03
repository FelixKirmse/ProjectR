#pragma once
#include "IView.hpp"
#include "IObserver.hpp"
#include "StateMachine.hpp"

namespace ProjectR
{
class ConsoleView : public IView, public IObserver, public StateMachine
{
public:
  static ConsoleView* Create();
  virtual ~ConsoleView(){}
};

}
