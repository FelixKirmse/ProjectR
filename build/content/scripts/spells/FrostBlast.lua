function GetTargetType()
  return Single
end

function GetName()
  return "Frost Blast"
end

function GetDescription()
  return "A chilling blast of frost.\nDeals ICE damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .88
end

function GetDelay()
  return .25
end

function SpellEffect()
  local damage = (6.25 * aMD * (aICE/100) - 1.25 * dMR) * (100/dICE)
  d:TakeDamage(damage)
end
