#include "queue.h"

/**
 * Initializes a given queue.
 * @param queue given queue
 */
void initialize_queue(struct queue* queue)
{
  mutex_init(&queue->mutex);
  queue->size  = 0;
  queue->front = 0;
  queue->rear  = 0;
}

/**
 * Adds a given character into a given queue.
 * @param queue given queue
 * @param character given character
 * @return 1 if the character is added to the queue. 0 if the queue is full.
 */
int enqueue_character(struct queue* queue, const unsigned char character)
{
  int success = 0;
  mutex_lock(&queue->mutex);
  if (queue->size < QUEUE_MAX_SIZE)
  {
    if (queue->size != 0)
    {
      queue->rear++;
      if (queue->rear >= QUEUE_MAX_SIZE)
      {
        queue->rear = 0;
      }
    }
    else
    {
      queue->rear = 0;
      queue->front = 0;
    }
    queue->size++;
        
    queue->data[queue->rear] = character;
    success = 1;
  }
  mutex_unlock(&queue->mutex);
  return success;
}

/**
 * Gets a character from a fiven queue.
 * @param queue given queue
 * @param character a character
 * @return 1 if a character is fetched from the queue. 0 if the queue is empy.
 */
int dequeue_character(struct queue* queue, unsigned char* character)
{
  int success = 0;
  mutex_lock(&queue->mutex);
  if (queue->size > 0)
  {
    *character = queue->data[queue->front];
    queue->front++;
    queue->size--;
    if (queue->front >= QUEUE_MAX_SIZE)
    {
      queue->front = 0;
    }
    success = 1;
  }
  mutex_unlock(&queue->mutex);
  return success;
}

/**
 * Adds a given string to a given queue.
 * @param queue given queue
 * @param string given string
 * @return The amount of characters successfully added to the queue.
 */
int enqueue_string(struct queue* queue, const unsigned char* string, int stringSize)
{
  int n = 0;
  while (n < stringSize && enqueue_character(queue, string[n]))
  {
    n++;
  }
  return n;
}

/**
 * Gets the number of characters that can be added to a given queue.
 * @return number of characters.
 */
int get_queue_room(struct queue* queue)
{
  int capacity = 0;
  mutex_lock(&queue->mutex);
  capacity = QUEUE_MAX_SIZE - queue->size;
  mutex_unlock(&queue->mutex);
  return capacity;
}

/**
 * Gets the number of characters contained in a given queue.
 * @return number of characters.
 */
int get_queue_size(struct queue* queue)
{
  return queue->size;
}
