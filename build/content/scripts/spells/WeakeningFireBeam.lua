function GetTargetType()
    return Single
end

function GetName()
return "Weakening Fire Beam"
end

function GetDescription()
return "Focus a fire beam on your target.\nSlightly lowers all stats of target.\nDeals FIR damage."
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
  local damage = (4 * aMD * (aFIR/100) - dMR) * (100/dFIR)
  d:TakeDamage(damage)

  for i = HP, SIL do
    d:BuffStat(i, -.15)
  end
end
