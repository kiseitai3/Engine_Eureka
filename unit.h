#ifndef UNIT_H
#define UNIT_H
#include <string>
#include <map>
#include <SDL.h>
#include "game.h"
#include "physics.h"
#include "sound_base.h"
#include "draw_base.h"
#include "scriptwrap.h"
#include "Timer.h"
#include <list>

//Forward declarations
class ProgressBar;
class ScriptWrap;

class Unit
{
    public:
        /** Default constructor */
        Unit(int BlitOrder, const std::string& path, math_point loc, SDL_Renderer &screen, Timer& t, bool hero = false, bool hasPBar = false);//PBar = progressbar
        /** Default destructor */
        ~Unit();
        //Question methods
        bool isMelee() const;
        //AI methods
        void LoadScript(ScriptWrap *script, const char *file);
        void MoveAI();
        void LoadAI(const char *file);
        void AttackAI(Unit* target);
        void ExecuteAI(Unit* target, const char axis = 'x');
        void MoveTowardsAI(double force, const char axis = 'x');

        //Timer
        void SetTimer(Timer* timerI);
        void Update_NewTime();
        void Update_OldTime();
        double GetTimeChange() const;

        //General getters and setters
        std::string GetName() const;
        Physics *GetPhysics() const;
        draw_base *GetDefaultDrawObject();
        void ToggleMelee();
        int GetHP() const;
        int GetAD() const;
        int GetAP() const;
        int GetAttackSpeed() const;
        int GetRange() const;
        int GetVisionRange() const;
        unsigned int GetID() const;
        double GetMovementSpeed() const;
        std::string GetType() const;
        int GetBlitOrder() const;
        void SetHP(int val);
        void SetAD(int val);
        void SetAP(int val);
        void SetAttackSpeed(int val);
        void SetRange(int val);
        void SetVisionRange(int val);
        void SetMovementSpeed(double val);
        void SetID(unsigned int id);
        void SetOwner(Game& game);
        bool GetDeath() const;
        void ToggleDeath();

        //Handle assets
        void PlaySounds(const math_point& screenLoc);
        void DrawImages();

        //Handle buffs
        void AddBuff(std::string buffName);
        void RemoveBuff(std::string buffName);
        bool BuffExists(std::string buffName);//Do not make const.
        void ApplyBuffs();

        //Physics handling
        std::string isColliding(Unit *target);
        void Update_Physics(Unit *target);
        void OnCollision(Unit *target, std::string side);

        //Player controls and behavior
        void ProcessKeyEvent(std::string key);
        void LoadKeyScript(const char *file);
        void LoadKeyBindings(const char *file);
        void ProcessMouseMovement(int x, int y);
        void ProcessMouseKey(unsigned int mouseButton, int x, int y);

    private:
        //structs
        struct movementTracker
        {
            int x;
            int y;
        };

        int blitOrder;
        int anim_counter, soundLoops; //!< Member variable "anim_counter"
        int hp, ad, ap, aSpeed, range, vRange, mana;//vRange is vision range. It's used for mobs and such. Can be used for fog of war
        int oldTime, t;//The first is the previous time. The second is the current new time.
        unsigned int ID; //Only used to check whether a unit was deleted from a level.
        double mSpeed;//Movement speed. Keep in mind it's pixels per seconds!
        double currentATime; //Use this variable to keep track of how fast the unit is attacking
        bool melee, dead;
        bool hasAI, showManaBar, showHPBar;
        std::map<std::string,draw_base*> images; //!< Member variable "draw"
        std::map<std::string,sound_base*> sounds; //!< Member variable "sound"
        std::list<std::string> buffs;
        std::string name, drawImage, soundName, type;
        math_point mapPoint, locBar; //mapPoint holds center point.
        data_base *DOM, *KeyDOM; //!< Member variable "dom"
        Physics *phys; //!< Member variable "phys"
        ScriptWrap *AI, *KeyScripts, *GeneralScripts, *BuffScripts;
        SDL_Renderer* ren;
        movementTracker movement;
        Timer *gameTime;
        ProgressBar *manaB, *hpB;
        Game* owner_ref;


};

#endif // UNIT_H
