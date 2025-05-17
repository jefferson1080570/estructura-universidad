#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Nodo {
    string nombre;
    int anio;
    string genero;
    float recaudacion;
    Nodo* izquierda;
    Nodo* derecha;

    Nodo(string n, int a, string g, float r)
        : nombre(n), anio(a), genero(g), recaudacion(r), izquierda(nullptr), derecha(nullptr) {}
};

Nodo* insertar(Nodo* raiz, string nombre, int anio, string genero, float recaudacion) {
    if (raiz == nullptr)
        return new Nodo(nombre, anio, genero, recaudacion);

    if (anio <= raiz->anio)
        raiz->izquierda = insertar(raiz->izquierda, nombre, anio, genero, recaudacion);
    else
        raiz->derecha = insertar(raiz->derecha, nombre, anio, genero, recaudacion);

    return raiz;
}

void inorden(Nodo* raiz) {
    if (raiz != nullptr) {
        inorden(raiz->izquierda);
        cout << raiz->nombre << " (" << raiz->anio << ") - " << raiz->genero << " - $" << raiz->recaudacion << "M\n";
        inorden(raiz->derecha);
    }
}

Nodo* encontrarMinimo(Nodo* nodo) {
    while (nodo && nodo->izquierda != nullptr)
        nodo = nodo->izquierda;
    return nodo;
}

Nodo* eliminarPorNombre(Nodo* raiz, string nombre) {
    if (raiz == nullptr)
        return nullptr;

    if (raiz->nombre == nombre) {
        // Caso 1: sin hijos
        if (raiz->izquierda == nullptr && raiz->derecha == nullptr) {
            delete raiz;
            return nullptr;
        }
        // Caso 2: un solo hijo
        if (raiz->izquierda == nullptr) {
            Nodo* temp = raiz->derecha;
            delete raiz;
            return temp;
        }
        if (raiz->derecha == nullptr) {
            Nodo* temp = raiz->izquierda;
            delete raiz;
            return temp;
        }
        // Caso 3: dos hijos
        Nodo* sucesor = encontrarMinimo(raiz->derecha);
        raiz->nombre = sucesor->nombre;
        raiz->anio = sucesor->anio;
        raiz->genero = sucesor->genero;
        raiz->recaudacion = sucesor->recaudacion;
        raiz->derecha = eliminarPorNombre(raiz->derecha, sucesor->nombre);
    } else {
        // Buscar recursivamente en ambos subárboles
        raiz->izquierda = eliminarPorNombre(raiz->izquierda, nombre);
        raiz->derecha = eliminarPorNombre(raiz->derecha, nombre);
    }

    return raiz;
}

int main() {
    Nodo* raiz = nullptr;
    int opcion;
    string nombre, genero;
    int anio;
    float recaudacion;

    do {
        cout << "\n--- MENÚ ---\n";
        cout << "1. Agregar película\n";
        cout << "2. Mostrar recorrido Inorden\n";
        cout << "3. Eliminar película por nombre\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                cout << "Nombre: ";
                getline(cin, nombre);
                cout << "Año: ";
                cin >> anio;
                cin.ignore();
                cout << "Género: ";
                getline(cin, genero);
                cout << "Recaudación (millones): ";
                cin >> recaudacion;
                raiz = insertar(raiz, nombre, anio, genero, recaudacion);
                break;

            case 2:
                cout << "\nRecorrido Inorden:\n";
                inorden(raiz);
                break;

            case 3:
                cout << "Nombre de la película a eliminar: ";
                getline(cin, nombre);
                raiz = eliminarPorNombre(raiz, nombre);
                cout << "Película eliminada (si existía).\n";
                break;
        }

    } while (opcion != 0);

    return 0;
}