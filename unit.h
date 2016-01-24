#ifndef UNIT_H
#define UNIT_H
#include <string>
#include <map>
#include <list>
#include "Timer.h"
#include "ai_store.h"
#include "typedefs.h"

//Engine name space macro
//ENGINE_NAMESPACE

//Forward declarations
class ProgressBar;
class ScriptWrap;
class sound_base;
class draw_base;
class data_base;
class Physics;
class Game;
class SDL_Renderer;

//General purpose script loader
void LoadScript(ScriptWrap* script, const char *file);

class Unit
{
    public:
        /** Default constructor */
        Unit(int BlitOrder, const std::string& path, math_point loc, SDL_Renderer* screen, size_t t_id, bool hero = false, bool hasPBar = false);//PBar = progressbar
        /** Default destructor */
        ~Unit();
        //Question methods
        bool isMelee() const;
        bool isNPC() const;

        //AI methods
        void MoveAI();
        void LoadAI(const char *file);
        void AttackAI(Unit* target);
        void ExecuteAI(Unit* target, const char axis = 'x');
        void MoveTowardsAI(double force, const char axis = 'x');

        //Timer
        void SetTimer(size_t timer_id);
        void Update_NewTime();
        void Update_OldTime();
        double GetTimeChange() const;

        //General getters and setters
        std::string GetName() const;
        Physics *GetPhysics() const;
        draw_base *GetDefaultDrawObject();
        void ToggleMelee();
        int GetHP() const;
        int GetMana() const;
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
        void SetMana(int val);
        void SetAD(int val);
        void SetAP(int val);
        void SetAttackSpeed(int val);
        void SetRange(int val);
        void SetVisionRange(int val);
        void SetMovementSpeed(double val);
        void SetID(unsigned int id);
        void SetOwner(Game* game);
        bool GetDeath() const;
        void ToggleDeath();
        void SetCurrentAnimation(const std::string& name);
        void SetCurrentSound(const std::string& name);
        void copy(const Unit& obj);

        //Handle assets
        void PlaySounds(const math_point& screenLoc);
        void DrawImages();
        static void RotateSprite(draw_base* sprite, double degrees);
        static void FlipSprite(draw_base* sprite, size_t direction = NOFLIP);
        static void ResetRotation(draw_base* sprite);

        //Handle buffs
        void AddBuff(std::string buffName);
        void RemoveBuff(std::string buffName);
        bool BuffExists(std::string buffName);//Do not make const.
        void ApplyBuffs();

        //Physics handling
        std::string isColliding(Unit *target);
        void Update_Physics(Unit *target);
        void OnCollision(Unit *target, std::string side);

        //Overloads

        //Global
        static AIStore ai;

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
        size_t gameTime;
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
        ScriptWrap *AI, *GeneralScripts, *BuffScripts;
        SDL_Renderer* ren;
        movementTracker movement;
        ProgressBar *manaB, *hpB;
        Game* owner_ref;
};

//End of namespace macro
//ENGINE_NAMESPACE_END
#endif // UNIT_H
