#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <stdio.h>
#include <cassert>
#include <string>
#include "color.h"

namespace Tracer {
struct Material {
    Material() :
        color(Color_UINT8(0,0,0)),
        specular_reflection(.2),
        diffuse_reflection(.7),
        ambient_reflection(.1),
        shininess(3)
           {
           }

 
  Material(Color_UINT8 c) :
        color(c),
        specular_reflection(.4),
        diffuse_reflection(.5),
        ambient_reflection(.1),
        shininess(100)
           {
           }

  Material(Color_UINT8 c, std::uint8_t spec, float diff,
           float amb, float shine)
           :
           color(c),
           specular_reflection(spec),
           diffuse_reflection(diff),
           ambient_reflection(amb),
           shininess(shine)
           {
               assert(specular_reflection <= 1 && specular_reflection >= 0);
               assert(diffuse_reflection <= 1 && diffuse_reflection >= 0);
               assert(ambient_reflection <= 1 && ambient_reflection >= 0);
               assert(specular_reflection + diffuse_reflection + ambient_reflection == 1);
               assert(shininess <= 1 && shininess >= 0);
           }
inline Color_F get_color_f() const {return Color_F(color);}
  Color_UINT8 color;
  float specular_reflection;
  float diffuse_reflection;
  float ambient_reflection;
  float shininess;
};
}  // namespace Tracer

#endif