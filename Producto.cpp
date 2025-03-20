#include <iostream>

using namespace std;

struct Nodo {
    int id;
    char nombre[30];
    Nodo *sig;
};

Nodo *cab, *aux, *aux2;

 //Esta es la funcion para poder resegistrar los datos de los prucctos
 
void registrar() {
    aux = (struct Nodo *) malloc (sizeof(Nodo));
    cout << "Ingrese ID del producto: ";
    cin >> aux->id;
    cout << "Ingrese nombre del producto: ";
    cin >> ws; 
    cin.getline(aux->nombre, 30);
    aux->sig = NULL;
    
    if (!cab) {
        cab = aux;
    } else {
        aux2 = cab;
        while (aux2->sig)
            aux2 = aux2->sig;
        aux2->sig = aux;
    }
    cout << "Producto registrado con exito"<<endl;
}
 //Esta funcion es para mostrar por pantalla
 
void mostrar() {
    aux = cab;
    if (!aux) {
        cout << "No hay productos registrados"<<endl;
        return;
    }
    while (aux) {
        cout << "ID: " << aux->id << "  Nombre: " << aux->nombre << endl;
        aux = aux->sig;
    }
}
 // Esta funcion es para buscar los nodos por ID
 
Nodo* buscar(int id) {
    aux = cab;
    while (aux) {
        if (aux->id == id)
            return aux;
        aux = aux->sig;
    }
    return NULL;
}
 // Esta funcion es para eliminar los nodos (los productos) por ID
 
void eliminar(int id) {
     Nodo *aux = cab, *prev = NULL; 
    while (aux && aux->id != id) {
        prev = aux;
        aux = aux->sig;
    }
    if (!aux) {
        cout << "Producto no encontrado. ";
        return;
    }
    if (!prev) {
        cab = aux->sig;
    } else {
        prev->sig = aux->sig;
    }
    free(aux); // se usa para liberar memoria 
    cout << "Producto eliminado con exito :)\n";
}

 // Esta funcion es para ver los  Productos que  hay reistrados
 
int contar() {
    int contador = 0;
    aux = cab;
    while (aux) {
        contador++;
        aux = aux->sig;
    }
    return contador;
}
 // Esta funcion es para modificar los productos
 
void modificar(int id) {
    aux = buscar(id);
    if (aux) {
        cout << "Ingrese nuevo nombre: ";
        cin >> ws;
        cin.getline(aux->nombre, 30);
        cout << "Producto modificado con exito! \n";
    } else {
        cout << "Producto no encontrado.\n";
    }
}
 //Esta funcon libera la memoria
 
void liberarMemoria() {
    aux;
    while (cab) {
        aux = cab;
        cab = cab->sig;
        free(aux);
    }
}

int main() {
    int opcion, id;
    do {
        cout << "\nMenu: "<<endl;
        cout << "1. Agregar producto"<<endl;
        cout << "2. Mostrar productos"<<endl;
        cout << "3. Buscar producto"<<endl;
        cout << "4. Eliminar producto"<<endl;
        cout << "5. Contar productos"<<endl;
        cout << "6. Modificar producto"<<endl;
        cout << "7. Salir"<<endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                registrar();
                break;
            case 2:
                mostrar();
                break;
            case 3:
                cout << "Ingrese ID del producto a buscar: ";
                cin >> id;
                if (Nodo *L = buscar(id)) {
                    cout << "Producto encontrado - ID: " << L->id << " - Nombre: " << L->nombre << endl;
                } else {
                    cout << "Producto no encontrado."<<endl;
                }
                break;
            case 4:
                cout << "Ingrese ID del producto a eliminar: ";
                cin >> id;
                eliminar(id);
                break;
            case 5:
                cout << "Total de productos registrados: " << contar() << endl;
                break;
            case 6:
                cout << "Ingrese ID del producto a modificar: ";
                cin >> id;
                modificar(id);
                break;
            case 7:
                liberarMemoria();
                cout << "Memoria liberada."<<endl;
                cout<<"Saliendo..."<<endl;
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo."<<endl;
        }
    } while (opcion != 7);
    
    return 0;
}