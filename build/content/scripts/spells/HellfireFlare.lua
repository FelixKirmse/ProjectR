function GetTargetType()
  return Enemies
end

function GetName()
  return "Hellfire Flare"
end

function GetDescription()
  return "Shoot a massive ball of hellfire at your enemies.\nHuge delay.\nDeals unresistable FIR damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return 1.68
end

function GetDelay()
  return 0
end

function SpellEffect()
  local damage = 3.5 * aMD * (aFIR/100)
  d:TakeTrueDamage(damage)
end
