function GetTargetType()
    return Enemies
end

function GetName()
return "Extinction"
end

function GetDescription()
    return "Meteors rain down upon your enemies.\nDeals FIR damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .52
end

function GetDelay()
  return .15
end

function SpellEffect()
  local damage = (5.0625 * aMD * (aFIR/100) - 1.125 * dMR) * (100/dFIR)
  d:TakeDamage(damage)
end
