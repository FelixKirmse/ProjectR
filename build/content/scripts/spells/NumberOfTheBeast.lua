function GetTargetType()
  return Enemies
end

function GetName()
  return "Number of the Beast"
end

function GetDescription()
  return "A strong attack dealing high unresistable physical damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return 1.2
end

function GetDelay()
  return .15
end

function SpellEffect()
  local damage = 6.66 * aAD
  d:TakeDamage(damage)
end
