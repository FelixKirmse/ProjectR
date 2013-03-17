function GetTargetType()
    return Decaying
end

function GetName()
  return "Seed of Corruption"
end

function GetDescription()
  return "Plant a seed of corruption in the target.\nThe seed explodes and damages nearby enemies.\nDeals DRK damage."
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
  local damage = ((3.75 * aMD * (aDRK/100) - .625 * dMR) * (100/dDRK)) / modifier
  d:TakeDamage(damage)
end
