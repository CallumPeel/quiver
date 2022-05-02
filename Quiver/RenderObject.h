#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

// display ground
void renderGround(void);
// display sun
void renderSun(double sunAngle);
// display all trees
void renderTrees(void);
// display all fences
void renderFences(void);
// display all targets
void renderTargets(double targetWithLegs[3][3]);
// display all houses
void renderHouses(void);

#endif // RENDEROBJECT_H
