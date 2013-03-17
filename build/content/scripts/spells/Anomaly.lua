function GetTargetType()
    return Enemies
end

function GetName()
  return "Anomaly"
end

function GetDescription()
  return "Deals magic damage to all enemies."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .64
end

function GetDelay()
  return .3
end

function SpellEffect()
  local damage = 3.0625 * aMD - .875 * dMR
  d:TakeDamage(damage)
end
