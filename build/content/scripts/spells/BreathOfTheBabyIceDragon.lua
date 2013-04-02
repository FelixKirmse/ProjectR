function GetTargetType()
    return Single
end

function GetName()
return "Breath of the Baby Ice Dragon"
end

function GetDescription()
    return "A breath attack using both your AD & MD to slow your target."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .2
end

function GetDelay()
  return .5
end

function SpellEffect()
  local damage = (((2.53 * aAD + 2.53 * aMD) * (aICE/100.)) - (.8 * dDEF + .8 * dMR)) * (100/dICE)

  d:TakeDamage(damage)
  d:BuffStat(SPD, -.5)
end
