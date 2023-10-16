#pragma once


#include <stdarg.h>
#include <string.h>
#include <stdlib.h>


// JSON-data format specifiers
#define JSON_DATA_INT       "%d"
#define JSON_DATA_FLOATING  "%lf"
#define JSON_DATA_STR       "%s"
#define JSON_DATA_BOOL      "%b"
#define JSON_DATA_NULL      "%n"
#define JSON_DATA_ARRAY     "%a"
#define JSON_DATA_OBJECT    "%o"
#define JSON_DATA_IGNORE    "%i"
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
#define JSON_MAX_DEPTH      32
#define JSON_MAX_DATA_COUNT 32
#define JSON_MAX_LEN        1024
#define JSON_MAX_ARR_LEN    32


// JSON-data types
typedef enum jtype_t {
  JTYPE_INT,
  JTYPE_FLOATING,
  JTYPE_STR,
  JTYPE_BOOL,
  JTYPE_NULL,
  JTYPE_ARRAY,
  JTYPE_OBJECT,
  JTYPE_IGNORE
} jtype_t;

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
};


// JSON-Parser functions
struct JsonData *parse_json_str(const char *jsonStr);
struct JsonData *fetch_json_data(struct JsonParser *parser);
struct JsonData *fetch_res(struct JsonData *data, const char *key);
char *fetch_str(const char *data, const char *key);
char **fetch_arr(const char *data, const char *key);
int fetch_int(const char *data, const char *key);
double fetch_floating(const char *data, const char *key);
int fetch_bool(const char *data, const char *key);
char *remove_isws(const char *str);
