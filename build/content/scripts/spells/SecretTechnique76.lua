function GetTargetType()
    return Single
end

function GetName()
return "Secret Technique #76"
end

function GetDescription()
return "A vicious strike that attempts to weaken the enemy.\nChance to steal stat buffs from target.\nDeals physical ARC damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .76
end

function GetDelay()
  return .3
end

function SpellEffect()
  local damage = (3.75 * aAD * (aARC/100) - 1.25 * dDEF) * (100/dARC)
  d:TakeDamage(damage)

  for i = HP, SIL do
    local singleStat = ds:GetSingleStat(i)
    local battleMod = singleStat:Get(BattleMod)
    if battleMod > 1 and Roll(0, 99) < 40 then
      a:BuffStat(i, battleMod - 1)
      singleStat:Set(BattleMod, 1)
      ds:SetSingleStat(singleStat, i)
    end
  end
end
