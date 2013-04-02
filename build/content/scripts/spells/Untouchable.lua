function GetTargetType()
    return Myself
end

function GetName()
return "Untouchable"
end

function GetDescription()
  return "Your concentration allows you to better react to incoming attacks.\nDoubles EVA."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .24
end

function GetDelay()
  return .66
end

function SpellEffect()
 a:BuffStat(EVA, 1)
end
