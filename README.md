# CubeMegaMod
This is a large mod for CubeWorld steam version. It adds underwater exploration, combat modifications,
lore improvements, gold usages and more.

**If anyone is in need for help with creating their own mods or a collaboration, don't hesitate to contact me. I am always glad to help and work with you. My discord is: Nichiren#3660.**

I am not to be held responsible for any damage because of usage of this mod. Use this mod at your own risk.

**Be safe and back up your save data when playing with mods**

## Features
Features of this mod include sea exploration, lore interactions and combat improvements. This mods also allowins the user to select which parts of the mod they want to have enabled while playing the game. These preferences will be saved and taken next time you start up the game.

**NOTE THAT EVERY SEPERATE FEATURE CAN BE DISABLED WITH THE CHAT**

### Sea exploration [ID: 1]
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

### Lore interactions [ID: 2]
Lore interactions are updated. Now, whenever you interaction with a lore object, you have a chance of finding an item.
In the chat, a message will appear on how this item was found. The rates for finding items are the following:
- Every (lore < 100) has a maximum of 50% (based on lore) chance to drop a 1 star gear.
- Every (lore >= 100 && lore < 150) has a maximum of 50% (based on lore) chance to drop 2-3 star weapon.
- Every (lore >= 150) has a maximum of 100% (based on lore) chance to drop an artifact.

### Combat improvements [ID: 3]
New combat abilities added:
- The 1 key converts your mana to stamina.
- The 2 key restores you to full health at the cost of 50 combo.

If the doubletap functionality is active, the following abilities can be activated by double tapping the mentioned key.
If it is disabled, it can be activated using leftControl + mentioned key.
- The movement keys (WASD) can be pressed for movement abilities (WAD) and an attack ability (S). The costs of these abilities is currently 75 stamina.

### Creature updates [ID: 4]
Stat updates to mobs and pets.
- Buffed pet stats. (All pet stats increased with 50%)
- Nerfing ranged mobs.
	- Nerfing mobs equiped with boomerangs. (Damage halved.)
	- Nerfing mage mobs. (Damage halved.)
- Creating a new character makes you start with 40g for a bit smoother start.

### Shop Updates [ID: 5]
- Gem trader shop:
	- Sells a random artifact (1000g).
	- Sells healing potions, to support non healing classes in desert and fireland regions (5g-20g).
	- Has a chance of selling spirit cubes (25g).
	- The old gems that were sold are removed.
![https://imgur.com/a/ivHSOIM](https://i.imgur.com/FxqLoov.png "Gem trader shop")
- Item vendor:
	- Sells special movement items (75g)
	- Sells a void stone (50g).
	- Sells a random amount of spirit cubes, amount and type vary each day (25g).
![https://imgur.com/a/x2FOGbV](https://i.imgur.com/XkZDkxd.png "Item vendor shop")


### World Generation Updates [ID: 6]
- Starting region can now by any of the normal temperature regions, such as hills, oceans, mountains, woodlands e.t.c.
- World now consists of bigger islands with similar biomes. The world should still be compatible with old save data, but please back it up to be sure no save data is lost.
![https://imgur.com/a/vh4U86s](https://i.imgur.com/yjl5c8m.png "New world generation")

### Beginner Mode [ID: 7]
- For the first 5 levels of the player, enemies are scaled down, to allow a more beginner friendly start of a new character.
	- Scaling is <17%, 33%, 50%, 67%, 83%> for each increasing level respectively.

### Region Lock Updates [ID: 8]
- Gear is tuned with local power of a region, so it is the strongest in that region and its power fades the further it gets from the region.
	- For normal gear, every region away from the source region substracts 2 stars of weapon effectiveness.
	- For + gear, every region away from the source region substracts 1 star of weapon effectiveness.

### Weapon Upgrading [ID: 9]
- Brings back the weapon adaption from the alpha in a new jacket. NPC's with the tag smithy appear in some towns at the smithy (where you melt iron).
	- Upgrading a normal weapon will convert it into a + weapon.
	- Upgrading a + weapon will convert it into a normal weapon with 1 star extra rarity.
	- Upgrading a weapon destroys all attached spirit cubes!
![https://imgur.com/a/cHnS1Ij](https://i.imgur.com/JahE2aD.png "Weapon adaption / upgrading")

### New Quests [ID: 10]
- Adds new quest types that can be dropped when talking to NPC's.
	- The quests consists of 4 different kill quest for 4 different animal types.
	- Quests of different rarities can drop, increasing the reward and amount of kills needed.

### New Classes	[ID: 11]
- Adds a modified version of the monk class into the game. Note that this part is still bound the change a lot.

### Spirit Cubes [ID: -]
Spirit cubes are available again in the game. They can be bought from the weapon vendor for 25g each! Checkout the 
Shop Updates [ID: 5] part of the mod. 

## Installing
Download the latest version from the releases. Put the `CubeMegaMod-v.x.x.x.dll` of one of the releases in your mod folder. For usage of the mod, checkout the attached readme.
If you have any trouble installing the mod, check out this guide: https://www.youtube.com/watch?v=Uuq47N3YT8I.

## Usage
For v.1.2.0+, the usage is the following:

### Commands
- `/enable doubletap`: Enables movement ability triggering with doubletap.
- `/disable doubletap`: Disables movement ability triggering with doubletap.
- `/mod <ID> <0 - 1>`: Turns feature with ID on (1) or off (0).
- *(No longer supported)*`/enable autogoldusage`: Enables automatic gold consumption during the diving event.
- *(No longer supported)*`/disable autogoldusage`: Disables automatic gold consumption during the diving event.


## Bugs
Bugs known:
- Interactable game elments not responding after playing for a long time.
- Doors not opening with harp sometimes.
- Game crashing sometimes when talking to NPC's.

## Possible features
This is a list of the possible features I am considering for this mod. Everything with a preceding *[possible]* is simply an idea that I might take a look into. Everything without the preceding possible is likely to be implemented at one point in this mod.

### 1. User mod selection.
  - *[Possible]* Automatic updating from the github repo.
### 2. Increased Supplier Gnome Usefullness.
  - *[Possible]* Extra usages for gems, such as leveling up weapons.
### 4. Creature updates.
  - Nerfing poison DOT by mobs.
### 5. Buff gold gained from gold bags. (They are useless right now)
### 6. Inceasing item stack sizes.
  - Gaining increased stack / 'pouch' sizes by buying them, gaining them with events or as an effect of certain artifacts.
### 7. Combat updates (not all of them may be implemented)
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
### 8. Buffing climbing speed by think of 100%. (The jumping hack is faster than climbing)
### 9. New classes.
  - Creating a new necromancer class.
  - Creating a flying vampire class.
  - Creating a stance changer class.
  - *[Possible]* Creating a woodland / druid class.
### 10. Incorporate previous mods into the mod.
  - Cubegression
  - GuardianFix
  - CubePatch
  - CubeTravel
### 11. Shop updates
  - New crafting recipes for crafting higher tiered potions.
### 12. Character creation updates
  - Allowing more races like necromancer and spike creatures e.t.c.
### 13. New Quest types:
  - A delivery quest: Person X of type Z needs special materials from a neighbouring village.
Talking another person of type Z gets you those materials. You need to bring them back and give them to the quest giver.
  - A gathering quest: Person X requires Y materials of type Z.
Delivering that gives a larger reward than the value of said materials.
### 14. New items
  - Item reskinning for unobtainable items.
### 15. Model loader
  - Model loader that loads in new cub files and distribute types.
### 16. New buyable skins with gold.
### 17. Unlocking new classes / skins with achievements.
### 18. Holding artefacts / wearing them.
### 19. Make portal stones spawn bosses on usage.

## Final words
Special thanks **Chris** for his work for the modding community and **Timothy(GrayShadoz - Youtube)** for his effort to make cubeworld videos (including of all of my mods).
Also thanks to **TheBagel3(Youtube, Discord, Twitch)**, **Raxiti(Reddit)**, **kuba.dlouhej(Discord)** for testing and giving feedback on the mod.
