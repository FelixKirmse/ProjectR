function GetTargetType()
  return Decaying
end

function GetName()
  return "Wind Slash"
end

function GetDescription()
  return "Disturb the wind around your target.\nEnemies in proximity take reduced damage.\nDeals WND damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return 1.44
end

function GetDelay()
  return .3
end

function SpellEffect()
  local damage = (4.5 * aMD * (aWND/100) - .75 * dMR) * (100/dWND) / modifier
  d:TakeDamage(damage)
end
