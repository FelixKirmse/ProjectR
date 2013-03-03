#include "TitleScreenView.hpp"
#include <iostream>
#include "ProjectR.Model/RMap.hpp"
#include "IModel.hpp"
#include "RConsole.hpp"

namespace ProjectR
{
struct TitleScreenViewImpl : public TitleScreenView
{
  TitleScreenViewImpl()
    : _masterMachine(),
      _mapConsole(1000, 1000)
  {
  }

  void Activate()
  {
  }

  void Deactivate()
  {
  }

  void Run()
  {
    _mapConsole.Clear();
    auto map = Model()->GetMap();
    Rectangle heatZone = map->HeatZone();
    for(int row = heatZone.Top(); row < heatZone.Bottom(); ++row)
    {
      for(int col = heatZone.Left(); col < heatZone.Right(); ++col)
      {
        auto& cell = map->Get(row, col);
        int cellChar = ' ';
        Colour cellColour(Colour::white);

        if(cell & Wall)
          cellChar = '#';
        if(cell & Floor)
          cellChar = '.';
        if(cell & Door)
          cellChar = 'D';
        if(cell & Uncommon)
          cellColour = Colour::lighterGreen;
        if(cell & Rare)
          cellColour = Colour::azure;
        if(cell & Epic)
          cellColour = Colour::lighterPurple;
        if(cell & Legendary)
          cellColour = Colour::gold;
        if(cell & Artifact)
          cellColour = Colour::lightCrimson;
        if(cell & Small)
          cellChar = 'S';
        if(cell & Normal)
          cellChar = 'N';
        if(cell & Big)
          cellChar = 'B';
        if(cell & Grand)
          cellChar = 'G';

        _mapConsole.SetCharacter(col, row, cellChar, cellColour, Colour::black);
      }
    }

    RConsole* root = RConsole::GetRootConsole();
    root->Blit(_mapConsole, Rectangle(heatZone.X, heatZone.Y, root->GetWidth(), root->GetHeight()), 0, 0);
  }

  void SetStateMachine(std::shared_ptr<IStateMachine> machine)
  {
    _masterMachine = machine;
  }

  std::shared_ptr<IStateMachine> _masterMachine;
  RConsole _mapConsole;
};

TitleScreenView* TitleScreenView::Create()
{
  return new TitleScreenViewImpl();
}
}
