function GetTargetType()
  return Allies
end

function GetName()
  return "Blessed Ground"
end

function GetDescription()
  return "The ground below you becomes filled with holy energy.\nThe healing is not much, but the thought counts.\nYou are pretty tired after this spell."
end

function IsSupportSpell()
  return true
end

function GetMPCost()
  return .72
end

function GetDelay()
  return 0
end

function SpellEffect()
  local amount = 0.88 * aMD * (aHOL/dHOL)
  d:Heal(amount)
end
