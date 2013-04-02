function GetTargetType()
  return Myself
end

function GetName()
  return "Dark Mend"
end

function GetDescription()
  return "Dark energy fills the air.\nDeals DRK damage to enemies.\nHeals allies by 10%% of their max HP."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return 1.44
end

function GetDelay()
  return .1
end

function SpellEffect()
  ForEachDefenderParty("DamageFunc")
  ForEachAttackerParty("HealFunc")
end

function HealFunc(character)
  character:Heal(GetStats(character):GetTotalStat(HP) * .1)
end

function DamageFunc(character)
  local defStats = GetStats(character)
  local defMR = defStats:GetTotalStat(MR)
  local defDRK = defStats:GetTotalStat(DRK)

  local damage = (4.5 * aMD * (aDRK/100) - 1.5 * defMR) * (100/defDRK)
  character:TakeDamage(damage)
end
