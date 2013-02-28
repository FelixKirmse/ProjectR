#pragma once
#include <boost/random.hpp>
#include <boost/unordered_map.hpp>
#include <ctime>

namespace ProjectR
{
template<typename T>
class RandomContainer
{
private:
  typedef boost::random::uniform_int_distribution<> IntGenerator;
  typedef boost::random::mt19937 Random;
  typedef boost::unordered::unordered_map<T, int> ObjectMap;

  static Random _rng;
  ObjectMap _objects;
  int _weightSum;

public:
  RandomContainer(std::initializer_list<typename std::map<T, int>::value_type> list)
    : _objects(), _weightSum(0)
  {
    _objects.insert(begin(list), end(list));
    for(auto item : list)
    {
      _weightSum += item.second;
    }
  }

  RandomContainer()
    : _objects(), _weightSum(0)
  {
  }

  void Add(T obj, int weight)
  {
    _objects[obj] = weight;
    _weightSum += weight;
  }

  int GetWeight(T obj)
  {
    return _objects[obj];
  }

  T Get()
  {
    int sumExtra = 0;
    IntGenerator gen(0, _weightSum - 1);
    int rand = gen(_rng);
    for(auto obj : _objects)
    {
      if(rand < obj.second + sumExtra)
        return obj.first;
      sumExtra += obj.second;
    }
    return T();
  }
};

template<class T>
boost::random::mt19937 RandomContainer<T>::_rng(time(0));
}
