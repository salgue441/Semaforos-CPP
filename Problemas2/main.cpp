#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <random>

#define THREADS 8
#define NUM_VEHICLES 8
#define MAX_VEHICLES 3

sem_t space_available;
pthread_mutex_t mutex;
pthread_cond_t change_direction;

std::string direction = "NORTH";

std::random_device rd;                         // Seed generator
std::mt19937 gen(rd());                        // Initialize generator
std::uniform_int_distribution<int> dist(1, 2); // Generate random integers between 1 and 2 (inclusive)

typedef struct
{
  std::string direction;
  std::string directionString;
  int id;

} Vehicle;

void arriveBridge(Vehicle vehicle)
{
  std::cout
      << "[ARRIVE] Vehicle " << vehicle.id << " is waiting to cross the bridge from " << vehicle.directionString << " ..." << std::endl;
}

void crossBridge(Vehicle vehicle)
{
  pthread_mutex_lock(&mutex);
  sem_wait(&space_available);

  int value;
  sem_getvalue(&space_available, &value);

  std::cout
      << "[CROSS] Vehicle " << vehicle.id << " is crossing the bridge from " << vehicle.directionString << std::endl;

  std::cout << "[STATUS] Vehicles crossing the bridge: " << MAX_VEHICLES - value << std::endl;
  pthread_mutex_unlock(&mutex);

  sleep(2);
}

void exitBridge(Vehicle vehicle)
{
  pthread_mutex_lock(&mutex);

  sem_post(&space_available);

  int value;
  sem_getvalue(&space_available, &value);

  std::cout << "[EXIT] Vehicle " << vehicle.id << " exited the bridge from " << vehicle.directionString << std::endl;
  std::cout << "[STATUS] Vehicles crossing the bridge: " << MAX_VEHICLES - value << std::endl;

  if (value == 3)
  {
    direction = "";
    std::cout << "\n----------------- BRIDGE IS EMPTY. ANYONE CAN CROSS -----------------\n\n";
    pthread_cond_broadcast(&change_direction);
  }

  pthread_mutex_unlock(&mutex);
}

void *vehicle(void *param)
{
  Vehicle *vehicle = (Vehicle *)param;

  arriveBridge(*vehicle);

  pthread_mutex_lock(&mutex);
  if (direction != vehicle->direction || direction == "")
  {
    pthread_cond_wait(&change_direction, &mutex);
    direction = vehicle->direction;
    std::cout << "\n----------------- CHANGED DIRECTION: " << direction << " -----------------\n\n";
  }
  pthread_mutex_unlock(&mutex);

  crossBridge(*vehicle);

  exitBridge(*vehicle);

  pthread_exit(0);
}

int main()
{
  sem_init(&space_available, 0, MAX_VEHICLES);
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&change_direction, NULL);

  pthread_t tids[NUM_VEHICLES];
  Vehicle vehicles[NUM_VEHICLES];

  std::cout << "\n----------------- DIRECTION: " << direction << " -----------------\n\n";

  for (int i = 0; i < NUM_VEHICLES; i++)
  {
    vehicles[i].direction = dist(gen) == 1 ? "NORTH" : "SOUTH";
    vehicles[i].id = i;
    vehicles[i].directionString = vehicles[i].direction == "NORTH" ? "North to South" : "South to North";

    pthread_create(&tids[i], NULL, vehicle, &vehicles[i]);

    sleep(1);
  }

  for (int i = 0; i < NUM_VEHICLES; i++)
  {
    pthread_join(tids[i], NULL);
  }

  sem_destroy(&space_available);

  return 0;
}