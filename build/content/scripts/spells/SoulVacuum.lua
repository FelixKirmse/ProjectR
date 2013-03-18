function GetTargetType()
    return Enemies
end

function GetName()
  return "Soul Vacuum"
end

function GetDescription()
  return "Suck in the souls of your enemies.\nChance to instantly kill targets.\nDeals DRK damage and heals you for 1/4th the damage done."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .96
end

function GetDelay()
  return .1
end

function SpellEffect()
  d:ApplyDebuff(DTH, 66)

  local damage = (4 * aMD * (aDRK/100) - dMR) * (100/dDRK)
  d:TakeDamage(damage)
  a:Heal(damage / 4)
end
