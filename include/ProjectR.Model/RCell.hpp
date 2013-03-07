#pragma once

namespace ProjectR
{
enum RCell
{
  Nothing = 0,
  Diggable = 1 << 1,
  Floor = 1 << 2,
  Wall = 1 << 3,
  Door = 1 << 4,
  Border = 1 << 5,
  Corridor = 1 << 6,
  Locked = 1 << 7,
  Chest = 1 << 8,
  Common = 1 << 9,
  Uncommon = 1 << 10,
  Rare = 1 << 11,
  Epic = 1 << 12,
  Legendary = 1 << 13,
  Artifact = 1 << 14,
  Small = 1 << 15,
  Normal = 1 << 16,
  Big = 1 << 17,
  Grand = 1 << 18,
  Item = 1 << 19,
  Important = 1 << 20,
  Warp = 1 << 21,
  Visited = 1 << 22,
  Walkable = Floor | Door | Item | Chest,
  Blocking = Wall | Diggable | Locked,
  Quality = Common | Uncommon | Rare | Epic | Legendary | Artifact,
  Size = Small | Normal | Big | Grand
};
}
