function GetTargetType()
  return Enemies
end

function GetName()
  return "Balance Strike"
end

function GetDescription()
  return "A strike that combines HOL and DRK, magic and physical,\nin order to achieve true balance."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .92
end

function GetDelay()
  return .4
end

function SpellEffect()
  local damage = ((3 * aAD + 3 * aMD) * ((aDRK + aHOL)/200) - (.75 * dDEF + .75 * dMR)) * (200/(dDRK + dHOL))
  d:TakeDamage(damage)
end
