function GetTargetType()
    return Single
end

function GetName()
  return "5 ExaWatts Xtermination Laser X1337"
end

function GetDescription()
    return "Oh god, what the shit is that thing?\nDon't point it in my direction, FUCK!"
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .88
end

function GetDelay()
  return 0
end

function SpellEffect()
  local damage = 10 * aAD - .75 * dDEF
  d:TakeDamage(damage)
end
