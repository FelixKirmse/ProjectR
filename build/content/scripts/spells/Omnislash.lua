function GetTargetType()
    return Enemies
end

function GetName()
  return "Omnislash"
end

function GetDescription()
    return "Using dark engery, strike out at all enemies.\nIgnores a good chunk of DEF\nDeals physical DRK damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .88
end

function GetDelay()
  return .5
end

function SpellEffect()
  local damage = (6 * aAD * (aDRK/100) - .5 * dDEF) * (100/dDRK)
  d:TakeDamage(damage)
end
