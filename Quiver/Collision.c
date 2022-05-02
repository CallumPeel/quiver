#include "Collision.h"

int checkCollision(double objPos1[], double objPos2[], point3D pnt1, point3D pnt2) {
    int xOverLap = 1, yOverLap = 1, zOverLap = 1, allOverLap = 0;

    if(fabs(objPos1[0] - objPos2[0]) > (pnt1.x + pnt2.x)) xOverLap = 0;
    if(fabs(objPos1[1] - objPos2[1]) > (pnt1.y + pnt2.y)) yOverLap = 0;
    if(fabs(objPos1[2] - objPos2[2]) > (pnt1.z + pnt2.z)) zOverLap = 0;

    allOverLap = xOverLap && yOverLap && zOverLap;

    return allOverLap;
}

int collider(OFFObj3d *obj1, OFFObj3d *obj2, double objPos1[], double objPos2[]) {
    int allOverLap2 = 0;

    for(int i = 0;i < obj1->nFace;++i) {
        int flag = 0;
        point3D temp1;

        temp1.x = obj1->rad[i].x;
        temp1.y = obj1->rad[i].y;
        temp1.z = obj1->rad[i].z;

        for(int j = 0;j < obj2->nFace;++j) {
            point3D temp2;
            int allOverLap = 0;

            temp2.x = obj2->rad[j].x ;
            temp2.y = obj2->rad[j].y;
            temp2.z = obj2->rad[j].z;

            allOverLap = checkCollision(objPos1, objPos2, temp1, temp2);

            if(allOverLap) {
                flag = 1;
                allOverLap2 = allOverLap;
                break;
            }
        }

        if(flag)
            break;
    }

    return allOverLap2;
}
