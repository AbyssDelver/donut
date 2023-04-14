#include <SFML/Graphics.hpp>  //SFML è la libreria grafica necessaria per visualizzare la ciambella. Il programma non funzionerà se non viene installata.
#include <SFML/Window.hpp>
#include <cmath>  //per seno e coseno
#include <iostream>

// ------costanti------------------------------------------------------------------------------------------------
float const phi_step = 0.05;  // determina spazio fra le circonferenze che compongono la ciambella
float const theta_step = 0.1;   //determina spazio fra i punti che formano una circonferenza della ciambella
float const a_step = 0.009; //quanto incrementa l'angolo intorno a un asse di rotazione
float const b_step = 0.0045; //quanto incrementa l'angolo intorno all'altro asse di rotazione
float const R_1 = 200;  // distanza del centro del buco della ciambella dal centro delle circonferenze
float const R_2 = 400;       // raggio della circonferenza della sezione
float const pi = 3.14159;    // numero pi greco
float const shape_size = 2;  // grandezza dei punti che formano la ciambella
std::vector<float> const displacement = {750, 750, 0}; //determina dove viene posto il centro della ciambella
std::vector<int> const color = {205, 255, 205}; //determina il colore della ciambella
// --------------------------------------------------------------------------------------------------------------


sf::CircleShape draw_circles(float x, float y) { //disegna un puntino sullo schermo, parametri sono coordinate
  sf::CircleShape shape(shape_size);
  shape.setPosition(x, y);
  shape.setFillColor(sf::Color(color[0], color[1], color[2]));
  return shape;
}

int main() {
  //gestione finestra
  sf::RenderWindow window;
  window.create(sf::VideoMode(1500, 1500), "ciambella!",
                sf::Style::Default);
  
  //inzializzo variabili necessarie per disegnare ciambella
  float A = 0; //angolo rotazione intorno a un asse
  float B = 0; //angolo di rotazione intorno all'altro
  float x_cor = 0;
  float y_cor = 0;

  //loop principale. si esce dal loop quando si chiude la finestra
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    window.clear(sf::Color::Black);  //fa ritornare la finestra nera
                                     
    //costruzione coordinate di ciascun punto che forma la ciambella
    //formula si trova su: https://www.a1k0n.net/2011/07/20/donut-math.html
    for (float phi = 0; phi <= 2 * pi; phi += phi_step) {
      for (float theta = 0; theta <= 2 * pi; theta += theta_step) {
        x_cor = displacement[0] +
                (R_2 + R_1 * cos(theta)) *
                    (cos(B) * cos(phi) + sin(A) * sin(B) * sin(phi)) -
                R_1 * cos(A) * sin(B) * sin(theta);
        y_cor = displacement[1] +
                (R_2 + R_1 * cos(theta)) *
                    (cos(phi) * sin(B) - cos(B) * sin(A) * sin(phi)) +
                R_1 * cos(A) * cos(B) * sin(theta);
        //disegna il punto
        window.draw(draw_circles(x_cor, y_cor));
      }
    }

    //incrementa angoli 
    A += a_step;
    B += b_step;

    window.display();  //aggiorna la finestra
  }
}