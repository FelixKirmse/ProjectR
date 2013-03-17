function GetTargetType()
    return Enemies
end

function GetName()
return "Secret Technique #64"
end

function GetDescription()
return "Strike out at all enemies using shadow energy.\nUseful against low DEF enemies.\nDeals physical DRK damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .64
end

function GetDelay()
  return .1
end

function SpellEffect()
  local damage = (5.25 * aAD * (aDRK/100) - 1.75 * dDEF) * (100/dDRK)
  d:TakeDamage(damage)
end
