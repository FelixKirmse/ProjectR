function GetTargetType()
    return Single
end

function GetName()
    return "Attack"
end

function GetDescription()
    return "Physical Attack dealing 100%% A.AD - 100%% D.DEF Damage"
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
    local damage = aAD - dDEF
    d:TakeDamage(damage)
end
