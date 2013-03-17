function GetTargetType()
    return Single
end

function GetName()
  return "Omega Slash"
end

function GetDescription()
    return "Attempts to execute the target.\nLess effective against enemies with high DEF.\nDeals triple damage to targets below 25% HP."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .88
end

function GetDelay()
  return .1
end

function SpellEffect()
  local bonusDamage = 1

  if d:GetCurrentHP() / dHP < .25 then
    bonusDamage = 3
  end

  local damage = (11.25 * aAD - 1.5 * dDEF) * bonusDamage
  d:TakeDamage(damage)
end
