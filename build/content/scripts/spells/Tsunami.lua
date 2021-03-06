function GetTargetType()
    return Enemies
end

function GetName()
  return "Tsunami"
end

function GetDescription()
  return "Summon a powerful Tsunami.\nReduces enemies MR.\nDeals WAT damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .65
end

function GetDelay()
  return .28
end

function SpellEffect()
  local damage = (4.5 * aMD * (aWAT/100) - 1.125 * dMR) * (100/dWAT)
  d:BuffStat(MR, -.25)
  d:TakeDamage(damage)
end
