# CubeMegaMod
This is a large mod for CubeWorld steam version. It adds / will add underwater exploration, combat modifications,
lore improvements, gold usages and more.

**If anyone is in need for help with creating their own mods or a collaboration, don't hesitate to contact me. I am always glad to help and work with you. My discord is: Nichiren#3660.**

I am not to be held responsible for any damage because of usage of this mod. Use this mod at your own risk.

**Be safe and back up your save data when playing with mods**

### Features
Features of this mod include sea exploration, lore interactions and combat improvements.

#### Sea exploration
Going underwater will spawn random hostile fishes around you. Going underwater usually drains stamina.
This is still the case, however now 10 gold is automatically used to gain the underwater breathing ability for 10 seconds.
On top of that, underwater exploring is rewarded with random chests spawning every 60 seconds.
The chest types are:
- Wood chest [Chances to drop gold, 1 - 5 star gear and consumables (also including unavailable ones)]
- Skull chest [Drops gold and one or two 4 - 6 star gear items]
- Obsedian chest [Drops artifacts]
- Bone chest [Drops pets (also including unavailable pets)]

Next to that, random spawn while diving.

#### Lore interactions
Lore interactions are updated. 
- Every (lore < 100) has a maximum of 50% (based on lore) chance to drop a 1 star gear.
- Every (lore >= 100 && lore < 150) has a maximum of 50% (based on lore) chance to drop 2-3 star weapon.
- Every (lore >= 150) has a maximum of 100% (based on lore) chance to drop an artifact.

#### Combat improvements
New combat abilities added: 
- The 1 key converts your mana to stamina.
- The 2 key restores you to full health at the cost of 50 combo.

If the doubletap functionality is active, the following abilities can be activated by double tapping the mentioned key.
If it is disabled, it can be activated using leftControl + mentioned key.
- The movement keys (WASD) can be pressed for movement abilities (WAD) and an attack ability (S). The costs of these abilities is currently 75 stamina.

## Installing
Download the latest version from the releases. Put the `CubeMegaMod-v.x.x.x.dll` of one of the releases in your mod folder. For usage of the mod, checkout the attached readme.
If you have any trouble installing the mod, check out this guide: https://www.youtube.com/watch?v=Uuq47N3YT8I.

## Usage
For v.1.0.0+, the usage is the following:

### Commands
- [Debug only] `/fish <0 - inf>`: Spawns which will spawn the defined amount of fish around you. (Gets really slow with high amounts of creatures, because Wollay)
- [Debug only] `/chest <0 - 3>`: Spawns a chests with defined type.
- [Debug only] `/roots`: Adds 60 dragon roots to your inventory.
- [Debug only] `/drop <0 - 4> <1 - inf>`: Tests for dropping items. First the type, then the count is specified.
- [Debug only] `/ability <0-160>`: Executes an ability defined by the id.
- `/enable doubletap`: Enables movement ability triggering with doubletap.
- `/disable doubletap`: Disables movement ability triggering with doubletap.
- `/enable autogoldusage`: Enables automatic gold consumption during the diving event.
- `/disable autogoldusage`: Disables automatic gold consumption during the diving event.

## Final words
Special thanks **Chris** for his work for the modding community and **Timothy(GrayShadoz - Youtube)** for his effort to make cubeworld videos (including of all of my mods).
Also thanks to **TheBagel3(Youtube, Discord, Twitch)**, **Raxiti(Reddit)**, **kuba.dlouhej(Discord)** for testing and giving feedback on the mod.
