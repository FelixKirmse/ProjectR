function GetTargetType()
    return Enemies
end

function GetName()
return "Blizzard of the Tundra Wasteland"
end

function GetDescription()
    return "Summon a powerful blizzard which slows every enemy."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .52
end

function GetDelay()
  return .25
end

function SpellEffect()
  local damage = (((2.7 * aAD + 2.7 * aMD) * (aICE/100)) - (.675 * dDEF + .675 * dMR)) * (100/dICE)

  d:TakeDamage(damage)
  d:BuffStat(SPD, -.3)
end
