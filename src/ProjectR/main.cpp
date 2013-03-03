#include <iostream>
#include "ProjectR.hpp"

int main(int argc, char** argv)
{
  ProjectR::ProjectR* _game(ProjectR::ProjectR::Create());
  _game->SetupGameStructure();
  _game->RunGame();
  delete _game;

  return 0;
}
