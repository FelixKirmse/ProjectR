function GetTargetType()
  return Single
end

function GetName()
  return "Chaos Barrier"
end

function GetDescription()
  return "Summon a small barrier that decreases damage done\nand increases damage taken.\nReduces AD, MD, DEF & MR.\nDeals HOL damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .48
end

function GetDelay()
  return .5
end

function SpellEffect()
  local damage = (3.75 * aMD * (aHOL/100) - 1.25 * dMR) * (100/dHOL)
  d:TakeDamage(damage)
  d:BuffStat(AD, -.15)
  d:BuffStat(MD, -.15)
  d:BuffStat(DEF, -.15)
  d:BuffStat(MR, -.15)
end
