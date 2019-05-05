#include <json/json.h>
#include <stdio.h>
 
void json_parse(json_object * jobj) {
    enum json_type type;
    json_object_object_foreach(jobj, key, val) {
    type = json_object_get_type(val);
    
            printf("type: json_type_string, ");
            printf("value: %s\n", json_object_get_string(val));
          break;
    }
}

int main() {
    char * string = "{ \"site\" : \" coding\", \"purpose\" : \" tips\", \"platform\" : \"temp\" }";
    printf ("JSON string: %s\n", string);
    json_object * jobj = json_tokener_parse(string);
    json_parse(jobj);
    return 0;
}