function GetTargetType()
    return Enemies
end

function GetName()
  return "Divine Light of the Goddess"
end

function GetDescription()
  return "Smite your enemies with this divine attack.\nVery high delay.\nDeals unresistable HOL damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return 1.58
end

function GetDelay()
  return 0
end

function SpellEffect()
  local damage = 6.25 * aMD * (aHOL/100)
  d:TakeDamage(damage)
end
