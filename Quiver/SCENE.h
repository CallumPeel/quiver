#ifndef SCENE_H
#define SCENE_H

//------------------------------------------------------------------------

#include "OFF.h"
#include "PHYSICS.h"

//------------------------------------------------------------------------

typedef struct Arrow {
    Off* off;
    Object obj;
    Vec3 offset; // centroid offset (for aligning tip of arrow to center)
} Arrow;

typedef struct Static {
    Off* off;
    AABB* aabb;
    float scale;
} Static;

// uses double inferencing. put the ListOff argument in as &listoff, where listoff is -> Off* listoff
void LoadOff(Off** offList, const char* filename);

void DrawStatic(const Static* model);
void DrawArrow(const Arrow* model);
void DrawOff(const Off* off);
void DrawSizeBox(const Vec3* size);
void DrawScene();
void AddSunAngle(float angle);
void renderGround(void);
void renderSun();
void renderTrees(void);
void renderFences(void);
void renderTargets();
void renderHouses(void);
void drawGround(void);
void drawTargetInnerRing(void);
void drawTargetSecondRing(void);
void drawTargetThirdRing(void);
void drawTargetOuterRing(void);
void drawTarget(void);
void drawTargetWithLegs(void);
void boxTarget(void);
void draw5BoxTarget(void);
void drawSun();
void drawFence(void);
void drawFenceArea(void);
void drawWindArrow(void);
void drawTree1(void);
void drawTree2(void);
void drawWallDoor(void);
void drawWall(void);
void drawRoof(void);
void drawHouseInterior(void);
void drawHouse(void);

#endif // SCENE_H
