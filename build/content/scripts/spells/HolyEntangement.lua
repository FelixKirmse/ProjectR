function GetTargetType()
    return Enemies
end

function GetName()
  return "Holy Entanglement"
end

function GetDescription()
    return "Prevent your enemies from evading.\nReduces enemies EVA.\nDeals HOL damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .46
end

function GetDelay()
  return .35
end

function SpellEffect()
  local damage = (3.24 * aMD * (aHOL/100) - .9 * dMR) * (100/dHOL)
  d:TakeDamage(damage)
  ds:BuffStat(EVA, -.5)
end
