function GetTargetType()
    return Enemies
end

function GetName()
  return "Dark Fog (Enemy)"
end

function GetDescription()
    return "Summon a fog that deals unresistable DRK damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .40
end

function GetDelay()
  return .38
end

function SpellEffect()
  local damage = 2 * aMD * (aDRK/100)
  d:TakeDamage(damage)
end
