function GetTargetType()
    return Enemies
end

function GetName()
    return "Distortion Field"
end

function GetDescription()
    return "Creates a field of arcane energy, damaging all enemies.\nSlightly ignores enemies MR."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .56
end

function GetDelay()
  return .25
end

function SpellEffect()
  local damage = (3.75 * aMD * (aARC/100) - 0.75 * dMR) * (100/dARC)
  d:TakeDamage(damage)
end
