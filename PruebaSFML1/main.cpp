#include <iostream>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include "GraficoSFML.h"
#include <time.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define WINDOW_H 800
#define WINDOW_V 600
#define TITLE "Mi super practica 1.2"

/*terminar ajustes de memoria
semaforos
XML
tiempo dentro de los hijos
*/

///Si se va un cliente clientin = true

///struct de memoria compartida
struct SharedMem {int time; bool table1Client;bool table2Client;bool table3Client;bool table1food;bool table2food;bool table3food; bool client1out; bool client1in;bool client2out; bool client2in;bool client3out; bool client3in; };

int main()
{
    srand(time(NULL));
    ///variables
    bool click = false;
    int interactingObject = -1;
    time_t starting;
    time(&starting);

    int clientesRestantes = 5;
    float duracionLlegada = 5.0;
    float duracionSalida = 5.0;

    ///Zona de memoria compartida
    key_t shmKey = ftok("./",'a');
    int shmID = shmget(shmKey, sizeof(struct SharedMem), IPC_CREAT|0666);
    struct SharedMem* shmPTR = (struct SharedMem*)shmat(shmID,NULL,0);

    ///creacion de procesos
    pid_t pid1, pid2;
    int status;
    pid1 = fork();
    if (pid1==0){
    ///hijo 1
        int start1Time, start2Time, start3Time;
        int rand3, rand2;
        while(true){

            if((shmPTR->table1Client)||(shmPTR->table2Client)||(shmPTR->table3Client)){
                if(shmPTR->clientin){
                    rand3 = rand()%3;
                    rand2 = rand()%2;
                    shmPTR->clientin = false;
                    startTime = shmPTR->time;
                }
            }

                    if((shmPTR->table1Client)&&(!shmPTR->table2Client)&&(!shmPTR->table3Client)){
                    if(start1Time-5>=shmPTR->time)
                        shmPTR->table1Client = false;

                    }else if((!shmPTR->table1Client)&&(shmPTR->table2Client)&&(!shmPTR->table3Client)){
                    if(start2Time-5>=shmPTR->time)
                        shmPTR->table2Client = false;

                    }else if((!shmPTR->table1Client)&&(!shmPTR->table2Client)&&(shmPTR->table3Client)){
                    if(start3Time-5>=shmPTR->time)
                        shmPTR->table3Client = false;

                    }else if((shmPTR->table1Client)&&(!shmPTR->table2Client)&&(shmPTR->table3Client)){
                        if(rand2 == 0){
                        if(start1Time-5>=shmPTR->time)
                            shmPTR->table1Client = false;
                        }else{
                        if(start3Time-5>=shmPTR->time)
                            shmPTR->table3Client = false;
                        }

                    }else if((shmPTR->table1Client)&&(shmPTR->table2Client)&&(!shmPTR->table3Client)){
                        if(rand2 == 0){
                        if(start1Time-5>=shmPTR->time)
                            shmPTR->table1Client = false;
                        }else{
                        if(start2Time-5>=shmPTR->time)
                            shmPTR->table2Client = false;
                        }

                    }else if((!shmPTR->table1Client)&&(shmPTR->table2Client)&&(shmPTR->table3Client)){
                        if(rand2 == 0){
                        if(start2Time-5>=shmPTR->time)
                            shmPTR->table2Client = false;
                        }else{
                        if(start3Time-5>=shmPTR->time)
                            shmPTR->table3Client = false;
                        }

                    }else if((shmPTR->table1Client)&&(shmPTR->table2Client)&&(shmPTR->table3Client)){
                        if(rand3 == 0){
                        if(start1Time-5>=shmPTR->time)
                            shmPTR->table1Client = false;
                        }else if(rand3 == 1){
                        if(start2Time-5>=shmPTR->time)
                            shmPTR->table2Client = false;
                        }else{
                        if(start3Time-5>=shmPTR->time)
                            shmPTR->table3Client = false;
                        }

                    }else {}
                }


        }

    }///final del hijo 1
    else{
        pid2 = fork();
        if(pid2==0){
        ///hijo 2

            while(true){

            if((shmPTR->table1food)||(shmPTR->table2food)||(shmPTR->table3food)){

                if(shmPTR->table1food){
                    shmPTR->table1food = false;

                }else if(shmPTR->table2food){
                    shmPTR->table2food = false;

                }else if (shmPTR->table3food){
                    shmPTR->table3food = false;

                }

            }
        }
      }
    }///final del hijo 2
    if((pid1>0)&&(pid2>0)){
    ///padre
        sf::RenderWindow window(sf::VideoMode(WINDOW_H,WINDOW_V), TITLE);

        GraficoSFML graficos;

        while(window.isOpen())
        {
            sf::Event event;
            while(window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        window.close();
                    }
                }
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        graficos.MueveJugador(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                        click = true;
                    }
                }
            }
            graficos.Timer(starting);
            shmPTR->time = graficos.tiempoRestante;

            interactingObject = graficos.Colisionando(graficos.posicionJugador,graficos.aOrigenMesas,graficos.aOrigenDispensadores,graficos.sizeMesa);

             if(click == true){
            switch(interactingObject){

                    case -1:
                    //mantener

                    break;

                    case 0:
                    //depostiar
                    graficos.DejaComida(COMIDA_VERDE);
                    graficos.PonPedido(0,COMIDA_VERDE);
                    break;

                    case 1:
                    //depositar
                    graficos.DejaComida(COMIDA_VERDE);
                    break;

                    case 2:
                    //depositar
                    graficos.DejaComida(COMIDA_VERDE);
                    break;

                    case 3:
                    //tomar
                    graficos.CogeComida(COMIDA_VERDE);
                    break;

                    case 4:
                    //tomar
                    graficos.CogeComida(COMIDA_AMARILLA);
                    break;

                    case 5:
                    //tomar
                    graficos.CogeComida(COMIDA_ROJA);
                    break;
                    }

                    click = false;

            }

            window.clear();


            for(size_t i = 0; i < graficos.aTextosADibujar.size(); i++)
            {
                window.draw(graficos.aTextosADibujar[i]);
            }
            for(size_t i = 0; i < graficos.aObjetosADibujar.size(); i++)
            {
                window.draw(graficos.aObjetosADibujar[i]);
            }

            for (size_t i =0 ; i< NUM_MESAS; i++)
            {
                window.draw(graficos.aTaburetesADibujar[i]);
                window.draw(graficos.aPedidosADibujar[i]);
            }
            window.draw(graficos.jugador);
            window.draw(graficos.manoIzquierda);
            window.draw(graficos.manoDerecha);

            window.display();
            }
    }///final proceso padre



    return 0;
}
