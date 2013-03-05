#pragma once
#include <memory>

class TCODImage;
namespace ProjectR
{
class TitleModel
{
public:
  TitleModel();
  std::shared_ptr<TCODImage> const& GetTitleScreen();

private:
  std::shared_ptr<TCODImage> _image;
};
}
