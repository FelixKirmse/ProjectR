function GetTargetType()
    return Allies
end

function GetName()
  return "Dark Fog (Ally)"
end

function GetDescription()
    return "Summon a fog that removes all debuffs and heals a little.\nHealing increased by DRK mastery."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .36
end

function GetDelay()
  return .3
end

function SpellEffect()
   local healing = .25 * aMD * (aDRK/100)
  d:Heal(healing)
  d:RemoveDebuffs()
end
