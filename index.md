## Instituto Tecnológico de Costa Rica
## Área de Ingeniería en Computadores
## Algoritmos y Estructuras de Datos II
## Primer Semestre 2015
## Proyecto 1 - VS Code Memory Manager
### Estudiantes:
### Simón Fallas Villalobos (2019324313)
### David Quesada Calderón (2016246935)

[Repositorio de GitHub](https://github.com/SimonFV/VScode-memory-manager/edit/master/index.md)
 / 
[Administración del proyecto en Jira](https://simonfv.atlassian.net/jira/software/projects/VMM/boards/2)


## Descripción del Proyecto

El software desarrollado consiste en una extensión para Visual Studio Code que permite a los usuarios administrar la memoria dinámica de forma automática utilizando una clase especial de puntero. La biblioteca incluye un garbage collector que se ejecuta cada cierto tiempo en busca de punteros inutilizados y los elimina de forma automática, de esta forma se evitan los memory leaks.


## Diagrama de Clases
![VS-mem-manager](https://user-images.githubusercontent.com/47420204/84465123-78e7fb00-ac33-11ea-8fbd-92b4327ca3c2.png)

## Algoritmos y estructuras de datos utilizados
### Singleton
Singleton es un patrón de diseño utilizado para asegurar la instanciación de un único objeto de una clase específica. Se utilizó en este proyecto para implementar el garbage collector, ya que solo se desea un único objeto de esta clase ejecutándose en el programa.
La implementación en el código es la siguiente:

```cpp
class g_collector{
private:
    static g_collector *gc_instance;
    g_collector(){}
    ~g_collector(){}
public:
    static g_collector *getInstance();
    g_collector(g_collector &other) = delete;
    void operator=(const g_collector &) = delete;
    ...
};
g_collector *g_collector::gc_instance = nullptr;`

...

g_collector *g_collector::getInstance(){
    if(gc_instance == nullptr){
        gc_instance = new g_collector();
    }
    return gc_instance;
}

```
Si se desea utilizar alguna función del garbage collector, para añadir algún puntero por ejemplo, se llama de la siguiente forma:
```cpp
g_collector::getInstance()->add_ptr(ID, bucket);
```
### Shared pointers
Para implementar la administración automática de punteros se aplicó el concepto de shared pointers, un tipo smart pointer. Los smart pointers son una clase de puntero que se eliminan automáticamente cuando el programa sale del scope donde se encuentran. Su funcionamiento consiste en guardar el verdadero puntero dentro de un objeto, y eliminar el puntero cuando se llame el destructor de dicho objeto, como se muestra a continuación:
```cpp
template <typename T>
class VSPtr{
private:
    T* ptr;
public:
    // Constructor
    VSPtr(T *p = NULL){
        ptr = p;
    }
    // Destructor 
    ~VSPtr(){
        delete(ptr)
    }
```
Para poder realizar operaciones con estos punteros se deben sobreescribir los operadores, por ejemplo:
```cpp
    T& operator *(){
        return *ptr;
    }

    T* operator ->(){
        return ptr;
    }
```
Ahora bien, los shared pointers son una clase de smart pointers que permmiten que varios smart pointers apunten a un mismo puntero, llevando un conteo de cuantos lo están haciendo a la vez. Para llevar este conteo se utiliza una clase adicional de que sirva de contador, y cuando este llegue a 0 el puntero se elimina. El código anterior luciría entonces similar al siguiente:
```cpp
template <typename T>
class VSPtr{
private:
    T* ptr;
    counter* count;
public:
    // Constructor
    VSPtr(T *p = NULL){
        ptr = p;
        count = new counter();
        count->plus(1);
    }
    // Copy constructor
    VSPtr(const VSPtr<T>& vsptr){
        ptr = vsptr.ptr; 
        count = vsptr.count; 
        count->plus(1); 
    }
    // Destructor 
    ~VSPtr(){
        count->plus(-1);
    }
```
Se agrega un constructor adicional para manejar el copiado de un puntero a otro cuando se construye. Se observa también como el contador aumenta cuando se construye o se copia un puntero y como decrece cuando se elimina. Cuando un contador esté en 0, el garbage collector elimina su respectivo puntero.
