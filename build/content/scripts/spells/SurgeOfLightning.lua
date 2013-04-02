function GetTargetType()
    return Single
end

function GetName()
  return "Surge of Lightning"
end

function GetDescription()
    return "Infuse your target with the power of lightning.\nIncreases AD & MD greatly.\nInflicts PAR."
end

function IsSupportSpell()
    return true
end

function GetMPCost()
    return .4
end

function GetDelay()
  return .6
end

function SpellEffect()
  d:BuffStat(AD, .72)
  d:BuffStat(MD, .72)
  d:ApplyDebuff(PAR, 300)
end
