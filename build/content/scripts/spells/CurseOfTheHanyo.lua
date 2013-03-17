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
  as:BuffStat(AD, .7)
  as:BuffStat(MD, .7)
  as:BuffStat(DEF, .7)
  as:BuffStat(MR, .7)

  a:ApplyDebuff(PSN, 200, a:GetLvl())
  a:ApplyDebuff(PAR, 200)
end
