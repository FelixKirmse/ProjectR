function GetTargetType()
    return Myself
end

function GetName()
return "True Form"
end

function GetDescription()
  return "Reveal your true form, sacrificing defense for pure offense.\nThis spell has no delay."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .75
end

function GetDelay()
  return .99
end

function SpellEffect()
  as:BuffStat(SPD, 1)
  as:BuffStat(AD, 1)
  as:BuffStat(DEF, -.5)
  as:BuffStat(MR, -.5)
end
