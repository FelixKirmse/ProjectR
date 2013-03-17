function GetTargetType()
    return Single
end

function GetName()
    return "Magic Missile"
end

function GetDescription()
    return "An arcane missile. Not really good for much, but cheap."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .16
end

function GetDelay()
  return .5
end

function SpellEffect()
  local damage = (3.6 * aMD * (aARC/100) - dMR) * (100/dARC)
  d:TakeDamage(damage)
end
