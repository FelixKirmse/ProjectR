function GetTargetType()
    return Single
end

function GetName()
  return "Catwalk"
end

function GetDescription()
  return "Swiftly attack your target.\nVery low delay.\nIgnores a bunch of DEF."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .1
end

function GetDelay()
  return .9
end

function SpellEffect()
  local damage = 1.25 * aAD - .625 * dDEF
  d:TakeDamage(damage)
end
