function GetTargetType()
    return Decaying
end

function GetName()
    return "Blind Knowledge"
end

function GetDescription()
    return "Blindly shoots a thousand arcane projectiles in targets direction.\nDeals more damage to enemies further away."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .32
end

function GetDelay()
  return .5
end

function SpellEffect()
  local damage = ((4 * aMD * (aARC/100) - dMR) * (100/dARC)) * modifier
  d:TakeDamage(damage)
end
