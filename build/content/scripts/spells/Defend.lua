function GetTargetType()
    return Myself
end

function GetName()
    return "Defend"
end

function GetDescription()
    return "Aquire a defensive stance, increasing DEF & MR by 20%% and recovering 20%% of MP"
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
    a:BuffStat(DEF, .2)
    a:BuffStat(MR, .2)
    a:UseMP(-(aMP * .2))
end
