function GetTargetType()
    return Single
end

function GetName()
  return "Cleanse"
end

function GetDescription()
  return "Cleanses target of all status effects. Also provides slight healing."
end

function IsSupportSpell()
    return true
end

function GetMPCost()
    return .1
end

function GetDelay()
  return .5
end

function SpellEffect()
  d:RemoveDebuffs()
  local healing = 1.5 * aAD + 1.5 * aMD
  d:Heal(healing)
end
