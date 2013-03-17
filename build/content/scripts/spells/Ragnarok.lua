function GetTargetType()
  return Myself
end

function GetName()
  return "Ragnarok"
end

function GetDescription()
  return "Fires a concentrated laser of pure arcane energy at your enemies.\nUses up all of your MP, making the spell stronger.\nYou are completely exhausted after using this."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return 1.6
end

function GetDelay()
  return 0
end

function SpellEffect()
  a:UseMP(160)
  damageMod = a:GetCurrentMP() / 10
  ForEachDefenderParty("DamageCalc")
  a:UseMP(200)
end

function DamageCalc(character)
  local charStats = GetStats(character)
  local defMR = charStats:GetTotalStat(MR)
  local defARC = charStats:GetTotalStat(ARC)

  local damage = ((8 + damageMod) * aMD * (aARC/100) - .5 * defMR) * (100/defARC)
  character:TakeDamage(damage)
end
