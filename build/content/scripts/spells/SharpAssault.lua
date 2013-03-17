function GetTargetType()
    return Enemies
end

function GetName()
return "Sharp Assault"
end

function GetDescription()
    return "Throw magic infused knives that seek out the enemy.\nIgnores MR."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .68
end

function GetDelay()
  return .25
end

function SpellEffect()
  local damage = (3.3 * aAD + .825 * aMD) - .825 * dDEF
  d:TakeDamage(damage)
end
