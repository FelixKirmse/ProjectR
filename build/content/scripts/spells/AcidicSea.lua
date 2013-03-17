function GetTargetType()
    return Enemies
end

function GetName()
return "Acidic Sea"
end

function GetDescription()
return "A sea of acid surrounds the enemy.\nLowers enemies AD.\nDeals WAT damage."
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
  local damage = 3.75 * aMD - .75 * dMR
  d:TakeDamage(damage)
end
