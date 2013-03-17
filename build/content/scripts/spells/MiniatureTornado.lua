function GetTargetType()
    return Decaying
end

function GetName()
  return "Miniature Tornado"
end

function GetDescription()
  return "Summon a mini tornado among the enemy ranks.\nEnemies near the target also take damage.\nDeals WND damage, but targets enemy DEF."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return .64
end

function GetDelay()
  return .4
end

function SpellEffect()
  local damage = (3.75 * aMD * (aWND/100) - .75 * dDEF) * (100/dWND)
  d:TakeDamage(damage)
end
