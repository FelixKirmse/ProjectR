#pragma once
#include <string>
#include "boost/format.hpp"

namespace ProjectR
{
class NumberSanitizer
{
public:
  static std::string Sanitize(double number, std::string const& format = std::string("%.2f"))
  {
    if(number <= 0)
      return "0";

    int const k = 10000;
    int const M = 1000000;
    int const G = 1000000000;

    std::string chosenFormat = number < k ? "%d" : format;

    boost::format resultFormat(chosenFormat + "%s");
    std::string damageLetter = number > G ? "G" :
                                            number > M ? "M":
                                                         number > k ?
                                                           "k" : "";
    double reducedNumber = number > G ? number / G :
                                        number > M ? number / M :
                                                     number > k ? number / 1000 :
                                                                  (int)reducedNumber;
    if(reducedNumber <= 0)
      return "0";

    resultFormat
        % reducedNumber
        % damageLetter;
    return resultFormat.str();
  }
};
}
