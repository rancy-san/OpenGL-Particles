#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h> 
#include "particle.h"

/****************************************************************************
FUNCTION : particle_init
PURPOSE : initialize the properties of a single particle
INPUT : pointer to the particle structure to be initialized
OUTPUT : returns 1 on error, 0 on success
NOTES : Random color, outward direction, random speed, initial position at 0. 
	There is no z axis.
*****************************************************************************/

int particle_init(struct particle* p) {

	p->col.r = ((float)rand()/(float)RAND_MAX);
	p->col.g = ((float)rand()/(float)RAND_MAX);
	p->col.b = ((float)rand()/(float)RAND_MAX);
	p->col.a = 1.0f;

	p->dir.x = ((float)rand()/(float)RAND_MAX - 0.5);
	p->dir.y = ((float)rand()/(float)RAND_MAX - 0.5);
	p->dir.z = 0;
	
	p->spd.x = ((float)rand()/(float)RAND_MAX);
	p->spd.y = ((float)rand()/(float)RAND_MAX);
	p->spd.z = 0;
	
	p->pos.x = 0;
	p->pos.y = 0;
	p->pos.z = 0;
	
	p->lifespan = 1; 
	p->size = 5; 
	
	return 0;       
}

/**********************************************************
FUNCTION : particle_add
PURPOSE : add a particle to the dynamic particle linked list
INPUT : struct particle *head. Head of the particle list
OUTPUT : returns 1 on error, 0 on success
NOTES : Calls particle_init()
************************************************************/

int particle_add( struct particle **head){
	struct particle *p = malloc(sizeof(struct particle));
	p->next = *head;
	particle_init(p);
	*head = p;

	return 0;
}

/****************************************************************************
FUNCTION : particle_remove
PURPOSE : remove a specific particle from the dynamic particle linked list
INPUT : pointer to the particle to remove
OUTPUT : returns 1 on error, 0 on success
NOTES : Particle can be situated in any place in the list. 
Usually deleted because the lifespan ran out
***************************************************************************/


int particle_remove(struct particle* p){
	struct particle *tmp; 
	tmp = p;

	while(tmp->lifespan > 0) {
		tmp->lifespan = tmp->lifespan-1;
	} 

	if(tmp->lifespan < 0 || tmp->next == NULL){
		return 1;
	}
	return 0;
}

/*******************************************************************
FUNCTION : particle_destroy
PURPOSE : free memory used by the dynamic particle linked list
INPUT : struct particle **head. Head of the particle list
OUTPUT : returns 1 on error, the number of particles destroyed on success
NOTES : removes all particles from the list Calls particle_remove()
********************************************************************/

int particle_destroy( struct particle **head ){
	struct particle *tmp;
	tmp = *head; 
	if(tmp == NULL) {
		return 1; 
	}
	*head = tmp->next;
	particle_remove(*head);
	free(tmp);
	free(*head);

	return DFLT_INIT_NUM_PARTICLES; 
}

/***************************************************************************
FUNCTION : particle_update
PURPOSE : update the particles properties to be rendered in the next frame
INPUT : struct particle **head. Head of the particle list
OUTPUT : returns 1 on error, 0 on success
NOTES : Creativity and more creativity here for you !!!
**************************************************************************/

int particle_update(struct particle **head ){
	struct particle *this;
	this = *head; 
	if(this == NULL){
		return 1;
	}
	while(this != NULL) {
		this->pos.x += this->spd.x * this->dir.x; 
		this->pos.y += this->spd.y * this->dir.y;
		this->pos.z = 0;

		if (this->pos.x > 75 || this->pos.x < -75) { 
			this->pos.x = 0;
		}else if (this->pos.y > 75 || this->pos.y < -75){
			this->pos.y = 0;
		}
		this = this->next; 
	}
	return 0;
}