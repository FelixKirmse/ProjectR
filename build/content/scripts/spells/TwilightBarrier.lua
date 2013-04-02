function GetTargetType()
    return Allies
end

function GetName()
  return "Twilight Barrier"
end

function GetDescription()
  return "Summon a twilight barrier to aid your allies.\nIncreases DEF & MR."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .88
end

function GetDelay()
  return .3
end

function SpellEffect()
  d:BuffStat(DEF, .5)
  d:BuffStat(MR, .5)
end
