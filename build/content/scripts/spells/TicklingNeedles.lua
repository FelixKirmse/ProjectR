function GetTargetType()
    return Enemies
end

function GetName()
return "Tickling Needles"
end

function GetDescription()
    return "Throw magic infused needles at your enemies.\nWeak but cheap."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .24
end

function GetDelay()
  return .4
end

function SpellEffect()
  local damage = (1.875 * aAD + .625 * aMD) - (.625 * dDEF + .3125 * dMR)
  d:TakeDamage(damage)
end
