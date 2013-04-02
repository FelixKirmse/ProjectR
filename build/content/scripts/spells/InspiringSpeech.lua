function GetTargetType()
    return Allies
end

function GetName()
  return "Inspiring Speech"
end

function GetDescription()
  return "Hold an incredibly inspiring speech.\nIncreases AD, MD, DEF & MR significantly.\nUses up all your MP."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return 1.88
end

function GetDelay()
  return 0
end

function SpellEffect()
  a:UseMP(200)
  d:BuffStat(AD, 1)
  d:BuffStat(MD, 1)
  d:BuffStat(DEF, 1)
  d:BuffStat(MR, 1)
end
