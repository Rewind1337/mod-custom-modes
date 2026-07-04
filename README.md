# mod-custom-modes
mod-custom-modes is a module directly forked from [HardMode](https://github.com/AnchyDev/HardMode), which in turn was heavily inspired by [mod-challenge-modes](https://github.com/ZhengPeiRu21/mod-challenge-modes). The purpose of this module (mod-custom-modes) is to restore previous functionality from the HardMode module, which is outdated and abandoned at this point.

This module was compiled & tested on:

- [AzerothCore](https://github.com/azerothcore/azerothcore-wotlk)
- [AzerothCore-Playerbots](https://github.com/mod-playerbots/azerothcore-wotlk/tree/Playerbot)

## Disclaimer

- I only really intended to update this module to work with the current Azerothcore build
- I changed the modules foldername, and some other things
- I DID NOT CHANGE the previous implementation of the database, this module is therefore INCOMPATIBLE with the original [HardMode](https://github.com/AnchyDev/HardMode) module, and simply reuses the existing implementation

## Features
- Custom Modes with specific restrictions
- Level based rewards for each mode you have created
- Dynamic auras for each mode
	- These are not visible to the Player in any way by default. See `Visible Buff/Debuff for the Custom Mode` further down below.
	- These open up a lot of possibilities with further customizing challenges

## Installation

Either via

- Cloning this Repository directly into your `AzerothCore/modules/` folder
or
- Downloading the Repository via GitHub
- Extracting it into the `AzerothCore/modules/` folder
- If the folder has a `-master` or `-main` at the end, rename it to just `mod-challenge-modes` 

## Building

As with most modules, you'll need to:

- Launch CMake
- Configure
- Make sure `MODULE_MOD-CUSTOM-MODES` is set to `default` or `enabled`
- Configure again, Generate, and Open the Project
- Fully Build the Project
- It should not throw any errors, if it does, please open an issue here.

## Applying the SQL

This module uses a few custom tables inside your `characters`-database and your `world`-database

- Open up the `mod-custom-modes` folder
- Locate the `data` folder, inside is the `sql` folder

- Open up the `db-characters` folder
- From the `base` folder, apply the `base.sql` to your `acore-characters` database (usually), using your preferred way (e.g. HeidiSQL, mysql cli)
- From the `updates` folder, apply all `*.sql` files to `acore-characters` in order.

- Do the same with the `db-world` folder

## Configuring

The module comes with a `mod-challenge-modes.conf.dist` with a few configurable options.
You'll need to copy this `mod-challenge-modes.conf.dist` file to your servers module config folder.

```
#    HardMode.Enable
#        Description: Enables/disables the HardMode modes.
#        Default:     0 - Disabled     (1 - Enabled)
#        Type:        bool
```
```
#    HardMode.Inspect.Alert
#        Description: Alerts the inspecting player of what modes the target has enabled.
#        Default:     1 - Enabled     (0 - Disabled)
#        Type:        bool
```
```
#    HardMode.Restrict.Interact.Group.Range
#        Description: The level range that players can group together when under this restriction.
#        Default:     3     (0 - MaxLevel)
#        Type:        uint32
```
```
#    HardMode.Restrict.BadLuck.Chance
#        Description: The chance that an item is deleted when under this restriction.
#        Note: When an item drops in BadLuck, there is another internal roll, if you fail this roll
#              the item is deleted from the loot table. This is what this config is responsible for.
#        Default:     10     (0 - 100, no decimals)
#        Type:        uint32
```
```
#    HardMode.Restrict.SelfCrafted.CreatedBy
#        Description: Items crafted by the player like potions and food with gain a created by tag, allowing self crafted players to use them.
#        Note: This will only let players use their own items.
#        Default:     1 - Enabled     (0 - Disabled)
#        Type:        bool
```
```
#    HardMode.Restrict.Permadeath.Announce
#        Description: Enables the announcement when a permadeath player dies.
#        Default:     1 - Enabled     (0 - Disabled)
#        Type:        bool
```

## How to add custom modes

- Use the [HardMode Restriction Builder](https://anchydev.github.io/HardMode/#mode-editor), made by the same developer (AnchyDev) that also made the previous version of this module (HardMode)

- If you want Players to be able to start the custom mode ingame, you need to have `Enabled By Default` checked in the tool.
- The description field is not used in-game
- When you're happy, click `Generate SQL`
- Apply that SQL to your `acore-world` database
- Restart the Server and go in-game
- The custom mode should now be accessible ingame via the `Shrine of Challenge`, which is placed in every starting location by default
- A Player becomes `tainted` as soon as he gains any kind of XP, Items or anything else that would deem him unworthy to start new challenges
- A Player can always stop any challenge he has active

## How to add rewards to the custom modes

- Run the following query on your `acore-world` database, and take note of the `id` field of your mode:
- `SELECT * FROM hardmode_modes;`
- For each reward you want to add, you'll need a few things:
- The `id` of the mode you want to add the reward to
- `reward_level` defines at which level the Player is rewarded
- `reward_type` defines the reward, 0 = item, 1 = title, 2 = spell
- `reward_id` defines the id, depending on `reward_type`
	- if `reward_type` is 0 and `reward_id` is 46171, The reward is 'Furious Gladiators Frost Wyrm'
	- if `reward_type` is 1 and `reward_id` is 91, The reward is the Title 'Hero of Northrend'
	- if `reward_type` is 2 and `reward_id` is 3101, The Player would learn 'Alchemy (Journeyman)'
- `reward_count` defines the number of items the Player will get. Needs to be at least 1
- Then finally, run the following query on `acore-world`:
```
INSERT INTO hardmode_rewards (`mode`, `reward_level`, `reward_type`, `reward_id`, `reward_count`, `comment`) VALUES
(<hardmode_mode id>, <reward_level>, <reward_type: 0 = item, 1 = title, 2 = spell>, <reward_id>, <reward_count>, 'comment for the database');
```

- example:  
```
INSERT INTO hardmode_rewards (`mode`, `reward_level`, `reward_type`, `reward_id`, `reward_count`, `comment`) VALUES 
(4, 80, 0, 46708, 1, 'Deadly Gladiators Frost Wyrm'),
(5, 80, 0, 46171, 1, 'Furious Gladiators Frost Wyrm'),
(6, 80, 0, 47840, 1, 'Relentless Gladiators Frost Wyrm');
```

## Visible Buff/Debuff for the Custom Mode

- `HardMode.Inspect.Alert` already informs the inspecting Player (or via mouse-hovering) of the Modes the targeted Player has. However, this was not sufficient for me or my server
- The original HardMode module supports having ANY Aura-Spell applied to the Player, for each individual Challenge
	- This means you can have existing Auras be applied to Players while specific Challenges are active
	- You can make a custom mode
- I used [StoneHarry's WoW Spell Editor](https://github.com/stoneharry/WoW-Spell-Editor) to make custom Aura-Spells, which i use to visually indicate the Challenges the Player has active.
	- I will not go into detail how to create your own Aura-Spell here, theres a few tutorials, and it's relatively straightforward
- Inside your `acore-world` database there should be a `hardmode_auras` table, which holds the information we need
	- `mode` is simply the `id` of your desired hardmode inside `hardmode_modes`
	- `aura` is the Spell-ID of your desired Aura-Spell you want to have active on the Player as long as the Challenge is active
	- `description` is only used inside the database, use it like a comment field
- For each Aura-Spell you want to apply, run the following query
```
INSERT INTO hardmode_auras (`mode`, `aura`, `description`) VALUES 
(<hardmode_mode id>, <aura spell id>, 'comment for the database');
```

## Credits
- Thanks to [ZhengPeiRu21](https://github.com/ZhengPeiRu21) for creating the original original module which inspired the HardMode one.
- Thanks to [AnchyDev](https://github.com/AnchyDev) for creating the HardMode-module which this is just an updated version of.
