function GetTargetType()
  return Allies
end

function GetName()
  return "Support Technique: Shield"
end

function GetDescription()
  return "Increases DEF of all allies."
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
  ds:BuffStat(DEF, .48)
end
