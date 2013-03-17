function GetTargetType()
    return Enemies
end

function GetName()
return "Mind Storm"
end

function GetDescription()
return "An arcane storm spreads chaos among your enemies.\nUseful against low MR enemies.\nDeals ARC damage."
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
  local damage = (4.725 * aMD * (aARC/100) - 1.75 * dMR) * (100/dARC)
  d:TakeDamage(damage)
end
