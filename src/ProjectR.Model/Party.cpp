#include "Party.hpp"
#include <boost/unordered_map.hpp>
#include "Character.hpp"
#include "ErrorCodes.hpp"
#include "IModel.hpp"
#include "CharacterFactory.hpp"
#include <utility>
#include <algorithm>

namespace ProjectR
{
struct PartyImpl : public Party
{
  PartyImpl(IModel const* model)
    : _model(model)
  {
  }

  std::vector<std::shared_ptr<Character> > const& GetFrontRow()
  {
    return _frontRow;
  }

  std::vector<std::shared_ptr<Character> > const& GetBackSeat()
  {
    return _backSeat;
  }

  std::vector<std::shared_ptr<Character> > const& GetReserve()
  {
    return _reserve;
  }

  void RemoveCharacter(std::shared_ptr<Character> const& chara)
  {
    auto it = _charMap.find(chara);
    if(it == _charMap.end())
      return;

    std::vector<std::shared_ptr<Character> >& charVec = *_charMap[chara];
    auto vecIt = std::find(charVec.begin(), charVec.end(), chara);
    charVec.erase(vecIt);
    _charMap.erase(it);
  }

  void Reset()
  {
    _experience = 0LL;
    _frontRow.clear();
    _backSeat.clear();
    _reserve.clear();
    _charMap.clear();
  }

  void AddExperience(long long amount)
  {
    _experience += amount;
    for(std::shared_ptr<Character> const& chara : _frontRow)
      chara->LvlUp(_experience);
    for(std::shared_ptr<Character> const& chara : _backSeat)
      chara->LvlUp(_experience);
    for(std::shared_ptr<Character> const& chara : _reserve)
      chara->LvlUp(_experience);
  }

  int GetAveragePartyLvl()
  {
    if(_cached)
      return _averagePartyLvl;

    int charCount = _frontRow.size() + _backSeat.size() + _reserve.size();
    int lvlSum = 0;

    for(std::shared_ptr<Character> const& chara : _frontRow)
      lvlSum += chara->GetLvl();
    for(std::shared_ptr<Character> const& chara : _backSeat)
      lvlSum += chara->GetLvl();
    for(std::shared_ptr<Character> const& chara : _reserve)
      lvlSum += chara->GetLvl();

    _cached = true;
    if(charCount == 0)
      return 0;

    _averagePartyLvl = lvlSum / charCount;
    return _averagePartyLvl;
  }

  long long GetExperience()
  {
    return _experience;
  }

  void ResetCache()
  {
    _cached = false;
  }

  void AddCharacter(std::shared_ptr<Character> const& chara, int position)
  {
    auto& posVec = position == FrontRow ? _frontRow :
                                          position == BackSeat ? _backSeat : _reserve;
    int limit = position == FrontRow ? FrontRowLimit :
                                       position == BackSeat ? BackSeatLimit : -1;
    if(posVec.size() == (size_t)limit)
      Exit(position == FrontRow ? ERROR_CHAR_LIMIT_REACHED_FRONTROW :
                                  position == BackSeat ? ERROR_CHAR_LIMIT_REACHED_BACKSEAT :
                                                         ERROR_CHAR_LIMIT_REACHED_RESERVE,
           "Attempted to add Character to party despite being full.");

    posVec.push_back(chara);
    _charMap[chara] = &posVec;
  }

  void SwitchCharacters(std::shared_ptr<Character> const& char1,
                        std::shared_ptr<Character> const& char2)
  {
    if(char1 == nullptr)
    {
      //We are replacing a dead frontrow member!
      auto endIter = _backSeat.end();
      auto pos = std::find(_backSeat.begin(), endIter, char2);
      assert(pos != endIter);
      _backSeat.erase(pos);
      _frontRow.push_back(char2);
      _charMap[char2] = &_frontRow;
      return;
    }

    auto& originVec = *_charMap[char1];
    auto& targetVec = *_charMap[char2];
    _charMap[char1] = &targetVec;
    _charMap[char2] = &originVec;

    int originPos = 0;
    for(;&(*char1) != &(*originVec[originPos]); ++originPos); // Intentionally Empty

    int targetPos = 0;
    for(;&(*char2) != &(*targetVec[targetPos]); ++targetPos); // Intentionally Empty

    std::swap(originVec[originPos], targetVec[targetPos]);
  }

  std::vector<std::shared_ptr<Character> > _frontRow;
  std::vector<std::shared_ptr<Character> > _backSeat;
  std::vector<std::shared_ptr<Character> > _reserve;

  boost::unordered::unordered_map<std::shared_ptr<Character>, std::vector<std::shared_ptr<Character>>*> _charMap;

  long long _experience = 0LL;
  bool _cached = false;
  int _averagePartyLvl = 0;
  int const FrontRowLimit = 4;
  int const BackSeatLimit = 8;
  IModel const* _model;
};

std::shared_ptr<Party> Party::Create(IModel const* model)
{
  return std::make_shared<PartyImpl>(model);
}
}
