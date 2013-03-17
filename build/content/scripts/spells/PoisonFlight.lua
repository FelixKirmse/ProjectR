function GetTargetType()
  return Enemies
end

function GetName()
  return "Poison Flight"
end

function GetDescription()
  return "Fly among the enemy ranks leaving a poison trail behind you.\nChance to inflict PAR and PSN.\nDeals physical DRK damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .8
end

function GetDelay()
  return .25
end

function SpellEffect()
  local damage = (4 * aAD * (aDRK/100) - dDEF) * (100/dDRK)
  d:TakeDamage(damage)
  d:ApplyDebuff(PAR, 70)
  d:ApplyDebuff(PSN, 70, a:GetLvl())
end
