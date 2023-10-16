#include "../include/Parser.h"


struct JsonData *
parse_json_str(const char *jsonStr)
{
  struct JsonParser parse;
  parse.jsonStr = (char *) malloc(sizeof(char) * JSON_MAX_LEN);
  strcpy(parse.jsonStr, remove_isws(jsonStr));
  parse.currChar = jsonStr[0];
  parse.depth = 0;
  parse.dataCount = 0;
  parse.currBuf = NULL;
  parse.currStruct = JSTRUCT_NONE;

  return fetch_json_data(&parse);
}


struct JsonData *
fetch_json_data(struct JsonParser *parser)
{
  struct JsonData *currData = (struct JsonData *) malloc(sizeof(struct JsonData) * 1);
  currData->next = NULL;
  currData->child = NULL;
  struct JsonData *dataHead = currData;

  currData->key = (char *) malloc(sizeof(char) * JSON_MAX_STR_LEN);
  currData->value = (char *) malloc(sizeof(char) * JSON_MAX_STR_LEN);

  parser->currBuf = currData->key;


  char *c = &(parser->currChar);
  for (int count = 0; count < JSON_MAX_LEN; count++) {
    parser->currChar = *(parser->jsonStr);
    parser->jsonStr++;

    if (*c == '\0') {
      break;
    }


    else if (*c == JSON_OBJECT_START) {
      jstruct_t currStruct = parser->currStruct;
      parser->currStruct = JSTRUCT_OBJECT;

      currData->value = (char *) malloc(sizeof(char) * JSON_MAX_STR_LEN);
      strcpy(currData->value, "JSON_OBJECT");

      struct JsonData *childResult = fetch_json_data(parser);
      currData->child = childResult;
      parser->currStruct = currStruct;
    }

    else if (*c == JSON_ARRAY_START) {
      jstruct_t currStruct = parser->currStruct;
      parser->currStruct = JSTRUCT_ARRAY;

      currData->value = (char *) malloc(sizeof(char) * JSON_MAX_STR_LEN);
      strcpy(currData->value, "JSON_ARRAY");

      struct JsonData *childResult = fetch_json_data(parser);
      currData->child = childResult;
      parser->currStruct = currStruct;
    }


    else if (*c == JSON_OBJECT_END || *c == JSON_ARRAY_END) {
      break;
    }


    else if (*c == JSON_DATA_DELIMITER) {
      struct JsonData *newData = (struct JsonData *) malloc(sizeof(struct JsonData) * 1);
      currData->next = newData;
      currData = newData;
      currData->next = NULL;

      currData->key = (char *) malloc(sizeof(char) * JSON_MAX_STR_LEN);
      currData->value = (char *) malloc(sizeof(char) * JSON_MAX_STR_LEN);

      parser->currBuf = currData->key;
    }

    else if (*c == JSON_KEY_VALUE_DELIMITER) {
      parser->currBuf = currData->value;
    }


    else {
      *parser->currBuf = parser->currChar;
      parser->currBuf++;
    }
  }


  return dataHead;
}


struct JsonData *
fetch_res(struct JsonData *data, const char *key)
{
  if (data == NULL) {
    return NULL;
  }

  struct JsonData *currData = data->child;

  char *keyCopy = (char *) malloc(sizeof(char) * JSON_MAX_STR_LEN);
  strcpy(keyCopy, key);
  char *currKey = strtok(keyCopy, JSON_DEPTH_DELIMITER);

  while (currData != NULL) {
    if ((int) strcmp(currData->key, currKey) == 0) {
      if (currData->child != NULL && strtok(NULL, JSON_DEPTH_DELIMITER) != NULL) {
        return fetch_res(currData, key + strlen(currKey) + 1);
      }
      return currData;
    }
    currData = currData->next;
  }

  return NULL;
}


char *
fetch_str(const char *data, const char *key)
{
  struct JsonData *currData = fetch_res(parse_json_str(data), key);
  if (currData == NULL) {
    return "JSON_KEY_NOT_FOUND";
  }

  return currData->value;
}


char **
fetch_arr(const char *data, const char *key)
{
  struct JsonData *currData = fetch_res(parse_json_str(data), key)->child;

  if (currData == NULL) {
    return NULL;
  }

  char **arr = (char **) malloc(sizeof(char *) * JSON_MAX_ARR_LEN);
  int count = 0;

  while (currData != NULL) {
    arr[count] = currData->key;
    count++;
    currData = currData->next;
  }

  return arr;
}


int
fetch_int(const char *data, const char *key)
{
  struct JsonData *currData = fetch_res(parse_json_str(data), key);
  if (currData == NULL) {
    return -1;
  }

  return atoi(currData->value);
}


double
fetch_floating(const char *data, const char *key)
{
  struct JsonData *currData = fetch_res(parse_json_str(data), key);
  if (currData == NULL) {
    return -1;
  }

  return atof(currData->value);
}


int
fetch_bool(const char *data, const char *key)
{
  struct JsonData *currData = fetch_res(parse_json_str(data), key);
  if (currData == NULL) {
    return -1;
  }

  if ((int) strcmp(currData->value, "true") == 0) {
    return 1;
  }

  return 0;
}


char *
remove_isws(const char *str)
{
  char *newStr = (char *) malloc(sizeof(char) * JSON_MAX_STR_LEN);
  char *currChar = newStr;

  for (int count = 0; count < JSON_MAX_STR_LEN; count++) {
    if (*str == '\0') {
      break;
    }

    if (*str != ' ' && *str != '\n' && *str != '\t') {
      *currChar = *str;
      currChar++;
    }

    str++;
  }

  return newStr;
}
