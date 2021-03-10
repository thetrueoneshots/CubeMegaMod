# CubeMegaMod
This is a large mod for CubeWorld steam version. It adds underwater exploration, combat modifications,
lore improvements, gold usages and more.

**If anyone is in need for help with creating their own mods or a collaboration, don't hesitate to contact me. I am always glad to help and work with you. My discord is: Nichiren#3660.**

I am not to be held responsible for any damage because of usage of this mod. Use this mod at your own risk.

**Be safe and back up your save data when playing with mods**

### Features
Features of this mod include sea exploration, lore interactions and combat improvements.

**NOTE THAT EVERY SEPERATE FEATURE CAN BE DISABLED WITH THE CHAT**

#### Sea exploration [ID: 1]
Going underwater will spawn random hostile fishes around you. Going underwater usually drains stamina.
This is still the case, however now 10 gold is automatically used to gain the underwater breathing ability for 10 seconds.
On top of that, underwater exploring is rewarded with random chests spawning every 60 seconds.
The chest types are:
- Wood chest [Chances to drop gold, 1 - 5 star gear and consumables (also including unavailable ones)]
- Skull chest [Drops gold and one or two 4 - 8 star gear items]
- Obsedian chest [Drops artifacts]
- Bone chest [Drops pets (also including unavailable pets)]

Next to that, random bosses spawn while diving. These can get be really strong (500k hp for example),
so only take them on when you are geared up with 5+ star gear.

#### Lore interactions [ID: 2]
Lore interactions are updated. Now, whenever you interaction with a lore object, you have a chance of finding an item.
In the chat, a message will appear on how this item was found. The rates for finding items are the following:
- Every (lore < 100) has a maximum of 50% (based on lore) chance to drop a 1 star gear.
- Every (lore >= 100 && lore < 150) has a maximum of 50% (based on lore) chance to drop 2-3 star weapon.
- Every (lore >= 150) has a maximum of 100% (based on lore) chance to drop an artifact.

#### Combat improvements [ID: 3]
New combat abilities added:
- The 1 key converts your mana to stamina.
- The 2 key restores you to full health at the cost of 50 combo.

If the doubletap functionality is active, the following abilities can be activated by double tapping the mentioned key.
If it is disabled, it can be activated using leftControl + mentioned key.
- The movement keys (WASD) can be pressed for movement abilities (WAD) and an attack ability (S). The costs of these abilities is currently 75 stamina.

#### Creature updates [ID: 4]
Stat updates to mobs and pets.
- Buffed pet stats. (All pet stats doubled)
- Nerfing ranged mobs.
	- Nerfing mobs equiped with boomerangs. (Damage halved.)
	- Nerfing mage mobs. (Damage halved.)

## Installing
Download the latest version from the releases. Put the `CubeMegaMod-v.x.x.x.dll` of one of the releases in your mod folder. For usage of the mod, checkout the attached readme.
If you have any trouble installing the mod, check out this guide: https://www.youtube.com/watch?v=Uuq47N3YT8I.

## Usage
For v.1.2.0+, the usage is the following:

### Commands
- *(Disabled)* [Debug only] `/fish <0 - inf>`: Spawns which will spawn the defined amount of fish around you. (Gets really slow with high amounts of creatures, because Wollay)
- *(Disabled)* [Debug only] `/chest <0 - 3>`: Spawns a chests with defined type.
- *(Disabled)* [Debug only] `/roots`: Adds 60 dragon roots to your inventory.
- *(Disabled)* [Debug only] `/drop <0 - 4> <1 - inf>`: Tests for dropping items. First the type, then the count is specified.
- *(Disabled)* [Debug only] `/ability <0-160>`: Executes an ability defined by the id.
- `/enable doubletap`: Enables movement ability triggering with doubletap.
- `/disable doubletap`: Disables movement ability triggering with doubletap.
- `/enable autogoldusage`: Enables automatic gold consumption during the diving event.
- `/disable autogoldusage`: Disables automatic gold consumption during the diving event.
- `/mod <ID> <0 - 1>`: Turns feature with ID on (1) or off (0).

## Bugs
Bugs known:
- Underwater bosses sometimes drop random region gear.
- Invisible creatures / chests (but visible on map).
- Dissapearing creatures / chest.

## Possible features
This is a list of the possible features I am considering for this mod. Everything with a preceding *[possible]* is simply an idea that I might take a look into. Everything without the preceding possible is likely to be implemented at one point in this mod.

### 1. User mod selection.
  - Allowing the user to select which parts of the mod they want to have enabled while playing the game.
  - Preferences will be saved
  - *[Possible]* Automatic updating from the github repo.
### 2. Increased Supplier Gnome Usefullness.
  - Selling artifacts for high prices.
  - Extra usages for gems, such as leveling up weapons.
  - Selling healing items, to support non healing classes in desert and fireland regions.
### 3. *[Possible]* Spirit cubes.
  - *[Possible]* Bringing back the old spirit cubes, if they can still be recovered from existing game code.
  - *[Possible]* Implement new kinds of spirit cubes. This can be: water spirit (the healing puddles as a weapon effect or chance to spawn bubbles on hit), shadow spirit (a chance to hit twice, much like the ranger's shadow), earth spirit (temporarily immobilizes the enemy, like the scout sand trap).
### 4. Weapon upgrading.
  - Either use gems, gold, XP or something else to upgrade weapons.
### 5. Creature updates.
  - Nerfing poison DOT by mobs.
### 6. Buff gold gained from gold bags. (They are useless right now)
### 7. Inceasing item stack sizes.
  - Gaining increased stack / 'pouch' sizes by buying them, gaining them with events or as an effect of certain artifacts.
### 8. Random starting regions. (Not always the basic area)
### 9. Combat updates (not all of them may be implemented)
  - An ability that gives 1-2% of hp at the cost of the amount of hp recovered in coins. Is a hold ability to support non-healing classes.
  - Mapping the movement abilities to better keys (currently left control)
  - Spending 50% of your hp to gain a damage buff.
  - Spending combo to gain movement speed.
  - Spending combo to gain HP.
  - Spending combo to gain a buff (firetrail)
  - Passives, like poison resistance or smth. Can also be when reaching 100+ combo, you gain a firetrail buff.
  - Converting mana to stamina / other way around.
  - Converting HP to mana / stamina.
  - Mapping the abilities to the appropriate keys (currently 1 - 9)
### 10. Increased starting gold (~40), to allow for a faster start (Buying some gear, a flask and a pet food at the start)
### 11. Buffing climbing speed by think of 100%. (The jumping hack is faster than climbing)
### 12. New classes.
  - Adding the monk class in the mod.
  - Creating a new necromancer class.
  - [Possible] Creating a woodland / druid class.
### 13. Buying artifacts with gold. (To make gold more useful again. Also done by the diving event and gold->hp ability)
### 14. Incorporate previous mods into the mod.
  - Cubegression
  - GuardianFix
  - CubePatch
  - CubeTravel
  - MonkClass




## Final words
Special thanks **Chris** for his work for the modding community and **Timothy(GrayShadoz - Youtube)** for his effort to make cubeworld videos (including of all of my mods).
Also thanks to **TheBagel3(Youtube, Discord, Twitch)**, **Raxiti(Reddit)**, **kuba.dlouhej(Discord)** for testing and giving feedback on the mod.
