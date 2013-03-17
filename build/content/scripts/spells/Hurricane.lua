function GetTargetType()
    return Enemies
end

function GetName()
  return "Surge of Lightning"
end

function GetDescription()
    return "Summon a hurricane to blast away your enemies.\nDeals WND damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .6
end

function GetDelay()
  return .28
end

function SpellEffect()
  local damage = (4.375 * aMD * (aWND/100) - .875 * dMR) * (100/dWND)
  d:TakeDamage(damage)
end
