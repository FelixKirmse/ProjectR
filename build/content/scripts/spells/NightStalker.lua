function GetTargetType()
    return Enemies
end

function GetName()
  return "Night Stalker"
end

function GetDescription()
  return "Attack all enemies with shadowy power.\nDeals physical DRK damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .88
end

function GetDelay()
  return .3
end

function SpellEffect()
  local damage = (4 * aAD * (aDRK/100) - dDEF) * (100/dDRK)
  d:TakeDamage(damage)
end
