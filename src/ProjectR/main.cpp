#include <iostream>
#include "ProjectR.hpp"

int main(int argc, char** argv)
{
  auto _game(ProjectR::ProjectR::Create());
  _game->SetupGameStructure();
  _game->RunGame();

  return 0;
}
