function GetTargetType()
    return Single
end

function GetName()
  return "Melting Thunder"
end

function GetDescription()
    return "Lightning strikes your target.\nThe heat melts most of their armor.\nDeals WND damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .25
end

function GetDelay()
  return .45
end

function SpellEffect()
  local damage = (4 * aMD * (aWND/100) - dMR) * (100/dWND)
  d:TakeDamage(damage)
end
