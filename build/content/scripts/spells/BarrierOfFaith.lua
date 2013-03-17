function GetTargetType()
  return Allies
end

function GetName()
 return "Barrier of Faith"
end

function GetDescription()
  return "Holy power flows through everyone in your party.\nIncreases DEF and MR."
end

function IsSupportSpell()
  return true
end

function GetMPCost()
  return .88
end

function GetDelay()
  return .3
end

function SpellEffect()
  ds:BuffStat(DEF, .5)
  ds:BuffStat(MR, .5)
end
