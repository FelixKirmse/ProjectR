function GetTargetType()
  return Enemies
end

function GetName()
  return "The New Ways"
end

function GetDescription()
  return "A physical attack dealing magical damage to all enemies.\nWhat a twist!"
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
  local damage = 3.4225 * aAD - .925 * dMR
  d:TakeDamage(damage)
end
