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
  ds:BuffStat(AD, .75)
  ds:BuffStat(DEF, .75)
  ds:BuffStat(SPD, -.75)
end
