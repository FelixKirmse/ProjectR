function GetTargetType()
    return Myself
end

function GetName()
return "Time Bubble"
end

function GetDescription()
    return "Create a time bubble around you that allows you to act faster.\nDoubles your SPD."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return 1
end

function GetDelay()
  return .8
end

function SpellEffect()
  d:BuffStat(SPD, 1)
end
