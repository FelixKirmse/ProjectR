function GetTargetType()
    return Single
end

function GetName()
return "Stonebreaker"
end

function GetDescription()
  return "A harsh kick that ignores a bunch of DEF."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .2
end

function GetDelay()
  return .5
end

function SpellEffect()
  local damage = 4.5 * aAD - .5 * dDEF
  d:TakeDamage(damage)
end
