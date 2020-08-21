#ifndef LIGHT_H_
#define LIGHT_H_

#include "material.h"
#include "vector3.h"

namespace Tracer{
    class Light{
        public:
        Light(Vector3 pos) :
        position(pos),
        specular(.5),
        diffuse(.5),
        intensity(1),
        color(Color_UINT8(255, 255, 255))
         {}
        Light(Vector3 pos, Color_UINT8 c) :
        position(pos),
        specular(.5),
        diffuse(.5),
        intensity(1),
        color(c)
         {}
        Light(Vector3 pos, float i) :
        position(pos),
        specular(.5),
        diffuse(.5),
        intensity(i),
        color(Color_UINT8(255, 255, 255))
         {}
        Light(Vector3 pos, float spec, float diff, float i) :
        position(pos),
        specular(spec),
        diffuse(diff),
        intensity(i),
        color(Color_UINT8(255, 255, 255))
         {}
        Vector3 get_direction(const Vector3& point) const;
        Vector3 get_reflection(const Vector3& point, const Vector3& normal) const;
        inline Vector3 get_position() const {return position;}
        inline float get_specular() const {return specular * intensity;}
        inline float get_diffuse() const {return diffuse * intensity;}
        inline Color_UINT8 get_color() const {return color;}
        inline Color_F get_color_f() const {return Color_F(color);}
        private:
        Vector3 position;
        float specular;
        float diffuse;
        float intensity;
        Color_UINT8 color;
    };
}
#endif