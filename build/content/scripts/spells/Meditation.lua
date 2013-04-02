function GetTargetType()
    return Myself
end

function GetName()
    return "Meditate"
end

function GetDescription()
    return "A defensive stance that recovers double the MP of a normal Defend action."
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
  a:BuffStat(DEF, .2)
  a:BuffStat(MR, .2)
  a:UseMP(-(aMP * .4))
end
