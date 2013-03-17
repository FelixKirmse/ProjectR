function GetTargetType()
    return Enemies
end

function GetName()
  return "Darkness Comes From Within"
end

function GetDescription()
  return "Unleash your inner darkness onto your enemies.\nRemoves caster's debuffs.\nDeals unresistable DRK damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .64
end

function GetDelay()
  return .4
end

function SpellEffect()
  a:RemoveDebuffs()

  local damage = 3.125 * aMD * (aDRK/100)
  d:TakeDamage(damage)
end
