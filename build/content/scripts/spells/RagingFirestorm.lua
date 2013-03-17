function GetTargetType()
    return Enemies
end

function GetName()
return "Raging Firestorm"
end

function GetDescription()
return "Summon a raging firestorm that engulfs all enemies.\nReduces enemies AD & MD.\nDeals both FIR & WND damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .6
end

function GetDelay()
  return .3
end

function SpellEffect()
  local damage = (3.375 * aMD * ((aFIR + aWND)/200) - 1.25 * dMR) * (200/(dFIR + dWND))
  d:TakeDamage(damage)
  ds:BuffStat(AD, -.12)
  ds:BuffStat(MD, -.12)
end
