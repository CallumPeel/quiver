#include "BoundingBox.h"
/**
int searchNearbyObjects(int numObjects, const OFFObj3d *fCoord, const OFFObj3d *fCoord2, const point3D *coMass, const point3D *coMass2, double dist[], double dist1[]) {
    point3D tempMagnitude;

    // form a distance vector between two objects
    //*tempMagnitude = subtractVector3D(fCoord->com, fCoord2->com);

    tempMagnitude.x = coMass->x - coMass2->x;
    //printf("%f %f %f\n", tempMagnitude.x, coMass->x, coMass2->x);
    tempMagnitude.y = coMass->y - coMass2->y;
    tempMagnitude.z = coMass->z - coMass2->z;

    // calc distance of com between obj1 and obj2
    //int objDist = magnitude(tempMagnitude);
    int objDist = sqrt(pow(tempMagnitude.x, 2) + pow(tempMagnitude.y, 2) + pow(tempMagnitude.z, 2));

    // increased boundary of first object
    //point3D objInc = scalar(fCoord->faceRad->com, 10);
    point3D objInc;
    objInc.x = coMass->x * 10;
    objInc.y = coMass->y * 10;
    objInc.z = coMass->z * 10;

			// distance of first object boundary
			//double areaCheck = magnitude(objInc);
    double areaCheck = sqrt(pow(objInc.x, 2) + pow(objInc.y, 2) + pow(objInc.z, 2));

			// search for collisions if true
    if(objDist <= areaCheck) {
        return CollisionDetect(fCoord, fCoord2, objDist, coMass, coMass2, dist, dist1);
    }

	return 0;
}

int CollisionDetect(const OFFObj3d *fCoord, const OFFObj3d *fCoord2, double objDist, const point3D *coMass, const point3D *coMass2, double dist[], double dist1[]) {
    for(int i = 0;i < fCoord->nFace;++i) {
		//Point3D tempVec = scalar(obj1.faceRad[i].com, obj1.faceRad[i].dist);
		point3D tempVec;

		tempVec.x = coMass->x * dist[i];
		//printf("%f %f %f\n", tempVec.x, coMass->x, dist[i]);
        tempVec.y = coMass->y * dist[i];
        tempVec.z = coMass->z * dist[i];

		double obj1Rad = sqrt(pow(tempVec.x, 2) + pow(tempVec.y, 2) + pow(tempVec.z, 2));

		for(int j = 0;j < fCoord2->nFace;++j) {
			//point3D tempVec2 = scalar(fCoord2->com, fCoord2->faceCoord[i].distToCOM);
            point3D tempVec2;

			tempVec2.x = coMass2->x * dist1[i];
            tempVec2.y = coMass2->y * dist1[i];
            tempVec2.z = coMass2->z * dist1[i];

			//double obj2Rad = magnitude(tempVec);
            double obj2Rad = sqrt(pow(tempVec2.x, 2) + pow(tempVec2.y, 2) + pow(tempVec2.z, 2));

			double gap = objDist - (obj1Rad + obj2Rad);
            //printf("%f\n", gap);
			if(gap <= 0.0) {
                return 1;
			}

		}
	}
	return 0;
}
*/
