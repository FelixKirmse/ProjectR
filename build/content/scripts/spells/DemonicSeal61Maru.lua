function GetTargetType()
  return Single
end

function GetName()
  return "Demonic Seal 61: Maru"
end

function GetDescription()
  return "A technique that uses HOL energy to focus down a target.\nIgnores most DEF.\nDeals composite HOL damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .48
end

function GetDelay()
  return .66
end

function SpellEffect()
  local damage = ((1.5 * aAD + 2.25 * aMD) * (aHOL/100) - (.15 * dDEF + .75 * dMR)) * (100/dHOL)
  d:TakeDamage(damage)
end
