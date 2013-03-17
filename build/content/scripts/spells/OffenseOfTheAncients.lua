function GetTargetType()
    return Allies
end

function GetName()
return "Offense of the Ancients"
end

function GetDescription()
return "An old and long forgotten spell.\nBuffs the offense of everyone in your Party,\nincluding characters on reserve."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return 1.12
end

function GetDelay()
  return .35
end

function SpellEffect()
  local aliveCount = GetAliveCount()
  local amount = .2 / aliveCount

  BuffAttackersReserveParty(AD, amount)
  BuffAttackersReserveParty(MD, amount)
end
