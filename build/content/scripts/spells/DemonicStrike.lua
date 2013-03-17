function GetTargetType()
    return Single
end

function GetName()
    return "Demonic Strike"
end

function GetDescription()
    return "A medium strong physical attack. It's cheap, but also the only\noffense you have. Get used to it!"
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .24
end

function GetDelay()
  return .5
end

function SpellEffect()
  local damage = 3.2 * aAD - .8 * dDEF
  d:TakeDamage(damage)
end
