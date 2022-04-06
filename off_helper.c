#include "off_helper.h"

void Off_draw(Off const * off) {
    for (unsigned i = 0; i < off->nfaces; ++i){
        glBegin(GL_TRIANGLES);
            glVertex3d(
                off->verts[ off->faces[i].a ].x,
                off->verts[ off->faces[i].a ].y,
                off->verts[ off->faces[i].a ].z
            );
            glVertex3d(
                off->verts[ off->faces[i].b ].x,
                off->verts[ off->faces[i].b ].y,
                off->verts[ off->faces[i].b ].z
            );
            glVertex3d(
                off->verts[ off->faces[i].c ].x,
                off->verts[ off->faces[i].c ].y,
                off->verts[ off->faces[i].c ].z
            );
        glEnd();
    }
}

vec Off_center(Off const * off) {
    vec c;
    c.x = c.y = c.z = 0;

    for (unsigned i = 0; i < off->nverts; ++i)
        c = Add(&c, &off->verts[i]);

    c = Div(&c, off->nverts);

    return c;
}

double Off_bsphere_rad(Off const * off, vec const * c) {
    vec d;
    double r_square, rmax_square;
    r_square = rmax_square = 0;

    for (unsigned i = 0; i < off->nverts; ++i)
    {
        d = Sub(&off->verts[i], c);

        r_square = Length_squared(&d);

        if (r_square > rmax_square)
            rmax_square = r_square;
    }

    return sqrt(rmax_square);
}

void Off_normalize(Off * off) {
    vec d;
    const vec c = Off_center(off);
    const double r = Off_bsphere_rad(off, &c);

    for (unsigned i = 0; i < off->nverts; ++i){
        d = Sub(&off->verts[i], &c);
        off->verts[i] = Div(&d, r);
    }
}
