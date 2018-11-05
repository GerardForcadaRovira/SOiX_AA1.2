#include "GraficoSFML.h"
#include <iostream>
#include <signal.h>

/*#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"*/

GraficoSFML::GraficoSFML():posicionJugador(sf::Vector2f(385.f,285.f)),jugador(30.f)
{
    //ctor
    clientesServidos = 0;
    tiempoRestante = 120;
    numClientesRestantes = 5;
    font.loadFromFile("courier.ttf");
    aOrigenMesas.push_back(sf::Vector2f(120,85));
    aOrigenMesas.push_back(sf::Vector2f(120,255));
    aOrigenMesas.push_back(sf::Vector2f(120,425));

    aOrigenDispensadores.push_back(sf::Vector2f(650, 85));
    aOrigenDispensadores.push_back(sf::Vector2f(650, 255));
    aOrigenDispensadores.push_back(sf::Vector2f(650, 425));

    InitContadorClientes();
    InitContadorTiempo();
    InitTaburetes();
    InitPedidos();
    InitObjetosFijos();
    InitPlayer();

    table1List = 0;
    table2List = 0;
    table3List = 0;

    for(int i = 0;i<30;i++){
        int randomNum = rand()%3;
        if(randomNum == 0)
        pedidos1[i]= COMIDA_VERDE;
        if(randomNum == 1)
        pedidos1[i]= COMIDA_AMARILLA;
        if(randomNum == 2)
        pedidos1[i]= COMIDA_ROJA;

        randomNum = rand()%3;
        if(randomNum == 0)
        pedidos2[i]= COMIDA_VERDE;
        if(randomNum == 1)
        pedidos2[i]= COMIDA_AMARILLA;
        if(randomNum == 2)
        pedidos2[i]= COMIDA_ROJA;

        randomNum = rand()%3;
        if(randomNum == 0)
        pedidos3[i]= COMIDA_VERDE;
        if(randomNum == 1)
        pedidos3[i]= COMIDA_AMARILLA;
        if(randomNum == 2)
        pedidos3[i]= COMIDA_ROJA;
    }
}

void GraficoSFML::InitContadorTiempo()
{
    sf::Text txtCounterTime;
    txtCounterTime.setFont(font);
    txtCounterTime.setPosition(10,10);
    txtCounterTime.setFillColor(sf::Color::White);
    txtCounterTime.setCharacterSize(14);
    txtCounterTime.setString(std::to_string(tiempoRestante)+" seg.");
    aTextosADibujar.push_back(txtCounterTime);
}

void GraficoSFML::InitContadorClientes()
{
    sf::Text txtCounterClients;
    txtCounterClients.setFont(font);
    txtCounterClients.setPosition(120,10);
    txtCounterClients.setFillColor(sf::Color::White);
    txtCounterClients.setCharacterSize(14);
    txtCounterClients.setString(std::to_string(numClientesRestantes)+" clientes");
    aTextosADibujar.push_back(txtCounterClients);
    aTextosADibujar[0].setString(std::to_string(clientesServidos)+" clientes servidos");
}

void GraficoSFML::InitTaburetes()
{
    sf::CircleShape shape(30.f);
    shape.setFillColor(TABURETE_VACIO);
    shape.setPosition(sf::Vector2f(10,120));
    aTaburetesADibujar[0] = shape;
    shape.setPosition(sf::Vector2f(10,290));
    aTaburetesADibujar[1] = shape;
    shape.setPosition(sf::Vector2f(10,460));
    aTaburetesADibujar[2] = shape;

}

void GraficoSFML::InitPedidos()
{
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(25,25));
    shape.setFillColor(PEDIDO_VACIO);

    shape.setPosition(sf::Vector2f(80,135));
    aPedidosADibujar[0] = shape;

    shape.setPosition(sf::Vector2f(80,305));
    aPedidosADibujar[1] = shape;

    shape.setPosition(sf::Vector2f(80,475));
    aPedidosADibujar[2] = shape;

}

void GraficoSFML::InitPlayer()
{
    jugador.setFillColor(sf::Color::Cyan);
    jugador.setPosition(posicionJugador);

    manoIzquierda.setSize(sf::Vector2f(25,25));
    manoIzquierda.setFillColor(PEDIDO_VACIO);
    manoIzquierda.setPosition(sf::Vector2f(posicionJugador.x-25,posicionJugador.y));

    manoDerecha.setSize(sf::Vector2f(25,25));
    manoDerecha.setFillColor(PEDIDO_VACIO);
    manoDerecha.setPosition(sf::Vector2f(posicionJugador.x+25+35,posicionJugador.y));

}

void GraficoSFML::InitObjetosFijos()
{
    sf::RectangleShape mesaShape;
    mesaShape.setSize(MESA_SIZE);
    mesaShape.setFillColor(sf::Color(150,150,150));

    for(size_t i = 0; i<NUM_MESAS; i++)
    {
        mesaShape.setPosition(aOrigenMesas[i]);
        aObjetosADibujar.push_back(mesaShape);
    }

    sf::RectangleShape dispensadorShape;
    dispensadorShape.setSize(DISPENSADOR_SIZE);
    dispensadorShape.setFillColor(sf::Color(150,150,150));

    for(size_t i = 0; i < aOrigenDispensadores.size(); i++)
    {
        dispensadorShape.setPosition(aOrigenDispensadores[i]);
        aObjetosADibujar.push_back(dispensadorShape);
    }

    sf::RectangleShape comidaDispensadorShape;
    comidaDispensadorShape.setSize(sf::Vector2f(25,25));
    comidaDispensadorShape.setFillColor(COMIDA_VERDE);
    comidaDispensadorShape.setPosition(sf::Vector2f(687,135));
    aObjetosADibujar.push_back(comidaDispensadorShape);
    comidaDispensadorShape.setFillColor(COMIDA_AMARILLA);
    comidaDispensadorShape.setPosition(sf::Vector2f(687,305));
    aObjetosADibujar.push_back(comidaDispensadorShape);
    comidaDispensadorShape.setFillColor(COMIDA_ROJA);
    comidaDispensadorShape.setPosition(sf::Vector2f(687,475));
    aObjetosADibujar.push_back(comidaDispensadorShape);


}

bool GraficoSFML::TabureteVacio(int _posicion)
{
    sf::Color color = aTaburetesADibujar[_posicion].getFillColor();
    if (color == TABURETE_VACIO)
    {
        return true;
    }
    return false;
}

bool GraficoSFML::PedidoVacio(int _posicion)
{
    sf::Color color = aPedidosADibujar[_posicion].getFillColor();
    if (color == PEDIDO_VACIO)
    {
        return true;
    }
    return false;
}

void GraficoSFML::OcupaTaburete(int _posicion, sf::Color colorTabu)
{
    aTaburetesADibujar[_posicion].setFillColor(colorTabu);
}

void GraficoSFML::VaciaTaburete(int _posicion)
{
    aTaburetesADibujar[_posicion].setFillColor(TABURETE_VACIO);
}

void GraficoSFML::VaciaPedido(int _posicion)
{
    aPedidosADibujar[_posicion].setFillColor(PEDIDO_VACIO);
}

void GraficoSFML::PonPedido(int _posicion, sf::Color _queComida)
{
    aPedidosADibujar[_posicion].setFillColor(_queComida);
}

void GraficoSFML::CogeComida(sf::Color _queComida)
{
    if (manoIzquierda.getFillColor() == PEDIDO_VACIO)
    {
        manoIzquierda.setFillColor(_queComida);
        return;
    }
    else if (manoDerecha.getFillColor() == PEDIDO_VACIO)
    {
        manoDerecha.setFillColor(_queComida);
        return;
    }
}

bool GraficoSFML::DejaComida(sf::Color _queComida)
{
    if (manoIzquierda.getFillColor() == _queComida)
    {
        manoIzquierda.setFillColor(PEDIDO_VACIO);
        return true;
    }
    else if (manoDerecha.getFillColor() == _queComida)
    {
        manoDerecha.setFillColor(PEDIDO_VACIO);
        return true;
    }
    return false;
}

 void GraficoSFML::MueveJugador(sf::Vector2f _posicion)
 {
    posicionJugador = _posicion;
    jugador.setPosition(posicionJugador);
    manoIzquierda.setPosition(sf::Vector2f(posicionJugador.x-25,posicionJugador.y));
    manoDerecha.setPosition(sf::Vector2f(posicionJugador.x+25+35,posicionJugador.y));

 }

 int GraficoSFML::Colisionando(sf::Vector2f ubicacion, std::vector<sf::Vector2f> fOrigenMesas,std::vector<sf::Vector2f> fOrigenDispensadores, sf::Vector2f tamanoMesa){

    int returnInt;
    int tamanoX = tamanoMesa.x/2;
    int tamanoY = tamanoMesa.y/2;

    if(ubicacion.x > fOrigenMesas[0].x - tamanoX && ubicacion.x < fOrigenMesas[0].x + tamanoX && ubicacion.y > fOrigenMesas[0].y - tamanoY && ubicacion.y < fOrigenMesas[0].y + tamanoY){
        returnInt = 0;
    } else

    if(ubicacion.x > fOrigenMesas[1].x - tamanoX && ubicacion.x < fOrigenMesas[1].x + tamanoX && ubicacion.y > fOrigenMesas[1].y - tamanoY && ubicacion.y < fOrigenMesas[1].y + tamanoY){
        returnInt = 1;
    } else

    if(ubicacion.x > fOrigenMesas[2].x - tamanoX && ubicacion.x < fOrigenMesas[2].x + tamanoX && ubicacion.y > fOrigenMesas[2].y - tamanoY && ubicacion.y < fOrigenMesas[2].y + tamanoY){
        returnInt = 2;
    } else

    if(ubicacion.x > fOrigenDispensadores[0].x - tamanoX && ubicacion.x < fOrigenDispensadores[0].x + tamanoX && ubicacion.y > fOrigenDispensadores[0].y - tamanoY && ubicacion.y < fOrigenDispensadores[0].y + tamanoY){
        returnInt = 3;
    } else

    if(ubicacion.x > fOrigenDispensadores[1].x - tamanoX && ubicacion.x < fOrigenDispensadores[1].x + tamanoX && ubicacion.y > fOrigenDispensadores[1].y - tamanoY && ubicacion.y < fOrigenDispensadores[1].y + tamanoY){
        returnInt = 4;
    } else

    if(ubicacion.x > fOrigenDispensadores[2].x - tamanoX && ubicacion.x < fOrigenDispensadores[2].x + tamanoX && ubicacion.y > fOrigenDispensadores[2].y - tamanoY && ubicacion.y < fOrigenDispensadores[2].y + tamanoY){
        returnInt = 5;
    } else {
        returnInt = -1;
    }



    return returnInt;
 }

 void GraficoSFML::Timer(){


    //std::cout << spanse << std::endl;




        tiempoRestante--;



        aTextosADibujar[1].setString(std::to_string(tiempoRestante)+" seg.");
        aTextosADibujar[0].setString(std::to_string(clientesServidos)+" clientes servidos");

       // txtCounterTime.setString(std::to_string(tiempoRestante)+" seg.");


};



GraficoSFML::~GraficoSFML()
{
    //dtor
}
