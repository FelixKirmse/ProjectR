function GetTargetType()
    return Enemies
end

function GetName()
return "8 Headed Radiant Hydra"
end

function GetDescription()
    return "Summon a hydra to cause chaos among your enemies.\nUseful against high MR enemies.\nDeals HOL damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .6
end

function GetDelay()
  return .4
end

function SpellEffect()
  local damage = (3.75 * aMD * (aHOL/100) - .75 * dMR) * (100/dHOL)
  d:TakeDamage(damage)
end
