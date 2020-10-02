#pragma once
    //Wrapper for calloc
    #define ALLOC(number_of_elements, obj_type) (obj_type *) calloc(number_of_elements, sizeof(obj_type))
    