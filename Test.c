#include "include/Parser.h"

#include <stdio.h>


struct Person {
  char *name;
  int age;
  bool married;
  char **children;
};


int
main(void)
{
  const char *json_str = "{Person: {Name: \"John\", Age: 30, Married: true, Children: [{\"name\":\"Ann\"}, {\"name\":\"Billy\"}]}}";

  (void) printf("Name: %s\n", fetch_str(json_str, "Person.Name"));

  (void) printf("Age: %d\n", fetch_int(json_str, "Person.Age"));

  (void) printf("Married: %d\n", fetch_bool(json_str, "Person.Married"));

  char **children = (char **) fetch_arr(json_str, "Person.Children");
  (void) printf("Children: %s, %s\n", children[0], children[1]);

  (void) printf("Person_obj: %s\n", fetch_obj(json_str, "Person"));

  return 0;
}
