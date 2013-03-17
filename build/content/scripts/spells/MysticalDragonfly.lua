function GetTargetType()
    return Enemies
end

function GetName()
return "Mystical Dragonfly"
end

function GetDescription()
    return "Summon a Dragonfly to attack your enemies.\nUseful against low MR enemies.\nDeals ARC damage, but doesn't use caster Mastery."
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
  local damage = (5.25 * aMD - 1.75 * dMR) * (100/dARC)
  d:TakeDamage(damage)
end
