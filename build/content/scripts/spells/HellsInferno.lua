function GetTargetType()
  return Enemies
end

function GetName()
  return "Hell's Inferno"
end

function GetDescription()
  return "An inferno from hell appears below the enemies.\nDecreases MR.\nDeals FIR damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return 1.12
end

function GetDelay()
  return .3
end

function SpellEffect()
  local damage = (4.5 * aMD * (aFIR/100) - 1.5 * dMR) * (100/dFIR)
  d:TakeDamage(damage)
  d:BuffStat(MR, -.25)
end
