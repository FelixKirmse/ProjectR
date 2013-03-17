function GetTargetType()
    return Enemies
end

function GetName()
  return "Fire Wheel"
end

function GetDescription()
  return "Spin around shrouded in fire and attack your enemies.\nDeals composite FIR damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .84
end

function GetDelay()
  return .35
end

function SpellEffect()
  local damage = ((4 * aAD + 4 * aMD) * (aFIR/100) - (dDEF + dMR)) * (100/dFIR)
  d:TakeDamage(damage)
end
