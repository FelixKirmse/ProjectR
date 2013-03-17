function GetTargetType()
    return Single
end

function GetName()
  return "Beastly Smash"
end

function GetDescription()
    return "Smash your target. Simple and easy. Relatively strong."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .30
end

function GetDelay()
  return .18
end

function SpellEffect()
  local damage = 3.5 * aAD - dDEF
  d:TakeDamage(damage)
end
