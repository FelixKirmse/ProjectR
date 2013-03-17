function GetTargetType()
  return Single
end

function GetName()
  return "Quick Dive"
end

function GetDescription()
  return "Quickly dive at the target.\nLow delay.\nDeals physical damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .24
end

function GetDelay()
  return .68
end

function SpellEffect()
  local damage = 4 * aAD - dDEF
  d:TakeDamage(damage)
end
