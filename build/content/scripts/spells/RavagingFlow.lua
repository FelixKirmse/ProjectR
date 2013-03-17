function GetTargetType()
    return Single
end

function GetName()
    return "Ravaging Flow"
end

function GetDescription()
    return "Fires a concentrated laser of pure arcane engery at the target.\nUses up all of your MP, making the spell stronger.\nYou are completely exhausted after using this."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .7
end

function GetDelay()
  return 0
end

function SpellEffect()
  a:UseMP(70)
  local currentMP = a:GetCurrentMP()
  local damage = ((8 + currentMP/10) * aMD * (aARC/100) - 0.5 * dMR) * (100/dARC)
  d:TakeDamage(damage)  
  a:UseMP(300)
end
