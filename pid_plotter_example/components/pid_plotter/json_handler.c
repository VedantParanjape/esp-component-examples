#include "json_handler.h"

/**
 * @brief Converts PID data to a json string
 * 
 * @param current current value
 * @param error error value, deviation of current from setpoint
 * @param P Value of Proportional Gain (P)
 * @param I Value of Integral Gain (I)
 * @param D Value of Derivative Gain (D)
 * @return char* - Json string of the data sent through parameters.
 **/
char *create_pid_data_to_json(float current, float error, float P, float I, float D)
{
    cJSON *data = cJSON_CreateObject();
    char* json_string = NULL;

    cJSON_AddNumberToObject(data, "current", current);
    cJSON_AddNumberToObject(data, "error", error);
    cJSON_AddNumberToObject(data, "P", P);
    cJSON_AddNumberToObject(data, "I", I);
    cJSON_AddNumberToObject(data, "D", D);

    json_string = cJSON_Print(data);
    cJSON_Delete(data);

    return json_string;
}

/**
 * @brief Reads PID constant data from a json formatted string
 * 
 * @param data: Pointer to char array containging the json formatted string
 * @return struct pid_const - Returns a array of PID constants, extracted from the json string
 **/
struct pid_const read_pid_data_from_json(const char* data)
{
    struct pid_const data_extracted;
    const cJSON *data_json = cJSON_Parse(data);

    data_extracted.kp = cJSON_GetObjectItemCaseSensitive(data_json, "Kp")->valuedouble;
    data_extracted.ki = cJSON_GetObjectItemCaseSensitive(data_json, "Ki")->valuedouble;
    data_extracted.kd = cJSON_GetObjectItemCaseSensitive(data_json, "Kd")->valuedouble;
    data_extracted.setpoint = cJSON_GetObjectItemCaseSensitive(data_json, "SetPoint")->valuedouble;

    cJSON_Delete(data_json);
    return data_extracted;
}
