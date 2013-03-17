function GetTargetType()
    return Single
end

function GetName()
  return "Alpha Slash"
end

function GetDescription()
    return "A strong physical sword slash."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .4
end

function GetDelay()
  return .4
end

function SpellEffect()
  local damage = 6 * aAD - dDEF
  d:TakeDamage(damage)
end
