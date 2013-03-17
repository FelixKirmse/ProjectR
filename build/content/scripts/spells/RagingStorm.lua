function GetTargetType()
    return Enemies
end

function GetName()
return "Raging Storm"
end

function GetDescription()
    return "Summon a storm to harm your foes.\nIgnores a good chunk of MR.\nDeals WND damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .38
end

function GetDelay()
  return .5
end

function SpellEffect()
  local damage = (3 * aMD * (aWND/100) - .45 * dMR) * (100/dWND)
  d:TakeDamage(damage)
end
