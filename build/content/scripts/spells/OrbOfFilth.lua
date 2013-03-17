function GetTargetType()
    return Enemies
end

function GetName()
return "Orb of Filth"
end

function GetDescription()
return "Summon an orb of filth among the enemy ranks that explodes.\nChance to inflict poison.\nDeals DRK damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .48
end

function GetDelay()
  return .3
end

function SpellEffect()
  local damage = (2 * aMD * (aDRK/100) - dMR) * (100/dDRK)
  d:TakeDamage(damage)
  d:ApplyDebuff(PSN, 60, a:GetLvl())
end
