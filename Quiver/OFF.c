#include "Off.h"

//---------------------------------------------------------------------------

void ReadOffFile(Off* off, const char* filename)
{
    FILE * fp = fopen(filename, "r");

    while (getc(fp) != '\n'); // skips first line, assumed to say 'OFF'

    fscanf(fp, "%u %u %*u"
           , &off->nverts
           , &off->nfaces);

    off->verts = (Vec3*)malloc(off->nverts * sizeof(Vec3));
    off->faces = (Face*)malloc(off->nfaces * sizeof(Face));

    for (unsigned i = 0; i < off->nverts; ++i)
        fscanf(fp, "%lf %lf %lf"
               , &off->verts[i].x
               , &off->verts[i].y
               , &off->verts[i].z);

    for (unsigned i = 0; i < off->nfaces; ++i)
        fscanf(fp, "%*u %u %u %u"       // ignores the face type parameter
               , &off->faces[i].a
               , &off->faces[i].b
               , &off->faces[i].c);

    fclose(fp);
}

void FreeOff(Off* off)
{
    free(off->verts);
    off->verts = NULL;

    free(off->faces);
    off->faces = NULL;
}

void PrintOff(Off* off)
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

Vec3 GetOffCenter(const Off* off)
{
    Vec3 c = {0, 0, 0};

    for (unsigned i = 0; i < off->nverts; ++i)
        c = Add(&c, &off->verts[i]);

    c = Div(&c, off->nverts);

    return c;
}

double GetOffBSR(const Off* off, const Vec3* c)
{
    Vec3 d;
    double r_square, rmax_square;
    r_square = rmax_square = 0;

    for (unsigned i = 0; i < off->nverts; ++i)
    {
        d = Sub(&off->verts[i], c);

        r_square = LengthSQ(&d);

        if (r_square > rmax_square)
            rmax_square = r_square;
    }

    return sqrt(rmax_square);
}

void NormOff(Off* off)
{
    Vec3 d;
    const Vec3 c = GetOffCenter(off);
    const double r = GetOffBSR(off, &c);

    for (unsigned i = 0; i < off->nverts; ++i){
        d = Sub(&off->verts[i], &c);
        off->verts[i] = Div(&d, r);
    }
}
