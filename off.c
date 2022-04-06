#include "off.h"

void ReadOffFile(Off * off, const char * filename)
{
    FILE * fp = fopen(filename, "r");

    while (getc(fp) != '\n'); // skips first line, assumed to say 'OFF'

    fscanf(fp, "%u %u %*u"
           , &off->nverts
           , &off->nfaces);

    InitLists(off);

    for (unsigned i = 0; i < off->nverts; ++i)
        fscanf(fp, "%lf %lf %lf"
               , &off->verts[i].x
               , &off->verts[i].y
               , &off->verts[i].z);

    for (unsigned i = 0; i < off->nfaces; ++i)
        fscanf(fp, "%*u %u %u %u"
               , &off->faces[i].a
               , &off->faces[i].b
               , &off->faces[i].c);

    fclose(fp);
}

void InitLists(Off * off)
{
    off->verts = (vec *)malloc(off->nverts * sizeof(vec));
    off->faces = (face *)malloc(off->nfaces * sizeof(face));
}

void FreeOff(Off * off)
{
    free(off->verts);
    off->verts = NULL;

    free(off->faces);
    off->faces = NULL;
}

void PrintOff(Off * off)
{
    printf("%d %d\n", off->nverts, off->nfaces);

    getchar();

    for (unsigned i = 0; i < off->nverts; ++i)
        printf("%lf %lf %lf\n"
               , off->verts[i].x
               , off->verts[i].y
               , off->verts[i].z);

    getchar();

    for (unsigned i = 0; i < off->nfaces; ++i)
        printf("%d %d %d\n"
               , off->faces[i].a
               , off->faces[i].b
               , off->faces[i].c);
}
