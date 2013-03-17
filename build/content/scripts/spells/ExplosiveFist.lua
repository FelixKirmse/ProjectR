function GetTargetType()
    return Decaying
end

function GetName()
  return "Explosive Fist"
end

function GetDescription()
  return "Attack your target with an arcane-enchanted punch.\nEnemies in proximity also take damage.\nDeals composite ARC damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .88
end

function GetDelay()
  return .3
end

function SpellEffect()
  local damage = ((3.75 * aAD + 3.75 * aMD) * (aARC/100) - (1.25 * dDEF + 1.25 * dMR)) * (100/dARC) / modifier
  d:TakeDamage(damage)
end
