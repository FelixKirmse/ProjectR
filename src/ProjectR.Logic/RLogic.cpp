#include "RLogic.hpp"
#include "IModel.hpp"
#include "TitleScreenLogic.hpp"
#include "RInput.hpp"

namespace ProjectR
{
struct RLogicImpl : public RLogic
{
  RLogicImpl()
  {
    LogicState::SetInput(RInput::Create());
  }

  ~RLogicImpl()
  {
  }

  void SetModel(std::shared_ptr<IModel> const& model)
  {
    AddState(TitleScreenLogic::Create());

    _model = model;
  }

  std::shared_ptr<IModel> _model;
};

std::shared_ptr<RLogic> RLogic::Create()
{
  return std::make_shared<RLogicImpl>();
}

}

