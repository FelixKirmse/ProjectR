#include "TargetSelectView.hpp"
#include "RConsole.hpp"
#include "IModel.hpp"
#include "BattleModel.hpp"
#include "ISpell.hpp"
#include "CharDescriptionDrawer.hpp"
#include "StatScreenDrawer.hpp"
#include "SpecialCharacter.hpp"

namespace ProjectR
{
struct TargetSelectViewImpl : public TargetSelectView
{
  TargetSelectViewImpl()
    : _descDrawer(CharDescriptionDrawer::Create()),
      _statDrawer(StatScreenDrawer::Create())
  {
    _descDrawer->SetPosition(80, 3);
    _statDrawer->SetPosition(80, 3);
  }

  void Run()
  {
     RConsole::GetRootConsole()->SetForegroundColour(Colour::white);
    RConsole::GetRootConsole()->PrintString(22, 52, "Choose target for " +
                                            Model()->GetBattleModel()->GetTargetInfo().Spell->GetName());


    auto const& target = Model()->GetBattleModel()->GetTargetInfo().Target;

    if(Model()->GetBattleModel()->CharacterIsEnemy(target))
      _descDrawer->DrawSummary(target);
    else
      _statDrawer->DrawStats(target);
  }

  std::shared_ptr<CharDescriptionDrawer> _descDrawer;
  std::shared_ptr<StatScreenDrawer> _statDrawer;
};

std::shared_ptr<TargetSelectView> TargetSelectView::Create()
{
  return std::make_shared<TargetSelectViewImpl>();
}
}
