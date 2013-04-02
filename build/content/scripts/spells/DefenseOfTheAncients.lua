function GetTargetType()
    return Allies
end

function GetName()
return "Defense of the Ancients"
end

function GetDescription()
return "An old and long forgotten spell.\nBuffs the defense of everyone in your Party,\nincluding characters on reserve."
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
  d:BuffStat(DEF, .2)
  d:BuffStat(MR, .2)

  local aliveCount = GetAliveCount()
  local amount = .2 / aliveCount

  BuffAttackersReserveParty(DEF, amount)
  BuffAttackersReserveParty(MR, amount)
end
