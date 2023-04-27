/**
 * @file pizza.cpp
 * @author Carlos Salguero
 * @author Sergio Garnica
 * @brief Implementation of the pizza class
 * @version 0.1
 * @date 2023-04-24
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "pizza.h"
/**
 * @file pizza.cpp
 * @author Carlos Salguero
 * @author Sergio Garnica
 * @brief Implementation of the pizza class
 * @version 0.1
 * @date 2023-04-24
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <chrono>

#define THREADS 8
#define NUM_STUDENTS 7
#define S 8 // pizza slices

/**
 * Mutexes
 * Used for critical sections in code
 * CS1: Grabbing pizza
 * CS2: Ordering pizza
 * pizza_mutex: It is locked for allowing only one student to grab a slice or for allowing the pizzeria to cook a pizza before students trying to grab a slice
 * order_mutex: It is locked for allowing only one student to order a pizza
 */
pthread_mutex_t pizza_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t order_mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * Condition variables
 * Used for signaling threads
 * pizza_order: used for ordering pizza. It is signaled when there are no more pizza slices
 * pizza_delivery: used for delivering pizza. It is signaled when the pizza is ready
 */
pthread_cond_t pizza_order = PTHREAD_COND_INITIALIZER;
pthread_cond_t pizza_delivery = PTHREAD_COND_INITIALIZER;

// Global variables
int pizza_slices = S;
bool pizza_ordered = false; // bool value used to indicate if a pizza has been ordered

/**
 * @brief Student thread
 * Students will try to grab a slice of pizza, and study.
 * If there are no more pizza slices, they will order a pizza and go to sleep until the pizza is ready
 * @param param student id
 * @return void*
 */
void *student(void *param)
{
  int id = *((int *)param);

  while (true)
  {
    pthread_mutex_lock(&pizza_mutex); // Lock pizza mutex for critical section. Only one student can grab a slice

    // If there are no more pizza slices, order a pizza if it has not been ordered yet
    while (pizza_slices == 0 && !pizza_ordered)
    {
      pthread_mutex_lock(&order_mutex); // Lock order mutex for critical section. Only one student can order a pizza

      pizza_ordered = true; // Pizza has been ordered
      std::cout << "No more pizza slices :(" << std::endl;
      sleep(1);
      std::cout << "Student " << id << " ordered a pizza" << std::endl;
      sleep(1);
      pthread_cond_signal(&pizza_order);                // Signal pizzeria that a pizza has been ordered. The pizzeria will receive the signal and cook a pizza
      pthread_cond_wait(&pizza_delivery, &pizza_mutex); // Wait for pizza delivery and unlock pizza mutex
      std::cout << "Student " << id << " received the pizza" << std::endl;
      sleep(1);

      pthread_mutex_unlock(&order_mutex); // Unlock order mutex after pizza is delivered and allow other students to order a pizza
    }

    if (!pizza_ordered) // If a pizza has not been ordered, grab a slice
    {
      pizza_slices--; // Grab a slice
      std::cout << "Student " << id << " took a slice. Slices left: " << pizza_slices << std::endl;
      sleep(1);
    }

    pthread_mutex_unlock(&pizza_mutex); // Unlock pizza mutex after grabbing a slice and allow other students to grab a slice

    sleep(2);
  }

  pthread_exit(NULL);
}

/**
 * @brief Pizzeria thread
 * The pizzeria will cook a pizza when there are no more pizza slices
 * @param param
 * @return void*
 */
void *pizzeria(void *param)
{

  while (true)
  {
    pthread_mutex_lock(&pizza_mutex); // Lock pizza mutex for critical section so the pizzeria can cook a pizza and no student can try to grab a slice

    while (pizza_slices > 0) // If there are pizza slices, wait for a pizza to be ordered
    {
      pthread_cond_wait(&pizza_order, &pizza_mutex); // Wait for a pizza to be ordered and unlock pizza mutex for allowing students to grab a slice
    }

    while (pizza_ordered) // If a pizza has been ordered, cook a pizza
    {
      std::cout << "--- All Night Long Pizzeria ---" << std::endl;
      sleep(1);
      std::cout << "Cooking pizza ..." << std::endl;
      sleep(1);
      pizza_slices = S; // Pizza is ready
      std::cout << "¡Pizza delivered!" << std::endl;
      sleep(1);
      pthread_cond_broadcast(&pizza_delivery); // Signal students that the pizza is ready. All students will receive the signal and try to grab a slice
      pizza_ordered = false;                   // Pizza has been delivered
      pthread_mutex_unlock(&pizza_mutex);      // Unlock pizza mutex after delivering the pizza and allow students to grab a slice
    }
    sleep(2);
  }

  pthread_exit(NULL);
}

// main function
int main(int argc, char *argv[])
{

  pthread_t pizzeria_thread;                // pizzeria thread
  pthread_t students_threads[NUM_STUDENTS]; // students threads
  int id_students[NUM_STUDENTS];

  for (int i = 0; i < NUM_STUDENTS; i++)
  {
    id_students[i] = i + 1;                                                       // Asign student id
    pthread_create(&students_threads[i], NULL, student, (void *)&id_students[i]); // Create student thread (thread, NULL, task, id)
  }
  pthread_create(&pizzeria_thread, NULL, pizzeria, NULL); // Create pizzeria thread (thread, NULL, task, NULL)

  for (int i = 0; i < NUM_STUDENTS; i++) // Join students threads
  {
    pthread_join(students_threads[i], NULL);
  }

  pthread_join(pizzeria_thread, NULL); // Join pizzeria thread

  return 0;
}