function GetTargetType()
    return Single
end

function GetName()
  return "Wind Strike"
end

function GetDescription()
    return "Strike with the power of the wind.\nDeals physical WND damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .32
end

function GetDelay()
  return .65
end

function SpellEffect()
  local damage = (3.3 * aAD * (aWND/100) - dDEF) * (100/dWND)
  d:TakeDamage(damage)
end
