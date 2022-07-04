LDD Lab Exam Questions

1. Kernel Synchronization Mechanisms for Multiple devices.
a) Write a character driver for Multiple devices and create 2 device numbers.Use
semaphore to protect the Critical section (write activity) and Use wait-queues to
avoid consecutive write operations.
b) Maintain a Kernel buffer of 50 bytes to Read and Write data.
c) Put write function to sleep using wait-queues after successful write operation
before releasing semaphore.
d) Wake-up sleep(wait-queues) operation only in Read function.
e) Write 2 separate programs for Read and Write for each device.
2. LED Operation Using GPIOs and Kernel Timers.
a) Write a character driver using ioctl functionality, kernel timer.
b) Use GPIO_23 to interface led on raspberry pi and blink the led periodically
using kernel timer.
c) Use ioctl functionality to change the periodicity of led blinking
