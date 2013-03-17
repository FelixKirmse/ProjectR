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
  ds:BuffStat(AD, -1)
  ds:BuffStat(MD, -1)
  ds:BuffStat(DEF, -1)
  ds:BuffStat(MR, -1)
end
