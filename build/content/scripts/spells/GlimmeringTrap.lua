function GetTargetType()
    return Single
end

function GetName()
  return "Glimmering Trap"
end

function GetDescription()
  return "Trap your target with arcane energy.\nChance to inflict PAR.\nDeals physical ARC damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .3
end

function GetDelay()
  return .45
end

function SpellEffect()
  local damage = (5 * aAD * (aARC/100) - 1.25 * dDEF) * (100/dARC)
  d:ApplyDebuff(PAR, 80)
  d:TakeDamage(damage)
end
