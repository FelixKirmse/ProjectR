function GetTargetType()
    return Single
end

function GetName()
return "Grand Healing Potion"
end

function GetDescription()
return "Heals target for 50%% of their max. HP."
end

function IsSupportSpell()
    return true
end

function GetMPCost()
    return .88
end

function GetDelay()
  return .25
end

function SpellEffect()
  d:Heal(dHP / 2)
end
