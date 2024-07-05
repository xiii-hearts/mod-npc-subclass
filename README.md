# ![logo](https://raw.githubusercontent.com/azerothcore/azerothcore.github.io/master/images/logo-github.png) AzerothCore

- Latest build status with azerothcore:
[![Build Status](https://github.com/xiii-hearts/mod-npc-subclass/workflows/core-build/badge.svg?branch=master&event=push)](https://github.com/xiii-hearts/mod-npc-subclass)



# NPC Subclass [Equipment Proficiency]

## Description
Adds an NPC that will teach all available Armors & Weapons Proficiency that are unavailable to all Classes, thus making a "subclass" like characters.

Part 1 of The SubClass Series Module.
- e.g - Priest will be able to learn Armor and Weapon proficiency like Plate Armour and Two-Handed Sword.

All of the procificiencies can be learned through purchasing the desired skills.

### Learnable Proficiencies/Skills

Armor Proficiencies
- Leather Armor Proficiency
- Mail Armor Proficiency
- Plate Armor Proficiency
- Shield Wielding Proficiency

Weapon Proficiencies
- Dual Wield Proficiency
- One-Handed Axe Proficiency
- Two-Handed Axe Proficiency
- One-Handed Sword Proficiency
- Two-Handed Sword Proficiency
- One-Handed Mace Proficiency
- Two-Handed Mace Proficiency
- Polearm Proficiency
- Dagger Proficiency
- Fist Weapon Proficiency
- Stave Proficiency
- Wand Proficiency
- Thrown Weapon Proficiency
- Throw Weapon Skill
- Bow Proficiency
- Crossbow Proficiency
- Gun Proficiency

## Installation
1) Unzip and place the module folder under the `modules` folder/directory of your AzerothCore source.
2) Rename `mod-npc-subclass-master` folder to `mod-npc-subclass`
3) Check `Modifying Core Section` below for further info before compiling.
4) After you're done with modifying the core, proceed to the next step.
5) Re-run cmake and launch a clean build of AzerothCore.
6) Put the SQL file to the world database.

## Modifying Core Section
1) Go to the Azerothcore Source/Root folder.
`\azerothcore-wotlk\src\server\game\Entities\Player`
2) Open up `PlayerStorage.cpp`
3) Find this line `if (!allowEquip && GetSkillValue(itemSkill) == 0)`
4) Paste this line above the it.

`switch (pProto->Class)`
`{`
`    case ITEM_CLASS_WEAPON:`
`    {`
`        if (pProto->SubClass & GetWeaponProficiency())`
`        {`
`            allowEquip = true;`
`            break;`
`        }`
`    }`
`    case ITEM_CLASS_ARMOR:`
`    {`
`        if (pProto->SubClass & GetArmorProficiency())`
`        {`
`            allowEquip = true;`
`            break;`
`        }`
`    }`
`}` 
 

5 Now you should be able to retained all of the learned proficiencies without losing it upon loggin out.

## How To Use
- Add the npc to the world by using GM command `.npc add 600001` or `.npc add temp 600001`

## Updates
- Added Warnings/Restrictions when player do not meet the cost and level requirement.
- Added Monetary Check Requirement.
- Added All of the Basic Equipment/Skills Proficiency to the NPC.
- Added Exception For Players With The Learned Abilities/Skills.
- Added Weapons Proficiency.
- Added Armor Proficiency.



