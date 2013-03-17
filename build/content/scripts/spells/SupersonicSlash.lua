function GetTargetType()
    return Enemies
end

function GetName()
  return "Supersonic Slash"
end

function GetDescription()
    return "Strike faster than sound, hits all enemies with immense force.\nDeals physical WND damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return 1.1
end

function GetDelay()
  return 0
end

function SpellEffect()
  local damage = (8.325 * aAD * (aWND/100) - 1.25 * dDEF) * (100/dWND)
  d:TakeDamage(damage)
end
