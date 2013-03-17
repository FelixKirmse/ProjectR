function GetTargetType()
    return Single
end

function GetName()
return "Stabby Stab!"
end

function GetDescription()
    return "Stab the target with a knife.\nVery ineffective against targets with high DEF."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .48
end

function GetDelay()
  return .48
end

function SpellEffect()
  local damage = 5.5 * aAD - 2.75 * dDEF
  d:TakeDamage(damage)
end
