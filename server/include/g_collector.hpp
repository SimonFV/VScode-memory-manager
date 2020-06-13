#ifndef G_COLLECT
#define G_COLLECT

/**
 * Garbage collector class.
 * Singleton class in charge of saving the information of the pointers and
 * deleting them when its counters drop to 0.
 * It runs on a separated thread and executes itself every second.
 */
class g_collector{
private:
    static g_collector *gc_instance; /* Unique instance of the garbage collector */
    g_collector(){}
    ~g_collector(){}

public:
    /**
     * Method to access the unique instance of the garbage collector.
     * 
     * @return Instance of the garbage collector.
     */
    static g_collector *getInstance();

    /**
     * Constructor that prevents copies of the garbage collector.
     */
    g_collector(g_collector &other) = delete;

    /**
     * Method tha prevents reassignments of the garbage collector.
     */
    void operator=(const g_collector &) = delete; 

public:
    /**
     * Generates a unique id for the VSPtrs.
     * 
     * @return int ID.
     */
    int generate_id();

    /**
     * Iterates the HashMap looking for trash pointers to delete them.
     * 
     */
    void run_inspection();

    /**
     * Adds the information of a pointer in the HashMap.
     * 
     * @param id ID of the VSPtr.
     * @param b Pointer to the Bucket object holding the pointer's info.
     */
    void add_ptr(int id, Bucket* b);

    /**
     * Creates a JSON file with the ID, type, value, address and number of references
     * of each pointer.
     */
    void generate_data();

};

g_collector *g_collector::gc_instance = nullptr;

#endif