#ifndef GRAFICOSFML_H
#define GRAFICOSFML_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#define TABURETE_VACIO sf::Color::White
#define TABURETE_OCUPADO sf::Color::Magenta
#define NUM_MESAS 3

#define PEDIDO_VACIO sf::Color::Black
#define COMIDA_VERDE sf::Color::Green
#define COMIDA_AMARILLA sf::Color::Yellow
#define COMIDA_ROJA sf::Color::Red

#define MESA_SIZE sf::Vector2f(100,120)
#define DISPENSADOR_SIZE sf::Vector2f(100,120)

class GraficoSFML
{
    public:
        sf::CircleShape jugador;
        sf::RectangleShape manoIzquierda;
        sf::RectangleShape manoDerecha;

        std::vector<sf::RectangleShape> aObjetosADibujar;
        std::vector<sf::Text> aTextosADibujar;
        sf::CircleShape aTaburetesADibujar[NUM_MESAS];
        sf::RectangleShape aPedidosADibujar[NUM_MESAS];

        int tiempoRestante;
        int numClientesRestantes;
        sf::Vector2f posicionJugador;

        std::vector<sf::Vector2f> aOrigenMesas;
        std::vector<sf::Vector2f> aOrigenDispensadores;
        sf::Vector2f sizeMesa = MESA_SIZE;

        GraficoSFML();
        bool TabureteVacio(int _posicion);
        bool PedidoVacio(int _posicion);
        void OcupaTaburete(int _posicion);
        void VaciaTaburete(int _posicion);

        void VaciaPedido(int _posicion);
        void PonPedido(int _posicion, sf::Color _queComida);

        void CogeComida(sf::Color _queComida);

        //Retorna false si la comida que tiene que dejar no la tiene en ninguna de las dos manos.
        bool DejaComida(sf::Color _queComida);

        void MueveJugador(sf::Vector2f _posicion);
        int Colisionando(sf::Vector2f ubicacion, std::vector<sf::Vector2f> fOrigenMesas,std::vector<sf::Vector2f> fOrigenDispensadores, sf::Vector2f tamanoMesa);

        void Timer(time_t &startTime);

        virtual ~GraficoSFML();

    protected:

    private:

        sf::Font font;

        void InitContadorTiempo();
        void InitContadorClientes();
        void InitTaburetes();
        void InitPedidos();
        void InitObjetosFijos();
        void InitPlayer();

};

#endif // GRAFICOSFML_H
