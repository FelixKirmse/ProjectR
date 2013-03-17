function GetTargetType()
    return Myself
end

function GetName()
return "The Alchemists Secret Elixir"
end

function GetDescription()
return "Chug down an elixir of great power.\nIncreases all your stats.\nLow delay."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .72
end

function GetDelay()
  return .84
end

function SpellEffect()
  for i = HP, SIL do
    as:BuffStat(i, .4)
  end
end
