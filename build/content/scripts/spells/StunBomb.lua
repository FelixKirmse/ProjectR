function GetTargetType()
    return Single
end

function GetName()
  return "Stun Bomb"
end

function GetDescription()
    return "Throw a bomb at the target.\nSlightly reduces target's AD.\nDeals physical FIR damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .36
end

function GetDelay()
  return .4
end

function SpellEffect()
  local damage = (5 * aMD * (aFIR/100) - dDEF) * (100/dFIR)
  d:TakeDamage(damage)
  ds:BuffStat(AD, -.18)
end
