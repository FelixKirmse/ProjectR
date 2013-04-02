function GetTargetType()
    return Enemies
end

function GetName()
  return "Fuck Them Up!"
end

function GetDescription()
    return "Spread a deadly disease to your enemies.\nReduces EVA, DEF, MR & SPD.\nCan also inflict PAR, PSN and DTH."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .6
end

function GetDelay()
  return .5
end

function SpellEffect()
  local damage = (1.25 * aAD * (aDRK/100) - 1.25 * dDEF) * (100/dDRK)
  d:ApplyDebuff(DTH, 30)
  d:TakeDamage(damage)

  d:ApplyDebuff(PSN, 45)
  d:ApplyDebuff(PAR, 30)

  d:BuffStat(EVA, -1.5)
  d:BuffStat(DEF, -.25)
  d:BuffStat(MR, -.25)
  d:BuffStat(SPD, -.25)
end
