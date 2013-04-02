function GetTargetType()
  return Single
end

function GetName()
  return "Cleansing Song"
end

function GetDescription()
  return "Sing a nice melody that removes all status debuffs of the target\nand converts stat debuffs into buffs."
end

function IsSupportSpell()
    return true
end

function GetMPCost()
    return .4
end

function GetDelay()
  return .65
end

function SpellEffect()
  d:RemoveDebuffs()
  for i = HP, SIL do
    local battleMod = ds:GetSingleStat(i):Get(BattleMod)
    if battleMod < 1 then
      d:BuffStat(i, 1 - battleMod)
    end
  end
end
