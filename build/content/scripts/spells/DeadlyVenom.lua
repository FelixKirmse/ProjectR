function GetTargetType()
    return Single
end

function GetName()
  return "Deadly Venom"
end

function GetDescription()
    return "Inject the target with a deadly venom.\nAlmost guaranteed to apply PSN.\nDeals physical DRK damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .28
end

function GetDelay()
  return .45
end

function SpellEffect()
  local damage = (3 * aAD * (aDRK/100) - dDEF) * (100/dDRK)
  d:TakeDamage(damage)

  d:ApplyDebuff(PSN, 120, a:GetLvl())
end
