function GetTargetType()
    return Single
end

function GetName()
  return "Vengeful Spirit"
end

function GetDescription()
  return "Send out a spirit to attack your target.\nLowers DEF and can inflict PNS.\nDeals composite HOL damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .6
end

function GetDelay()
  return .32
end

function SpellEffect()
  local damage = ((2.625 * aAD + 2.625 * aMD) * (aHOL/100) - (.875 * dDEF + .875 * dMR)) * (100/dHOL)
  d:TakeDamage(damage)
  ds:BuffStat(DEF, -.5)
  d:ApplyDebuff(PSN, 35, a:GetLvl())
end
