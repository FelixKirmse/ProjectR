function GetTargetType()
    return Allies
end

function GetName()
  return "Let's speed this up"
end

function GetDescription()
  return "Instantly fills the speed bar of your allies to 100%%."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return 2
end

function GetDelay()
  return 0
end

function SpellEffect()
  if not IsSameChar(a, d) then
    d:SetTurnCounter(GetTimeToAction())
  end
end
