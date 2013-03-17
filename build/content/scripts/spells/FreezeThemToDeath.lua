function GetTargetType()
    return Enemies
end

function GetName()
  return "Freeze Them To Death!"
end

function GetDescription()
    return "Absorb all heat from your enemies bodies.\nChance to instantly kill targets.\nDeals physical ICE damage."
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
  local damage = (4.375 * aAD * (aICE/100) - .875 * dDEF) * (100/dICE)
  d:ApplyDebuff(DTH, 40)
  d:TakeDamage(damage)
end
