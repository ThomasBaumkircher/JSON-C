#include "Composer.h"
#include "Parser.h"


char *
compose_json_str(struct JsonData *data)
{
  char *jsonStr = (char *) malloc(sizeof(char) * JSON_MAX_LEN);
  char *currChar = jsonStr;

  int isArr = (strcmp(data->parent->value, "JSON_ARRAY") == 0);
  if (isArr) {
      currChar += sprintf(currChar, "[");
  } else {
      currChar += sprintf(currChar, "{");
  }

  while (data != NULL) {
    if (data->child != NULL) {
      if (strlen(data->key) == 0) {
        currChar += sprintf(currChar, "%s", compose_json_str(data->child));
      }
      else {
        currChar += sprintf(currChar, "%s:%s", data->key, compose_json_str(data->child));
      }
    }
    else {
      if (strlen(data->key) == 0) {
        currChar += sprintf(currChar, "%s", data->value);
      }
      else {
        currChar += sprintf(currChar, "%s:%s", data->key, data->value);
      }
    }

    if (data->next != NULL) {
      currChar += sprintf(currChar, ",");
    }

    data = data->next;
  }

  if (isArr) {
      currChar += sprintf(currChar, "]");
  } else {
      currChar += sprintf(currChar, "}");
  }

  return jsonStr;
}
