function GetTargetType()
    return Allies
end

function GetName()
return "Healing Rain"
end

function GetDescription()
  return "Summon a healing rain that provides slight healing to your party.\nHealing not affected by HOL."
end

function IsSupportSpell()
    return true
end

function GetMPCost()
    return .44
end

function GetDelay()
  return .5
end

function SpellEffect()
  local healing = 1.5 * aAD + 1.5 * aMD
  d:Heal(healing)
end
