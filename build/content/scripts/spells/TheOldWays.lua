function GetTargetType()
  return Enemies
end

function GetName()
  return "The Old Ways"
end

function GetDescription()
  return "A physical attack dealing physical damage to all enemies.\nGood old times."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .52
end

function GetDelay()
  return .4
end

function SpellEffect()
  local damage = 3.4225 * aAD - .925 * dDEF
  d:TakeDamage(damage)
end
