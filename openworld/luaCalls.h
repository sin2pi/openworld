//
//  luaCalls.h
//  openworld
//
//  Created by martin dionisi on 24/3/16.
//  Copyright (c) 2016 martin dionisi. All rights reserved.
//

#ifndef openworld_luaCalls_h
#define openworld_luaCalls_h

#include "npc.h"
#include "Item.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

extern vector<cNpc*>npc;
extern vector<cItem*>item;

int setNpc(lua_State *L){ // int x int y int spd
    
    int arg = lua_gettop(L);
    
    int x = (int)lua_tonumber(L,-arg);
    int y = (int)lua_tonumber(L,-arg+1);
    int xs = (int)lua_tonumber(L,-arg+2);
    int ys = (int)lua_tonumber(L,-arg+2);
    int nx;
    int hp;
    
    string file;
  
    if(lua_isnumber(L,-arg+3)){
        file = "/Users/martindionisi/Desktop/openworld/openworld/Luigi.bmp";
        hp = lua_tonumber(L,-arg+3);
        nx = 3;
    }
    const char *f =file.c_str();
    npc.push_back(new cNpc(x,y,20,40,xs,ys,20,20,hp,f,nx));
    
    return 0;
}

int setNpcSpeed(lua_State *L){ // int id - float spd
    float spd = lua_tonumber(L,-lua_gettop(L)+1);
    npc.at(lua_tonumber(L,-lua_gettop(L)))->setSpeed(spd);
    return 0;
}

int setNpcPos(lua_State *L){ // int id - int x - int y
    int x = lua_tonumber(L, -lua_gettop(L)+1);
    int y = lua_tonumber(L, -lua_gettop(L)+2);
    npc.at(lua_tonumber(L,-lua_gettop(L)))->setPos(x,y);
    return 0;
}

int setNpcRep(lua_State *L){
    int r = lua_tonumber(L,-lua_gettop(L)+1);
    npc.at(lua_tonumber(L,-lua_gettop(L)))->setRep(r);
    return 0;
}

int setNpcPath(lua_State *L){
    int w = lua_tonumber(L,-lua_gettop(L)+1);
    int h = lua_tonumber(L,-lua_gettop(L)+2);
    npc.at(lua_tonumber(L,-lua_gettop(L)))->setSquarePath(w,h);
    return 0;
}

int npcstart(lua_State *L){
    npc.at(lua_tonumber(L,-lua_gettop(L)))->startPath(lua_tonumber(L,-lua_gettop(L)+1));
    return 0;
}

int npcstop(lua_State *L){
    npc.at(lua_tonumber(L,-lua_gettop(L)))->stopPath();
    return 0;
}

int setNpcRandPath(lua_State *L){
    int ix = lua_tonumber(L,-lua_gettop(L)+1);
    int iy = lua_tonumber(L,-lua_gettop(L)+2);
    int hr = lua_tonumber(L,-lua_gettop(L)+3);
    int vr = lua_tonumber(L,-lua_gettop(L)+4);
    int tr = lua_tonumber(L,-lua_gettop(L)+5);
    npc.at(lua_tonumber(L,-lua_gettop(L)))->setRandPath(ix, iy, hr, vr, tr);
    
    return 1;
}

void RegisterCalls(lua_State *L)
{
    lua_register(L,"setNpc",setNpc);
    lua_register(L,"npcPos",setNpcPos);
    lua_register(L,"npcSpeed",setNpcSpeed);
    lua_register(L,"npcRep",setNpcRep);
    lua_register(L,"npcStart",npcstart);
    lua_register(L,"npcStop",npcstop);
    lua_register(L,"npcPath",setNpcPath);
    lua_register(L,"npcRandPath",setNpcRandPath);
}


#endif