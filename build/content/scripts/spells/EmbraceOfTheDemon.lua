function GetTargetType()
    return Single
end

function GetName()
    return "Embrace of the Demon"
end

function GetDescription()
    return "The targets heart is embraced by demonic energy. Deals unresistable DRK damage\nand has a chance to instantly kill the target.\nTargets under 25%% health receive triple damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return 1.5
end

function GetDelay()
  return 0
end

function SpellEffect()

  local bonusDamage = 1
  if d:GetCurrentHP() / dHP < .25 then
    bonusDamage = 3
  end

  local damage = 5 * aMD * (aDRK/100) * bonusDamage
  d:ApplyDebuff(DTH, 50)

  d:TakeDamage(damage)
end
