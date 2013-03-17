function GetTargetType()
    return Myself
end

function GetName()
return "Optical Camouflage X69"
end

function GetDescription()
    return "Extend your arm to bitchslap all enemies.\nDeals physical DRK damage, WTF?!"
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .64
end

function GetDelay()
  return .36
end

function SpellEffect()
  as:BuffStat(EVA, .66)
  as:BuffStat(DEF, .5)
  as:BuffStat(MR, .5)
  as:BuffStat(SPD, .5)
end
