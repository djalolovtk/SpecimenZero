#include "Canvas/ESP.h"
#include "Canvas/Bools.h"
#include "Canvas/StructsCommon.h"

#include "DarkManager.h"

#include <Substrate/SubstrateHook.h>
#include <Substrate/CydiaSubstrate.h>

#define libName OBFUSCATE("libil2cpp.so")

bool GodMode = false;
bool Keys = false;
bool Items = false;
bool UnKeys = false;
bool Woods = false;
bool Darts = false;
bool Bullets = false;

int (*org_TakeDamage)(void*inst);
int new_TakeDamage(void*inst) {
    if (inst != nullptr) {
      if (GodMode) {
          
         return 0;
        }
    }
    org_TakeDamage(inst);
}

void (*org_isChasing)(void*inst);
void new_isChasing(void*inst) {
    if (inst != nullptr) {
      if (GodMode) {
          
         return;
        }
    }
    org_isChasing(inst);
}

void (*org_PlayerItems)(void*inst);
void new_PlayerItems(void*inst) {
    if (inst != nullptr) {      
        if (Keys) {
            *(bool*) ((uint32_t) inst + 0x30) = true;
            *(bool*) ((uint32_t) inst + 0x31) = true;
            *(bool*) ((uint32_t) inst + 0x32) = true;
            *(bool*) ((uint32_t) inst + 0x33) = true;
            *(bool*) ((uint32_t) inst + 0x34) = true;
            *(bool*) ((uint32_t) inst + 0x35) = true;
            *(bool*) ((uint32_t) inst + 0x36) = true;
            *(bool*) ((uint32_t) inst + 0x37) = true;
            *(bool*) ((uint32_t) inst + 0x38) = true;
            *(bool*) ((uint32_t) inst + 0x39) = true;
            *(bool*) ((uint32_t) inst + 0x3A) = true;
            *(bool*) ((uint32_t) inst + 0x3B) = true;
            *(bool*) ((uint32_t) inst + 0x3C) = true;          
        }     
        if (Items) {
            *(bool*) ((uint32_t) inst + 0x44) = true;
            *(bool*) ((uint32_t) inst + 0x4C) = true;
            *(bool*) ((uint32_t) inst + 0x4D) = true;
            *(bool*) ((uint32_t) inst + 0x4E) = true;
            *(bool*) ((uint32_t) inst + 0x4F) = true;
            *(bool*) ((uint32_t) inst + 0x50) = true;
            *(bool*) ((uint32_t) inst + 0x51) = true;
            *(bool*) ((uint32_t) inst + 0x52) = true;
            *(bool*) ((uint32_t) inst + 0x53) = true;
            *(bool*) ((uint32_t) inst + 0x54) = true;
            *(bool*) ((uint32_t) inst + 0x55) = true;
            *(bool*) ((uint32_t) inst + 0x56) = true;
            *(bool*) ((uint32_t) inst + 0x57) = true;
            *(bool*) ((uint32_t) inst + 0x58) = true;
        }
        if (UnKeys) {
            *(int*) ((uint32_t) inst + 0x40) = 99999;
        }
        if (Darts) {
            *(int*) ((uint32_t) inst + 0x20) = 99999;
        }
        if (Woods) {
            *(int*) ((uint32_t) inst + 0x2C) = 99999;
        }
        if (Bullets) {
            *(int*) ((uint32_t) inst + 0x18) = 99999;
            *(int*) ((uint32_t) inst + 0x1C) = 99999;
        }
    }
    org_PlayerItems(inst);
}

void *(*get_transform)(void*inst);
Vector3 (*get_position)(void*inst);
void *(*get_camera)();
Vector3 (*worldToScreen)(void *cam, Vector3 pos);
Vector3 getPosition(void *transform) {
    return get_position(get_transform(transform));
} 





void DrawESP(ESP esp, int screenWidth, int screenHeight) {
   
    
  if(Esp) {  

       for (int i = 0; i < players.size(); i++) { 
        void *Player;         
        if (i < players.size()) Player = players[i];      
        if (Player != NULL && get_camera() != NULL) {  
        
            int get_height = *(int*) (getAbsoluteAddress("libil2cpp.so",0x938A80));
            int get_width = *(int*) (getAbsoluteAddress("libil2cpp.so",0x9389FC));
            auto SetResolution = (void (*)(int, int, bool)) (getAbsoluteAddress("libil2cpp.so",0x938E20));
            SetResolution(screenWidth, screenHeight, true);
     
            get_height = screenHeight;   
            get_width = screenWidth;    
                                             
            auto isPlayerLocation = worldToScreen(get_camera(),getPosition(Player));
            if (isPlayerLocation.z < 1.f) continue; 
            
            Vector3 HeadPos = getPosition(Player);  
            Vector3 Head = Vector3(HeadPos.x, HeadPos.y + 0.6,HeadPos.z);
           
          
            Vector3 BottomPos = getPosition(Player);
            Vector3 Bottom = Vector3(BottomPos.x, BottomPos.y - 1.2,BottomPos.z);
              
         
            auto HeadPosition = worldToScreen(get_camera(),Head);
            auto BottomPosition = worldToScreen(get_camera(),Bottom);  
            
            if (HeadPosition.z < 1.f) continue;
            if (BottomPosition.z < 1.f) continue;
            
            float boxHeight = abs(HeadPosition.y - BottomPosition.y);
            float boxWidth = boxHeight * 0.60f;          
            Rect PlayerRect(HeadPosition.x - (boxWidth / 2), (screenHeight - HeadPosition.y - 45), boxWidth, boxHeight);                                                                                           
            float isBoxWidth = (float) screenWidth / 10.0f;
            float isBoxHeight = (float) screenHeight / 8.0f;

  
            if (EspLine) {                 
                esp.DrawLine(Color::White(), 1,Vector2(screenWidth / 2, 0),Vector2(HeadPosition.x,screenHeight - HeadPosition.y - 45 )); 
            }       
            if(EspBox){
                esp.DrawBox(Color::White(), 1, PlayerRect);                 
            }   
            if(EspObject) {        
             std::string Allplayers;     
             Allplayers += "Counter : ";
             Allplayers += std::to_string((int32_t) players.size());
              esp.DrawText(Color::White(), Allplayers.c_str(), Vector2(screenWidth / 2 ,screenHeight / 2), 35.0f);      
            }   
          }                    
       }
     }
}
  
void (*org_EnemyEntity)(...);
void new_EnemyEntity(void*entity) {
    if (entity != NULL & entity != NULL && Esp) {
        
        if (!playerFind(entity)) players.push_back(entity);
        if (players.size() > 10) {
            players.clear();
        }
    }
    clearPlayers();
    org_EnemyEntity(entity);
}

void (*org_SpecimenEntity)(...);
void new_SpecimenEntity(void*entity) {
    if (entity != NULL & entity != NULL && Esp) {
        
        if (!playerFind(entity)) players.push_back(entity);
        if (players.size() > 10) {
            players.clear();
        }
    }
    clearPlayers();
    org_SpecimenEntity(entity);
}


void MainThread() {
    
     do {
        sleep(1);
    } while (!isLibraryLoaded(libName));

    // Structur
    get_transform = (void *(*)(void *)) getAbsoluteAddress(libName,0x9ABE88);
    get_position = (Vector3 (*)(void*)) getAbsoluteAddress(libName,0xD54660);
    get_camera = (void *(*)()) getAbsoluteAddress(libName,0x9A9BC4);
    worldToScreen = (Vector3 (*)(void *, Vector3)) getAbsoluteAddress(libName,0x9A95C4);
    
    // Entity List 
    MSHookFunction((void *) getAbsoluteAddress(libName,0x3A50A0),(void *) &new_EnemyEntity, (void **) &org_EnemyEntity);  
    MSHookFunction((void *) getAbsoluteAddress(libName,0x3CDF2C),(void *) &new_SpecimenEntity,(void **) &org_SpecimenEntity); 
    
    // Feature
    MSHookFunction((void *) getAbsoluteAddress(libName,0x319A20),(void *) &new_TakeDamage,(void **) &org_TakeDamage);  
    MSHookFunction((void *) getAbsoluteAddress(libName,0x3A6558),(void *) &new_isChasing,(void **) &org_isChasing);  
    MSHookFunction((void *) getAbsoluteAddress(libName,0x2F3D00),(void *) &new_PlayerItems,(void **) &org_PlayerItems);
    
    
}
