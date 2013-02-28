#pragma once
#include "IGenerator.hpp"
#include <memory>

namespace ProjectR
{
class RMap;

class Generator : public IGenerator
{
public:
  Generator(int minWidth, int minHeight, int maxWidth, int maxHeight, std::shared_ptr<RMap> map);
  virtual ~Generator(){}

  inline int GetMinWidth() { return _minWidth; }
  inline int GetMinHeight() { return _minHeight; }
  inline int GetMaxWidth() { return _maxWidth; }
  inline int GetMaxHeight() { return _maxHeight; }

  inline void SetMinWidth(int w) { _minWidth = w; }
  inline void SetMinHeight(int h) { _minHeight = h; }
  inline void SetMaxWidth(int w) { _maxWidth = w; }
  inline void SetMaxHeight(int h) { _maxHeight = h; }

  inline int GetWidth() { return _width; }
  inline int GetHeight() { return _height; }

  inline int OffsetX() { return _offsetX; }
  inline int OffsetY() { return _offsetY; }

  bool Generate(int row, int col, Direction dir);
  void GetTopLeftCorner(int& row, int& col, Direction dir);

protected:
  inline std::shared_ptr<RMap> Map() { return _map; }

  void SetWidth(int w);
  void SetHeight(int h);
  virtual void GenerateImpl(int row, int col, Direction dir) = 0;

private:
  bool CheckAvailableSpace(int row, int col, Direction dir);

  int _minWidth;
  int _minHeight;
  int _maxWidth;
  int _maxHeight;
  int _width;
  int _height;
  int _offsetX;
  int _offsetY;

  std::shared_ptr<RMap> _map;
};
}
