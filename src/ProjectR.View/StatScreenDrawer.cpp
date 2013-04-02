#include "StatScreenDrawer.hpp"
#include "Character.hpp"
#include "NumberSanitizer.hpp"
#include "Stats.hpp"

namespace ProjectR
{
struct StatScreenDrawerImpl : public StatScreenDrawer
{
  StatScreenDrawerImpl()
    : StatScreenDrawer(37, 39),
      StatRectangle(7, 9, 17, 9),
      StatStrengthRect(29, 9, 4, 9),
      MasteryRect(7, 22, 4, 9),
      MasteryStrengthRect(13, 22, 4, 9),
      ResiRect(26, 22, 2, 4),
      ResiStrengthRect(29, 22, 4, 4),
      StatFormat("%s / %s\n"
                 "%s / %i\n"
                 "%s\n"
                 "%s\n"
                 "%s\n"
                 "%s\n"
                 "%s\n"
                 "%s\n"
                 "%s"),
      StatStrengthFormat("%%c%i%%%%%%c\n"
                         "%%c%i%%%%%%c\n"
                         "%%c%i%%%%%%c\n"
                         "%%c%i%%%%%%c\n"
                         "%%c%i%%%%%%c\n"
                         "%%c%i%%%%%%c\n"
                         "%%c%i%%%%%%c\n"
                         "%%c%i%%%%%%c\n"
                         "%%c%i%%%%%%c"),
      MasteryFormat("%i\n"
                    "%i\n"
                    "%i\n"
                    "%i\n"
                    "%i\n"
                    "%i\n"
                    "%i\n"
                    "%i\n"
                    "%i"),
      MasteryStrengthFormat("%%c%i%%%%%%c\n"
                            "%%c%i%%%%%%c\n"
                            "%%c%i%%%%%%c\n"
                            "%%c%i%%%%%%c\n"
                            "%%c%i%%%%%%c\n"
                            "%%c%i%%%%%%c\n"
                            "%%c%i%%%%%%c\n"
                            "%%c%i%%%%%%c\n"
                            "%%c%i%%%%%%c"),
      ResiFormat("%i\n"
                 "%i\n"
                 "%i\n"
                 "%i"),
      ResiStrengthFormat("%%c%i%%%%%%c\n"
                         "%%c%i%%%%%%c\n"
                         "%%c%i%%%%%%c\n"
                         "%%c%i%%%%%%c")
  {
  }

  void SetupStatics()
  {
    DrawBorder();
    PrintString(1, 1, "Name:");
    PrintString(1, 4, "Race:");
    PrintString(1, 7, "Stats:");
    PrintString(27, 7, "Strength:");
    PrintString(Rectangle(2, 9, 4, 9), "HP :\nMP :\nAD :\nMD :\nDEF:MR :\nEVA:SPD:CHA:");
    PrintString(1, 20, "Masteries:");
    PrintString(20, 20, "Resistances:");
    PrintString(20, 28, "Type of EVA:");
    PrintString(Rectangle(2, 22, 4, 9), "FIR:WAT:ICE:ARC:WND:HOL:DRK:GRN:LGT:");
    PrintString(Rectangle(21, 22, 4, 4), "PSN:PAR:DTH:SIL:");
    PrintString(1, 34, "Currently inflicted by:");    
  }

  void DrawStats(std::shared_ptr<Character> const& chara,
                 RConsole* targetConsole = nullptr)
  {
    RConsole* target = targetConsole == nullptr ? GetRootConsole() : targetConsole;
    SetColourControl(TCOD_COLCTRL_1, Colour::red);
    SetColourControl(TCOD_COLCTRL_2, Colour::green);

    Clear();
    SetupStatics();
    PrintString(35, 1, "Level: " + std::to_string(chara->GetLvl()), TCOD_RIGHT);
    PrintString(23, 30, chara->GetStats()->GetEVAType() == Dodge ? "Dodge" : "Block");

    PrintString(4, 2, chara->GetName());
    PrintString(4, 5, chara->GetRace());
    auto const& stats = chara->GetStats();

    boost::format statFormat(StatFormat);
    statFormat % NumberSanitizer::Sanitize(chara->GetCurrentHP());
    statFormat % NumberSanitizer::Sanitize(stats->GetTotalStat(HP));
    statFormat % chara->GetCurrentMP();
    statFormat % 200;

    boost::format statStrengthFormat(StatStrengthFormat);
    float hpPercentage = chara->GetCurrentHP() / stats->GetTotalStat(HP);
    float mpPercentage = chara->GetCurrentMP() / 200.f;

    SetColourControl(TCOD_COLCTRL_3, Colour(120.f * hpPercentage, 1.f, 1.f));
    SetColourControl(TCOD_COLCTRL_4, Colour(205.f * mpPercentage, 1.f, 1.f));
    statStrengthFormat
        % (int)(hpPercentage * 100)
        % (int)(mpPercentage * 100);

    for(int i = AD; i <= CHA; ++i)
    {
      statFormat % NumberSanitizer::Sanitize(stats->GetTotalStat(i));
      statStrengthFormat % int(stats->GetSingleStat(i).Get(BattleMod) * 100);
    }

    PrintString(StatRectangle, statFormat.str());
    PrintString(StatStrengthRect, statStrengthFormat.str(),
                TCOD_COLCTRL_3, TCOD_COLCTRL_STOP,
                TCOD_COLCTRL_4, TCOD_COLCTRL_STOP,
                GetColor(stats, AD), TCOD_COLCTRL_STOP,
                GetColor(stats, MD), TCOD_COLCTRL_STOP,
                GetColor(stats, DEF), TCOD_COLCTRL_STOP,
                GetColor(stats, MR), TCOD_COLCTRL_STOP,
                GetColor(stats, EVA), TCOD_COLCTRL_STOP,
                GetColor(stats, SPD), TCOD_COLCTRL_STOP,
                GetColor(stats, CHA), TCOD_COLCTRL_STOP);

    boost::format masteryFormat(MasteryFormat);
    boost::format masteryStrengthFormat(MasteryStrengthFormat);

    for(int i = FIR; i <= LGT; ++i)
    {
      masteryFormat % (int)stats->GetTotalStat(i);
      masteryStrengthFormat % (int)(stats->GetSingleStat(i).Get(BattleMod) * 100);
    }

    PrintString(MasteryRect, masteryFormat.str());
    PrintString(MasteryStrengthRect, masteryStrengthFormat.str(),
                GetColor(stats, FIR), TCOD_COLCTRL_STOP,
                GetColor(stats, WAT), TCOD_COLCTRL_STOP,
                GetColor(stats, ICE), TCOD_COLCTRL_STOP,
                GetColor(stats, ARC), TCOD_COLCTRL_STOP,
                GetColor(stats, WND), TCOD_COLCTRL_STOP,
                GetColor(stats, HOL), TCOD_COLCTRL_STOP,
                GetColor(stats, DRK), TCOD_COLCTRL_STOP,
                GetColor(stats, GRN), TCOD_COLCTRL_STOP,
                GetColor(stats, LGT), TCOD_COLCTRL_STOP);

    boost::format resiFormat(ResiFormat);
    boost::format resiStrengthFormat(ResiStrengthFormat);

    for(int i = PSN; i <= SIL; ++i)
    {
      if(i == SLW || i == STD)
        continue;
      resiFormat % (int)stats->GetTotalStat(i);
      resiStrengthFormat % (int)(stats->GetSingleStat(i).Get(BattleMod) * 100);
    }

    PrintString(ResiRect, resiFormat.str());
    PrintString(ResiStrengthRect, resiStrengthFormat.str(),
                GetColor(stats, PSN), TCOD_COLCTRL_STOP,
                GetColor(stats, PAR), TCOD_COLCTRL_STOP,
                GetColor(stats, DTH), TCOD_COLCTRL_STOP,
                GetColor(stats, SIL), TCOD_COLCTRL_STOP);

    target->Blit(*this, GetBounds(), _position.X, _position.Y);
  }

  void SetPosition(int x, int y)
  {
    _position.X = x;
    _position.Y = y;
  }

  TCOD_colctrl_t GetColor(std::shared_ptr<Stats> const& stats, int stat)
  {
    int value = stats->GetSingleStat(stat).Get(BattleMod) * 100;
    return value == 100 ? TCOD_COLCTRL_STOP :
                          value > 100 ? TCOD_COLCTRL_2 :
                                        TCOD_COLCTRL_1;
  }

  Point _position;
  Rectangle const StatRectangle;
  Rectangle const StatStrengthRect;
  Rectangle const MasteryRect;
  Rectangle const MasteryStrengthRect;
  Rectangle const ResiRect;
  Rectangle const ResiStrengthRect;
  std::string const StatFormat;
  std::string const StatStrengthFormat;
  std::string const MasteryFormat;
  std::string const MasteryStrengthFormat;
  std::string const ResiFormat;
  std::string const ResiStrengthFormat;
};

std::shared_ptr<StatScreenDrawer> StatScreenDrawer::Create()
{
  return std::make_shared<StatScreenDrawerImpl>();
}
}
