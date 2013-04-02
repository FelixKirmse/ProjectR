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

  d:BuffStat(AD, .75)
  d:BuffStat(MD, .75)
  d:BuffStat(DEF, .75)
  d:BuffStat(MR, .75)
  d:SetTurnCounter(d:GetTurnCounter() / 2)
end
