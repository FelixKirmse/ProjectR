function GetTargetType()
    return Enemies
end

function GetName()
return "Ultimate Taboo"
end

function GetDescription()
return "Drain energy from your allies to empower your strike.\nUses 10%% of max HP per target hit from each ally.\nDeals composite FIR damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return 2
end

function GetDelay()
  return 0
end

function SpellEffect()
  extraDamage = 0
  ForEachAttackerParty("AddExtraDamage")

  local damage = ((4.5 * aAD + 4.5 * aMD) * (aFIR/100) - (.75 * dDEF + .75 * dMR)) * (100/dFIR) + extraDamage
  d:TakeDamage(damage)
end

function AddExtraDamage(char)
  char:SetTurnCounter(0)
  local extraValue = GetStats(char):GetTotalStat(HP) * .1
  extraDamage = extraDamage + extraValue
end
