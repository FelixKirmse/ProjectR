function GetTargetType()
    return Single
end

function GetName()
    return "Kon Slash"
end

function GetDescription()
    return "Strong Physical attack that bypasses some of the enemies armor."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return 0
end

function GetDelay()
  return .5
end

function SpellEffect()
    local damage = 3 * aAD - .8 * dDEF
    d:TakeDamage(damage)
end
