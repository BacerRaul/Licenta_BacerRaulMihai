#define NUM_SENSORS 5
#define NUM_SAMPLES 16
#define NUM_DECIMALS 4



const uint8_t sensorPins[NUM_SENSORS] = {A0, A1, A2, A3, A4};
const uint16_t sensorMin[NUM_SENSORS] = {200,160,120,130,125};
const uint16_t sensorMax[NUM_SENSORS] = {250,270,245,245,250};



float calculateAverageSensorValue(const uint8_t index)
{
    uint8_t i;
    float sum = 0.0f;
    float averageValue;

    for (i = 0; i < NUM_SAMPLES; i++)
    {
        sum = sum + analogRead(sensorPins[index]);
    }

    averageValue = sum / NUM_SAMPLES;

    return averageValue;
}



float normalizeAverageSensorValue(const uint8_t index, float averageValue)
{
    float normalizedValue;

    if (averageValue < sensorMin[index])
        averageValue = sensorMin[index];

    if (averageValue > sensorMax[index])
        averageValue = sensorMax[index];

    normalizedValue = (averageValue - sensorMin[index]) / (sensorMax[index] - sensorMin[index]);

    return normalizedValue;
}



void setup()
{
    Serial.begin(115200);
}



void loop()
{
    uint8_t index;

    for (index = 0; index < NUM_SENSORS; index++)
    {
        float averageValue;
        float normalizedValue;

        averageValue = calculateAverageSensorValue(index);
        normalizedValue = normalizeAverageSensorValue(index, averageValue);

        Serial.print(normalizedValue, NUM_DECIMALS);

        if (index != NUM_SENSORS - 1)
        {
            Serial.print(" ");
        }
    }

    Serial.print("\n");
    
    delay(20);
}