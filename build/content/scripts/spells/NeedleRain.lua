function GetTargetType()
    return Enemies
end

function GetName()
  return "Needle Rain"
end

function GetDescription()
  return "Needles rain down from the sky upon your enemies.\nIgnores most DEF."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .72
end

function GetDelay()
  return .3
end

function SpellEffect()
  local damage = 3.2 * aAD - .5 * dDEF
  d:TakeDamage(damage)
end
