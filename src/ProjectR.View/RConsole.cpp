#include "RConsole.hpp"
#include "libtcod/libtcod.hpp"

namespace ProjectR
{
RConsole::RConsole(int width, int height)
  : _console(new TCODConsole(width, height))
{
}

RConsole::RConsole(TCODConsole *console)
  : _console(console)
{
}

RConsole::~RConsole()
{
  delete _console;
}

void RConsole::SetForegroundColour(Colour const& colour)
{
  _console->setDefaultForeground(colour);
}

inline void RConsole::SetBackgroundColour(Colour const& colour)
{
  _console->setDefaultBackground(colour);
}

void RConsole::SetBackgroundColour(Rectangle const& area, Colour const& colour)
{
  SetBackgroundColour(colour);
  _console->rect(area.X, area.Y, area.Width, area.Height, true);
}

void RConsole::SetCharacter(int x, int y, char character)
{
  _console->putChar(x, y, character);
}

void RConsole::SetCharacter(int x, int y, char character,Colour const& foreground, Colour const& background)
{
  _console->putCharEx(x, y, character, foreground, background);
}

void RConsole::DrawHorizontalLine(int x, int y, int length)
{
  _console->hline(x, y, length);
}

void RConsole::DrawVerticalLine(int x, int y, int length)
{
  _console->vline(x, y, length);
}

void RConsole::Blit(RConsole& src, Rectangle const& srcRect, int dstX, int dstY, float fgAlpha, float bgAlpha)
{
  TCODConsole::blit(src._console,
                    srcRect.X, srcRect.Y, srcRect.Width, srcRect.Height,
                    _console,
                    dstX, dstY, fgAlpha, bgAlpha);
}

void RConsole::Clear()
{
  _console->clear();
}

int RConsole::GetWidth() const
{
  return _console->getWidth();
}

int RConsole::GetHeight() const
{
  return _console->getHeight();
}

Rectangle RConsole::GetBounds() const
{
  return Rectangle(0, 0, GetWidth(), GetHeight());
}

RConsole* RConsole::GetRootConsole()
{
  static RConsole rootConsole(TCODConsole::root);
  return &rootConsole;
}

void RConsole::InitializeRootConsole(int width, int height)
{
  TCODConsole::initRoot(width, height, "ProjectR", false, TCOD_RENDERER_GLSL);
}

bool RConsole::ConsoleWindowClosed()
{
  return TCODConsole::isWindowClosed();
}

void RConsole::Draw()
{
  TCODConsole::flush();
}
}
