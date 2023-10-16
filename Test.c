#include "include/Parser.h"

#include <stdio.h>
#include <string.h>


int
main(void)
{
  const char *json_str = "{Person: {Name: \"John\", Age: 30, Married: true, Children: [\"Ann\", \"Billy\"]}, Double: 3.14}";

  printf("Name: %s\n", fetch_str(json_str, "Person.Name"));
  printf("Age: %d\n", fetch_int(json_str, "Person.Age"));
  printf("Married: %d\n", fetch_bool(json_str, "Person.Married"));
  char **children = fetch_arr(json_str, "Person.Children");
  printf("Children: %s, %s\n", children[0], children[1]);
  printf("Floating: %lf\n", fetch_floating(json_str, "Double"));

  return 0;
}
