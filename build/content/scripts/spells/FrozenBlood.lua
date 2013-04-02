function GetTargetType()
    return Myself
end

function GetName()
return "Frozen Blood"
end

function GetDescription()
    return "Freeze your blood to enhance your defesive capabilities.\nAlso vastly increases ICE mastery."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .36
end

function GetDelay()
  return .5
end

function SpellEffect()
  a:BuffStat(DEF, .5)
  a:BuffStat(MR, .5)
  a:BuffStat(ICE, 1)
end
