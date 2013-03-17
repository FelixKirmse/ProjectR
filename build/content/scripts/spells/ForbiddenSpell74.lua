function GetTargetType()
  return Enemies
end

function GetName()
  return "Forbidden Spell #74"
end

function GetDescription()
  return "Through some foul magic this spell's damage is reduced by DEF.\nTargets all enemies."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .96
end

function GetDelay()
  return .35
end

function SpellEffect()
  local damage = 3.5 * aMD - .875 * dDEF
  d:TakeDamage(damage)
end
