#ifndef READFILE_H
#define READFILE_H

#include "OffData.h"
#include <stdio.h>

/** @brief discards first line of file and assigns the total
  *         verts, faces and edges in the OFF file to 'fileCoords'
  */
void ReadInitFileData(FILE *nFile, OFFObj3d *fileCoords);

/** @brief Open the OFF file if found or exit program if not found
 *
 *  @return FILE*
 */
FILE* getFile(const char *inFile);

/** @brief Stores data from the OFF file in a struct 'OFFObj3d'
 */
void readOFFFile(OFFObj3d *fileCoords, const char *inFile);

#endif // READFILE_H

