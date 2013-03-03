#pragma once
#include "libtcod/libtcod.h"
#include "libtcod/color.hpp"
#include "libtcod/console.hpp"
#include <string>
#include "Rectangle.hpp"

namespace ProjectR
{
typedef TCODColor Colour;

class RConsole
{
public:
  RConsole(int width, int height);
  ~RConsole();

  void SetForegroundColour(Colour const& colour);


  void SetBackgroundColour(Colour const& colour);
  void SetBackgroundColour(Rectangle const& area, Colour const& colour);

  void SetCharacter(int x, int y, char character);
  void SetCharacter(int x, int y, char character,
                    Colour const& foreground,
                    Colour const& background);

  void DrawHorizontalLine(int x, int y, int length);
  void DrawVerticalLine(int x, int y, int length);

  void Blit(RConsole& src, Rectangle const& srcRect, int dstX, int dstY,
            float fgAlpha = 1.0f, float bgAlpha = 1.0f);

  void Clear();

  int GetWidth() const;
  int GetHeight() const;
  Rectangle GetBounds() const;

  template<typename ... T>
  void PrintString(int x, int y, std::string const& string, T ... args)
  {
    _console->print(x, y, string.c_str(), args... );
  }

  template<typename ... T>
  void PrintString(Rectangle const& rect, std::string const& string, T ... args)
  {
    _console->printRect(rect.X, rect.Y, rect.Width, rect.Height, string.c_str(), args... );
  }

  static RConsole* GetRootConsole();
  static void InitializeRootConsole(int width, int height);
  static bool ConsoleWindowClosed();
  static void Draw();

private:
  RConsole(TCODConsole* console);
  TCODConsole* _console;
};
}
