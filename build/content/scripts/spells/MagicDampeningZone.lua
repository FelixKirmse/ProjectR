function GetTargetType()
    return Enemies
end

function GetName()
return "Magic-Dampening Zone"
end

function GetDescription()
return "Summon a magic-dampening zone.\nReduces enemies MD.\nDeals ARC damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .6
end

function GetDelay()
  return .3
end

function SpellEffect()
  local damage = (3.0625 * aMD * (aARC/100) - .875 * dMR) * (100/dARC)
  d:TakeDamage(damage)
  ds:BuffStat(MD, -.18)
end
