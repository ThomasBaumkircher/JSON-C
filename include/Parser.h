#pragma once


#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#include "Composer.h"


// JSON-data structure specifiers
#define JSON_ARRAY_START          '['
#define JSON_ARRAY_END            ']'
#define JSON_OBJECT_START         '{'
#define JSON_ARRAY_ELEM_KEY       "JSON_ARRAY_ELEMENT"
#define JSON_OBJECT_END           '}'
#define JSON_DATA_DELIMITER       ','
#define JSON_KEY_VALUE_DELIMITER  ':'
#define JSON_DEPTH_DELIMITER      "."

// Parser specific limits
#define JSON_MAX_STR_LEN    256
#define JSON_MAX_LEN        1024
#define JSON_MAX_ARR_LEN    32


// JSON-data structure types
typedef enum jstruct_t {
  JSTRUCT_ARRAY,
  JSTRUCT_OBJECT,
  JSTRUCT_NONE
} jstruct_t;


// JSON-Parser struct
struct JsonParser {
  char *jsonStr;

  int depth;
  int dataCount;

  char currChar;

  char *currBuf;
  jstruct_t currStruct;
};

// JSON-data structure
struct JsonData {
  char *key;
  char *value;

  struct JsonData *next;
  struct JsonData *child;
  struct JsonData *parent;
};


// JSON-Parser functions
struct JsonData *parse_json_str(const char *jsonStr);
struct JsonData *fetch_json_data(struct JsonParser *parser);
struct JsonData *fetch_res(struct JsonData *data, const char *key);
char *fetch_str(const char *data, const char *key);
void **fetch_arr(const char *data, const char *key);
char *fetch_obj(const char *data, const char *key);
int fetch_int(const char *data, const char *key);
double fetch_floating(const char *data, const char *key);
bool fetch_bool(const char *data, const char *key);
void *fetch_struct(const char *data, const char **keys);
char *remove_isws(const char *str);
