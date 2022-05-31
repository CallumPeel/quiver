#include "Collision.h"

int isCollidingForTwo(GameObject objA, GameObject* objB) {
    int xco = (
            objA.box.minX + objA.position->x <= objB->box.maxX + objB->position->x
         && objA.box.maxX + objA.position->x >= objB->box.minX + objB->position->x
        );
    int yco = (
            objA.box.minY + objA.position->y <= objB->box.maxY + objB->position->y
        &&  objA.box.maxY + objA.position->y >= objB->box.minY + objB->position->y
        );
    int zco = (
            objA.box.minZ + objA.position->z <= objB->box.maxZ + objB->position->z
         && objA.box.maxZ + objA.position->z >= objB->box.minZ + objB->position->z
        );
    return (xco && yco && zco);
}

int isColliding(GameObject arrow, GameObject** objectList, int numObjs) {
    int isColliding = 0;
    for (int i = 1; i < numObjs; i++) {
        isColliding = isCollidingForTwo(arrow, objectList[i]);
        if (isColliding) {
            break;
        }
    }
    return isColliding;
}
