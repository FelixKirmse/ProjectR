function GetTargetType()
    return Single
end

function GetName()
  return "Omae Wa Mo Shindeiru"
end

function GetDescription()
  return "You are already dead."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return 1
end

function GetDelay()
  return 0
end

function SpellEffect()
  local bonusDamage = 1
  if d:GetCurrentHP() / dHP < .5 then
    bonusDamage = 3
  end

  local damage = (5 * aAD * (aDRK/100) - dDEF) * (100/dDRK) * bonusDamage
  d:ApplyDebuff(DTH, 75)
  d:TakeDamage(damage)
end
