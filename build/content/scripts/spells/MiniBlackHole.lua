function GetTargetType()
    return Enemies
end

function GetName()
  return "Mini Black Hole"
end

function GetDescription()
  return "Summon a mini black hole behind your enemies.\nReduces SPD.\nDeals composite WND damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .6
end

function GetDelay()
  return .25
end

function SpellEffect()
  local damage = ((2.25 * aAD + 2.25 * aMD) * (aWND/100) - (.75 * dDEF + .75 * dMR)) * (100/dWND)
  d:TakeDamage(damage)
  ds:BuffStat(SPD, -.4)
end
