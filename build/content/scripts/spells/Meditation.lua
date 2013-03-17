function GetTargetType()
    return Myself
end

function GetName()
    return "Meditation"
end

function GetDescription()
    return "A defensive stance that recovers double the MP"
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return 0
end

function GetDelay()
  return .5
end

function SpellEffect()
  as:BuffStat(DEF, .2)
  as:BuffStat(MR, .2)
  a:UseMP(-(aMP * .4))
end
