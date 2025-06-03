#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <sstream>
#include <functional>

//#include <conio.h>
//#include <Windows.h>
//#include <fstream>
//#include <mmsystem.h>

//#include <chrono>

//#include <ctime> 
//#include <algorithm>
//#include <iomanip>
//#include <limits>

using namespace std;
using namespace sf;

//estructura del producto
struct producto {
    int idProducto;
    int ordenEntrada;
    string fechaRegistro;
    string modelo;
    string material;
    string precio;
    string costoFabricacion;
    string dimensiones;
    string stock;
    string color;
    string capacidad;
    string tipoColchon;
};

struct cliente {
    int idCliente;
    int ordeEntrada;
    string fechaRegistro;
    string nombre;
    string apellido;
    string direccion;
    string telefono;
    string email;
    string municipio;
    string departamento;
    string totalGastado;
    string metodoPagoPref;
};

struct proveedor {
    int idProveedor;
    int ordenEntrada;
    string fechaIngreso;
    string nombreEmpresa;
    string contacto;
    string telefono;
    string email;
    string direccion;
    string tipoProducto;
    string totalGastado;
    string metodoPago;
    string tiempoEntrega;

};

struct empleado {
    int idEmpleado;
    int ordenEntrada;
    string fechaIngreso;
    string nombre;
    string apellido;
    string cargo;
    string salario;
    string telefono;
    string email;
    string direccion;
    string horasTrabajadas;
    string turno;
    
};

struct ReporteProduccion {
    int idReporte; 
    int ordenFicha;
    string fecha;
    string turno;
    string camasProducidas;
    string camasDefectuosas;
    string horasTrabajadas;
    string supervisor;
    string observaciones;
};

//Estructura de los nodos

struct NodoPila {
    struct producto produc;
    NodoPila* siguiente;
}*primero;

struct NodoCola {
    struct cliente infor;
    NodoCola* siguienteC;
} *primeroC, * ultimoC;

struct NodoLista {
    struct proveedor prove;
    NodoLista* siguienteL;
} *primeroL, * ultimoL;


struct NodoListaDoble {
    struct empleado emplea;
    NodoListaDoble* siguienteLD;
    NodoListaDoble* atrasLD;
} *primeroLD, * ultimoLD;

struct NodoCircular {
    struct ReporteProduccion report;
    NodoCircular* siguienteLC;
} *primeroLC, * ultimoLC;

NodoPila* pila = NULL;
NodoCola* cola = NULL;
NodoLista* lista = NULL;
NodoListaDoble* listaDoble = NULL;
NodoCircular* listaCircular = NULL;

//Prototipos de funciones
//Funciones de diseño
void pantallaBienvenida();

int menu(const char*, const char* [], int);
void menuPrincipal();
void subMenu1();
void subMenu2();
void subMenu3();
void subMenu4();
void subMenu5();

//Funciones para pila
void insertarNodoPila(NodoPila*&);
void desplegarPila(NodoPila*&, RenderWindow&);
NodoPila* buscarNodoPila(NodoPila*&, const string&);
void eliminarNodoPila(NodoPila*&);
void vaciarPila(NodoPila*&);
void modificarNodoPila(NodoPila*& );
string fichaPila(NodoPila*);
void mostrarNodoPila(NodoPila*&, RenderWindow&, float, float, float, float);

//Funciones para cola
string fichaCola(NodoCola*);
void insertarNodoCola(NodoCola*&);
void desplegarCola(NodoCola*&, RenderWindow&);
void eliminarNodoCola(NodoCola*&);
void vaciarCola(NodoCola*&);
NodoCola* buscarNodoCola(NodoCola*, const string&);
void modificarNodoCola(NodoCola*&);
void mostrarNodoCola(NodoCola*&, RenderWindow&, float, float, float, float);

//Funciones para lista
string fichaLista(NodoLista*);
void insertarNodoLista(NodoLista*&);
void desplegarLista(NodoLista*&, RenderWindow&);
void vaciarLista(NodoLista*&);
NodoLista* buscarNodoLista(NodoLista*&, const string&);
void modificarNodoLista(NodoLista*&);
void eliminarNodoLista(NodoLista*&);
void mostrarNodoLista(NodoLista*&, RenderWindow&, float, float, float, float);

//Funciones para Lista doble
string fichaListaDoble(NodoListaDoble*);
void insertarNodoListaDoble(NodoListaDoble*&);
void desplegarListaDoblePU(NodoListaDoble*&, RenderWindow&);
void desplegarListaDobleUP(NodoListaDoble*&, RenderWindow&);
void eliminarNodoListaDoble(NodoListaDoble*&);
void vaciarListaDoble(NodoListaDoble*&);
NodoListaDoble* buscarNodoListaDoble(NodoListaDoble*, const string&);
void modificarNodoListaDoble(NodoListaDoble*&);
void mostrarNodoListaDoble(NodoListaDoble*&, RenderWindow&, float, float, float, float);

//Funciones para Lista circular
string fichaListaCircular(NodoCircular*);
void insertarNodoListaCircular(NodoCircular*&);
void desplegarListaCircular(NodoCircular*&, RenderWindow&);
void eliminarNodoListaCircular(NodoCircular*&);
void vaciarListaCircular(NodoCircular*&);
NodoCircular* buscarNodoListaCircular(NodoCircular*, const string&);
void modificarNodoListaCircular(NodoCircular*&);
void mostrarNodoListaCircular(NodoCircular*&, RenderWindow&, float, float, float, float);

//Funciones 
string fechaActual();
int generarID();
void alerta(RenderWindow&, const string&);
bool mouseSobre(const RectangleShape&, const Vector2f&);
vector<string> mostrarFormulario(RenderWindow&, const vector<string>&, string, string);


string formularioID(RenderWindow&);
string formularioCampo(RenderWindow&, const string& );

//funciones para la cola

void pantallaBienvenida() {
    RenderWindow window(VideoMode(800, 600), "FÁBRICA DE CAMAS");

    Font font;
    if (!font.loadFromFile("PressStart2P.ttf")) {
        cerr << "No se pudo cargar la fuente." << endl;
        return;
    }

    // Sonido
    SoundBuffer buffer;
    Sound sonidoIntro;
    if (buffer.loadFromFile("intro.wav")) {
        sonidoIntro.setBuffer(buffer);
        sonidoIntro.play();
    }

    // Colores
    Color colorFondo(10, 10, 30);          // Azul oscuro
    Color colorTitulo(0, 255, 255);        // Cian neón
    Color colorSubtitulo(255, 0, 255);     // Fucsia neón
    Color colorTexto(0, 255, 128);         // Verde neón
    Color colorBordes(0, 255, 213);        // Verde menta
    Color colorDetalle(147, 94, 255);      // Morado neón

    // Marco 
    RectangleShape marco(Vector2f(720, 540));
    marco.setPosition(40, 30);
    marco.setFillColor(Color(15, 15, 45));
    marco.setOutlineColor(colorBordes);
    marco.setOutlineThickness(10);

    // Marquesina 
    RectangleShape marquesina(Vector2f(720, 60));
    marquesina.setPosition(40, 30);
    marquesina.setFillColor(colorDetalle);

    // Título
    Text titulo("FABRICA DE CAMAS", font, 28);
    titulo.setFillColor(colorTitulo);
    FloatRect boundsTitulo = titulo.getLocalBounds();
    titulo.setOrigin(boundsTitulo.width / 2, boundsTitulo.height / 2);
    titulo.setPosition(400, -100); // Empieza fuera de pantalla
    float velocidadY = 150.0f;

    //Nombre
    Text nombre("NOMBRE", font, 28);
    nombre.setFillColor(colorTitulo);
    FloatRect boundsNombre = titulo.getLocalBounds();
    nombre.setOrigin(boundsNombre.width / 2, boundsNombre.height / 2);
    nombre.setPosition(550, -200); // Empieza fuera de pantalla

    // Subtítulo
    Text subtitulo("PRESIONA UNA TECLA PARA CONTINUAR", font, 10);
    subtitulo.setFillColor(colorSubtitulo);
    FloatRect boundsSub = subtitulo.getLocalBounds();
    subtitulo.setOrigin(boundsSub.width / 2, boundsSub.height / 2);
    Vector2f subtituloBasePos(400, 520);

    // Integrantes
    vector<string> integrantes = {
        "INTEGRANTES:",
        "Carla Marina Chumil Sequen          2290-23-14690",
        "William Eduardo Yoc Chalcu          2290-23-11497",
        "Maria Natividad Velazquez Sequec    2290-23-14631"
    };

    vector<Text> textosIntegrantes;
    for (size_t i = 0; i < integrantes.size(); ++i) {
        Text txt(integrantes[i], font, 10);
        txt.setFillColor(colorTexto);
        FloatRect bounds = txt.getLocalBounds();
        txt.setOrigin(bounds.width / 2, bounds.height / 2);
        txt.setPosition(400, 280 + i * 25);
        textosIntegrantes.push_back(txt);
    }

    // Botones decorativos
    vector<CircleShape> botones;
    Color coloresBotones[] = {
        Color(255, 50, 50),
        Color(255, 226, 89),
        Color(45, 255, 196)
    };
    for (int i = 0; i < 3; ++i) {
        CircleShape btn(12);
        btn.setFillColor(coloresBotones[i]);
        btn.setPosition(110 + i * 40, 480);
        botones.push_back(btn);
    }

    // Luces laterales
    vector<CircleShape> luces;
    for (int y = 100; y <= 500; y += 60) {
        CircleShape luz(5);
        luz.setFillColor(Color(255, 20, 147));
        luz.setPosition(55, y);
        luces.push_back(luz);
        luz.setPosition(740, y);
        luces.push_back(luz);
    }

    // Scanlines 
    vector<RectangleShape> scanlines;
    for (int y = 0; y < 600; y += 4) {
        RectangleShape line(Vector2f(800, 1));
        line.setPosition(0, y);
        line.setFillColor(Color(0, 0, 0, 40));
        scanlines.push_back(line);
    }

    Clock clock;
    float alpha = 0;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed || event.type == Event::KeyPressed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();
        alpha += deltaTime;

        // Animar título descendente
        if (titulo.getPosition().y < 150)
            titulo.move(0, velocidadY * deltaTime);

        // Animar nombre descendente
        if (nombre.getPosition().y < 200)
            nombre.move(0, velocidadY * deltaTime);

        // Glitch en el título
        if (static_cast<int>(alpha * 10) % 10 == 0) {
            titulo.setPosition(400 + rand() % 3 - 1, titulo.getPosition().y + rand() % 3 - 1);
        }

        // Glitch en el nombre
        if (static_cast<int>(alpha * 10) % 10 == 0) {
            nombre.setPosition(550 + rand() % 3 - 1, nombre.getPosition().y + rand() % 3 - 1);
        }

        // Parpadeo subtítulo
        float brillo = abs(sin(alpha * 4)) > 0.5 ? 255 : 0;
        subtitulo.setFillColor(Color(colorSubtitulo.r, colorSubtitulo.g, colorSubtitulo.b, static_cast<Uint8>(brillo)));
        subtitulo.setPosition(subtituloBasePos.x + sin(alpha * 3) * 6, subtituloBasePos.y);

        Texture camaTexture;
        if (!camaTexture.loadFromFile("cama.png")) {}
        Sprite camaSprite(camaTexture);
        camaSprite.setPosition(550, 350);  // Posición deseada
        
        window.clear(colorFondo);
        window.draw(marco);
        window.draw(marquesina);
        window.draw(titulo);
        window.draw(nombre);
        window.draw(camaSprite);
        for (auto& txt : textosIntegrantes) window.draw(txt);
        for (auto& b : botones) window.draw(b);
        for (auto& l : luces) window.draw(l);
        window.draw(subtitulo);
        for (auto& s : scanlines) window.draw(s);
        window.display();
    }
}

int menu(const char* titulo, const char* opciones[], int n) {
    RenderWindow window(VideoMode(800, 800), "Menú");

    // Fuente estilo arcade
    Font font;
    if (!font.loadFromFile("PressStart2P.ttf")) {
        cerr << "No se pudo cargar la fuente." << endl;
        return -1;
    }

    // Sonidos
    SoundBuffer bufferMover, bufferSeleccionar;
    if (!bufferMover.loadFromFile("navegar.wav") || !bufferSeleccionar.loadFromFile("seleccionar.wav")) {
        cerr << "No se pudieron cargar los sonidos." << endl;
        return -1;
    }
    Sound sonidoMover(bufferMover);
    Sound sonidoSeleccionar(bufferSeleccionar);

    int opcionSeleccionada = 0;

    // Colores
    Color fondoColor(10, 10, 30);              // Azul oscuro
    Color tituloColor(0, 255, 255);            // Cian neón
    Color opcionColorNormal(0, 255, 128);      // Verde neón
    Color opcionColorActiva(255, 0, 255);      // Fucsia neón
    Color ayudaColor(255, 255, 0);             // Amarillo neón

    Text txtTitulo(titulo, font, 22);
    txtTitulo.setFillColor(tituloColor);
    FloatRect boundsTitulo = txtTitulo.getLocalBounds();
    txtTitulo.setOrigin(boundsTitulo.width / 2, boundsTitulo.height / 2);
    txtTitulo.setPosition(400, 70);

    // Ayuda
    Text ayuda("Usa las teclas direccionales para navegar. ENTER para seleccionar.", font, 10);
    ayuda.setFillColor(ayudaColor);
    FloatRect ayudaBounds = ayuda.getLocalBounds();
    ayuda.setOrigin(ayudaBounds.width / 2, 0);
    ayuda.setPosition(700, 550);

    // Opciones
    vector<Text> textosOpciones;
    for (int i = 0; i < n; ++i) {
        Text txt(string(to_string(i + 1) + ". " + opciones[i]), font, 14);
        txt.setFillColor(opcionColorNormal);
        FloatRect bounds = txt.getLocalBounds();
        txt.setOrigin(bounds.width / 2, bounds.height / 2);
        txt.setPosition(400, 180 + i * 50);
        textosOpciones.push_back(txt);
    }

    // Scanlines
    vector<RectangleShape> scanlines;
    for (int y = 0; y < 600; y += 4) {
        RectangleShape line(Vector2f(800, 1));
        line.setPosition(0, y);
        line.setFillColor(Color(0, 0, 0, 50));
        scanlines.push_back(line);
    }

    Clock clock;
    float alpha = 0;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Up) {
                    opcionSeleccionada = (opcionSeleccionada - 1 + n) % n;
                    sonidoMover.play();
                }
                else if (event.key.code == Keyboard::Down) {
                    opcionSeleccionada = (opcionSeleccionada + 1) % n;
                    sonidoMover.play();
                }
                else if (event.key.code == Keyboard::Enter) {
                    sonidoSeleccionar.play();
                    sleep(milliseconds(300));
                    window.close();
                    return opcionSeleccionada + 1;
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();
        alpha += deltaTime;

        // Parpadeo suave en opción activa
        float brillo = (abs(sin(alpha * 3)) > 0.5) ? 255 : 120;

        // Onda en texto de ayuda
        ayuda.setPosition(400 + sin(alpha * 2) * 5, 550);

        // Dibujar fondo
        window.clear(fondoColor);
        window.draw(txtTitulo);

        // Dibujar opciones
        for (int i = 0; i < n; ++i) {
            if (i == opcionSeleccionada) {
                textosOpciones[i].setFillColor(Color(opcionColorActiva.r, opcionColorActiva.g, opcionColorActiva.b, brillo));
            }
            else {
                textosOpciones[i].setFillColor(opcionColorNormal);
            }
            window.draw(textosOpciones[i]);
        }

        // Dibujar ayuda
        window.draw(ayuda);

        // Dibujar scanlines
        for (auto& line : scanlines)
            window.draw(line);

        window.display();
    }

    return -1;
}

void menuPrincipal()
{
    bool rep = true;
    int op = 0;
    const char* titulo = "* MENU PRINCIPAL *";
    const char* opciones[] = { "* GESTION DE PRODUCTOS <PILA>           *","* GESTION DE CLIENTES <COLA>            *","* GESTION DE PROVEEDORES <LISTA SIMPLE> *","* GESTION DE EMPLEADOS <LISTA DOBLE>    *","* GESTION DE REPORTES <LISTA CIRCULAR>  *","* SALIR                                 *" };
    int n = 5;

    do
    {
        op = menu(titulo, opciones, n);
        switch (op) {
        case 1:
            subMenu1();
            break;

        case 2:
            subMenu2();
            break;

        case 3:
            subMenu3();
            break;

        case 4:
            subMenu4();
            break;
        case 5:
            subMenu5();
            break;
        case 6:

            rep = false;

            break;
        }

    } while (rep);

}

void subMenu1()
{
    bool rep = true;
    int op = 0;
    const char* titulo = "* GESTION DE PRODUCTOS *";
    const char* opciones[] = { "* INGRESAR PRODUCTO  *","* VER PRODUCTO       *","* BUSCAR PRODUCTO    *","* MODIFICAR PRODUCTO *","* ELIMINAR PRODUCTO  *","* VACIAR PILA        *", "* SALIR              *" };
    int n = 7;
    
    do
    {
        op = menu(titulo, opciones, n);
        switch (op) {
        case 1:
            insertarNodoPila(pila);

            break;

        case 2:
        {
            RenderWindow window(VideoMode(700, 1000), "Visualizar Pila");
            sf::View view(sf::FloatRect(0, 0, 700, 1000));
            window.setView(view);

            while (window.isOpen()) {
                Event event;
                while (window.pollEvent(event)) {
                    if (event.type == Event::Closed)
                        window.close();

                    // Scroll con rueda del ratón
                    if (event.type == sf::Event::MouseWheelScrolled) {
                        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                            float delta = event.mouseWheelScroll.delta;
                            view.move(0, -delta * 30);  // Mueve la vista verticalmente
                            window.setView(view);
                        }
                    }

                    // Opcional: Scroll con teclas
                    if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Up)
                            view.move(0, -30);
                        else if (event.key.code == sf::Keyboard::Down)
                            view.move(0, 30);
                        window.setView(view);
                    }

                }

                window.clear(Color(10, 10, 30));
                desplegarPila(pila, window);
                window.display();
            }
        }

        break;

        case 3:
        {
            if (pila == nullptr) {
                RenderWindow alertaWin(VideoMode(500, 50), "Alerta");
                alerta(alertaWin, "LA PILA ESTÁ VACÍA");
                break;
            }

            RenderWindow window(VideoMode(500, 200), "Formulario ID");
            string idStr = formularioID(window);
            window.close();

            NodoPila* nodo = buscarNodoPila(pila, idStr);
            if (nodo == nullptr) return;

            RenderWindow mostrarWin(VideoMode(700, 430), "Nodo encontrado");
            while (mostrarWin.isOpen()) {
                Event e;
                while (mostrarWin.pollEvent(e)) {
                    if (e.type == Event::Closed)
                        mostrarWin.close();
                }
                mostrarWin.clear(Color(10, 10, 30));
                mostrarNodoPila(nodo, mostrarWin, 50, 50, 600, 350);
                mostrarWin.display();
            }

        }
            break;

        case 4:
            modificarNodoPila(pila);
            break;

        case 5:
            eliminarNodoPila(pila);
            break;

        case 6:
            vaciarPila(pila);
            break;

        case 7:
            rep = false;
            break;
        }


    } while (rep);

}

void subMenu2()
{
    bool rep = true;
    int op = 0;
    const char* titulo = "* GESTION DE CLIENTES *";
    const char* opciones[] = { "* INGRESAR CLIENTE  *","* VER CLIENTE       *","* BUSCAR CLIENTE    *","* MODIFICAR CLIENTE *","* ELIMINAR CLIENTE  *","* VACIAR COLA        *", "* SALIR              *" };
    int n = 7;
    
    do
    {
        op = menu(titulo, opciones, n);
        switch (op) {
        case 1:
            insertarNodoCola(cola);
            break;

        case 2:
        {
            
            if (cola == nullptr) {
                RenderWindow alertaWin(VideoMode(500, 50), "Alerta");
                alerta(alertaWin, "LA COLA ESTÁ VACÍA");
                break;
            }

            RenderWindow window(VideoMode(1000, 500), "Visualizar Cola");
            sf::View view(sf::FloatRect(0, 0, 1000, 500));
            window.setView(view);

            while (window.isOpen()) {
                Event event;
                while (window.pollEvent(event)) {
                    if (event.type == Event::Closed)
                        window.close();

                    if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Left)
                            view.move(-30, 0);  // Mover a la izquierda
                        else if (event.key.code == sf::Keyboard::Right)
                            view.move(30, 0);   // Mover a la derecha
                        window.setView(view);
                    }

                }

                window.clear(Color(10, 10, 30));
                desplegarCola(cola, window);
                window.display();
            }
        }
        break;

        case 3:
        {
            if (cola == nullptr) {
                RenderWindow alertaWin(VideoMode(500, 50), "Alerta");
                alerta(alertaWin, "LA COLA ESTÁ VACÍA");
                break;
            }

            RenderWindow window(VideoMode(500, 200), "Formulario ID");
            string idStr = formularioID(window);
            window.close();

            NodoCola* nodo = buscarNodoCola(cola, idStr);
            if (nodo == nullptr) {
                // Ya se muestra alerta en buscarNodoCola
                break;
            }

            RenderWindow mostrarWin(VideoMode(400, 500), "Nodo encontrado");
            while (mostrarWin.isOpen()) {
                Event e;
                while (mostrarWin.pollEvent(e)) {
                    if (e.type == Event::Closed)
                        mostrarWin.close();
                }

                mostrarWin.clear(Color(10, 10, 30));
                mostrarNodoCola(nodo, mostrarWin, 50, 50, 300, 400);
                mostrarWin.display();
            }

            break;
        }

            break;

        case 4:
            modificarNodoCola(cola);
            break;

        case 5:
            eliminarNodoCola(cola);
            break;

        case 6:
            vaciarCola(cola);
            break;

        case 7:
            rep = false;
            break;
        }


    } while (rep);

}

void subMenu3()
{
    bool rep = true;
    int op = 0;
    const char* titulo = "* GESTION DE PROVEEDORES *";
    const char* opciones[] = { "* INGRESAR PROVEEDOR  *","* VER PROVEEDOR       *","* BUSCAR PROVEEDOR    *","* MODIFICAR PROVEEDOR *","* ELIMINAR PROVEEDOR  *","* VACIAR LISTA        *", "* SALIR               *" };
    int n = 7;

    do
    {
        op = menu(titulo, opciones, n);
        switch (op) {
        case 1:
            insertarNodoLista(lista);
            break;

        case 2:
        {

            if (lista == nullptr) {
                RenderWindow alertaWin(VideoMode(500, 50), "Alerta");
                alerta(alertaWin, "LA LISTA ESTÁ VACÍA");
                break;
            }

            RenderWindow window(VideoMode(1000, 500), "Visualizar Lista");
            sf::View view(sf::FloatRect(0, 0, 1000, 500));
            window.setView(view);

            while (window.isOpen()) {
                Event event;
                while (window.pollEvent(event)) {
                    if (event.type == Event::Closed)
                        window.close();

                    if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Left)
                            view.move(-30, 0);  // Mover a la izquierda
                        else if (event.key.code == sf::Keyboard::Right)
                            view.move(30, 0);   // Mover a la derecha
                        window.setView(view);
                    }

                }

                window.clear(Color(10, 10, 30));
                desplegarLista(lista, window);
                window.display();
            }
        }
        break;

        case 3:
        {
            if (lista == nullptr) {
                RenderWindow alertaWin(VideoMode(500, 50), "Alerta");
                alerta(alertaWin, "LA LISTA ESTÁ VACÍA");
                break;
            }

            RenderWindow window(VideoMode(500, 200), "Formulario ID");
            string idStr = formularioID(window);
            window.close();

            NodoLista* nodo = buscarNodoLista(lista, idStr);
            if (nodo == nullptr) return;

            RenderWindow mostrarWin(VideoMode(400, 500), "Nodo encontrado");
            while (mostrarWin.isOpen()) {
                Event e;
                while (mostrarWin.pollEvent(e)) {
                    if (e.type == Event::Closed)
                        mostrarWin.close();
                }
                mostrarWin.clear(Color(10, 10, 30));
                mostrarNodoLista(nodo, mostrarWin, 50, 50, 300, 400);
                mostrarWin.display();
            }

        }
        break;

        case 4:
            modificarNodoLista(lista);
            break;

        case 5:
            eliminarNodoLista(lista);
            break;

        case 6:
            vaciarLista(lista);
            break;

        case 7:
            rep = false;
            break;
        }


    } while (rep);

}

void subMenu4()
{
    bool rep = true;
    int op = 0;
    const char* titulo = "* GESTION DE EMPLEADOS *";
    const char* opciones[] = { "* INGRESAR EMPLEADO          *","* VER EMPLEADO (ASCENDENTE)  *","* VER EMPLEADO (DESCENDENTE) *","* BUSCAR EMPLEADO            *","* MODIFICAR EMPLEADO         *","* ELIMINAR EMPLEADO          *","* VACIAR LISTA               *", "* SALIR                      *" };
    int n = 8;

    do
    {
        op = menu(titulo, opciones, n);
        switch (op) {
        case 1:
            insertarNodoListaDoble(listaDoble);
            break;

        case 2:
        {

            if (listaDoble == NULL) {
                RenderWindow alertaWin(VideoMode(500, 50), "Alerta");
                alerta(alertaWin, "LA LISTA DOBLE ESTÁ VACÍA");
                break;
            }

            RenderWindow window(VideoMode(1000, 500), "Visualizar Lista Doble");
            sf::View view(sf::FloatRect(0, 0, 1000, 500));
            window.setView(view);

            while (window.isOpen()) {
                Event event;
                while (window.pollEvent(event)) {
                    if (event.type == Event::Closed)
                        window.close();

                    if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Left)
                            view.move(-30, 0);  // Mover a la izquierda
                        else if (event.key.code == sf::Keyboard::Right)
                            view.move(30, 0);   // Mover a la derecha
                        window.setView(view);
                    }

                }

                window.clear(Color(10, 10, 30));
                desplegarListaDoblePU(listaDoble, window);
                window.display();
            }
        }
        break;
        case 3:
        {

            if (listaDoble == nullptr) {
                RenderWindow alertaWin(VideoMode(500, 50), "Alerta");
                alerta(alertaWin, "LA LISTA DOBLE ESTÁ VACÍA");
                break;
            }

            RenderWindow window(VideoMode(1000, 500), "Visualizar Lista");
            sf::View view(sf::FloatRect(0, 0, 1000, 500));
            window.setView(view);

            while (window.isOpen()) {
                Event event;
                while (window.pollEvent(event)) {
                    if (event.type == Event::Closed)
                        window.close();

                    if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Left)
                            view.move(-30, 0);  // Mover a la izquierda
                        else if (event.key.code == sf::Keyboard::Right)
                            view.move(30, 0);   // Mover a la derecha
                        window.setView(view);
                    }

                }

                window.clear(Color(10, 10, 30));
                desplegarListaDobleUP(listaDoble, window);
                window.display();
            }
        }
        break;

        case 4:
        {
            if (listaDoble == nullptr) {
                RenderWindow alertaWin(VideoMode(500, 50), "Alerta");
                alerta(alertaWin, "LA LISTA DOBLE ESTÁ VACÍA");
                break;
            }

            RenderWindow window(VideoMode(500, 200), "Formulario ID");
            string idStr = formularioID(window);
            window.close();

            NodoListaDoble* nodo = buscarNodoListaDoble(listaDoble, idStr);
            if (nodo == nullptr) return;

            RenderWindow mostrarWin(VideoMode(400, 500), "Nodo encontrado");
            while (mostrarWin.isOpen()) {
                Event e;
                while (mostrarWin.pollEvent(e)) {
                    if (e.type == Event::Closed)
                        mostrarWin.close();
                }
                mostrarWin.clear(Color(10, 10, 30));
                mostrarNodoListaDoble(nodo, mostrarWin, 50, 50, 300, 400);
                mostrarWin.display();
            }

        }
        break;

        case 5:
            modificarNodoListaDoble(listaDoble);
            break;

        case 6:
            eliminarNodoListaDoble(listaDoble);
            break;

        case 7:
            vaciarListaDoble(listaDoble);
            break;

        case 8:
            rep = false;
            break;
        }


    } while (rep);

}

void subMenu5()
{
    bool rep = true;
    int op = 0;
    const char* titulo = "* GESTION DE REPORTES *";
    const char* opciones[] = { "* INGRESAR PROVEEDOR  *","* VER PROVEEDOR       *","* BUSCAR PROVEEDOR    *","* MODIFICAR PROVEEDOR *","* ELIMINAR PROVEEDOR  *","* VACIAR LISTA        *", "* SALIR               *" };
    int n = 7;

    do
    {
        op = menu(titulo, opciones, n);
        switch (op) {
        case 1:
            insertarNodoListaCircular(listaCircular);
            break;

        case 2:
        {

            if (listaCircular == nullptr) {
                RenderWindow alertaWin(VideoMode(500, 50), "Alerta");
                alerta(alertaWin, "LA LISTA ESTÁ VACÍA");
                break;
            }

            RenderWindow window(VideoMode(1000, 1000), "Visualizar Lista");

            while (window.isOpen()) {
                Event e;
                while (window.pollEvent(e)) {
                    if (e.type == Event::Closed)
                        window.close();
                }

                window.clear(Color(20, 20, 40));
                desplegarListaCircular(listaCircular, window);
                window.display();
            }

        }
        break;

        case 3:
        {
            if (lista == nullptr) {
                RenderWindow alertaWin(VideoMode(500, 50), "Alerta");
                alerta(alertaWin, "LA LISTA ESTÁ VACÍA");
                break;
            }

            RenderWindow window(VideoMode(500, 200), "Formulario ID");
            string idStr = formularioID(window);
            window.close();

            NodoLista* nodo = buscarNodoLista(lista, idStr);
            if (nodo == nullptr) return;

            RenderWindow mostrarWin(VideoMode(400, 500), "Nodo encontrado");
            while (mostrarWin.isOpen()) {
                Event e;
                while (mostrarWin.pollEvent(e)) {
                    if (e.type == Event::Closed)
                        mostrarWin.close();
                }
                mostrarWin.clear(Color(10, 10, 30));
                mostrarNodoLista(nodo, mostrarWin, 50, 50, 300, 400);
                mostrarWin.display();
            }

        }
        break;

        case 4:
            modificarNodoLista(lista);
            break;

        case 5:
            eliminarNodoLista(lista);
            break;

        case 6:
            vaciarLista(lista);
            break;

        case 7:
            rep = false;
            break;
        }


    } while (rep);

}

string fechaActual() {
    // Obtener la fecha actual
    time_t t = time(nullptr);
    struct tm tiempo;

#ifdef _WIN32
    localtime_s(&tiempo, &t);
#else
    localtime_r(&t, &tiempo);
#endif

    // Formatear la fecha en "dd/mm/yyyy"
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", &tiempo);
    return string(buffer);
}

int generarID() {
    static std::mt19937 generador(static_cast<unsigned int>(time(nullptr)));
    std::uniform_int_distribution<int> distribucion(100, 999); // IDs de 3 dígitos
    return distribucion(generador);
}

void alerta(RenderWindow& window, const string& mensaje) {
    Font font;
    if (!font.loadFromFile("Geo.ttf")) {
        cerr << "No se pudo cargar la fuente.\n";
        return;
    }

    Text texto;
    texto.setFont(font);
    texto.setString(mensaje);
    texto.setCharacterSize(30);
    texto.setFillColor(Color::Magenta);
    texto.setPosition((window.getSize().x-400) / 2, (window.getSize().y - 50) / 2);

    window.draw(texto);
    window.display();
    sleep(seconds(2));
}

bool mouseSobre(const RectangleShape& rect, const Vector2f& mousePos) {
    return rect.getGlobalBounds().contains(mousePos);
}

vector<string> mostrarFormulario(RenderWindow& window, const vector<string>& etiquetas, string orden, string id) {

    Font fuente;
    fuente.loadFromFile("arcade.ttf");

    vector<string> contenidos(etiquetas.size(), "");
    vector<bool> escribiendo(etiquetas.size(), false);
    vector<Text> etiquetasTexto;
    vector<RectangleShape> campos;
    vector<Text> textosRender;

    const float fieldWidth = 400;
    const float fieldHeight = 50;
    const float spacing = 80;
    const float etiquetasX = 100.f;
    const float camposX = 300.f;
    const float camposTextoOffset = 10.f;
    float startY = 100;

    for (size_t i = 0; i < etiquetas.size(); ++i) {
        float y = startY + i * spacing;

        Text label(etiquetas[i] + ":", fuente, 22);
        label.setFillColor(Color::Cyan);
        label.setPosition(etiquetasX, y);
        etiquetasTexto.push_back(label);

        RectangleShape campo({ fieldWidth, fieldHeight });
        campo.setPosition(camposX, y);
        campo.setFillColor(Color::Transparent);
        campo.setOutlineColor(Color::Magenta);
        campo.setOutlineThickness(3);
        campos.push_back(campo);

        Text texto;
        texto.setFont(fuente);
        texto.setCharacterSize(22);
        texto.setFillColor(Color::Cyan);
        texto.setPosition(camposX + camposTextoOffset, y + 10);
        textosRender.push_back(texto);
    }

    // Botón
    RectangleShape boton({ 200, 50 });
    boton.setOrigin(80, 0);
    boton.setPosition(window.getSize().x / 2.f, startY + etiquetas.size() * spacing);
    boton.setFillColor(Color::Transparent);
    boton.setOutlineColor(Color::Magenta);
    boton.setOutlineThickness(3);

    Text textoBoton("GUARDAR", fuente, 28);
    textoBoton.setFillColor(Color::Cyan);
    textoBoton.setPosition(boton.getPosition().x - 60, boton.getPosition().y + 10);

    // Datos adicionales
    string fecha = fechaActual();
    Text textoFecha("FECHA: " + fecha, fuente, 20);
    textoFecha.setFillColor(Color::Cyan);
    textoFecha.setPosition(10, 10);

    Text textoId("ID: " + id, fuente, 28);
    textoId.setFillColor(Color::Cyan);
    textoId.setPosition(camposX, 50);

    Text textoOrden("FORMULARIO No: " + orden, fuente, 20);
    textoOrden.setFillColor(Color::Cyan);
    textoOrden.setPosition(600, 10);

    bool terminado = false;
    while (window.isOpen() && !terminado) {
        Event evento;
        while (window.pollEvent(evento)) {
            if (evento.type == Event::Closed) {
                window.close();
                return {};
            }

            if (evento.type == Event::MouseButtonPressed) {
                Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
                for (size_t i = 0; i < campos.size(); ++i)
                    escribiendo[i] = campos[i].getGlobalBounds().contains(mouse);
                if (boton.getGlobalBounds().contains(mouse)) {
                    terminado = true;
                }
            }

            if (evento.type == Event::TextEntered && evento.text.unicode < 128) {
                char letra = static_cast<char>(evento.text.unicode);
                for (size_t i = 0; i < campos.size(); ++i) {
                    if (escribiendo[i]) {
                        if (letra == 8 && !contenidos[i].empty()) {
                            contenidos[i].pop_back();
                        }
                        else if (letra >= 32 && letra <= 126) {
                            contenidos[i] += letra;
                        }
                        textosRender[i].setString(contenidos[i]);
                    }
                }
            }

            if (evento.type == Event::KeyPressed) {
                int actual = -1;
                for (size_t i = 0; i < escribiendo.size(); ++i)
                    if (escribiendo[i]) actual = i;

                if (evento.key.code == Keyboard::Tab || evento.key.code == Keyboard::Down) {
                    if (actual != -1) escribiendo[actual] = false;
                    actual = (actual + 1) % escribiendo.size();
                    escribiendo[actual] = true;
                }

                if (evento.key.code == Keyboard::Up) {
                    if (actual != -1) escribiendo[actual] = false;
                    actual = (actual - 1 + escribiendo.size()) % escribiendo.size();
                    escribiendo[actual] = true;
                }

                if (evento.key.code == Keyboard::Enter) {
                    if (actual == escribiendo.size() - 1) {
                        terminado = true;
                    }
                    else if (actual != -1) {
                        escribiendo[actual] = false;
                        escribiendo[actual + 1] = true;
                    }
                }
            }
        }

        window.clear(Color(15, 15, 30));

        for (size_t i = 0; i < campos.size(); ++i) {
            campos[i].setOutlineColor(escribiendo[i] ? Color::Yellow : Color::Magenta);
            window.draw(etiquetasTexto[i]);
            window.draw(campos[i]);
            window.draw(textosRender[i]);
        }

        window.draw(boton);
        window.draw(textoBoton);
        window.draw(textoFecha);
        window.draw(textoOrden);
        window.draw(textoId);
        window.display();
    }

    return contenidos;
}

string formularioID(RenderWindow& window) {
    Font font;
    if (!font.loadFromFile("Orbitron.ttf")) {
        cerr << "No se pudo cargar la fuente.\n";
        return "";
    }

    string input = "";
    Text inputText;
    inputText.setFont(font);
    inputText.setCharacterSize(30);
    inputText.setFillColor(Color::White);
    inputText.setPosition(50, 50);

    Text etiqueta;
    etiqueta.setFont(font);
    etiqueta.setString("Ingrese el ID:");
    etiqueta.setCharacterSize(30);
    etiqueta.setFillColor(Color::Cyan);
    etiqueta.setPosition(50, 100);

    RectangleShape box(Vector2f(400, 50));
    box.setPosition(50, 50);
    box.setFillColor(Color(0, 0, 0, 150));
    box.setOutlineColor(Color::Cyan);
    box.setOutlineThickness(2);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if (!input.empty())
                        input.pop_back();
                }
                else if (event.text.unicode == '\r') {
                    return input; // Enter presionado
                }
                else if (event.text.unicode < 128 && input.size() < 20) {
                    input += static_cast<char>(event.text.unicode);
                }
            }
        }

        inputText.setString(input);

        window.clear(Color(10, 10, 30));
        window.draw(box);
        window.draw(etiqueta);
        window.draw(inputText);
        window.display();
    }

    return "";
}

string formularioCampo(RenderWindow& window, const string& etiquetaTexto) {
    Font font;
    if (!font.loadFromFile("Orbitron.ttf")) {
        cerr << "No se pudo cargar la fuente.\n";
        return "";
    }

    string input = "";
    Text inputText;
    inputText.setFont(font);
    inputText.setCharacterSize(30);
    inputText.setFillColor(Color::White);
    inputText.setPosition(150, 200);

    Text etiqueta;
    etiqueta.setFont(font);
    etiqueta.setString(etiquetaTexto);
    etiqueta.setCharacterSize(30);
    etiqueta.setFillColor(Color::Cyan);
    etiqueta.setPosition(150, 150);

    RectangleShape box(Vector2f(500, 50));
    box.setPosition(145, 195);
    box.setFillColor(Color(0, 0, 0, 150));
    box.setOutlineColor(Color::Cyan);
    box.setOutlineThickness(2);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if (!input.empty())
                        input.pop_back();
                }
                else if (event.text.unicode == '\r') {
                    return input;
                }
                else if (event.text.unicode < 128 && input.size() < 20) {
                    input += static_cast<char>(event.text.unicode);
                }
            }
        }

        inputText.setString(input);

        window.clear(Color(10, 10, 30));
        window.draw(box);
        window.draw(etiqueta);
        window.draw(inputText);
        window.display();
    }

    return "";
}

void mostrarNodoPila(NodoPila*& nodo, RenderWindow& ventana, float x, float y, float ancho, float alto) {

    Font fuente;
    if (!fuente.loadFromFile("Orbitron.ttf")) {
        cerr << "No se pudo cargar la fuente.\n";
        return;
    }

    // Rectángulo
    RectangleShape rect(Vector2f(ancho, alto));
    rect.setFillColor(Color::Transparent);
    rect.setOutlineColor(Color(0, 255, 255));
    rect.setOutlineThickness(2);
    rect.setPosition(x, y);

    // Texto con datos del nodo actual
    Text texto(fichaPila(nodo), fuente, 20);
    texto.setFillColor(Color(0, 255, 255));
    texto.setPosition(x + 10, y + 10);

    ventana.draw(rect);
    ventana.draw(texto);
}

string fichaPila(NodoPila* nodo) {
    vector<string> etiquetas = {
    "ID: ", "Ficha No: ", "Fecha: ",
    "Modelo: ", "Material: ", "Precio: ",
    "Costo: ", "Dimensiones: ", "Stock: ",
    "Color: ", "Capacidad: ", "Colchon: "
    };
    if (nodo == nullptr) return "";

    ostringstream ss;
    ss << "Direccion de memoria: " << nodo << '\n';
    ss << etiquetas[0] << nodo->produc.idProducto << '\n';
    ss << etiquetas[1] << nodo->produc.ordenEntrada << '\n';
    ss << etiquetas[2] << nodo->produc.fechaRegistro << '\n';
    ss << etiquetas[3] << nodo->produc.modelo << '\n';
    ss << etiquetas[4] << nodo->produc.material << '\n';
    ss << etiquetas[5] << nodo->produc.precio << '\n';
    ss << etiquetas[6] << nodo->produc.costoFabricacion << '\n';
    ss << etiquetas[7] << nodo->produc.dimensiones << '\n';
    ss << etiquetas[8] << nodo->produc.stock << '\n';
    ss << etiquetas[9] << nodo->produc.color << '\n';
    ss << etiquetas[10] << nodo->produc.capacidad << '\n';
    ss << etiquetas[11] << nodo->produc.tipoColchon << '\n';
    return ss.str();
}

void insertarNodoPila(NodoPila*& pila) {

    NodoPila* nuevo = new NodoPila();

        static int ordenP = 0;
        ++ordenP;

        nuevo->produc.idProducto = generarID();
        nuevo->produc.ordenEntrada = ordenP;
        nuevo->produc.fechaRegistro = fechaActual();
        
        

        string orden = to_string(nuevo->produc.ordenEntrada);
        string id = to_string(nuevo->produc.idProducto);

        RenderWindow window(VideoMode(900, 900), "FORMULARIO PRODUCTOS", Style::Close);

        vector<string> etiquetas = { "Modelo", "Material", "Precio", "Costo", "Dimensiones","Stock", "Color", "Capacidad", "Colchon" };

        vector<string> datosProducto = mostrarFormulario(window, etiquetas, orden, id);
       
        if (datosProducto.size() != etiquetas.size()) return;

            nuevo->produc.modelo = datosProducto[0];
            nuevo->produc.material = datosProducto[1];
            nuevo->produc.precio = datosProducto[2];
            nuevo->produc.costoFabricacion = datosProducto[3];
            nuevo->produc.dimensiones = datosProducto[4];
            nuevo->produc.stock = datosProducto[5];
            nuevo->produc.color = datosProducto[6];
            nuevo->produc.capacidad = datosProducto[7];
            nuevo->produc.tipoColchon = datosProducto[8];
        

        nuevo->siguiente = pila;
        pila = nuevo;

        RenderWindow alertaWindow(VideoMode(500, 50), "Confirmacion");
        alerta(alertaWindow, "NODO INSERTADO CORRECTAMENTE");
}

void desplegarPila(NodoPila*& pila, RenderWindow& ventana) {
    float x = 50;
    float y = 50;
    float ancho = 600;
    float alto = 350;

    if (pila != NULL) {

        NodoPila* actual = pila;
        while (actual != nullptr) {
            mostrarNodoPila(actual, ventana, x, y, ancho, alto);
            y += alto + 10;
            actual = actual->siguiente;
        }
    }
    else {
        RenderWindow ventanaAlerta(VideoMode(500, 50), "Alerta");
        alerta(ventanaAlerta, "LA PILA ESTA VACIA");
        ventana.close();
        return;

    }
}

NodoPila* buscarNodoPila(NodoPila*& pila, const string& idStr) {
    int idBuscado;
    try {
        idBuscado = std::stoi(idStr);
    }
    catch (...) {
        RenderWindow alertaWindow(VideoMode(500, 50), "Error");
        alerta(alertaWindow, "ID inválido");
        return nullptr;
    }

    NodoPila* aux = pila;
    while (aux != nullptr) {
        if (aux->produc.idProducto == idBuscado) {
            return aux;
        }
        aux = aux->siguiente;
    }

    RenderWindow alertaWindow(VideoMode(500, 50), "Alerta");
    alerta(alertaWindow, "NODO NO ENCONTRADO");
    return nullptr;
}

void eliminarNodoPila(NodoPila*& pila)
{
    NodoPila* aux = new NodoPila;
    aux = pila;

    if (pila != NULL)
    {
        pila = aux->siguiente; // Actualizar el puntero siguiente del nodo anterior
        delete aux;

    }
    else
    {
        RenderWindow ventanaAlerta(VideoMode(500, 50), "Alerta");
        alerta(ventanaAlerta, "LA PILA ESTA VACIA");
        return;
    }
}

void vaciarPila(NodoPila*& pila)
{
    NodoPila* actual = new NodoPila;
    actual = pila;

    if (pila != NULL)
    {
        while (actual->siguiente = NULL);
        {
            actual = actual->siguiente;
            delete actual;
        }
        pila = NULL;
        RenderWindow ventanaAlerta(VideoMode(500, 50), "Confirmacion");
        alerta(ventanaAlerta, "LA PILA A SIDO VACIADA");
        return;
    }
    else
    {
        RenderWindow ventanaAlerta(VideoMode(500, 50), "Alerta");
        alerta(ventanaAlerta, "LA PILA ESTA VACIA");
        return;
    }
}

void modificarNodoPila(NodoPila*& pila) {

    if (pila == nullptr) {
        RenderWindow alertaWin(VideoMode(500, 50), "Alerta");
        alerta(alertaWin, "LA PILA ESTÁ VACÍA");
        return;
    }

    // Pedir ID
    RenderWindow window(VideoMode(500, 200), "Formulario ID");
    string idStr = formularioID(window);
    window.close();

    NodoPila* nodo = buscarNodoPila(pila, idStr);
    if (nodo == nullptr) return;

    // Mostrar nodo actual
    RenderWindow mostrarWin(VideoMode(700, 430), "Nodo encontrado");
    while (mostrarWin.isOpen()) {
        Event e;
        while (mostrarWin.pollEvent(e)) {
            if (e.type == Event::Closed)
                mostrarWin.close();
        }
        mostrarWin.clear(Color(10, 10, 30));
        mostrarNodoPila(nodo, mostrarWin,50, 50, 600, 350);
        mostrarWin.display();
    }

    bool rep = true;
    int op = 0;
    const char* titulo = "OPCIONES DE MODIFICACION DEL NODO";
    const char* opciones[] = { "MODELO     ", "MATERIAL   ", "PRECIO     ", "COSTO      ", "DIMENSIONES","STOCK      ", "COLOR      ", "CAPACIDAD  ", "COLCHON    ", "SALIR      " };
    int no = 10;

    RenderWindow form(VideoMode(800, 600), "Modificar nodo");

    do
    {
        op = menu(titulo, opciones, no);
        switch (op) {

        case 1: {
            string nuevoModelo = formularioCampo(form, "Nuevo modelo:");
            form.close();
            nodo->produc.modelo = nuevoModelo;
            break;
        }
        case 2:
        {
            string nuevoMaterial = formularioCampo(form, "Nuevo material:");
            form.close();
            nodo->produc.material = nuevoMaterial;
            break;
        }
        case 3:
        {
            string nuevoPrecio = formularioCampo(form, "Nuevo precio:");
            form.close();
            nodo->produc.precio = nuevoPrecio;
            break;
        }
        case 4:
        {
            string nuevoCosto = formularioCampo(form, "Nuevo costo:");
            form.close();
            nodo->produc.costoFabricacion = nuevoCosto;
            break;
        }
        case 5:
        {
            string nuevoDimensiones = formularioCampo(form, "Nuevo dimensiones:");
            form.close();
            nodo->produc.dimensiones = nuevoDimensiones;
            break;
        }
        case 6:
        {
            string nuevoStock = formularioCampo(form, "Nuevo stock:");
            form.close();
            nodo->produc.stock = nuevoStock;
            break;
        }
        case 7:
        {
            string nuevoColor = formularioCampo(form, "Nuevo color:");
            form.close();
            nodo->produc.color = nuevoColor;
            break;
        }
        case 8:
        {
            string nuevoCapacidad = formularioCampo(form, "Nuevo capacidad:");
            form.close();
            nodo->produc.capacidad = nuevoCapacidad;
            break;
        }
        case 9:
        {
            string nuevoColchon = formularioCampo(form, "Nuevo colchon:");
            form.close();
            nodo->produc.tipoColchon = nuevoColchon;
            break;
        }
        case 10:
            rep = false;
            break;
        }

        RenderWindow confirm(VideoMode(500, 50), "Confirmación");
        alerta(confirm, "Nodo modificado correctamente");
        break;

    } while (rep);

    return;

}

void mostrarNodoCola(NodoCola*& nodo, RenderWindow& ventana, float x, float y, float ancho, float alto) {

    Font fuente;
    if (!fuente.loadFromFile("Orbitron.ttf")) {
        cerr << "No se pudo cargar la fuente.\n";
        return;
    }

    // Rectángulo
    RectangleShape rect(Vector2f(ancho, alto));
    rect.setFillColor(Color::Transparent);
    rect.setOutlineColor(Color(0, 255, 255));
    rect.setOutlineThickness(2);
    rect.setPosition(x, y);

    // Texto con datos del nodo actual
    Text texto(fichaCola(nodo), fuente, 20);
    texto.setFillColor(Color(0, 255, 255));
    texto.setPosition(x + 10, y + 10);

    ventana.draw(rect);
    ventana.draw(texto);
}

string fichaCola(NodoCola* nodo) {
    vector<string> etiquetas = {
    "ID: ", "Ficha No: ", "Fecha: ",
    "Nombre: ", "Apellido: ", "Direccion: ",
    "Telefono: ", "Email: ", "Municipio: ",
    "Departamento: ", "Total Gastado: ", "Metodo de\nPago: "
    };
    if (nodo == nullptr) return "";

    ostringstream ss;
    ss << "Direccion de memoria: \n"<< nodo << '\n';
    ss << etiquetas[0] << nodo->infor.idCliente << '\n';
    ss << etiquetas[1] << nodo->infor.ordeEntrada << '\n';
    ss << etiquetas[2] << nodo->infor.fechaRegistro << '\n';
    ss << etiquetas[3] << nodo->infor.nombre << '\n';
    ss << etiquetas[4] << nodo->infor.apellido << '\n';
    ss << etiquetas[5] << nodo->infor.direccion << '\n';
    ss << etiquetas[6] << nodo->infor.telefono << '\n';
    ss << etiquetas[7] << nodo->infor.email << '\n';
    ss << etiquetas[8] << nodo->infor.municipio << '\n';
    ss << etiquetas[9] << nodo->infor.departamento << '\n';
    ss << etiquetas[10] << nodo->infor.totalGastado << '\n';
    ss << etiquetas[11] << nodo->infor.metodoPagoPref << '\n';
    return ss.str();

}

void insertarNodoCola(NodoCola*& cola) {

    NodoCola* nuevo = new NodoCola();

    static int ordenC = 0;
    ++ordenC;

    nuevo->infor.idCliente = generarID();
    nuevo->infor.ordeEntrada = ordenC;
    nuevo->infor.fechaRegistro = fechaActual();

    string orden = to_string(nuevo->infor.ordeEntrada);
    string id = to_string(nuevo->infor.idCliente);

    RenderWindow window(VideoMode(900, 900), "FORMULARIO CLIENTES", Style::Close);

    vector<string> etiquetas = { "Nombre", "Apellido", "Direccion", "Telefono", "Email", "Municipio","Departamento", "Total\nGastado", "Metodo de\nPago" };

    vector<string> datosProducto = mostrarFormulario(window, etiquetas, orden, id);

    if (datosProducto.size() != etiquetas.size()) return;

    nuevo->infor.nombre = datosProducto[0];
    nuevo->infor.apellido = datosProducto[1];
    nuevo->infor.direccion = datosProducto[2];
    nuevo->infor.telefono = datosProducto[3];
    nuevo->infor.email = datosProducto[4];
    nuevo->infor.municipio= datosProducto[5];
    nuevo->infor.departamento = datosProducto[6];
    nuevo->infor.totalGastado = datosProducto[7];
    nuevo->infor.metodoPagoPref = datosProducto[8];

    cola = nuevo;

    if (primeroC == NULL) {
        primeroC = nuevo;
        primeroC->siguienteC = NULL;
        ultimoC = nuevo;
    }
    else {
        ultimoC->siguienteC = nuevo;
        nuevo->siguienteC = NULL;
        ultimoC = nuevo;
    }

    RenderWindow alertaWindow(VideoMode(500, 50), "Confirmacion");
    alerta(alertaWindow, "NODO INSERTADO CORRECTAMENTE");
}

void desplegarCola(NodoCola*& cola, RenderWindow& ventana) {
    float x = 50;
    float y = 50;
    float ancho = 300;
    float alto = 400;

    if (cola != NULL) {

        NodoCola* actual = new NodoCola();
        actual = primeroC;

        while (actual != nullptr) {
            mostrarNodoCola(actual, ventana,x, y, ancho, alto);
            x += ancho + 10;
            actual = actual->siguienteC;
        }
    }
}

void eliminarNodoCola(NodoCola*& cola)
{
    NodoCola* actual = new NodoCola();
    actual = primeroC;

    if (primeroC != NULL)
    {
        primeroC = primeroC->siguienteC; // Actualizar el puntero siguiente del nodo anterior
        delete actual;
    }
    else
    {
        RenderWindow ventanaAlerta(VideoMode(500, 50), "Alerta");
        alerta(ventanaAlerta, "LA COLA ESTA VACIA");
        return;
    }
}

void vaciarCola(NodoCola*& cola)
{
    NodoCola* actual = new NodoCola();
    actual = primeroC;

    if (primeroC != NULL)
    {
        while (primeroC != NULL)
        {
            actual = primeroC;
            primeroC = primeroC->siguienteC;
            delete actual;
        }
        cola = NULL;

        RenderWindow ventanaAlerta(VideoMode(500, 50), "Confirmacion");
        alerta(ventanaAlerta, "LA COLA A SIDO VACIADA");
        return;
    }
    else
    {
        RenderWindow ventanaAlerta(VideoMode(500, 50), "Alerta");
        alerta(ventanaAlerta, "LA COLA ESTA VACIA");
        return;
    }

}

NodoCola* buscarNodoCola(NodoCola* cola, const string& idStr) {
    int idBuscado;
    try {
        idBuscado = stoi(idStr);
    }
    catch (const invalid_argument&) {
        RenderWindow alertaWindow(VideoMode(500, 50), "Error");
        alerta(alertaWindow, "ID no es un número válido");
        return nullptr;
    }
    catch (const out_of_range&) {
        RenderWindow alertaWindow(VideoMode(500, 50), "Error");
        alerta(alertaWindow, "ID fuera de rango");
        return nullptr;
    }

    NodoCola* aux = primeroC;
    while (aux != nullptr) {
        if (aux->infor.idCliente == idBuscado) {
            return aux;
        }
        aux = aux->siguienteC;
    }

    RenderWindow alertaWindow(VideoMode(500, 50), "Alerta");
    alerta(alertaWindow, "Nodo con ID no encontrado");
    return nullptr;
}

void modificarNodoCola(NodoCola*& cola) {

    if (cola == nullptr) {
        RenderWindow alertaWin(VideoMode(500, 50), "Alerta");
        alerta(alertaWin, "LA COLA ESTÁ VACÍA");
        return;
    }

    // Pedir ID
    RenderWindow window(VideoMode(500, 200), "Formulario ID");
    string idStr = formularioID(window);
    window.close();

    NodoCola* nodo = buscarNodoCola(cola, idStr);
    if (nodo == nullptr) return;

    // Mostrar nodo actual
    RenderWindow mostrarWin(VideoMode(400, 500), "Nodo encontrado");
    while (mostrarWin.isOpen()) {
        Event e;
        while (mostrarWin.pollEvent(e)) {
            if (e.type == Event::Closed)
                mostrarWin.close();
        }
        mostrarWin.clear(Color(10, 10, 30));
        mostrarNodoCola(nodo, mostrarWin, 50, 50, 300, 400);
        mostrarWin.display();
    }

    bool rep = true;
    int op = 0;
    const char* titulo = "OPCIONES DE MODIFICACION DEL NODO";
    const char* opciones[] = { "NOMBRE        ", "APELLIDO      ", "DIRECCION     ", "TELEFONO      ", "EMAIL         ","MUNICIPIO     ", "DEPARTAMENTO  ", "TOTAL GASTADO ", "METODO DE PAGO", "SALIR         " };
    int no = 10;

    RenderWindow form(VideoMode(800, 600), "Modificar nodo");

    do
    {
        op = menu(titulo, opciones, no);
        switch (op) {

        case 1: {
            string nuevoNombre = formularioCampo(form, "Nuevo Nombre:");
            form.close();
            nodo->infor.nombre = nuevoNombre;
            break;
        }
        case 2:
        {
            string nuevoApellido = formularioCampo(form, "Nuevo apellido:");
            form.close();
            nodo->infor.apellido = nuevoApellido;
            break;
        }
        case 3:
        {
            string nuevoDireccion = formularioCampo(form, "Nuevo direccion:");
            form.close();
            nodo->infor.direccion = nuevoDireccion;
            break;
        }
        case 4:
        {
            string nuevoTelefono = formularioCampo(form, "Nuevo telefono:");
            form.close();
            nodo->infor.telefono = nuevoTelefono;
            break;
        }
        case 5:
        {
            string nuevoEmail = formularioCampo(form, "Nuevo email:");
            form.close();
            nodo->infor.email = nuevoEmail;
            break;
        }
        case 6:
        {
            string nuevoMunicipio = formularioCampo(form, "Nuevo municipio:");
            form.close();
            nodo->infor.municipio = nuevoMunicipio;
            break;
        }
        case 7:
        {
            string nuevoDepartamento = formularioCampo(form, "Nuevo departamento:");
            form.close();
            nodo->infor.departamento = nuevoDepartamento;
            break;
        }
        case 8:
        {
            string nuevoTotal = formularioCampo(form, "Nuevo total gastado:");
            form.close();
            nodo->infor.totalGastado = nuevoTotal;
            break;
        }
        case 9:
        {
            string nuevoMetodo = formularioCampo(form, "Nuevo metodo de pago:");
            form.close();
            nodo->infor.metodoPagoPref = nuevoMetodo;
            break;
        }
        case 10:
            rep = false;
            break;
        }

        RenderWindow confirm(VideoMode(500, 50), "Confirmación");
        alerta(confirm, "NODO MODIFICADO CORRECTAMENTE");
        break;

    } while (rep);

    return;

}

void mostrarNodoLista(NodoLista*& nodo, RenderWindow& ventana, float x, float y, float ancho, float alto) {

    Font fuente;
    if (!fuente.loadFromFile("Orbitron.ttf")) {
        cerr << "No se pudo cargar la fuente.\n";
        return;
    }

    // Rectángulo
    RectangleShape rect(Vector2f(ancho, alto));
    rect.setFillColor(Color::Transparent);
    rect.setOutlineColor(Color(0, 255, 255));
    rect.setOutlineThickness(2);
    rect.setPosition(x, y);

    // Texto con datos del nodo actual
    Text texto(fichaLista(nodo), fuente, 20);
    texto.setFillColor(Color(0, 255, 255));
    texto.setPosition(x + 10, y + 10);

    ventana.draw(rect);
    ventana.draw(texto);
}

string fichaLista(NodoLista* nodo) {
    vector<string> etiquetas = {
    "ID: ", "Ficha No: ", "Fecha: ",
    "Empresa: ", "Contacto: ", "Direccion: ",
    "Telefono: ", "Email: ", "Tipo de\nproducto: ",
    "Tiempo de\nentrega: ", "Total Gastado: ", "Metodo de\nPago: "
    };

    if (nodo == nullptr) return "";

    ostringstream ss;
    ss << "Direccion de memoria: \n" << nodo << '\n';
    ss << etiquetas[0] << nodo->prove.idProveedor << '\n';
    ss << etiquetas[1] << nodo->prove.ordenEntrada << '\n';
    ss << etiquetas[2] << nodo->prove.fechaIngreso << '\n';
    ss << etiquetas[3] << nodo->prove.nombreEmpresa << '\n';
    ss << etiquetas[4] << nodo->prove.contacto << '\n';
    ss << etiquetas[5] << nodo->prove.direccion << '\n';
    ss << etiquetas[6] << nodo->prove.telefono << '\n';
    ss << etiquetas[7] << nodo->prove.email << '\n';
    ss << etiquetas[8] << nodo->prove.tipoProducto << '\n';
    ss << etiquetas[9] << nodo->prove.tiempoEntrega << '\n';
    ss << etiquetas[10] << nodo->prove.totalGastado << '\n';
    ss << etiquetas[11] << nodo->prove.metodoPago << '\n';
    return ss.str();
}

void insertarNodoLista(NodoLista*& lista) {
    NodoLista* nuevo = new NodoLista();
    lista = nuevo;
    static int ordenC = 0;
    ++ordenC;

    nuevo->prove.idProveedor = generarID();
    nuevo->prove.ordenEntrada = ordenC;
    nuevo->prove.fechaIngreso = fechaActual();

    string orden = to_string(nuevo->prove.ordenEntrada);
    string id = to_string(nuevo->prove.idProveedor);

    RenderWindow window(VideoMode(900, 900), "FORMULARIO PROVEEDORES", Style::Close);
    vector<string> etiquetas = { "Empresa", "Contacto", "Direccion", "Telefono", "Email", "Tipo de\nproducto", "Tiempo de\nentrega", "Total\nGastado", "Metodo de\nPago" };
    vector<string> datosProducto = mostrarFormulario(window, etiquetas, orden, id);
    if (datosProducto.size() != etiquetas.size()) return;

    nuevo->prove.nombreEmpresa = datosProducto[0];
    nuevo->prove.contacto = datosProducto[1];
    nuevo->prove.direccion = datosProducto[2];
    nuevo->prove.telefono = datosProducto[3];
    nuevo->prove.email = datosProducto[4];
    nuevo->prove.tipoProducto = datosProducto[5];
    nuevo->prove.tiempoEntrega = datosProducto[6];
    nuevo->prove.totalGastado = datosProducto[7];
    nuevo->prove.metodoPago = datosProducto[8];
    nuevo->siguienteL = nullptr;

    // Inserción ordenada por ID
    if (primeroL == nullptr || nuevo->prove.idProveedor < primeroL->prove.idProveedor) {
        // Insertar al inicio
        nuevo->siguienteL = primeroL;
        primeroL = nuevo;
        if (ultimoL == nullptr) {
            ultimoL = nuevo;
        }
    }
    else {
        NodoLista* actual = primeroL;
        NodoLista* anterior = nullptr;

        while (actual != nullptr && actual->prove.idProveedor < nuevo->prove.idProveedor) {
            anterior = actual;
            actual = actual->siguienteL;
        }

        anterior->siguienteL = nuevo;
        nuevo->siguienteL = actual;

        if (nuevo->siguienteL == nullptr) {
            ultimoL = nuevo; // Si se insertó al final
        }
    }

    RenderWindow alertaWindow(VideoMode(500, 50), "Confirmación");
    alerta(alertaWindow, "NODO INSERTADO CORRECTAMENTE");
}

void desplegarLista(NodoLista*& lista, RenderWindow& ventana) {
    float x = 50;
    float y = 50;
    float ancho = 300;
    float alto = 400;

    if (lista != NULL) {

        NodoLista* actual = new NodoLista();
        actual = primeroL;

        while (actual != nullptr) {
            mostrarNodoLista(actual, ventana, x, y, ancho, alto);
            x += ancho + 10;
            actual = actual->siguienteL;
        }
    }
}

void vaciarLista(NodoLista*& lista)
{
    NodoLista* actual = new NodoLista();
    actual = primeroL;

    if (primeroL != NULL)
    {
        while (primeroL != NULL)
        {
            actual = primeroL;
            primeroL = primeroL->siguienteL;
            delete actual;
        }
        lista = NULL;

        RenderWindow ventanaAlerta(VideoMode(500, 50), "Confirmacion");
        alerta(ventanaAlerta, "LA LISTA A SIDO VACIADA");
        return;
    }
    else
    {
        RenderWindow ventanaAlerta(VideoMode(500, 50), "Alerta");
        alerta(ventanaAlerta, "LA LISTA ESTA VACIA");
        return;
    }

}

NodoLista* buscarNodoLista(NodoLista*& lista, const string& idStr) {
    int idBuscado;
    try {
        idBuscado = std::stoi(idStr);
    }
    catch (...) {
        RenderWindow alertaWindow(VideoMode(500, 50), "Error");
        alerta(alertaWindow, "ID inválido");
        return nullptr;
    }

    NodoLista* aux = primeroL;
    while (aux != nullptr) {
        if (aux->prove.idProveedor == idBuscado) {
            return aux;
        }
        aux = aux->siguienteL;
    }

    RenderWindow alertaWindow(VideoMode(500, 50), "Alerta");
    alerta(alertaWindow, "NODO NO ENCONTRADO");
    return nullptr;
}

void modificarNodoLista(NodoLista*& lista) {

    if (lista == nullptr) {
        RenderWindow alertaWin(VideoMode(500, 50), "Alerta");
        alerta(alertaWin, "LA LISTA ESTÁ VACÍA");
        return;
    }

    // Pedir ID
    RenderWindow window(VideoMode(500, 200), "Formulario ID");
    string idStr = formularioID(window);
    window.close();

    NodoLista* nodo = buscarNodoLista(lista, idStr);
    if (nodo == nullptr) return;

    // Mostrar nodo actual
    RenderWindow mostrarWin(VideoMode(400, 500), "Nodo encontrado");
    while (mostrarWin.isOpen()) {
        Event e;
        while (mostrarWin.pollEvent(e)) {
            if (e.type == Event::Closed)
                mostrarWin.close();
        }
        mostrarWin.clear(Color(10, 10, 30));
        mostrarNodoLista(nodo, mostrarWin, 50, 50, 300, 400);
        mostrarWin.display();
    }

    bool rep = true;
    int op = 0;
    const char* titulo = "OPCIONES DE MODIFICACION DEL NODO";
    const char* opciones[] = { "EMPRESA          ", "CONTACTO         ", "DIRECCION        ", "TELEFONO         ", "EMAIL            ","TIPO DE PRODUCTO ", "TIEMPO DE ENTREGA", "TOTAL GASTADO    ", "METODO DE PAGO   ", "SALIR            " };
    int no = 10;

    RenderWindow form(VideoMode(800, 600), "Modificar nodo");

    do
    {
        op = menu(titulo, opciones, no);
        switch (op) {

        case 1: {
            string nuevoNombre = formularioCampo(form, "Nuevo Nombre:");
            form.close();
            nodo->prove.nombreEmpresa = nuevoNombre;
            break;
        }
        case 2:
        {
            string nuevoContacto = formularioCampo(form, "Nuevo contacto:");
            form.close();
            nodo->prove.contacto = nuevoContacto;
            break;
        }
        case 3:
        {
            string nuevoDireccion = formularioCampo(form, "Nuevo direccion:");
            form.close();
            nodo->prove.direccion = nuevoDireccion;
            break;
        }
        case 4:
        {
            string nuevoTelefono = formularioCampo(form, "Nuevo telefono:");
            form.close();
            nodo->prove.telefono = nuevoTelefono;
            break;
        }
        case 5:
        {
            string nuevoEmail = formularioCampo(form, "Nuevo email:");
            form.close();
            nodo->prove.email = nuevoEmail;
            break;
        }
        case 6:
        {
            string nuevoProducto = formularioCampo(form, "Nuevo producto:");
            form.close();
            nodo->prove.tipoProducto = nuevoProducto;
            break;
        }
        case 7:
        {
            string nuevoTiempo = formularioCampo(form, "Nuevo tiempo:");
            form.close();
            nodo->prove.tiempoEntrega = nuevoTiempo;
            break;
        }
        case 8:
        {
            string nuevoTotal = formularioCampo(form, "Nuevo total gastado:");
            form.close();
            nodo->prove.totalGastado = nuevoTotal;
            break;
        }
        case 9:
        {
            string nuevoMetodo = formularioCampo(form, "Nuevo metodo de pago:");
            form.close();
            nodo->prove.metodoPago = nuevoMetodo;
            break;
        }
        case 10:
            rep = false;
            break;
        }

        RenderWindow confirm(VideoMode(500, 50), "Confirmación");
        alerta(confirm, "NODO MODIFICADO CORRECTAMENTE");
        break;

    } while (rep);

    return;

}

void eliminarNodoLista(NodoLista*& lista)
{
    if (lista == nullptr) {
        RenderWindow alertaWin(VideoMode(500, 50), "Alerta");
        alerta(alertaWin, "LA LISTA ESTÁ VACÍA");
        return;
    }

    // Pedir ID
    RenderWindow window(VideoMode(500, 200), "Formulario ID");
    string idStr = formularioID(window);
    window.close();

    int id;
    bool encontrado = false;
    try {
        id = stoi(idStr);
    }
    catch (...) {
        RenderWindow alertaWin(VideoMode(500, 50), "Error");
        alerta(alertaWin, "ID INVÁLIDO");
        return;
    }

    NodoLista* actual = new NodoLista();
    actual = primeroL;
    NodoLista* anterior = new NodoLista();
    anterior = NULL;

    while (actual != NULL && encontrado != true) {

        if (actual->prove.idProveedor == id) {

            // Mostrar nodo actual
            RenderWindow mostrarWin(VideoMode(400, 500), "Nodo encontrado");
            while (mostrarWin.isOpen()) {
                Event e;
                while (mostrarWin.pollEvent(e)) {
                    if (e.type == Event::Closed)
                        mostrarWin.close();
                }
                mostrarWin.clear(Color(10, 10, 30));
                mostrarNodoLista(actual, mostrarWin, 50, 50, 300, 400);
                mostrarWin.display();
            }

            if (actual == primeroL) {
                primeroL = primeroL->siguienteL;
            }
            else if (actual == ultimoL) {
                anterior->siguienteL = NULL;
                ultimoL = anterior;
            }
            else {
                anterior->siguienteL = actual->siguienteL;
            }

            delete actual;
            encontrado = true;
            RenderWindow confirmWin(VideoMode(500, 50), "Confirmación");
            alerta(confirmWin, "NODO ELIMINADO CORRECTAMENTE");
        }

        anterior = actual;
        actual = actual->siguienteL;
    }
}

void mostrarNodoListaDoble(NodoListaDoble*& nodo, RenderWindow& ventana, float x, float y, float ancho, float alto) {

    Font fuente;
    if (!fuente.loadFromFile("Orbitron.ttf")) {
        cerr << "No se pudo cargar la fuente.\n";
        return;
    }

    // Rectángulo
    RectangleShape rect(Vector2f(ancho, alto));
    rect.setFillColor(Color::Transparent);
    rect.setOutlineColor(Color(0, 255, 255));
    rect.setOutlineThickness(2);
    rect.setPosition(x, y);

    // Texto con datos del nodo actual
    Text texto(fichaListaDoble(nodo), fuente, 20);
    texto.setFillColor(Color(0, 255, 255));
    texto.setPosition(x + 10, y + 10);

    ventana.draw(rect);
    ventana.draw(texto);
}

string fichaListaDoble(NodoListaDoble* nodo) {
    vector<string> etiquetas = {
    "ID: ", "Ficha No: ", "Fecha: ",
    "Nombre: ", "Apellido: ", "Direccion: ",
    "Telefono: ", "Email: ", "Cargo: ",
    "Turno: ", "Salario: ", "Horas\nTrabajadas: "
    };
    if (nodo == nullptr) return "";

    ostringstream ss;
    ss << "Direccion de memoria: \n" << nodo << '\n';
    ss << etiquetas[0] << nodo->emplea.idEmpleado << '\n';
    ss << etiquetas[1] << nodo->emplea.ordenEntrada << '\n';
    ss << etiquetas[2] << nodo->emplea.fechaIngreso << '\n';
    ss << etiquetas[3] << nodo->emplea.nombre << '\n';
    ss << etiquetas[4] << nodo->emplea.apellido << '\n';
    ss << etiquetas[5] << nodo->emplea.direccion << '\n';
    ss << etiquetas[6] << nodo->emplea.telefono << '\n';
    ss << etiquetas[7] << nodo->emplea.email << '\n';
    ss << etiquetas[8] << nodo->emplea.cargo << '\n';
    ss << etiquetas[9] << nodo->emplea.turno << '\n';
    ss << etiquetas[10] << nodo->emplea.salario << '\n';
    ss << etiquetas[11] << nodo->emplea.horasTrabajadas << '\n';
    return ss.str();

}

void insertarNodoListaDoble(NodoListaDoble*& listaDoble) {
    NodoListaDoble* nuevo = new NodoListaDoble();

    static int ordenLD = 0;
    ++ordenLD;

    nuevo->emplea.idEmpleado = generarID();
    nuevo->emplea.ordenEntrada = ordenLD;
    nuevo->emplea.fechaIngreso = fechaActual();

    string orden = to_string(nuevo->emplea.ordenEntrada);
    string id = to_string(nuevo->emplea.idEmpleado);

    RenderWindow window(VideoMode(900, 900), "FORMULARIO EMPLEADOS", Style::Close);
    vector<string> etiquetas = { "Nombre", "Apellido", "Direccion", "Telefono", "Email", "Cargo","Turno", "Salario", "Horas\nTrabajadas" };
    vector<string> datosEmpleado = mostrarFormulario(window, etiquetas, orden, id);
    if (datosEmpleado.size() != etiquetas.size()) return;

    nuevo->emplea.nombre = datosEmpleado[0];
    nuevo->emplea.apellido = datosEmpleado[1];
    nuevo->emplea.direccion = datosEmpleado[2];
    nuevo->emplea.telefono = datosEmpleado[3];
    nuevo->emplea.email = datosEmpleado[4];
    nuevo->emplea.cargo = datosEmpleado[5];
    nuevo->emplea.turno = datosEmpleado[6];
    nuevo->emplea.salario = datosEmpleado[7];
    nuevo->emplea.horasTrabajadas = datosEmpleado[8];

    listaDoble = nuevo;
    // Inserción ordenada por ID
    if (primeroLD == nullptr) {
        // Primer nodo
        primeroLD = nuevo;
        ultimoLD = nuevo;
        nuevo->siguienteLD = nullptr;
        nuevo->atrasLD = nullptr;
    }
    else if (nuevo->emplea.idEmpleado < primeroLD->emplea.idEmpleado) {
        // Insertar al inicio
        nuevo->siguienteLD = primeroLD;
        nuevo->atrasLD = nullptr;
        primeroLD->atrasLD = nuevo;
        primeroLD = nuevo;
    }
    else {
        // Insertar en medio o al final
        NodoListaDoble* actual = primeroLD;
        while (actual->siguienteLD != nullptr && actual->siguienteLD->emplea.idEmpleado < nuevo->emplea.idEmpleado) {
            actual = actual->siguienteLD;
        }

        nuevo->siguienteLD = actual->siguienteLD;
        nuevo->atrasLD = actual;

        if (actual->siguienteLD != nullptr) {
            actual->siguienteLD->atrasLD = nuevo;
        }
        else {
            ultimoLD = nuevo; // Insertado al final
        }

        actual->siguienteLD = nuevo;
    }

    RenderWindow alertaWindow(VideoMode(500, 50), "Confirmación");
    alerta(alertaWindow, "NODO INSERTADO CORRECTAMENTE");
}

void desplegarListaDoblePU(NodoListaDoble*& listaDoble, RenderWindow& ventana) {
    float x = 50;
    float y = 50;
    float ancho = 300;
    float alto = 400;

    NodoListaDoble* actual = new NodoListaDoble();
    actual = primeroLD;

    if (primeroLD != NULL) {

        while (actual != nullptr) {
            mostrarNodoListaDoble(actual, ventana, x, y, ancho, alto);
            x += ancho + 10;
            actual = actual->siguienteLD;
        }
    }
}

void desplegarListaDobleUP(NodoListaDoble*& listaDoble, RenderWindow& ventana) {
    float x = 50;
    float y = 50;
    float ancho = 300;
    float alto = 400;

    NodoListaDoble* actual = new NodoListaDoble();
    actual = ultimoLD;

    if (primeroLD != NULL) {

        while (actual != NULL) {
            mostrarNodoListaDoble(actual, ventana, x, y, ancho, alto);
            x += ancho + 10;
            actual = actual->atrasLD;
        }
    }
}

void eliminarNodoListaDoble(NodoListaDoble*& listaDoble)
{

    if (listaDoble == nullptr) {
        RenderWindow alertaWin(VideoMode(500, 50), "Alerta");
        alerta(alertaWin, "LA LISTA ESTÁ VACÍA");
        return;
    }

    // Pedir ID
    RenderWindow window(VideoMode(500, 200), "Formulario ID");
    string idStr = formularioID(window);
    window.close();

    int id;
    bool encontrado = false;
    try {
        id = stoi(idStr);
    }
    catch (...) {
        RenderWindow alertaWin(VideoMode(500, 50), "Error");
        alerta(alertaWin, "ID INVÁLIDO");
        return;
    }

    NodoListaDoble* actual = new NodoListaDoble();
    actual = primeroLD;
    NodoListaDoble* anterior = new NodoListaDoble();
    anterior = NULL;

    while (actual != NULL&& encontrado != true) {

        if (actual->emplea.idEmpleado == id) {

            // Mostrar nodo actual
            encontrado = true;
            RenderWindow mostrarWin(VideoMode(400, 500), "Nodo encontrado");
            while (mostrarWin.isOpen()) {
                Event e;
                while (mostrarWin.pollEvent(e)) {
                    if (e.type == Event::Closed)
                        mostrarWin.close();
                }
                mostrarWin.clear(Color(10, 10, 30));
                mostrarNodoListaDoble(actual, mostrarWin, 50, 50, 300, 400);
                mostrarWin.display();
            }

            if (actual == primeroLD) {
                primeroLD = primeroLD->siguienteLD;
                primeroLD->atrasLD = NULL;
            }
            else if (actual == ultimoLD) {
                anterior->siguienteLD = NULL;
                ultimoLD = anterior;
            }
            else {
                anterior->siguienteLD = actual->siguienteLD;
                actual->siguienteLD->atrasLD = anterior;
            }

            delete actual;
            RenderWindow confirmWin(VideoMode(500, 50), "Confirmación");
            alerta(confirmWin, "NODO ELIMINADO CORRECTAMENTE");
        }

        anterior = actual;
        actual = actual->siguienteLD;
    }

}

void vaciarListaDoble(NodoListaDoble*& listaDoble)
{
    NodoListaDoble* actual = new NodoListaDoble();
    actual = primeroLD;

    if (primeroLD != NULL)
    {
        while (primeroLD != NULL)
        {
            actual = primeroLD;
            primeroLD = primeroLD->siguienteLD;
            delete actual;
        }
        listaDoble = NULL;

        RenderWindow ventanaAlerta(VideoMode(500, 50), "Confirmacion");
        alerta(ventanaAlerta, "LA LISTA A SIDO VACIADA");
        return;
    }
    else
    {
        RenderWindow ventanaAlerta(VideoMode(500, 50), "Alerta");
        alerta(ventanaAlerta, "LA LISTA ESTA VACIA");
        return;
    }

}

NodoListaDoble* buscarNodoListaDoble(NodoListaDoble* listaDoble, const string& idStr) {
    int idBuscado;
    try {
        idBuscado = stoi(idStr);
    }
    catch (const invalid_argument&) {
        RenderWindow alertaWindow(VideoMode(500, 50), "Error");
        alerta(alertaWindow, "ID no es un número válido");
        return nullptr;
    }
    catch (const out_of_range&) {
        RenderWindow alertaWindow(VideoMode(500, 50), "Error");
        alerta(alertaWindow, "ID fuera de rango");
        return nullptr;
    }

    NodoListaDoble* aux = primeroLD;
    while (aux != nullptr) {
        if (aux->emplea.idEmpleado == idBuscado) {
            return aux;
        }
        aux = aux->siguienteLD;
    }

    RenderWindow alertaWindow(VideoMode(500, 50), "Alerta");
    alerta(alertaWindow, "Nodo con ID no encontrado");
    return nullptr;
}

void modificarNodoListaDoble(NodoListaDoble*& listaDoble) {

    if (listaDoble == nullptr) {
        RenderWindow alertaWin(VideoMode(500, 50), "Alerta");
        alerta(alertaWin, "LA LISTA ESTÁ VACÍA");
        return;
    }

    // Pedir ID
    RenderWindow window(VideoMode(500, 200), "Formulario ID");
    string idStr = formularioID(window);
    window.close();

    NodoListaDoble* nodo = buscarNodoListaDoble(listaDoble, idStr);
    if (nodo == nullptr) return;

    // Mostrar nodo actual
    RenderWindow mostrarWin(VideoMode(400, 500), "Nodo encontrado");
    while (mostrarWin.isOpen()) {
        Event e;
        while (mostrarWin.pollEvent(e)) {
            if (e.type == Event::Closed)
                mostrarWin.close();
        }
        mostrarWin.clear(Color(10, 10, 30));
        mostrarNodoListaDoble(nodo, mostrarWin, 50, 50, 300, 400);
        mostrarWin.display();
    }

    bool rep = true;
    int op = 0;
    const char* titulo = "OPCIONES DE MODIFICACION DEL NODO";
    const char* opciones[] = { "NOMBRE          ", "APELLIDO        ", "DIRECCION       ", "TELEFONO        ", "EMAIL           ","CARGO           ", "TURNO           ", "SALARIO         ", "HORAS TRABAJADAS", "SALIR           " };
    int no = 10;

    RenderWindow form(VideoMode(800, 600), "Modificar nodo");

    do
    {
        op = menu(titulo, opciones, no);
        switch (op) {

        case 1: {
            string nuevoNombre = formularioCampo(form, "Nuevo Nombre:");
            form.close();
            nodo->emplea.nombre = nuevoNombre;
            break;
        }
        case 2:
        {
            string nuevoApellido = formularioCampo(form, "Nuevo apellido:");
            form.close();
            nodo->emplea.apellido = nuevoApellido;
            break;
        }
        case 3:
        {
            string nuevoDireccion = formularioCampo(form, "Nuevo direccion:");
            form.close();
            nodo->emplea.direccion = nuevoDireccion;
            break;
        }
        case 4:
        {
            string nuevoTelefono = formularioCampo(form, "Nuevo telefono:");
            form.close();
            nodo->emplea.telefono = nuevoTelefono;
            break;
        }
        case 5:
        {
            string nuevoEmail = formularioCampo(form, "Nuevo email:");
            form.close();
            nodo->emplea.email = nuevoEmail;
            break;
        }
        case 6:
        {
            string nuevoCargo = formularioCampo(form, "Nuevo cargo:");
            form.close();
            nodo->emplea.cargo = nuevoCargo;
            break;
        }
        case 7:
        {
            string nuevoTurno = formularioCampo(form, "Nuevo turno:");
            form.close();
            nodo->emplea.turno = nuevoTurno;
            break;
        }
        case 8:
        {
            string nuevoSalario = formularioCampo(form, "Nuevo salario:");
            form.close();
            nodo->emplea.salario = nuevoSalario;
            break;
        }
        case 9:
        {
            string nuevoHorasTrabajadas = formularioCampo(form, "Nuevo horas trabajadas:");
            form.close();
            nodo->emplea.horasTrabajadas = nuevoHorasTrabajadas;
            break;
        }
        case 10:
            rep = false;
            break;
        }

        RenderWindow confirm(VideoMode(500, 50), "Confirmación");
        alerta(confirm, "NODO MODIFICADO CORRECTAMENTE");
        break;

    } while (rep);

    return;

}

string fichaListaCircular(NodoCircular* nodo) {
    vector<string> etiquetas = {
    "ID: ", "Ficha No: ", "Fecha: ",
    "Turno: ", "Camas\nProducidas: ", "Camas\Defectuosas: ",
    "Horas\nTrabajadas: ", "Supervisor: ", "Observaciones: "
    };
    if (nodo == nullptr) return "";

    ostringstream ss;
    ss << "Direccion de memoria: \n" << nodo << '\n';
    ss << etiquetas[0] << nodo->report.idReporte << '\n';
    ss << etiquetas[1] << nodo->report.ordenFicha << '\n';
    ss << etiquetas[2] << nodo->report.fecha << '\n';
    ss << etiquetas[3] << nodo->report.turno << '\n';
    ss << etiquetas[4] << nodo->report.camasProducidas << '\n';
    ss << etiquetas[5] << nodo->report.camasDefectuosas << '\n';
    ss << etiquetas[6] << nodo->report.horasTrabajadas << '\n';
    ss << etiquetas[7] << nodo->report.supervisor << '\n';
    ss << etiquetas[8] << nodo->report.observaciones << '\n';
    return ss.str();
}

void insertarNodoListaCircular(NodoCircular*& listaCircular) {
    NodoCircular* nuevo = new NodoCircular();
    listaCircular = nuevo;
    static int ordenLC = 0;
    ++ordenLC;

    nuevo->report.idReporte = generarID();
    nuevo->report.ordenFicha = ordenLC;
    nuevo->report.fecha = fechaActual();

    string orden = to_string(nuevo->report.ordenFicha);
    string id = to_string(nuevo->report.idReporte);
    
    RenderWindow window(VideoMode(900, 900), "FORMULARIO REPORTES", Style::Close);
    vector<string> etiquetas = { "Turno", "Camas\nProducidas", "Camas\Defectuosas", "Horas\nTrabajadas", "Supervisor", "Observaciones" };
    vector<string> datosProducto = mostrarFormulario(window, etiquetas, orden, id);
    
    if (datosProducto.size() != etiquetas.size()) return;

    nuevo->report.turno = datosProducto[0];
    nuevo->report.camasProducidas = datosProducto[1];
    nuevo->report.camasDefectuosas = datosProducto[2];
    nuevo->report.horasTrabajadas = datosProducto[3];
    nuevo->report.supervisor = datosProducto[4];
    nuevo->report.observaciones = datosProducto[5];

    if (primeroLC == NULL) {
        // Primer nodo
        primeroLC = nuevo;
        nuevo->siguienteLC = nuevo;
        ultimoLC = nuevo;
    }
    else if (nuevo->report.idReporte < primeroLC->report.idReporte) {
        // Insertar antes del primero
        nuevo->siguienteLC = primeroLC;
        ultimoLC->siguienteLC = nuevo;
        primeroLC = nuevo;
    }
    else {
        // Buscar posición correcta
        NodoCircular* actual = primeroLC;
        while (actual->siguienteLC != primeroLC && actual->siguienteLC->report.idReporte < nuevo->report.idReporte) {
            actual = actual->siguienteLC;
        }

        nuevo->siguienteLC = actual->siguienteLC;
        actual->siguienteLC = nuevo;

        // Actualizar último si se inserta al final
        if (actual == ultimoLC) {
            ultimoLC = nuevo;
        }
    }

    RenderWindow alertaWindow(VideoMode(500, 50), "Confirmación");
    alerta(alertaWindow, "NODO INSERTADO CORRECTAMENTE");

}

void desplegarListaCircular(NodoCircular*& listaCircular, RenderWindow& ventana) {
    if (!primeroL) return;

    // Contar nodos
    int num = 0;
    NodoCircular* temp = primeroLC;
    do {
        num++;
        temp = temp->siguienteLC;
    } while (temp != primeroLC);

    // Calcular posiciones circulares
    float radio = 300;
    Vector2f centro(450, 450);  // Centro de la ventana
    vector<Vector2f> posiciones;

    for (int i = 0; i < num; ++i) {
        float angulo = 2 * 3.1416 * i / num;
        float x = centro.x + radio * cos(angulo);
        float y = centro.y + radio * sin(angulo);
        posiciones.push_back(Vector2f(x, y));
    }

    // Dibujar nodos y líneas
    NodoCircular* actual = primeroLC;
    for (int i = 0; i < num; ++i) {
        // Línea al siguiente nodo
        Vector2f inicio = posiciones[i];
        Vector2f fin = posiciones[(i + 1) % num];
        Vertex linea[] = {
            Vertex(Vector2f(inicio.x, inicio.y), Color::White),
            Vertex(Vector2f(fin.x, fin.y), Color::White)
        };
        ventana.draw(linea, 2, Lines);

        // Dibujar nodo
        mostrarNodoListaCircular(actual, ventana, posiciones[i].x, posiciones[i].y, 150, 80);

        actual = actual->siguienteLC;
    }
}

void eliminarNodoListaCircular(NodoCircular*& listaCircular) {

}

void vaciarListaCircular(NodoCircular*& listaCircular) {

}

NodoCircular* buscarNodoListaCircular(NodoCircular* listaCircular, const string& idStr) {
    return nullptr;
}

void modificarNodoListaCircular(NodoCircular*& listaCircular) {

}

void mostrarNodoListaCircular(NodoCircular*& nodo, RenderWindow& ventana, float x, float y, float ancho, float alto) {
    Font fuente;
    if (!fuente.loadFromFile("Orbitron.ttf")) {
        cerr << "No se pudo cargar la fuente.\n";
        return;
    }

    // Centro el rectángulo en (x, y)
    RectangleShape rect(Vector2f(ancho, alto));
    rect.setFillColor(Color::Transparent);
    rect.setOutlineColor(Color(0, 255, 255));
    rect.setOutlineThickness(2);
    rect.setPosition(x - ancho / 2, y - alto / 2);

    // Texto con datos del nodo actual
    Text texto(fichaListaCircular(nodo), fuente, 14); // ajusta el tamaño si es mucho texto
    texto.setFillColor(Color(0, 255, 255));
    texto.setPosition(x - ancho / 2 + 10, y - alto / 2 + 10);

    ventana.draw(rect);
    ventana.draw(texto);
}










int main() {

    //pantallaBienvenida();
    menuPrincipal();

    return 0;
}
