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
  ds:BuffStat(DEF, .5)
  ds:BuffStat(MR, .5)
end
