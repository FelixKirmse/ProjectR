function GetTargetType()
    return Single
end

function GetName()
  return "Blessing of the Gods"
end

function GetDescription()
  return "Bless the target, increasing all their stats.\nAlso sets their speed bar to 100%%."
end

function IsSupportSpell()
    return true
end

function GetMPCost()
    return 1.32
end

function GetDelay()
  return .5
end

function SpellEffect()
  d:SetTurnCounter(GetTimeToAction() * .99)

  for i = HP, SIL, 1 do
    d:BuffStat(i, .25)
  end
end
