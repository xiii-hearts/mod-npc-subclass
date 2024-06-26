/*
# NPC - Equipment Proficiency #

- This module is based on Azerothcore's Module NPC-All-Mounts (https://github.com/azerothcore/mod-npc-all-mounts).
- Repurposed as NPC [Equipment Proficiency]

### Description ###
------------------------------------------------------------------------------------------------------------------
- Adds NPCs that will teach all available Armors, Weapons, Skills & Spells Proficiency that is unavailable to the current Class.
- This module focus on Equipment Proficiency (Armors & Weapons)
- Creating SubClasses like character(s).

### To-Do ###
------------------------------------------------------------------------------------------------------------------
- Add Warnings/Restrictions when player do not meet the cost and level requirement.
- Add Basic Equipment/Skills Proficiency NPC.
- Add Intermediate Skills Proficiency NPC,
- Add Advanced Skills Proficiency NPC,
- Test & Tweak SubClasses Skills & Spells (Balancing).

### Data ###
------------------------------------------------------------------------------------------------------------------
- Type: NPC
- Script: SubClassEq_NPC
- Config: Yes
- SQL: Yes
- NPC ID: 600001


### Updates ###
------------------------------------------------------------------------------------------------------------------
- Added Exception For Players With The Learned Abilities/Skills.
- Added Weapons Proficiency.
- Added Armor Proficiency.

*/

#include "Config.h"
#include "ScriptMgr.h"
#include "Chat.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"

bool SubClassAnnounceModule;
bool SubClassEnableAI;

class SubClassConfig : public WorldScript
{
public:
    SubClassConfig() : WorldScript("SubClassConfig_conf") { }

    void OnBeforeConfigLoad(bool reload) override
    {
        if (!reload) {
            SubClassAnnounceModule = sConfigMgr->GetOption<bool>("SubClassNPC.Announce", 1);
            SubClassEnableAI = sConfigMgr->GetOption<bool>("SubClassNPC.EnableAI", 1);
        }
    }
};

class SubClassAnnounce : public PlayerScript
{

public:

    SubClassAnnounce() : PlayerScript("SubClassAnnounce") {}

    void OnLogin(Player* player)
    {
        // Announce Module
        if (SubClassAnnounceModule)
        {
            ChatHandler(player->GetSession()).SendSysMessage("This server is running the |cff4CFF00SubClassNPC |rmodule.");
        }
    }
};

class SubClass_NPC : public CreatureScript
{

public:

    SubClass_NPC() : CreatureScript("SubClass_NPC") {}

    bool OnGossipHello(Player* player, Creature* creature)
    {
        AddGossipItemFor(player, GOSSIP_ICON_TABARD, "Leather Armor Proficiency [20 Silv]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        AddGossipItemFor(player, GOSSIP_ICON_TABARD, "Mail Armor Proficiency [2 Golds]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
        AddGossipItemFor(player, GOSSIP_ICON_TABARD, "Plate Armor Proficiency [3 Golds]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Shield Wielding Proficiency [30 Silv]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "One-Handed Axe Proficiency [10 Silv]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Two-Handed Axe Proficiency [10 Silv]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "One-Handed Sword Proficiency [10 Silv]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Two-Handed Sword Proficiency [10 Silv]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "One-Handed Mace Proficiency [10 Silv]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Two-Handed Mace Proficiency [10 Silv]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Polearm Proficiency [1 Gold]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Dagger Proficiency [10 Silv]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Fist Weapon Proficiency [10 Silv]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Stave Proficiency [10 Silv]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Wand Proficiency [10 Silv]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 15);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Thrown Weapon Proficiency [10 Silv]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 16);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Bow Proficiency [10 Silv]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 17);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Crossbow Proficiency [10 Silv]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 18);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Gun Proficiency [10 Silv]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 19);
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Be Seeing You Again Next Time", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 100);

        SendGossipMenuFor(player, 601014, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* /* creature */, uint32 sender, uint32 uiAction) override
    {
        player->PlayerTalkClass->ClearMenus();

        if (sender != GOSSIP_SENDER_MAIN)
            return false;

        switch (uiAction)
        {
        case GOSSIP_ACTION_INFO_DEF + 1:

            if (player->HasSpell(9077))
            {
                ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                player->PlayerTalkClass->SendCloseGossip();
                return true;
                break;
            }
            else
            {
                if (player->HasEnoughMoney(2000))

                    // Set Skills
                    player->SetSkill(414, 0, 1, 1);  // Leather Armor Skill

                    // Learn Spells
                    player->learnSpell(9077);   // Leather

                    // Cost
                    player->ModifyMoney(-2000);   // 20 Silver

                    // Chat Indicator
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now able to wear Leather Armor");

                    // Goodbye
                    player->PlayerTalkClass->SendCloseGossip();
                    return true;
                    break;
            }
            return true;
            break;

        case GOSSIP_ACTION_INFO_DEF + 2:

            if (player->HasSpell(8737))
            {
                ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                player->PlayerTalkClass->SendCloseGossip();
                return true;
                break;
            }
            else
            {
                if (player->HasEnoughMoney(20000))

                    // Set Skills
                    player->SetSkill(413, 0, 1, 1);  // Mail Armor Skill

                    // Learn Spells
                    player->learnSpell(8737);   // Mail

                    // Cost
                    player->ModifyMoney(20000);   // 2 Golds

                    // Chat Indicator
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now able to wear Mail Armor");

                    // Goodbye
                    player->PlayerTalkClass->SendCloseGossip();
                    return true;
                    break;
            }
            return true;
            break;

        case GOSSIP_ACTION_INFO_DEF + 3:

            if (player->HasSpell(750))
            {
                ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                player->PlayerTalkClass->SendCloseGossip();
                return true;
                break;
            }
            else
            {
                if (player->HasEnoughMoney(30000))

                    // Set Skills
                    player->SetSkill(293, 0, 1, 1);  // Plate Armor Skill

                    // Learn Spells
                    player->learnSpell(750);   // Plate

                    // Cost
                    player->ModifyMoney(-30000);   // 3 Golds 

                    // Chat Indicator
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now able to wear Plate Armor");

                    // Goodbye
                    player->PlayerTalkClass->SendCloseGossip();
                    return true;
                    break;
            }
            return true;
            break;

        case GOSSIP_ACTION_INFO_DEF + 4:

            if (player->HasSpell(9116))
            {
                ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                player->PlayerTalkClass->SendCloseGossip();
                return true;
                break;
            }
            else
            {
                if (player->HasEnoughMoney(3000))

                    // Set Skills
                    player->SetSkill(433, 0, 1, 1);  // Shield Armor Skill

                    // Learn Spells
                    player->learnSpell(9116);   // Shield
                    player->learnSpell(107);    // Block

                    // Cost
                    player->ModifyMoney(-3000);   // 30 Silvers

                    // Chat Indicator
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now able to wield Shield");

                    // Goodbye
                    player->PlayerTalkClass->SendCloseGossip();
                    return true;
                    break;
            }
            return true;
            break;

        case GOSSIP_ACTION_INFO_DEF + 5:

            if (player->HasSpell(196))
            {
                ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                player->PlayerTalkClass->SendCloseGossip();
                return true;
                break;
            }
            else
            {
                if (player->HasEnoughMoney(1000))

                    // Set Skills
                    player->SetSkill(44, 0, 1, 1);   // One-Handed Axe

                    // Learn Spells
                    player->learnSpell(196);   // Axe

                    // Cost
                    player->ModifyMoney(-1000);   // 10 Silvers

                    // Chat Indicator
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now able to wield One-Handed Axe");

                    // Goodbye
                    player->PlayerTalkClass->SendCloseGossip();
                    return true;
                    break;
            }
            return true;
            break;

        case GOSSIP_ACTION_INFO_DEF + 6:
        
            if (player->HasSpell(197))
            {
                ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                player->PlayerTalkClass->SendCloseGossip();
                return true;
                break;
            }
            else
            {
                if (player->HasEnoughMoney(1000))

                    // Set Skills
                    player->SetSkill(172, 0, 1, 1);   // Two-Handed Axe

                    // Learn Spells
                    player->learnSpell(197);   // Two-Handed Axe

                    // Cost
                    player->ModifyMoney(-1000);   // 10 Silvers

                    // Chat Indicator
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now able to wield Two-Handed Axe");

                    // Goodbye
                    player->PlayerTalkClass->SendCloseGossip();
                    return true;
                    break;
            }
            return true;
            break;

        case GOSSIP_ACTION_INFO_DEF + 7:

            if (player->HasSpell(201))
            {
                ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                player->PlayerTalkClass->SendCloseGossip();
                return true;
                break;
            }
            else
            {
                if (player->HasEnoughMoney(1000))

                    // Set Skills
                    player->SetSkill(43, 0, 1, 1);   // One-Handed Sword

                    // Learn Spells
                    player->learnSpell(201);   // One-Handed Sword

                    // Cost
                    player->ModifyMoney(-1000);   // 10 Silvers

                    // Chat Indicator
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now able to wield One-Handed Sword");

                    // Goodbye
                    player->PlayerTalkClass->SendCloseGossip();
                    return true;
                    break;
            }
            return true;
            break;

        case GOSSIP_ACTION_INFO_DEF + 8:

            if (player->HasSpell(202))
            {
                ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                player->PlayerTalkClass->SendCloseGossip();
                return true;
                break;
            }
            else
            {
                if (player->HasEnoughMoney(1000))

                    // Set Skills
                    player->SetSkill(55, 0, 1, 1);   // Two-Handed Sword

                    // Learn Spells
                    player->learnSpell(202);   // Two-Handed Sword

                    // Cost
                    player->ModifyMoney(-1000);   // 10 Silvers

                    // Chat Indicator
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now able to wield Two-Handed Sword");

                    // Goodbye
                    player->PlayerTalkClass->SendCloseGossip();
                    return true;
                    break;
            }
            return true;
            break;

        case GOSSIP_ACTION_INFO_DEF + 9:

            if (player->HasSpell(198))
            {
                ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                player->PlayerTalkClass->SendCloseGossip();
                return true;
                break;
            }
            else
            {
                if (player->HasEnoughMoney(1000))

                    // Set Skills
                    player->SetSkill(54, 0, 1, 1);   // One-Handed Mace

                    // Learn Spells
                    player->learnSpell(198);   // One-Handed Mace

                    // Cost
                    player->ModifyMoney(-1000);   // 10 Silvers

                    // Chat Indicator
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now able to wield One-Handed Mace");

                    // Goodbye
                    player->PlayerTalkClass->SendCloseGossip();
                    return true;
                    break;
            }
            return true;
            break;

        case GOSSIP_ACTION_INFO_DEF + 10:

            if (player->HasSpell(199))
            {
                ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                player->PlayerTalkClass->SendCloseGossip();
                return true;
                break;
            }
            else
            {
                if (player->HasEnoughMoney(1000))

                    // Set Skills
                    player->SetSkill(160, 0, 1, 1);   // Two-Handed Mace

                    // Learn Spells
                    player->learnSpell(199);   // Two-Handed Mace

                    // Cost
                    player->ModifyMoney(-1000);   // 10 Silvers

                    // Chat Indicator
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now able to wield Two-Handed Mace");

                    // Goodbye
                    player->PlayerTalkClass->SendCloseGossip();
                    return true;
                    break;
            }
            return true;
            break;

        case GOSSIP_ACTION_INFO_DEF + 11:

            if (player->HasSpell(200))
            {
                ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                player->PlayerTalkClass->SendCloseGossip();
                return true;
                break;
            }
            else
            {
                if (player->HasEnoughMoney(10000))

                    // Set Skills
                    player->SetSkill(229, 0, 1, 1);   // Polearm

                    // Learn Spells
                    player->learnSpell(200);   // Polearm

                    // Cost
                    player->ModifyMoney(-10000);   // 1 Gold

                    // Chat Indicator
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now able to wield Polearm");

                    // Goodbye
                    player->PlayerTalkClass->SendCloseGossip();
                    return true;
                    break;
            }
            return true;
            break;

        case GOSSIP_ACTION_INFO_DEF + 12:

            if (player->HasSpell(1180))
            {
                ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                player->PlayerTalkClass->SendCloseGossip();
                return true;
                break;
            }
            else
            {
                if (player->HasEnoughMoney(1000))

                    // Set Skills
                    player->SetSkill(173, 0, 1, 1);   // Dagger

                    // Learn Spells
                    player->learnSpell(1180);   // Dagger

                    // Cost
                    player->ModifyMoney(-1000);   // 10 Silvers

                    // Chat Indicator
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now able to wield Dagger");

                    // Goodbye
                    player->PlayerTalkClass->SendCloseGossip();
                    return true;
                    break;
            }
            return true;
            break;

        case GOSSIP_ACTION_INFO_DEF + 13:

            if (player->HasSpell(15590))
            {
                ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                player->PlayerTalkClass->SendCloseGossip();
                return true;
                break;
            }
            else
            {
                if (player->HasEnoughMoney(1000))

                    // Set Skills
                    player->SetSkill(473, 0, 1, 1);   // Fist Weapon

                    // Learn Spells
                    player->learnSpell(15590);   // Fist Weapon

                    // Cost
                    player->ModifyMoney(-1000);   // 10 Silvers

                    // Chat Indicator
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now able to use Fist Weapon");

                    // Goodbye
                    player->PlayerTalkClass->SendCloseGossip();
                    return true;
                    break;
            }
            return true;
            break;

        case GOSSIP_ACTION_INFO_DEF + 14:

            if (player->HasSpell(227))
            {
                ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                player->PlayerTalkClass->SendCloseGossip();
                return true;
                break;
            }
            else
            {
                if (player->HasEnoughMoney(1000))

                    // Set Skills
                    player->SetSkill(136, 0, 1, 1);   // Stave

                    // Learn Spells
                    player->learnSpell(227);   // Stave

                    // Cost
                    player->ModifyMoney(-1000);   // 10 Silvers

                    // Chat Indicator
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now able to wield Stave");

                    // Goodbye
                    player->PlayerTalkClass->SendCloseGossip();
                    return true;
                    break;
            }
            return true;
            break;

        case GOSSIP_ACTION_INFO_DEF + 15:

            if (player->HasSpell(5009))
            {
                ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                player->PlayerTalkClass->SendCloseGossip();
                return true;
                break;
            }
            else
            {
                if (player->HasEnoughMoney(1000))

                    // Set Skills
                    player->SetSkill(228, 0, 1, 1);   // Wand

                    // Learn Spells
                    player->learnSpell(5009);   // Wand
                    player->learnSpell(5019);   // Shooting Wand

                    // Cost
                    player->ModifyMoney(-1000);   // 10 Silvers

                    // Chat Indicator
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now able to cast with Wand");

                    // Goodbye
                    player->PlayerTalkClass->SendCloseGossip();
                    return true;
                    break;
            }
            return true;
            break;

        case GOSSIP_ACTION_INFO_DEF + 16:

            if (player->HasSpell(2567))
            {
                ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                player->PlayerTalkClass->SendCloseGossip();
                return true;
                break;
            }
            else
            {
                if (player->HasEnoughMoney(1000))

                    // Set Skills
                    player->SetSkill(176, 0, 1, 1);   // Thrown Weapon

                    // Learn Spells
                    player->learnSpell(2567);   // Thrown Weapon

                    // Cost
                    player->ModifyMoney(-1000);   // 10 Silvers

                    // Chat Indicator
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now able to use Thrown Weapon");

                    // Goodbye
                    player->PlayerTalkClass->SendCloseGossip();
                    return true;
                    break;
            }
            return true;
            break;

        case GOSSIP_ACTION_INFO_DEF + 17:

            if (player->HasSpell(264))
            {
                ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                player->PlayerTalkClass->SendCloseGossip();
                return true;
                break;
            }
            else
            {
                if (player->HasEnoughMoney(1000))

                    // Set Skills
                    player->SetSkill(45, 0, 1, 1);   // Bow

                    // Learn Spells
                    player->learnSpell(264);    // Bow
                    player->learnSpell(3018);   // Shooting Bow

                    // Cost
                    player->ModifyMoney(-1000);   // 10 Silvers

                    // Chat Indicator
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now able to use shoot Bow");

                    // Goodbye
                    player->PlayerTalkClass->SendCloseGossip();
                    return true;
                    break;
            }
            return true;
            break;

        case GOSSIP_ACTION_INFO_DEF + 18:

            if (player->HasSpell(5011))
            {
                ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                player->PlayerTalkClass->SendCloseGossip();
                return true;
                break;
            }
            else
            {
                if (player->HasEnoughMoney(1000))

                    // Set Skills
                    player->SetSkill(226, 0, 1, 1);   // Crossbow

                    // Learn Spells
                    player->learnSpell(5011);   // Crossbow
                    player->learnSpell(3018);   // Shooting Crossbow

                    // Cost
                    player->ModifyMoney(-1000);   // 10 Silvers

                    // Chat Indicator
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now able to use shoot Crossbow");

                    // Goodbye
                    player->PlayerTalkClass->SendCloseGossip();
                    return true;
                    break;
            }
            return true;
            break;

        case GOSSIP_ACTION_INFO_DEF + 19:

            if (player->HasSpell(266))
            {
                ChatHandler(player->GetSession()).SendSysMessage("You are competent with this skill already");
                player->PlayerTalkClass->SendCloseGossip();
                return true;
                break;
            }
            else
            {
                if (player->HasEnoughMoney(1000))

                    // Set Skills
                    player->SetSkill(46, 0, 1, 1);   // Gun

                    // Learn Spells
                    player->learnSpell(266);   // Gun
                    player->learnSpell(3018);   // Shooting Gun

                    // Cost
                    player->ModifyMoney(-1000);   // 10 Silvers

                    // Chat Indicator
                    ChatHandler(player->GetSession()).SendSysMessage("|cff4CFF00You're now able to use shoot Gun");

                    // Goodbye
                    player->PlayerTalkClass->SendCloseGossip();
                    return true;
                    break;
            }
            return true;
            break;

        case GOSSIP_ACTION_INFO_DEF + 100:

            // Goodbye
            player->PlayerTalkClass->SendCloseGossip();
            break;
        }

        return true;
    }


    // Passive Emotes
    struct NPC_PassiveAI : public ScriptedAI
    {
        NPC_PassiveAI(Creature * creature) : ScriptedAI(creature) { }

        uint32 Choice;
        uint32 MessageTimer;

        // Called once when client is loaded
        void Reset()
        {
            MessageTimer = urand(60000, 180000); // 1-3 minutes
        }

        // Called at World update tick
        void UpdateAI(const uint32 diff)
        {
            if (SubClassEnableAI)
            {
                if (MessageTimer <= diff)
                {
                    // Make a random message choice
                    Choice = urand(1, 3);

                    switch (Choice)
                    {
                    case 1:
                    {
                        me->Say("I can teach you anything and everything!", LANG_UNIVERSAL);
                        me->HandleEmoteCommand(EMOTE_ONESHOT_WAVE);
                        MessageTimer = urand(60000, 180000);
                        break;
                    }
                    case 2:
                    {
                        me->Say("You should learn to subclassing!", LANG_UNIVERSAL);
                        me->HandleEmoteCommand(EMOTE_ONESHOT_WAVE);
                        MessageTimer = urand(60000, 180000);
                        break;
                    }
                    case 3:
                    {
                        me->Say("Wield any weapon that you have always wanted!.", LANG_UNIVERSAL);
                        me->HandleEmoteCommand(EMOTE_ONESHOT_WAVE);
                        MessageTimer = urand(60000, 180000);
                        break;
                    }
                    default:
                    {
                        me->Say("Have you ever wanted to wear different type of armor?.", LANG_UNIVERSAL);
                        me->HandleEmoteCommand(EMOTE_ONESHOT_WAVE);
                        MessageTimer = urand(60000, 180000);
                        break;
                    }
                    }
                }
                else { MessageTimer -= diff; }
            }
        };
    };

    // CREATURE AI
    CreatureAI * GetAI(Creature * creature) const override
    {
        return new NPC_PassiveAI(creature);
    }
};

void AddSubClassNPCScripts()
{
    new SubClassConfig();
    new SubClassAnnounce();
    new SubClass_NPC();
}
