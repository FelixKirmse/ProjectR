function GetTargetType()
    return Single
end

function GetName()
return "Flying Phoenix"
end

function GetDescription()
return "Become a phoenix to strike the enemy.\nDeals FIR damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .6
end

function GetDelay()
  return .4
end

function SpellEffect()
  local damage = (4 * aMD * (aFIR/100) - dMR) * (100/dFIR)
  d:TakeDamage(damage)
end
