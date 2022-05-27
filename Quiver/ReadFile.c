#include "ReadFile.h"

/** @brief discards first line of file and assigns the total
  *         verts, faces and edges in the OFF file to 'fileCoords'
  */
void ReadInitFileData(FILE *nFile, OFFObj3d *fileCoords) {
    char inData[256];

    //Read first line
    fgets(inData, 256, nFile);

    //read verts, faces, and edges
    fgets(inData, 256, nFile);
    sscanf(inData, "%d %d %d", &fileCoords->nVert, &fileCoords->nFace, &fileCoords->nEdge);
}

/** @brief Open the OFF file if found or exit program if not found
 *
 *  @return FILE*
 */
FILE* getFile(const char *inFile) {
    FILE *nFile;

    nFile = fopen(inFile, "r");

    if(!nFile) {
        printf("Read file error\n");
        exit(0);
    }

    return nFile;
}

/** @brief Stores data from the OFF file in a struct 'OFFObj3d'
 */
void readOFFFile(OFFObj3d *offObject, const char *inFile) {
    FILE *offFile;
    int i = 0, j = 0;
    char inData[256];
    double temp;

    offFile = getFile(inFile);

    ReadInitFileData(offFile, offObject);
    allocCoordMem(offObject);

    while((fgets(inData, 256, offFile)) != NULL) {
        sscanf(inData, "%lf", &temp);

        if(temp != 3) {
            point3D newPoint;
            sscanf(inData, "%lf %lf %lf", &newPoint.x, &newPoint.y, &newPoint.z);

            offObject->vertCoord[i].x = newPoint.x;
            offObject->vertCoord[i].y = newPoint.y;
            offObject->vertCoord[i].z = newPoint.z;

            ++i;
        } else if(temp == 3) {
            Face newPoint;

            sscanf(inData, "%lf %d %d %d", &temp, &newPoint.x, &newPoint.y, &newPoint.z);

            offObject->faceCoord[j].x = newPoint.x;
            offObject->faceCoord[j].y = newPoint.y;
            offObject->faceCoord[j].z = newPoint.z;

            ++j;
        }
    }

    offObject->rot->x = 0;
    offObject->rot->y = 0;
    offObject->rot->z = 0;

    fclose(offFile);
}

