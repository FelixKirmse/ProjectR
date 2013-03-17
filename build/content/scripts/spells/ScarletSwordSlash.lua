function GetTargetType()
    return Single
end

function GetName()
  return "Scarlet Sword Slash"
end

function GetDescription()
  return "Slash your scarlet sword at the enemy.\nUseful on high DEF enemies.\nDeals physical damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .52
end

function GetDelay()
  return .4
end

function SpellEffect()
  local damage = 3.5 * aAD - .4375 * dDEF
  d:TakeDamage(damage)
end
