#include <iostream>      // Incluye la biblioteca estándar para entrada y salida
#include <cstdlib>       // Incluye funciones como malloc y free
using namespace std;     // Para evitar escribir std:: en cada instrucción

// Enum para representar los colores de los nodos
enum Color { ROJO, NEGRO };

// Definición de la estructura de un nodo del árbol
struct Nodo {
    int valor;             // Valor del nodo
    Color color;           // Color del nodo (ROJO o NEGRO)
    Nodo *izq, *der;       // Punteros a hijo izquierdo y derecho
    Nodo *padre;           // Puntero al nodo padre
};

// Función para crear un nuevo nodo con el valor dado
Nodo* crearNodo(int valor) {
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo)); // Reserva memoria para el nodo
    nodo->valor = valor;                      // Asigna el valor
    nodo->color = ROJO;                       // Por defecto, el nodo es rojo
    nodo->izq = nodo->der = nodo->padre = nullptr; // Inicializa punteros a null
    return nodo;                              // Retorna el nuevo nodo
}

// Rotación a la izquierda alrededor del nodo x
void rotarIzquierda(Nodo*& raiz, Nodo* x) {
    Nodo* y = x->der;               // y es el hijo derecho de x
    x->der = y->izq;                // El hijo izquierdo de y pasa a ser hijo derecho de x
    if (y->izq) y->izq->padre = x;  // Actualiza el padre del hijo izquierdo de y
    y->padre = x->padre;            // y adopta el padre de x
    if (!x->padre) raiz = y;        // Si x era la raíz, y se convierte en la nueva raíz
    else if (x == x->padre->izq) x->padre->izq = y; // Actualiza el hijo izquierdo del padre
    else x->padre->der = y;         // O el hijo derecho, si corresponde
    y->izq = x;                     // x pasa a ser hijo izquierdo de y
    x->padre = y;                   // y es el nuevo padre de x
}

// Rotación a la derecha alrededor del nodo y
void rotarDerecha(Nodo*& raiz, Nodo* y) {
    Nodo* x = y->izq;               // x es el hijo izquierdo de y
    y->izq = x->der;                // El hijo derecho de x pasa a ser hijo izquierdo de y
    if (x->der) x->der->padre = y;  // Actualiza el padre del hijo derecho de x
    x->padre = y->padre;            // x adopta el padre de y
    if (!y->padre) raiz = x;        // Si y era la raíz, x se convierte en la nueva raíz
    else if (y == y->padre->izq) y->padre->izq = x; // Actualiza el hijo izquierdo del padre
    else y->padre->der = x;         // O el hijo derecho, si corresponde
    x->der = y;                     // y pasa a ser hijo derecho de x
    y->padre = x;                   // x es el nuevo padre de y
}

// Función para restaurar las propiedades del árbol Rojo-Negro después de insertar
void repararInsercion(Nodo*& raiz, Nodo* z) {
    while (z->padre && z->padre->color == ROJO) {  // Mientras el padre de z sea rojo
        Nodo* abuelo = z->padre->padre;           // Obtenemos el abuelo de z
        if (z->padre == abuelo->izq) {            // Si el padre es hijo izquierdo del abuelo
            Nodo* tio = abuelo->der;              // El tío es el hijo derecho del abuelo
            if (tio && tio->color == ROJO) {      // Caso 1: el tío también es rojo
                z->padre->color = NEGRO;          // Recolorea al padre
                tio->color = NEGRO;               // Recolorea al tío
                abuelo->color = ROJO;             // Recolorea al abuelo
                z = abuelo;                       // Repetimos con el abuelo
            } else {
                if (z == z->padre->der) {         // Caso 2: z es hijo derecho
                    z = z->padre;                
                    rotarIzquierda(raiz, z);     // Rotamos a la izquierda
                }
                // Caso 3: z es hijo izquierdo
                z->padre->color = NEGRO;          // Recolorea al padre
                abuelo->color = ROJO;             // Recolorea al abuelo
                rotarDerecha(raiz, abuelo);       // Rotamos a la derecha
            }
        } else {                                   // Simétrico al caso anterior
            Nodo* tio = abuelo->izq;
            if (tio && tio->color == ROJO) {
                z->padre->color = NEGRO;
                tio->color = NEGRO;
                abuelo->color = ROJO;
                z = abuelo;
            } else {
                if (z == z->padre->izq) {
                    z = z->padre;
                    rotarDerecha(raiz, z);
                }
                z->padre->color = NEGRO;
                abuelo->color = ROJO;
                rotarIzquierda(raiz, abuelo);
            }
        }
    }
    raiz->color = NEGRO;  // La raíz siempre debe ser negra
}

// Función para insertar un valor en el árbol Rojo-Negro
void insertar(Nodo*& raiz, int valor) {
    Nodo* z = crearNodo(valor);  // Crea el nuevo nodo
    Nodo* y = nullptr;
    Nodo* x = raiz;

    // Busca la posición adecuada en el árbol
    while (x) {
        y = x;
        if (valor < x->valor) x = x->izq;
        else x = x->der;
    }

    z->padre = y;               // Asigna el padre del nuevo nodo
    if (!y) raiz = z;           // Si el árbol estaba vacío, z es la nueva raíz
    else if (valor < y->valor) y->izq = z; // Se conecta como hijo izquierdo
    else y->der = z;                       // O como hijo derecho

    repararInsercion(raiz, z); // Repara las propiedades del árbol Rojo-Negro
}

// Busca un nodo con un valor específico
Nodo* buscar(Nodo* raiz, int valor) {
    if (!raiz || raiz->valor == valor) return raiz;      // Caso base
    if (valor < raiz->valor) return buscar(raiz->izq, valor); // Recurre a la izquierda
    return buscar(raiz->der, valor);                          // O a la derecha
}

// Devuelve el nodo con el valor mínimo desde el nodo dado
Nodo* minimo(Nodo* nodo) {
    while (nodo->izq) nodo = nodo->izq; // Se mueve al hijo izquierdo hasta el final
    return nodo;
}

// Reemplaza un nodo por otro en el árbol
void reemplazar(Nodo*& raiz, Nodo* u, Nodo* v) {
    if (!u->padre) raiz = v;                  // Si u es la raíz
    else if (u == u->padre->izq) u->padre->izq = v; // Si u es hijo izquierdo
    else u->padre->der = v;                  // Si u es hijo derecho
    if (v) v->padre = u->padre;              // Actualiza el padre de v
}

// Elimina un nodo con un valor específico
void eliminar(Nodo*& raiz, int valor) {
    Nodo* z = buscar(raiz, valor);           // Busca el nodo a eliminar
    if (!z) {
        cout << "No se encontr\xF3 el valor.\n";
        return;
    }

    Nodo* y = z;
    Nodo* x;
    Color colorOriginal = y->color;

    if (!z->izq) {
        x = z->der;
        reemplazar(raiz, z, z->der);
    } else if (!z->der) {
        x = z->izq;
        reemplazar(raiz, z, z->izq);
    } else {
        y = minimo(z->der);
        colorOriginal = y->color;
        x = y->der;
        if (y->padre == z) {
            if (x) x->padre = y;
        } else {
            reemplazar(raiz, y, y->der);
            y->der = z->der;
            if (y->der) y->der->padre = y;
        }
        reemplazar(raiz, z, y);
        y->izq = z->izq;
        y->izq->padre = y;
        y->color = z->color;
    }

    free(z); // Libera la memoria del nodo eliminado
    cout << "Valor eliminado.\n";

    // Nota: no reparamos el árbol tras eliminación (simplificado)
}

// Recorre el árbol en inorden (izquierda, nodo, derecha)
void inorden(Nodo* raiz) {
    if (!raiz) return;
    inorden(raiz->izq);
    cout << raiz->valor << (raiz->color == ROJO ? " (R) " : " (N) ") << "  ";
    inorden(raiz->der);
}

// Libera toda la memoria del árbol
void liberar(Nodo* raiz) {
    if (!raiz) return;
    liberar(raiz->izq);
    liberar(raiz->der);
    free(raiz);
}

// Función principal del programa
int main() {
    Nodo* raiz = nullptr; // Árbol inicialmente vacío
    int opcion, numero;

    do {
        cout << " MENE:"<<endl;
        cout << "1. Insertar numero\n";
        cout << "2. Eliminar numero\n";
        cout << "3. Imprimir arbol (inorden)\n";
        cout << "4. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "numero a insertar: ";
                cin >> numero;
                insertar(raiz, numero);
                break;
            case 2:
                cout << "numero a eliminar: ";
                cin >> numero;
                eliminar(raiz, numero);
                break;
            case 3:
                cout << "\arbol inorden (valor y color):\n";
                inorden(raiz);
                cout << "\n";
                break;
            case 4:
                liberar(raiz);
                cout << "Memoria liberada. Saliendo...\n";
                break;
            default:
                cout << "opcion invalida";
        }
    } while (opcion != 4);

    return 0;
}
