function GetTargetType()
    return Decaying
end

function GetName()
return "Expect the Unexpected"
end

function GetDescription()
  return "Unleash a flurry of attacks on one target.\nTargets in proximity take collateral damage.\nLargely ignores DEF."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .24
end

function GetDelay()
  return .66
end

function SpellEffect()
  local damage = (3.3 * aAD - .25 * dDEF) / modifier
  d:TakeDamage(damage)
end
