function GetTargetType()
    return Enemies
end

function GetName()
  return "Crippling Aura"
end

function GetDescription()
  return "Focus your aura to cripple your enemies.\nReduces AD, MD, DEF & MR of enemies."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .88
end

function GetDelay()
  return 0
end

function SpellEffect()
  d:BuffStat(AD, -1)
  d:BuffStat(MD, -1)
  d:BuffStat(DEF, -1)
  d:BuffStat(MR, -1)
end
