function GetTargetType()
    return Myself
end

function GetName()
return "Rise of the Phoenix"
end

function GetDescription()
return "Rise up from the ashes, healing you to full.\nVastly increases all stats.\nThis effect is passive and activated on death.\nUsing it does nothing.\nOnly works once per battle."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return 0
end

function GetDelay()
  return .99
end

function SpellEffect()
  local as = GetStats(a)
  if a:GetCurrentHP() / as:GetTotalStat(HP) > 0.01 then
    return
  end
  a:Heal(as:GetTotalStat(HP))
  for i = HP, SIL do
    a:BuffStat(i, 2)
  end
end
