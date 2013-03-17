function GetTargetType()
    return Enemies
end

function GetName()
  return "Thousand Needles"
end

function GetDescription()
    return "Wears down the enemies defense."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .6
end

function GetDelay()
  return .3
end

function SpellEffect()
  local damage = 4 * aMD - dDEF
  d:TakeDamage(damage)
  ds:BuffStat(DEF, -.25)
end
