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
*/

bool go1;
///Si se va un cliente clientin = true

///struct de memoria compartida
struct SharedMem {int time; bool table1Client = false;bool table2Client = false;bool table3Client = false;bool table1food;bool table2food;bool table3food; bool client1out; bool client2out; bool client3out; bool client1leave; bool client2leave; bool client3leave; };

void handler1 (int sign){
    //timerLess = true;
    go1 = true;

    alarm(1);
    //times++;
    //putPerson = true;

    }

int main()
{
    //srand(time(NULL));
    ///variables
    bool click = false;
    int interactingObject = -1;
    time_t starting;
    time(&starting);

    int clientesRestantes = 5;
    float duracionLlegada = 5.0;
    float duracionSalida = 5.0;




    ///Zona de memoria compartida
    SharedMem* shmPTR;
    key_t shmKey = ftok("./",'h');
    int shmID = shmget(shmKey , sizeof(struct SharedMem), IPC_CREAT | 0666);
    shmPTR = (SharedMem*)shmat(shmID,NULL,0);
    shmPTR->table1Client =true;
    shmPTR->table2Client =true;
    shmPTR->table3Client =true;
    shmPTR->client1leave = false;
    shmPTR->client2leave = false;
    shmPTR->client3leave = false;
    shmPTR->time = 120;
    std::cout<<shmPTR->table1Client<< ' '<<shmPTR->table2Client<< ' '<<shmPTR->table3Client<< ' '<<std::endl;

    signal (SIGALRM,handler1);


    alarm(1);

    ///creacion de procesos
    pid_t pid1, pid2;
    int status;
    pid1 = fork();
    if (pid1==0){
    ///hijo 1 entrada de los clientes
        int startTime;
        int rand3, rand2;
        bool clientin = true;
        while(true){

            if((shmPTR->table1Client)||(shmPTR->table2Client)||(shmPTR->table3Client)){
                rand3 = rand()%3;
                rand2 = rand()%2;
                if(clientin){
                    startTime = shmPTR->time;
                    clientin =false;
                }

                if(startTime-5>=shmPTR->time)
                    if((shmPTR->table1Client)&&(!shmPTR->table2Client)&&(!shmPTR->table3Client)){
                        clientin =true;
                        shmPTR->table1Client = false;

                    }else if((!shmPTR->table1Client)&&(shmPTR->table2Client)&&(!shmPTR->table3Client)){
                        clientin =true;
                        shmPTR->table2Client = false;

                    }else if((!shmPTR->table1Client)&&(!shmPTR->table2Client)&&(shmPTR->table3Client)){
                        clientin =true;
                        shmPTR->table3Client = false;

                    }else if((shmPTR->table1Client)&&(!shmPTR->table2Client)&&(shmPTR->table3Client)){
                        if(rand2 == 0){
                            clientin =true;
                            shmPTR->table1Client = false;
                        }else{
                            clientin =true;
                            shmPTR->table3Client = false;
                        }

                    }else if((shmPTR->table1Client)&&(shmPTR->table2Client)&&(!shmPTR->table3Client)){
                        if(rand2 == 0){
                            clientin =true;
                            shmPTR->table1Client = false;
                        }else{
                            clientin =true;
                            shmPTR->table2Client = false;
                        }

                    }else if((!shmPTR->table1Client)&&(shmPTR->table2Client)&&(shmPTR->table3Client)){
                        if(rand2 == 0){
                            clientin =true;
                            shmPTR->table2Client = false;
                        }else{
                            clientin =true;
                            shmPTR->table3Client = false;
                        }

                    }else if((shmPTR->table1Client)&&(shmPTR->table2Client)&&(shmPTR->table3Client)){
                        if(rand3 == 0){
                            clientin =true;
                            shmPTR->table1Client = false;
                        }else if(rand3 == 1){
                            clientin =true;
                            shmPTR->table2Client = false;
                        }else{
                            clientin =true;
                            shmPTR->table3Client = false;
                        }

                    }else {}
                }


        }

    }///final del hijo 1

    else{
        pid2 = fork();
        if(pid2==0){
        ///hijo 2 salida de clientes
            int start1Time, start2Time, start3Time;
            start1Time = start2Time = start3Time = -5;
            while(true){

            if((shmPTR->table1food)||(shmPTR->table2food)||(shmPTR->table3food)){
                if(shmPTR->client1out){
                shmPTR->client1out = false;

                    if(shmPTR->table1food){
                        start1Time = shmPTR->time;
                    }
                }
                if(shmPTR->client2out){
                shmPTR->client2out = false;

                    if(shmPTR->table2food){
                        start2Time = shmPTR->time;
                    }
                }
                if(shmPTR->client3out){
                shmPTR->client3out = false;

                    if(shmPTR->table3food){
                        start3Time = shmPTR->time;
                    }
                }

                if((start1Time-5)>=shmPTR->time){
                    if(shmPTR->table1food){
                        shmPTR->table1food = false;
                        shmPTR->client1leave = true;
                        shmPTR->table1Client = true;

                    }
                }
                if((start2Time-5)>=shmPTR->time){
                    if(shmPTR->table2food){
                        shmPTR->table2food = false;
                        shmPTR->client2leave = true;
                        shmPTR->table2Client = true;

                    }
                }
                if((start3Time-5)>=shmPTR->time){
                    if(shmPTR->table3food){
                        shmPTR->table3food = false;
                        shmPTR->client3leave = true;
                        shmPTR->table3Client = true;

                    }
                }

            }
        }
      }
    }///final del hijo 2

    if((pid1>0)&&(pid2>0)){
    ///padre logica general e impresion por pantalla
        sf::RenderWindow window(sf::VideoMode(WINDOW_H,WINDOW_V), TITLE);

        GraficoSFML graficos;

            for (size_t i =0 ; i< NUM_MESAS; i++)
            {
                graficos.VaciaTaburete(i);
            }
        while(window.isOpen())
        {
            //std::cout<< shmPTR->table3Client<<std::endl;
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

            if(graficos.clientesServidos>=5 || graficos.tiempoRestante<=0){
                window.close();
            }

            //graficos.Timer(starting);
            if(go1){
                graficos.Timer();
                go1 = false;
            }

            shmPTR->time = graficos.tiempoRestante;

            interactingObject = graficos.Colisionando(graficos.posicionJugador,graficos.aOrigenMesas,graficos.aOrigenDispensadores,graficos.sizeMesa);

             if(click == true){
            switch(interactingObject){

                    case -1:
                    //mantener

                    break;

                    case 0:
                    //depostiar
                    if(graficos.PedidoVacio(0) && !graficos.TabureteVacio(0)){

                        if(graficos.DejaComida(graficos.pedidos1[graficos.table1List])){
                        graficos.PonPedido(0,graficos.pedidos1[graficos.table1List]);
                        shmPTR->table1food = true;
                        shmPTR->client1out = true;
                        }
                    }
                    break;

                    case 1:
                    //depositar
                    if(graficos.PedidoVacio(1) && !graficos.TabureteVacio(1)){
                        if(graficos.DejaComida(graficos.pedidos2[graficos.table2List])){
                        graficos.PonPedido(1,graficos.pedidos2[graficos.table2List]);
                        shmPTR->table2food = true;
                        shmPTR->client2out = true;
                        }
                    }
                    break;

                    case 2:
                    //depositar
                    if(graficos.PedidoVacio(2) && !graficos.TabureteVacio(2)){
                        if(graficos.DejaComida(graficos.pedidos3[graficos.table3List])){
                        graficos.PonPedido(2,graficos.pedidos3[graficos.table3List]);
                        shmPTR->table3food = true;
                        shmPTR->client3out = true;
                        }
                    }
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

            if(shmPTR->client1leave){

            graficos.VaciaTaburete(0);
            graficos.VaciaPedido(0);
            shmPTR->client1leave = false;
            graficos.clientesServidos++;
            graficos.table1List++;

            }

            if(shmPTR->client2leave){

            graficos.VaciaTaburete(1);
            graficos.VaciaPedido(1);
            shmPTR->client2leave = false;
            graficos.clientesServidos++;
            graficos.table2List++;

            }

            if(shmPTR->client3leave){

            graficos.VaciaTaburete(2);
            graficos.VaciaPedido(2);
            shmPTR->client3leave = false;
            graficos.clientesServidos++;
            graficos.table3List++;

            }

            if(!shmPTR->table1Client){
            graficos.OcupaTaburete(0,graficos.pedidos1[graficos.table1List]);
            }
            if(!shmPTR->table2Client){
            graficos.OcupaTaburete(1,graficos.pedidos2[graficos.table2List]);
            }
            if(!shmPTR->table3Client){
            graficos.OcupaTaburete(2,graficos.pedidos3[graficos.table3List]);
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

        kill(pid1,SIGKILL);
        kill(pid2,SIGKILL);

    }///final proceso padre



    return 0;
}
