function GetTargetType()
    return Single
end

function GetName()
  return "Miracle Poke"
end

function GetDescription()
    return "Poke an ally, increasing all their stats."
end

function IsSupportSpell()
    return true
end

function GetMPCost()
    return .48
end

function GetDelay()
  return .25
end

function SpellEffect()
  for i = HP, SIL do
    d:BuffStat(i, .35)
  end
end
