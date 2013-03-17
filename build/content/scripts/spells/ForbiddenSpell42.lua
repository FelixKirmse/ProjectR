function GetTargetType()
    return Single
end

function GetName()
return "Forbidden Spell #42"
end

function GetDescription()
return "Noone knows why it is forbidden.\nIt doesn't seem particularly strong."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .4
end

function GetDelay()
  return .4
end

function SpellEffect()
  local damage = 3.75 * aMD - .75 * dMR
  d:TakeDamage(damage)
end
