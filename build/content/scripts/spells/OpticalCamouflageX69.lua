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
  a:BuffStat(EVA, .66)
  a:BuffStat(DEF, .5)
  a:BuffStat(MR, .5)
  a:BuffStat(SPD, .5)
end
