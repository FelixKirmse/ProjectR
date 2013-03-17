function GetTargetType()
    return Single
end

function GetName()
  return "Fiery Fury Fist"
end

function GetDescription()
    return "Strike with your flame-imbued fist.\nThe heat causes you to ignore some of the enemies DEF.\nDeals physical FIR damage."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .58
end

function GetDelay()
  return 0
end

function SpellEffect()
  local damage = (5 * aAD * (aFIR/100) - .8 * dDEF) * (100/dFIR)
  d:TakeDamage(damage)
end
