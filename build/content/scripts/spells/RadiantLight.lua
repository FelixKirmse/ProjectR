function GetTargetType()
    return Decaying
end

function GetName()
    return "Radiant Light"
end

function GetDescription()
    return "A beam of holy engery radiates from the sky onto the target.\nDeals damage depending on proximity to target.\nHas a chance to paralize."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .4
end

function GetDelay()
  return .38
end

function SpellEffect()
  local damage = ((3 * aAD + 3 * aMD * (aHOL/100) - (dDEF + dMR)) * (100/dHOL)) / modifier
  d:TakeDamage(damage)
  d:ApplyDebuff(PAR, 25)
end
