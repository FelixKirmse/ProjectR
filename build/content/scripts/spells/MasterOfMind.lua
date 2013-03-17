function GetTargetType()
    return Myself
end

function GetName()
    return "Mastery of Mind"
end

function GetDescription()
    return "You gain complete mastery over your mind, doubling your MD."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .72
end

function GetDelay()
  return .7
end

function SpellEffect()
  as:BuffStat(MD, 1)
end
