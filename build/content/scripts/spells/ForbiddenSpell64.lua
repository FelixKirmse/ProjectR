function GetTargetType()
    return Decaying
end

function GetName()
return "Forbidden Spell #64"
end

function GetDescription()
return "Summons an explosion of unfathomable energy\nat target's location. Enemies in proximity\nof target also take reduced damage.\nDamage greatly increased by FIR,WND & DRK.\nDamage unresistable and can't be evaded."
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
  local damage = (4.375 * aMD * ((aFIR + aWND + aDRK)/100) - 1.75 * dMR)/modifier
  d:TakeDamage(damage)
end
