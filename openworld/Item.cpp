//  Item.cpp
//  openworld
//
//  Created by martin dionisi on 2/12/15.
//  Copyright (c) 2015 martin dionisi. All rights reserved.
//

#include "Item.h"

extern SDL_Rect camera;

cItem::cItem(int xp,int yp,int w,int h,float vel,string file,string script,int index)
{
    box.x = xp;
    box.y = yp;
    box.w = w;
    box.h = h;
    pos.x = xp;
    pos.y = yp;
    pos.w = w;
    pos.h = h;
    xvel = yvel = vel;
    filename = file;
    const char *f =file.c_str();
    grabed = false;
    image = SDL_LoadBMP(f);
    sf = script;
    txt = SDL_CreateTextureFromSurface(SDL_GetRenderer(SDL_GetWindowFromID(1)),image);
    id = index;
}


void cItem::Interact(vector<cItem*> items)
{
    for(int i = 0;i<items.size();i++)
    {
        if(box.x == items.at(i)->box.x && box.y == items.at(i)->box.y)
        {
            continue;
        }
        else if(Physics::collision(&pos,&items.at(i)->pos))
        {
            if(xvel!=0){
                Physics::elasticCollision(xvel,20,items.at(i)->xvel,20);
                pos.x += xvel;
                box.x += xvel;
                items.at(i)->pos.x += items.at(i)->xvel;
                items.at(i)->box.x += items.at(i)->xvel;
            }
            if(yvel!=0) {
                Physics::elasticCollision(yvel,20,items.at(i)->yvel,20);
                pos.y += yvel;
                box.y += yvel;
                items.at(i)->pos.y += items.at(i)->yvel;
            }
            
        }
    }
    if(xvel > 0){
        //int xs = xvel;
        xvel -= 0.05;
        if(xvel <= 0)
            xvel = 0;
        pos.x += xvel;
    }
    else if(xvel < 0){
        //int xs = xvel;
        xvel += 0.05;
        if(xvel >= 0)
            xvel = 0;
        pos.x += xvel;
    }
    else xvel = 0;
    if(yvel > 0){
        //int ys = yvel;
        yvel -= 0.05;
        if(yvel <= 0)
            yvel = 0;
        pos.y += yvel;
    }
    else if(yvel < 0){
        //int xs = xvel;
        yvel += 0.05;
        if(yvel >= 0)
            yvel = 0;
        pos.y += yvel;
    }
    else yvel = 0;
}

void cItem::Render(light w)
{
    float amb = w.getAmb();
    box.x = (int)pos.x;
    box.y = (int)pos.y;
    SDL_Rect box1 = {static_cast<Sint16>(box.x-camera.x),static_cast<Sint16>(box.y-camera.y),box.w,box.h};
    if(Physics::circlecol(&box1, 600-camera.x, 700-camera.y, 4000))
    {
        float a = w.resolvePointLight(600-camera.x, 700-camera.y,box1.x,box1.y);
        float c1 = a*255;
        float c2 = a*255;
        float c3 = a*255;
        if(c1 > 255)
            c1 = 255;
        if(c2 > 255)
            c2 = 255;
        if(c3 > 255)
            c3 = 255;
        SDL_SetTextureColorMod(txt,c1,c2,c3);
    }
   // SDL_SetTextureColorMod(txt,255*amb,255*amb,255*amb);
    
    if(grabed == false){
        
        SDL_RenderCopy(SDL_GetRenderer(SDL_GetWindowFromID(1)),txt,NULL,&box1);
    }
}







