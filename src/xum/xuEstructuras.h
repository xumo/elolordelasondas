#ifndef _XU_ESTRUCTURAS_H_
#define _XU_ESTRUCTURAS_H_

//#include <sys/types.h>
//76#include <inaddr.h>

struct nodo
{
	int id;
};

struct arista
{
	//in_addr		origen;
	//in_addr		destino;
	int			id;
	int			peso;
};

class vNodo
{
public:
	float	x;
	float	y;
	float	z;
	float	peso;
	int		tipo;
};

typedef vNodo vec3;






#endif //den fine _XU_ESTRUCTURAS_H_