function GetTargetType()
    return Decaying
end

function GetName()
return "Balance Is Key"
end

function GetDescription()
    return "A composite attack using both AD & MD.\nLow recovery.\nDamage depends on proximity to target."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .48
end

function GetDelay()
  return .7
end

function SpellEffect()
  local damage = (3.5 * aAD + 3.5 * aMD) - (dDEF + dMR) / modifier
  d:TakeDamage(damage)
end
