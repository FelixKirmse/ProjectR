function GetTargetType()
    return Enemies
end

function GetName()
  return "Waterfall X86"
end

function GetDescription()
    return "Out of nowhere, a fucking waterfall.\nDeals physical WAT damage, wait what?"
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .48
end

function GetDelay()
  return .4
end

function SpellEffect()
  local damage = (5.5 * aAD * (aWAT/100) - 2.75 * dDEF) * (100/dWAT)
  d:TakeDamage(damage)
end
