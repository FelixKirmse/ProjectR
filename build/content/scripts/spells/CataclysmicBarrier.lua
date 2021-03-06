function GetTargetType()
  return Enemies
end

function GetName()
  return "Cataclysmic Barrier"
end

function GetDescription()
  return "Summon a huge barrier that decreases damage done\nand increases damage taken.\nReduces AD, MD, DEF & MR.\nDeals HOL damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return 1.44
end

function GetDelay()
  return .15
end

function SpellEffect()
  local damage = (5.25 * aMD * (aHOL/100) - 1.75 * dMR) * (100/dHOL)
  d:TakeDamage(damage)
  d:BuffStat(AD, -.25)
  d:BuffStat(MD, -.25)
  d:BuffStat(DEF, -.25)
  d:BuffStat(MR, -.25)
end
