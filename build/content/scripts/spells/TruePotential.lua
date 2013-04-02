function GetTargetType()
  return Myself
end

function GetName()
  return "True Potential"
end

function GetDescription()
  return "Unlocks your full potential and increase all your stats."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .88
end

function GetDelay()
  return 0
end

function SpellEffect()
  for i = HP, SIL do
    a:BuffStat(i, .75)
  end
end
