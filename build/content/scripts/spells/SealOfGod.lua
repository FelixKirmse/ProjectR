function GetTargetType()
  return Enemies
end

function GetName()
  return "Seal of God"
end

function GetDescription()
  return "Tries to seal away all enemies with holy energy."
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
  local damage = (4 * aAD + 4 * aMD * (aHOL/100) - (dDEF + dMR)) * (100/dHOL)
  d:TakeDamage(damage)
end
