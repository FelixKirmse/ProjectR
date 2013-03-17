function GetTargetType()
    return Allies
end

function GetName()
  return "Blood for Power"
end

function GetDescription()
  return "Hit your allies with empowering magic.\nIncreases AD, MD, MR & DEF, but halves speed bar.\nDeals minor unresistable magic damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return 1.24
end

function GetDelay()
  return 0
end

function SpellEffect()
  local damage = .5 * aMD
  d:TakeDamage(damage)

  ds:BuffStat(AD, .75)
  ds:BuffStat(MD, .75)
  ds:BuffStat(DEF, .75)
  ds:BuffStat(MR, .75)
  d:SetTurnCounter(d:GetTurnCounter() / 2)
end
