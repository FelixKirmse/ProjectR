function GetTargetType()
    return Single
end

function GetName()
  return "Embrace of the Wind God"
end

function GetDescription()
    return "Strike your target with an empowered Wind Strike.\nIncreases your SPD.\nDeals physical WND damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .7
end

function GetDelay()
  return .7
end

function SpellEffect()
  local damage = (3.75 * aAD * (aWND/100) - 1.25 * dDEF) * (100/dWND)
  d:TakeDamage(damage)
  as:BuffStat(SPD, .3)
end
