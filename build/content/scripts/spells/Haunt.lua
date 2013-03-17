function GetTargetType()
    return Single
end

function GetName()
  return "Haunt"
end

function GetDescription()
  return "Haunt the enemy, dealing damage and healing you.\nChance to instantly kill target.\nDeals DRK damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .64
end

function GetDelay()
  return .38
end

function SpellEffect()
  d:ApplyDebuff(DTH, 75)
  local damage = (3.0625 * aMD * (aDRK/100) - .875 * dMR) * (100/dDRK)
  d:TakeDamage(damage)
  a:Heal(damage)
end
