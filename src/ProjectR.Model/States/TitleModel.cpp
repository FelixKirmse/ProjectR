#include "TitleModel.hpp"
#include "libtcod/libtcod.hpp"

namespace ProjectR
{
TitleModel::TitleModel()
  : _image(new TCODImage("content/images/logo.png"))
{
}

std::shared_ptr<TCODImage> const& TitleModel::GetTitleScreen()
{
  return _image;
}
}
