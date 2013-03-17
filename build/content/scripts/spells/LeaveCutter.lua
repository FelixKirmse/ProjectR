function GetTargetType()
    return Single
end

function GetName()
return "Leavecutter"
end

function GetDescription()
    return "Send sharp leaves flying at the enemy.\nVery large MR piercing.\nDeals WND damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .2
end

function GetDelay()
  return .5
end

function SpellEffect()
  local damage = (3.375 * aMD * (aWND/100) - .15 * dMR) * (100/dWND)
  d:TakeDamage(damage)
end
