function GetTargetType()
  return Myself
end

function GetName()
  return "Chaos Cleanse"
end

function GetDescription()
  return "Summon a chaotic storm on the battlefield.\nDeals DRK damage to enemies.\nCleanses stat debuffs of allies."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .96
end

function GetDelay()
  return .24
end

function SpellEffect()
  ForEachDefenderParty("DamageFunc")
  ForEachAttackerParty("HealFunc")
end

function HealFunc(character)
  GetStats(character):RemoveDebuffs()
end

function DamageFunc(character)
  local defStats = GetStats(character)
  local defMR = defStats:GetTotalStat(MR)
  local defDRK = defStats:GetTotalStat(DRK)

  local damage = (3.75 * aMD * (aDRK/100) - .625 * defMR) * (100/defDRK)
  character:TakeDamage(damage)
end
