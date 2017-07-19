#ifndef LIBOSRM_GLOBALS_H_
#define LIBOSRM_GLOBALS_H_

#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"
#include "rice/Enum.hpp"
#include "rice/Struct.hpp"

using namespace Rice;

static Module rb_mLibOSRM = define_module("LibOSRM");

#define ATTR_ACCESSOR_DECL(klass, variable) \
    .define_method(#variable, &klass##_##variable##_get) \
    .define_method(#variable "=", &klass##_##variable##_set)

#endif
