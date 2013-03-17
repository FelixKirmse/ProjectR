function GetTargetType()
  return Enemies
end

function GetName()
  return "Wind God Tornado"
end

function GetDescription()
  return "Summon a powerful tornado to wreak havoc among your enemies.\nDeals WND damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return 1.48
end

function GetDelay()
  return .2
end

function SpellEffect()
  local damage = (6 * aMD * (aWND/100) - 1.5 * dMR) * (100/dWND)
  d:TakeDamage(damage)
end
