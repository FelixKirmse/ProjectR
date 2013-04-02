function GetTargetType()
    return Myself
end

function GetName()
  return "Hidden Power"
end

function GetDescription()
  return "Heighten your combat ability for speed.\nIncreases AD & DEF, decreases SPD."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .8
end

function GetDelay()
  return .8
end

function SpellEffect()
  d:BuffStat(AD, .75)
  d:BuffStat(DEF, .75)
  d:BuffStat(SPD, -.75)
end
