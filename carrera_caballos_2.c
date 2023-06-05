//para compilar usar: gcc -o carrera_caballos_2 carrera_caballos_2.c -lpthread -lncurses -DMUTEX
//./carrera_caballos_2 para ejecutar una vez compilado

#include<pthread.h>							//bibliotecas de threads
#include<unistd.h>							//bibliotecas de sistema Unix
#include<stdlib.h> 							//bibliotecas funciones estandar
#include<ncurses.h> 						//bibliotecas manejo de pantalla

//estructura para cada caballo
typedef struct{									
	int carril;										
	char caballo;									
	int vuelta[2];
	int distancia[2];
	int competidores;
} parametros_t;



void *funcionThread(parametros_t *parametro);
void *funcionTotal(parametros_t *parametro);
void obtenerPrimerCaballo(parametros_t *parametros, char *primerCaballo);

#ifdef MUTEX
pthread_mutex_t pantalla;
#endif
	

void obtenerPrimerCaballo(parametros_t *parametros, char *primerCaballo) {
    int vueltasTotales = parametros[0].vuelta[1] * parametros[0].competidores;
    int vueltasCompletadas = 0;

    while (vueltasCompletadas < vueltasTotales) {
        for (int i = 0; i < parametros[0].competidores; i++) {
            if (parametros[i].vuelta[0] >= parametros[i].vuelta[1]) {
                *primerCaballo = parametros[i].caballo;
                return;
            }
        }
        usleep(1000000 / 10);
    }
}


int main(void){
	
	char letras[] = {'A','B','C','D','E','F','G'};
	
	initscr();										//inicializa la pantalla para ncurses
	curs_set(0);									//elimina el cursor
	erase();											//limpia pantalla
	refresh();										//refresca los cambion en la pantalla
	srand(time(NULL));								//inicializa semilla de la funcion random
	
	#ifdef MUTEX
	pthread_mutex_init (&pantalla, NULL); //inicializa variable pantalla tipo mutex
	#endif

	
	//Preguntar por caballos en total
    char inputf;
	int j=1;
	
	#ifdef MUTEX
  	pthread_mutex_lock(&pantalla);	//bloquea la pantalla (seccion critica)
   	#endif
	printw("Seleccionar cantidad de caballos para la carrera, digite un numero de 1 a 7 para seleccionar de 1 a 7 caballos:\n1  2  3  4  5  6  7");
	refresh();
	#ifdef MUTEX
  	pthread_mutex_unlock(&pantalla);	//bloquea la pantalla (seccion critica)
    #endif
	
	while(j==1){
		
		scanf("%c",&inputf);
		char aux1[7]={'1','2','3','4','5','6','7'};
		for(int i=0;i<7;i++){
			if(inputf == aux1[i]){
				j++;
				break;
			}
		}
		#ifdef MUTEX
  		pthread_mutex_lock(&pantalla);	//bloquea la pantalla (seccion critica)
   		#endif
   		erase();
		printw("error, seleccione una opción valida:\nSeleccionar cantidad de caballos para la carrera, digite un numero de 1 a 7 para seleccionar de 1 a 7 caballos:\n1  2  3  4  5  6  7 ");
		refresh();
		#ifdef MUTEX
  		pthread_mutex_unlock(&pantalla);	//bloquea la pantalla (seccion critica)
    	#endif
	}
	
	int competidores = inputf - '0';
	
	//Atributos para la creacion de los threads caballos e id para cada thread caballo hijo
	pthread_attr_t atr[competidores];
	pthread_t idHilo[competidores];
	int error[competidores];
	
	//Atributos para la creacion del thread total e id del thread total
	pthread_attr_t atr2;
	pthread_t idHilo2;
	int error2;
	
	//Inicializa threads caballos
	for(int i=0;i<competidores;i++){
		pthread_attr_init(&atr[i]);
	}
	
	//Inicializa thread total
	pthread_attr_init(&atr2);
	
	//Preguntar por cantidad de vueltas
	j=1;
	
	#ifdef MUTEX
  	pthread_mutex_lock(&pantalla);	
   	#endif
   	erase();
	printw("Seleccionar cantidad de vueltas para la carrera, digite un numero de 1 a 4 para seleccionar de 1 a 4 vueltas:\n1  2  3  4");
	refresh();
	#ifdef MUTEX
  	pthread_mutex_unlock(&pantalla);	
    #endif
	
	while(j==1){
		
		scanf("%c",&inputf);
		char aux1[4]={'1','2','3','4'};
		for(int i=0;i<4;i++){
			if(inputf == aux1[i]){
				j++;
				break;
			}
		}
		#ifdef MUTEX
  		pthread_mutex_lock(&pantalla);	
   		#endif
   		erase();
		printw("error, seleccione una opción valida:\nSeleccionar cantidad de vueltas para la carrera, digite un numero de 1 a 4 para seleccionar de 1 a 4 vueltas:\n1  2  3  4");
		refresh();
		#ifdef MUTEX
  		pthread_mutex_unlock(&pantalla);	
    	#endif
	}
	
	int vueltas = inputf - '0';
	
	//Preguntar por cantidad de metros
	j=1;
	
	#ifdef MUTEX
  	pthread_mutex_lock(&pantalla);	
   	#endif
   	erase();
	printw("Seleccionar cantidad de metros para la carrera, digite un numero de 1 a 4 para seleccionar de 30 a 60 metros:\n1   2   3   4\n30  40  50  60");
	refresh();
	#ifdef MUTEX
  	pthread_mutex_unlock(&pantalla);	
    #endif
	
	while(j==1){
		
		scanf("%c",&inputf);
		char aux1[4]={'1','2','3','4'};
		for(int i=0;i<4;i++){
			if(inputf == aux1[i]){
				j++;
				break;
			}
		}
		#ifdef MUTEX
  		pthread_mutex_lock(&pantalla);	
   		#endif
   		erase();
		printw("error, seleccione una opción valida\nSeleccionar cantidad de metros para la carrera, digite un numero de 1 a 4 para seleccionar de 30 a 60 metros:\n1   2   3   4\n30  40  50  60");
		refresh();
		#ifdef MUTEX
  		pthread_mutex_unlock(&pantalla);	//bloquea la pantalla (seccion critica)
    	#endif
	}


	int distanciasf[4]={30,40,50,60};
	int distancias = distanciasf[(inputf - '0')-1];
	
	//estructura carrera que contendra cada caballo con sus datos
	parametros_t carrera[competidores];
	
	//constructor de la carrera para cada caballo
	for(int i=0;i<competidores;i++){
		parametros_t aux;
		aux.carril=i;
		aux.caballo=letras[i];
		aux.vuelta[0]=0;
		aux.vuelta[1]=vueltas;
		aux.distancia[0]=0;
		aux.distancia[1]=distancias;
		aux.competidores=competidores;
		carrera[i]=aux;
	};
	
	//Imprimir los datos iniciales de la carrera para mostrar al usuario
	#ifdef MUTEX
  	pthread_mutex_lock(&pantalla);
    #endif
	erase();
	for(int i=0;i<competidores;i++){
		mvprintw(i,0,"Caballo %c: 0 vueltas - 0 metros", carrera[i].caballo);
	}
	mvprintw(competidores+1,0,"Totales: 0 vueltas - 0 metros");
	
	for(int i=0;i<competidores;i++){
		mvprintw(competidores+3+carrera[i].carril,0,"Carril %d|%c|------------------------|%d/%d vueltas",carrera[i].carril,carrera[i].caballo,carrera[i].vuelta[0],carrera[i].vuelta[1]);
	}
	
	mvprintw(competidores+competidores+3+1,0,"Largo de la pista: %d metros",distancias);
	mvprintw(competidores+competidores+3+2,0,"Numero de vueltas: %d",vueltas);
	refresh();
	
	#ifdef MUTEX
  	pthread_mutex_unlock(&pantalla);
    #endif

  //AAAAAAAAAA
	char primerCaballo = ' ';


	//Creacion de los thread para los caballos
	for(int i=0;i<competidores;i++){
		error[i]=pthread_create(&idHilo[i],&atr[i],(void *)funcionThread,(void *)&carrera[i]);
		if(error[i] != 0){
			perror ("No puedo crear la hebra caballo");
    		exit (-1);
		}
	}
		
	//Creacion del thread para los totales
	error2=pthread_create(&idHilo2,&atr2,(void *)funcionTotal,(void*)&carrera);
	if(error2 != 0){
		perror ("No puedo crear hebra total");
		exit (-1);
	}

	obtenerPrimerCaballo(carrera, &primerCaballo);


    mvprintw(competidores + competidores + 3 + 3, 0, "El ganador es: %c", primerCaballo);
    refresh();
	getch();
	endwin();
    return EXIT_SUCCESS;
}



//Funcion para actualizar la pantalla si se cambia algun parametro
void actualizar(parametros_t *parametro){
	
	#ifdef MUTEX
  	pthread_mutex_lock(&pantalla);		
    #endif
	
	mvprintw(parametro->carril,0,"Caballo %c: %d vueltas - %d metros", parametro->caballo, parametro->vuelta[0], parametro->distancia[0]);
	
	int new_distance = parametro->distancia[0]-(parametro->distancia[1]*parametro->vuelta[0]);
	int aux = (int)new_distance*24;
	aux/=parametro->distancia[1];
	aux+=11;
	if(new_distance==0){
		mvprintw(parametro->competidores+3+parametro->carril,34,"-|%d/%d vueltas",parametro->vuelta[0],parametro->vuelta[1]);
		mvprintw(parametro->competidores+3+parametro->carril,aux,"%c",parametro->caballo);
	}
	else{
		if(aux==34){
			mvprintw(parametro->competidores+3+parametro->carril,aux,"%c",parametro->caballo);
		}
		else{
			mvprintw(parametro->competidores+3+parametro->carril,aux,"-%c",parametro->caballo);
		}
	}
	
	refresh();
	
	#ifdef MUTEX
  	pthread_mutex_unlock(&pantalla);		
    #endif

}
void determinarGanador(parametros_t *carrera, int competidores);
//Hilo que se encarga de contar los metros y vueltas totales
void *funcionTotal(parametros_t *parametro){

	int dtotal=0;
	int vtotal=0;

	parametros_t puesto[parametro[0].competidores];
	
	int size = parametro[0].competidores;
	
	int x=1;
	
	while(x==1){
	
		for(int i=0;i<size;i++){
			dtotal+=parametro[i].distancia[0];
			vtotal+=parametro[i].vuelta[0];
		}
	
		#ifdef MUTEX
		pthread_mutex_lock(&pantalla);		
    	#endif
    	refresh();
		mvprintw(size+1,0,"Totales: %d vueltas - %d metros\n", vtotal, dtotal);
		
		refresh();
		
		#ifdef MUTEX
	  	pthread_mutex_unlock(&pantalla);		
    	#endif
    	
    	//condicion de termino while
    	if(vtotal==(parametro[0].vuelta[1]*size)){
    		x++;
    		#ifdef MUTEX
			pthread_mutex_lock(&pantalla);		
    		#endif
    		mvprintw(size+size+3.5+3.5,0,"Carrera Terminada!!!!!!");
    		refresh();
    		#ifdef MUTEX
			pthread_mutex_unlock(&pantalla);		
    		#endif
    	}
    	else{
   			dtotal=0;
   			vtotal=0;
   		}
   		
    	usleep(1000000/10);
    
    }
}

//Funcion Hilo para cada caballo
void *funcionThread(parametros_t *parametro){
	
	int vueltas=parametro->vuelta[1];
	int distanciaf=parametro->distancia[1];
	
	while(parametro->distancia[0] < distanciaf*(parametro->vuelta[0]+1) && parametro->vuelta[0] < vueltas){
	
		if(rand()% 100 < 50){
			parametro->distancia[0]++;
			if(parametro->distancia[0]>=distanciaf*(parametro->vuelta[0]+1) && parametro->vuelta[0]<vueltas){
				parametro->vuelta[0]++;
			}
			actualizar(parametro);
		}
		usleep(1000000/10);
	}
}
