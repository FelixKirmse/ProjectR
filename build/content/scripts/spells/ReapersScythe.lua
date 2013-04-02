function GetTargetType()
    return Single
end

function GetName()
    return "Reaper's Scythe"
end

function GetDescription()
    return "A deadly slash with your scythe.\nDeals DRK damage.\nChance to instantly kill target.\nHeals for 100%% of damage done.\nDoesn't target DEF nor MR."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return 0
end

function GetDelay()
  return .5
end

function SpellEffect()
    d:ApplyDebuff(DTH, 30)
    local damage = aAD * (aDRK/dDRK)
    d:TakeDamage(damage)
    a:Heal(damage)
end
