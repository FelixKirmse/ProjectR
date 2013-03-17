function GetTargetType()
    return Myself
end

function GetName()
return "Secret Technique: Stoneform"
end

function GetDescription()
return "Turn to stone. Increases DEF, MR & EVA.\nReduces SPD.\nInflicts PAR & SIL."
end

function IsSupportSpell()
    return false
end

function GetMPCost()
    return 1.28
end

function GetDelay()
  return 0
end

function SpellEffect()
  as:BuffStat(DEF, 1)
  as:BuffStat(MR, 1)
  as:BuffStat(EVA, 1)
  as:BuffStat(SPD, -1)

  a:ApplyDebuff(PAR, 200)
  a:ApplyDebuff(SIL, 200)
end
