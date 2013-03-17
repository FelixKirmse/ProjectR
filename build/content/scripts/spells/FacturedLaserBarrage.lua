function GetTargetType()
    return Enemies
end

function GetName()
return "Fractured Laser Barrage"
end

function GetDescription()
return "Bombard your foes with sharp arcane lasers.\nLowers enemies MR.\nDeals ARC damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .56
end

function GetDelay()
  return .35
end

function SpellEffect()
  local damage = (3.875 * aMD * (aARC/100) - 1.25 * dMR) * (100/dARC)
  d:TakeDamage(damage)
  ds:BuffStat(MR, -.35)
end
