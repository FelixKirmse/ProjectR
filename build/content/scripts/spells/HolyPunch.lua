function GetTargetType()
    return Single
end

function GetName()
return "Holy Punch"
end

function GetDescription()
  return "Punch the enemy with a holy-infused fist. Deals physical damage."
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
  local damage = 4.5 * aAD * (aHOL/100) - 1.5 * dDEF
  d:TakeDamage(damage)
end
