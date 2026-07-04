#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>





// Configureaza comunicatia prin monitor serial
#define SERIAL_PORT "/dev/ttyUSB0"

static int serialMonitor = -1;

int initializeSerialMonitor(void);
void closeSerialMonitor(void);





// Configureaza comunicatia cu PCA9685
#define I2C_DEVICE "/dev/i2c-1"

static int pca9685 = -1;

#define PCA9685_ADDRESS    0x40
#define PCA9685_MODE1      0x00
#define PCA9685_MODE2      0x01
#define PCA9685_PRESCALE   0xFE
#define PCA9685_LED0_ON_L  0x06

int initializePCA9685(void);
void closePCA9685(void);
int writeRegisterPCA9685(uint8_t reg, uint8_t value);





// Senzori
#define NUM_SENSORS 5

#define THRESHOLD 0.03f

float sensorPrevious[NUM_SENSORS];
float sensorValues[NUM_SENSORS];

int readSensorValues(void);
void writeSensorPrevious(void);
void printSensorValues(void);





// Servomotoare
#define NUM_SERVOS 5

const uint16_t servoMin[NUM_SERVOS] = {280,155,90,90,90};

const uint16_t servoMax[NUM_SERVOS] = {500,500,500,500,500};

int setServoPWM(uint8_t channel, uint16_t onTime, uint16_t offTime);
uint16_t calculateServoPulse(uint8_t channel, float normalizedValue);
int resetServos(void);





// Generale
void closePeripherals(void);





// Functii pentru comunicatia prin monitor serial cu Arduino
int initializeSerialMonitor(void)
{
    if (serialMonitor >= 0)
    {
        return 1;
    }

    struct termios settings;

    serialMonitor = open(SERIAL_PORT, O_RDWR | O_NOCTTY);

    if (serialMonitor < 0)
    {
        return 0;
    }

    if (tcgetattr(serialMonitor, &settings) != 0)
    {
        closeSerialMonitor();
        return 0;
    }

    cfsetispeed(&settings, B115200);
    cfsetospeed(&settings, B115200);

    settings.c_cflag |= (CLOCAL | CREAD);
    settings.c_cflag &= ~PARENB;
    settings.c_cflag &= ~CSTOPB;
    settings.c_cflag &= ~CSIZE;
    settings.c_cflag |= CS8;

    settings.c_lflag = 0;
    settings.c_iflag = 0;
    settings.c_oflag = 0;

    settings.c_cc[VMIN] = 1;
    settings.c_cc[VTIME] = 0;

    if (tcsetattr(serialMonitor, TCSANOW, &settings) != 0)
    {
        closeSerialMonitor();
        return 0;
    }

    tcflush(serialMonitor, TCIFLUSH);

    return 1;
}

void closeSerialMonitor(void)
{
    if (serialMonitor >= 0)
    {
        close(serialMonitor);
        serialMonitor = -1;
    }
}





// Functii pentru comunicatia prin I2C cu PCA9685
int initializePCA9685(void)
{
    if (pca9685 >= 0)
    {
        return 1;
    }

    pca9685 = open(I2C_DEVICE, O_RDWR);

    if (pca9685 < 0)
    {
        return 0;
    }

    if (ioctl(pca9685, I2C_SLAVE, PCA9685_ADDRESS) < 0)
    {
        closePCA9685();
        return 0;
    }

    if (!writeRegisterPCA9685(PCA9685_MODE1, 0x10))
    {
        closePCA9685();
        return 0;
    }

    usleep(5000);

    if (!writeRegisterPCA9685(PCA9685_PRESCALE, 121))
    {
        closePCA9685();
        return 0;
    }

    if (!writeRegisterPCA9685(PCA9685_MODE1, 0xA1))
    {
        closePCA9685();
        return 0;
    }

    if (!writeRegisterPCA9685(PCA9685_MODE2, 0x04))
    {
        closePCA9685();
        return 0;
    }

    usleep(5000);

    return 1;
}

void closePCA9685(void)
{
    if (pca9685 >= 0)
    {
        close(pca9685);
        pca9685 = -1;
    }
}

int writeRegisterPCA9685(uint8_t reg, uint8_t value)
{
    if (pca9685 < 0)
    {
        return 0;
    }

    uint8_t buffer[2];

    buffer[0] = reg;
    buffer[1] = value;

    if (write(pca9685, buffer, 2) != 2)
    {
        return 0;
    }

    return 1;
}





// Functii pentru senzori
int readSensorValues(void)
{
    if (serialMonitor < 0)
    {
        return 0;
    }

    char line[64];
    uint8_t index = 0;
    char character;

    while (index < sizeof(line) - 1)
    {
        if (read(serialMonitor, &character, 1) != 1)
        {
            return 0;
        }

        if (character == '\n')
        {
            break;
        }

        line[index++] = character;
    }

    line[index] = '\0';

    if (sscanf(line,
               "%f %f %f %f %f",
               &sensorValues[0],
               &sensorValues[1],
               &sensorValues[2],
               &sensorValues[3],
               &sensorValues[4]) != NUM_SENSORS)
    {
        return 0;
    }

    return 1;
}

void writeSensorPrevious(void)
{
    uint8_t channel;

    for (channel = 0; channel < NUM_SENSORS; channel++)
    {
        sensorPrevious[channel] = sensorValues[channel];
    }
}

void printSensorValues(void)
{
    uint8_t channel;

    for (channel = 0; channel < NUM_SENSORS; channel++)
    {
        printf("%.4f", sensorValues[channel]);

        if (channel != NUM_SENSORS - 1)
        {
            printf(" ");
        }
    }

    printf("\n");
}





// Functii pentru servomotoare
int setServoPWM(uint8_t channel, uint16_t onTime, uint16_t offTime)
{
    if (channel >= NUM_SERVOS)
    {
        return 0;
    }

    if (pca9685 < 0)
    {
        return 0;
    }

    uint8_t reg = PCA9685_LED0_ON_L + (4 * channel);

    uint8_t buffer[5];

    buffer[0] = reg;
    buffer[1] = onTime & 0xFF;
    buffer[2] = onTime >> 8;
    buffer[3] = offTime & 0xFF;
    buffer[4] = offTime >> 8;

    if (write(pca9685, buffer, 5) != 5)
    {
        return 0;
    }

    return 1;
}

uint16_t calculateServoPulse(uint8_t channel, float normalizedValue)
{
    if (channel >= NUM_SERVOS)
    {
        return 0;
    }

    uint16_t pulse;

    if (normalizedValue < 0.0f)
    {
        normalizedValue = 0.0f;
    }

    if (normalizedValue > 1.0f)
    {
        normalizedValue = 1.0f;
    }

    pulse = (uint16_t) (servoMin[channel] + normalizedValue * (servoMax[channel] - servoMin[channel]));

    return pulse;
}

int resetServos(void)
{
    uint8_t channel;

    for (channel = 0; channel < NUM_SERVOS; channel++)
    {
        if (!setServoPWM(channel, 0, servoMax[channel]))
        {
            return 0;
        }
    }

    return 1;
}





// Functii generale

void closePeripherals(void)
{
    closeSerialMonitor();
    closePCA9685();
}

int main(void)
{
    if (!initializeSerialMonitor())
    {
        printf("Failed to initialize serial monitor.\n");
        closePeripherals();
        return 1;
    }

    if (!initializePCA9685())
    {
        printf("Failed to initialize PCA9685.\n");
        closePeripherals();
        return 1;
    }

    uint8_t channel;
    uint16_t pulse;
    
    if (!resetServos())
    {
        printf("Failed to reset servos.\n");
        closePeripherals();
        return 1;
    }

    if (!readSensorValues())
    {
        printf("Failed to read initial sensor values.\n");
        closePeripherals();
        return 1;
    }

    writeSensorPrevious();

    while (1)
    {
        if (!readSensorValues())
        {
            printf("Failed to read sensor values.\n");
            continue;
        }

        printSensorValues();

        for (channel = 0; channel < NUM_SERVOS; channel++)
        {
            if (fabs(sensorValues[channel] - sensorPrevious[channel]) > THRESHOLD)
            {
                pulse = calculateServoPulse(channel, sensorValues[channel]);

                if (!setServoPWM(channel, 0, pulse))
                {
                    printf("Failed to move servo %d.\n", channel);
                    break;
                }
            }
        }

        writeSensorPrevious();

        usleep(10000);
    }

    closePeripherals();

    return 0;
}