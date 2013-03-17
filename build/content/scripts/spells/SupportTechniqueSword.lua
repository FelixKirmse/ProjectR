function GetTargetType()
  return Allies
end

function GetName()
  return "Support Technique: Sword"
end

function GetDescription()
  return "Increases AD of all allies."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .8
end

function GetDelay()
  return .3
end

function SpellEffect()
  ds:BuffStat(AD, .48)
end
