function GetTargetType()
    return Single
end

function GetName()
    return "Holy Orb"
end

function GetDescription()
    return "An orb of pure holy power encased in a physical shell.\nCheap, but not very powerful."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .2
end

function GetDelay()
  return .45
end

function SpellEffect()
  local damage = (2.625 * aAD + 2.625 * aMD * (aHOL/100) -
                 (0.875 * dDEF + 0.875 * dMR)) * (100/dHOL)
  d:TakeDamage(damage)
end
