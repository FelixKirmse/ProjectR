function GetTargetType()
    return Myself
end

function GetName()
    return "Curse of the Han'yo"
end

function GetDescription()
    return "Unleash your full demonic potential.\nIncreases AD, MD, DEF & MR.\nInflicts PSN & PAR."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .66
end

function GetDelay()
  return .5
end

function SpellEffect()
  a:BuffStat(AD, .7)
  a:BuffStat(MD, .7)
  a:BuffStat(DEF, .7)
  a:BuffStat(MR, .7)

  a:ApplyDebuff(PSN, 200, a:GetLvl())
  a:ApplyDebuff(PAR, 200)
end
