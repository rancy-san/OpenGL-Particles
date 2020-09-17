/*****************************************************************************
FILE      :  particle.h
PURPOSE	  :  Custom header file
*****************************************************************************/

struct color {
	float r;
	float g;
	float b;
	float a;
};

typedef struct color Color4;

struct vector{
	float x;
	float y;
	float z;
};

typedef struct vector Point3D;
typedef struct vector Vector3D;

struct particle {
	Color4 col;
	Point3D pos;
	Vector3D dir;
	Vector3D spd;
	int lifespan;
	int size;
	struct particle* next;
};	

#define DFLT_INIT_NUM_PARTICLES 99

int particle_init(struct particle* p);
int particle_add( struct particle **head);
int particle_remove(struct particle* p);
int particle_destroy( struct particle **head );
int particle_update(struct particle **head );
