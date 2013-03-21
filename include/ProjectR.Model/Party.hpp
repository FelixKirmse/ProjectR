#pragma once
#include <memory>
#include <vector>

namespace ProjectR
{
class Character;
class IModel;

enum Slot
{
  FrontRow,
  BackSeat,
  Reserve
};

class Party
{
public:
  virtual std::vector<std::shared_ptr<Character> > const& GetFrontRow() = 0;
  virtual std::vector<std::shared_ptr<Character> > const& GetBackSeat() = 0;
  virtual std::vector<std::shared_ptr<Character> > const& GetReserve() = 0;
  virtual void Reset() = 0;
  virtual void AddExperience(long long amount) = 0;
  virtual int GetAveragePartyLvl() = 0;
  virtual long long GetExperience() = 0;
  virtual void ResetCache() = 0;
  virtual void SwitchCharacters(std::shared_ptr<Character> const& char1,
                                std::shared_ptr<Character> const& char2) = 0;
  virtual void AddCharacter(std::shared_ptr<Character> const& chara, int position) = 0;
  virtual void RemoveCharacter(std::shared_ptr<Character> const& chara) = 0;

  static std::shared_ptr<Party> Create(IModel const* model);
  virtual ~Party(){}
};
}
